#include "algoritmos.h"
#include <cmath>
#include <vector>

using namespace std;


// Está en orden O(V + E) por iteración, porque recorre todos los nodos y para cada nodo recorre sus vecinos (adyacencia).
vector<double> calcPageRank(const Grafo &g, double dampingFactor, int maxIteraciones, double tolerancia)
{
    int n = g.numNodos();
    if (n == 0)
        return vector<double>();

    // Inicializar el vector uniformemente.
    vector<double> pagerank(n, 1.0 / n);

    // Precalculamos la suma de pesos de las aristas para cada nodo.
    vector<double> sumaPesosNodos(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        double suma = 0.0;
        for (const auto &vecino : g.vecinosDe(i))
        {
            suma += vecino.second;
        }
        sumaPesosNodos[i] = suma;
    }

    // Factor base constante debido al teletransporte.
    double baseTp = (1.0 - dampingFactor) / n;

    for (int it = 0; it < maxIteraciones; it++)
    {
        vector<double> nuevoPagerank(n, 0.0);
        double prSum = 0.0; // Suma de PageRank de nodos sin salida (sumideros)

        /*
        Distribuir el pagerank hacia los vecinos.
        Decidi usar el enfoque de PageRank ponderado por el peso de las aristas,
        ya que lo considero relevante para el dataset de actores, donde el peso representa la cantidad de películas compartidas.
        Así el algoritmo refleja mejor la importancia de los actores que han trabajado juntos en múltiples proyectos.
        En el caso de grafos no ponderados, este enfoque se comporta de manera similar al PageRank tradicional.
        */

        for (int i = 0; i < n; i++)
        {
            double sumaPesos = sumaPesosNodos[i];

            if (sumaPesos > 0)
            {
                for (const auto &vecino : g.vecinosDe(i))
                {
                    int idVecino = vecino.first;
                    int pesoArista = vecino.second;

                    // El aporte depende del peso de la arista sobre la suma de los pesos de las aristas del nodo actual.
                    double aportePonderado = pagerank[i] * (double(pesoArista) / sumaPesos);
                    nuevoPagerank[idVecino] += aportePonderado;
                }
            }
            else
            {
                prSum += pagerank[i]; // Nodo sumidero
            }
        }

        double aporteSum = (dampingFactor * prSum) / n; // Distribuir el PageRank de los sumideros uniformemente.
        double cambioMax = 0.0;

        for (int i = 0; i < n; i++)
        {
            nuevoPagerank[i] = baseTp + (dampingFactor * nuevoPagerank[i]) + aporteSum;

            // Calcular la diferencia para verificar convergencia
            double diferencia = abs(nuevoPagerank[i] - pagerank[i]);
            if (diferencia > cambioMax)
            {
                cambioMax = diferencia;
            }
        }

        pagerank = nuevoPagerank;

        // Si converge, salimos de bucle.
        if (cambioMax < tolerancia)
        {
            break;
        }
    }

    return pagerank;
}