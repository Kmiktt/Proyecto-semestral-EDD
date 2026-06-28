#include "algoritmos.h"
#include <vector>
#include <cmath>

using namespace std;

vector<double> calcSubgraphCentrality(const Grafo& g)
{
    int n = g.numNodos();
    vector<double> sc(n, 0.0);

    if (n <= 0) return sc;

    const int K = 10; // truncamiento para serie de taylor

    // Precalcular factoriales inversos para eficiencia
    vector<double> invFactorial(K + 1, 1.0);
    double fact = 1.0;
    for (int k = 1; k <= K; ++k) {
        fact *= k;
        invFactorial[k] = 1.0 / fact;
    }

    // Para cada nodo 's' se calcula la centralidad de subgrafo aproximada
    for (int s = 0; s < n; ++s)
    {
        // Vector que almacena cuántos caminos de longitud 'k' terminan en cada nodo partiendo desde 's'
        vector<double> caminosActual(n, 0.0);
        caminosActual[s] = 1.0; // k es 0: hay 1 camino de longitud 0 que empieza en 's' y termina en 's'

        // k = 0 aporta 1 al subgraph centrality
        sc[s] += caminosActual[s] * invFactorial[0];

        // se simula A^k para k = 1 a K
        for (int k = 1; k <= K; ++k)
        {
            vector<double> caminosSiguiente(n, 0.0);

            // se recorre cada nodo 'v' y se propaga a sus vecinos
            for (int v = 0; v < n; ++v)
            {
                if (caminosActual[v] == 0.0) continue;

                for (const auto& arista : g.vecinosDe(v))
                {
                    int w = arista.first;
                    caminosSiguiente[w] += caminosActual[v]; 
                }
            }

            // al final de cada paso, se agrega cuanto contribuyen los subgrafos de longitud k al nodo s
            sc[s] += caminosSiguiente[s] * invFactorial[k];
            
            // Actualizamos para la siguiente longitud de ciclo
            caminosActual = move(caminosSiguiente);
        }
    }
    return sc;
}