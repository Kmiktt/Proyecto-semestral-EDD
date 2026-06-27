#include "algoritmos.h"
#include <vector>
#include <queue>

using namespace std;

/*
La implementación es utilizando BFS para cada nodo, ignorando el peso.
Esto tiene una complejidad de O(V * (V + E)), donde V es el número de nodos y E es el número de aristas.
*/
double calcAverageShortestPath(const Grafo& g){
    int n = g.numNodos();
    if (n <= 1) return 0.0;

    long long sumaTotalDistancias = 0;
    long long totalCaminosValidos = 0;

    // Lanzamos un BFS desde cada nodo 's'
    for (int s = 0; s < n; s++)
    {
        vector<int> dist(n, -1);
        queue<int> q;

        dist[s] = 0;
        q.push(s);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            // Si v != s, se encontró un camino válido desde s hasta v de distancia dist[v]
            if (v != s)
            {
                sumaTotalDistancias += dist[v];
                totalCaminosValidos++;
            }

            for (const auto& arista : g.vecinosDe(v))
            {
                int w = arista.first;
                if (dist[w] == -1) // No visitado
                {
                    dist[w] = dist[v] + 1;
                    q.push(w);
                }
            }
        }
    }

    // Evitar división por cero si el grafo no tiene aristas
    if (totalCaminosValidos == 0) return 0.0;

    // retorna el promedio de las distancias más cortas entre todos los pares de nodos conectados
    return (double)sumaTotalDistancias / totalCaminosValidos;

}