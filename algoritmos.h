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
 * 4. PageRank
 * Calcula la importancia de los nodos mediante recorridos aleatorios iterativos (Power Iteration).
 * @param dampingFactor Factor de amortiguación (típicamente 0.85).
 * @param maxIteraciones Límite máximo de ciclos.
 * @param tolerancia Criterio de parada por convergencia.
 */
vector<double> calcPageRank(const Grafo& g, double dampingFactor = 0.85, int maxIteraciones = 100, double tolerancia = 1e-6);

/**
 * 6. Centralidad de Subgrafo (Subgraph Centrality)
 * Retorna ...
 */
vector<double> calcSubgraphCentrality(const Grafo& g);

/**
 * 7. Coeficiente de Agrupamiento Local (Clustering Coefficient)
 * Retorna ...
 */
vector<double> calcClusteringCoefficient(const Grafo& g);

// -------------------------------------------
// Métricas que actúan sobre el grafo completo.

/**
 * 5. Longitud Promedio del Camino Más Corto (Average Shortest Path Length)
 * Devuelve la distancia promedio entre todos los pares de nodos conectados en el grafo.
 */
double calcAverageShortestPath(const Grafo& g);



// Función de utilidad

/**
 * Muestra un ranking ordenado de mayor a menor según la métrica entregada.
 * @param valores Vector con los resultados indexados por ID de nodo.
 * @param nombreMetrica Etiqueta para que aparezca el nombre de la métrica en la salida.
 * @param topN Cantidad de elementos a mostrar en el top (por defecto 10).
 */
void mostrarTopCentralidad(const Grafo& g, const vector<double>& valores, const string& nombreMetrica, int topN = 10);

#endif // ALGORITMOS_H