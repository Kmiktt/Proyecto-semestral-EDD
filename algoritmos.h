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
 * 1. Centralidad de Grado (Degree Centrality)
 * Retorna ...
 */
vector<double> calcDegreeCentrality(const Grafo& g);

/**
 * 2. Centralidad de Intermediación (Betweenness Centrality)
 * Retorna ...
 */
vector<double> calcBetweennessCentrality(const Grafo& g);

/**
 * 3. Centralidad de Cercanía (Closeness Centrality)
 * Retorna ...
 */
vector<double> calcClosenessCentrality(const Grafo& g);

/**
 * @brief 4. PageRank
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
 * 6. Centralidad de Subgrafo (Subgraph Centrality)
 * Retorna ...
 */
vector<double> calcSubgraphCentrality(const Grafo& g);


// -------------------------------------------
// Métricas que actúan sobre el grafo completo.

/**
 * 5. Longitud Promedio del Camino Más Corto (Average Shortest Path Length)
 * Devuelve la distancia promedio entre todos los pares de nodos conectados en el grafo.
 */
double calcAverageShortestPath(const Grafo& g);

/**
 * @brief 7. Coeficiente de agrupamiento global (Global Clustering Coefficient).
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

#endif // ALGORITMOS_H