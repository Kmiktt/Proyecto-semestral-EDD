#include "algoritmos.h"
#include <vector>
#include <set>

using namespace std;


/*
Tiene una complejidad temporal de O(E * V * log(V)), donde E es el número de aristas y V es el número de nodos.
Esto es en el peor caso de un grafo muy denso, ya que para cada nodo se recorren sus vecinos y se verifica la existencia de aristas entre ellos.

Si se ve en función del grado máximo, es O(V* k^2 * log(k)), donde k es el grado máximo de un nodo,
ya que para cada nodo se recorren sus k vecinos y para cada vecino se verifica la existencia de aristas entre ellos.

*/
double calcGlobalClusteringCoefficient(const Grafo &g)
{
    int n = g.numNodos();
    long long totalTriangulosCerrados = 0;
    long long totalTriangulosPosibles = 0; // Caminos de longitud 2 (tripletas)

    for (int i = 0; i < n; i++)
    {
        const auto &vecinos = g.vecinosDe(i);
        long long k = vecinos.size();

        if (k < 2) continue;

        // Guardamos los vecinos en un set para búsqueda rápida
        set<int> conjuntoVecinos;
        for (const auto &vecino : vecinos)
        {
            conjuntoVecinos.insert(vecino.first);
        }

        // Contamos cuántas aristas existen realmente entre sus vecinos
        for (size_t j = 0; j < vecinos.size(); j++)
        {
            int u = vecinos[j].first;

            for (const auto &vecinoDeU : g.vecinosDe(u))
            {
                int v = vecinoDeU.first;

                // Contamos la arista si 'v' también es vecino de 'i'
                if (conjuntoVecinos.count(v))
                {
                    totalTriangulosCerrados++;
                }
            }
        }

        // Tripletas posibles centradas en el nodo i: k * (k - 1)
        totalTriangulosPosibles += k * (k - 1);
    }

    if (totalTriangulosPosibles == 0) return 0.0;

    // El coeficiente global es (3 * Triángulos) / Tripletas Posibles.
    // Como al recorrer el grafo contamos cada triángulo desde sus 3 nodos y en ambas direcciones,
    // la relación directa de lo que sumamos es simplemente cerrados / posibles.
    return (double)totalTriangulosCerrados / totalTriangulosPosibles;
}