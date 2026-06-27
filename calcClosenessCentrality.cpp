#include "algoritmos.h"
#include <vector>
#include <queue>

using namespace std;

// Por si hay nodos aislados, se normaliza con Wasserman-Faust
// La implementación es utilizando BFS para cada nodo, ignorando el peso.
// Esto tiene una complejidad de O(V * (V + E)), donde V es el número de nodos y E es el número de aristas.
vector<double> calcClosenessCentrality(const Grafo &g)
{

    int n = g.numNodos();
    vector<double> closeness(n, 0.0);

    if (n <= 1)
        return closeness;

    // hacemos bfs desde cada nodo 's' para saber distancias
    for (int s = 0; s < n; s++)
    {
        vector<int> dist(n, -1); // -1 significa no visitado
        queue<int> Q;

        Q.push(s);
        dist[s] = 0;

        long long sumaDistancias = 0;
        int alcanzados = 0;

        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();
            alcanzados++;
            sumaDistancias += dist[v];

            for (const auto &arista : g.vecinosDe(v))
            {
                int w = arista.first;
                if (dist[w] == -1) // Si no ha sido visitado
                {
                    dist[w] = dist[v] + 1;
                    Q.push(w);
                }
            }
        }

        // Si el nodo alcanzó a otros vecinos (más allá de sí mismo)
        // Esta variante multiplica el resultado por la proporción de nodos que pertenecen a la misma componente conectada que el nodo v
        if (alcanzados > 1 && sumaDistancias > 0)
        {
            // Componente de tamaño (alcanzados)
            double num = (double)(alcanzados - 1) * (alcanzados - 1);
            double den = (double)(n - 1) * sumaDistancias;
            closeness[s] = num / den;
        }
        else
        {
            closeness[s] = 0.0;
        }
    }

    return closeness;
}