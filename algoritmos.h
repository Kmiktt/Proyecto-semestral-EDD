#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafos.h"
#include <vector>
#include <string>

using namespace std;


// Estructura para almacenar el ranking de nodos según una métrica.
struct NodoRanking {
    int id;
    string nombre;
    double valor;
};


// Métricas que actúan por nodos.

/**
 * Centralidad de Grado (Degree Centrality)
 * Retorna un vector con la centralidad de grado normalizada para cada nodo.
 */
vector<double> calcDegreeCentrality(const Grafo& g);

/**
 * Centralidad de Intermediación (Betweenness Centrality)
 * Retorna un vector con la centralidad de intermediación normalizada para cada nodo.
 */
vector<double> calcBetweennessCentrality(const Grafo& g);

/**
 * Centralidad de Cercanía (Closeness Centrality)
 * Retorna un vector con la centralidad de cercanía normalizada para cada nodo.
 * Este valor indica qué tan cerca está un nodo de todos los demás nodos en el grafo.
 *  */
vector<double> calcClosenessCentrality(const Grafo& g);

/**
 * @brief PageRank
 *
 * Calcula la importancia de los nodos mediante recorridos aleatorios iterativos 
 * utilizando el método de Modelo de Navegación aleatorio.
 *
 * @note Referencia basada en el siguiente video:
 * https://www.youtube.com/watch?v=meonLcN7LD4
 *
 * @param g Referencia al grafo sobre el que se calcula
 * @param dampingFactor Factor de amortiguación o probabilidad de seguir enlaces (típicamente 0.85).
 * @param maxIteraciones Límite máximo de iteraciones en caso de no converger.
 * @param tolerancia Criterio de break cuando la diferencia entre iteraciones es mínima.
 * @return vector<double> Vector con el puntaje de PageRank indexado por el ID de cada nodo.
 */
vector<double> calcPageRank(const Grafo& g, double dampingFactor = 0.85, int maxIteraciones = 100, double tolerancia = 1e-6);

/**
 * Centralidad de Subgrafo (Subgraph Centrality)
 * Retorna la importancia de un nodo según cuántas veces es parte de un ciclo cerrado,
 * la implementación se basa en aproximación mediante la serie de Taylor de la función exponencial, truncada en k=10.
 * 
 * Esto debido a que la implementación exacta requiere calcular la exponencial de la matriz de adyacencia,
 * lo que tiene una complejidad temporal de O(n^3) y espacial de O(n^2), lo que es inviable para grafos grandes.
 */
vector<double> calcSubgraphCentrality(const Grafo& g);


// -------------------------------------------
// Métricas que actúan sobre el grafo completo.

/**
 * Longitud Promedio del Camino Más Corto (Average Shortest Path Length)
 * Devuelve la distancia promedio entre todos los pares de nodos conectados en el grafo.
 */
double calcAverageShortestPath(const Grafo& g);

/**
 * @brief Coeficiente de agrupamiento global (Global Clustering Coefficient).
 * 
 * Retorna un valor entre 0 y 1 que indica la tendencia de los nodos a formar clústeres o grupos densamente conectados.
 */
double calcGlobalClusteringCoefficient(const Grafo& g);



// Función de utilidad

/**
 * Muestra un ranking ordenado de mayor a menor según la métrica entregada.
 * @param valores Vector con los resultados indexados por ID de nodo.
 * @param nombreMetrica Etiqueta para que aparezca el nombre de la métrica en la salida.
 * @param topN Cantidad de elementos a mostrar en el top (por defecto 10).
 */
void mostrarTopCentralidad(const Grafo& g, const vector<double>& valores, const string& nombreMetrica, int topN = 10);

void eliminarTopMetrica(Grafo& g, const vector<double>& valores, int topN = 10);

#endif // ALGORITMOS_H