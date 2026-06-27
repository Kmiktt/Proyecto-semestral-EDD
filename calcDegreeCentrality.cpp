#include "algoritmos.h"
#include <vector>

using namespace std;

/*
Tiene una complejidad de O(V), porque se recorre cada nodo y se obtiene su grado en O(1).
*/
vector<double> calcDegreeCentrality(const Grafo& g)
{
    int n = g.numNodos();
    vector<double> degreeCentrality(n, 0.0);

    if (n <= 1) return degreeCentrality; // Evitar división por cero

    // normalización 
    double factorNormalizacion = 1.0 / (n - 1);

    for (int i = 0; i < n; i++)
    {
        // El grado es la cantidad de vecinos
        double grado = (double)g.vecinosDe(i).size();
        
        // Se normaliza por el mayor grado posible.
        degreeCentrality[i] = grado * factorNormalizacion;
    }

    return degreeCentrality;
}