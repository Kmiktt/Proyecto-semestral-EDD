#include "algoritmos.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Se implementa usando el algoritmo de Brandes
// No se tiene en cuenta el peso de las aristas, para el caso de los actores, se ve de forma binaria si actuaron juntos o no.
// Este algoritmo tiene una complejidad de O(V * (V + E)), donde V es el número de nodos y E es el número de aristas.
vector<double> calcBetweennessCentrality(const Grafo &g)
{
    int n = g.numNodos();
    vector<double> betweenness(n, 0.0);

    if (n <= 2)
        return betweenness; // Evitar división por cero en la normalización

    // Se hace BFS desde cada nodo 's' como fuente
    for (int s = 0; s < n; s++)
    {

        // Inicializamos estructuras para Brandes

        stack<int> S; // Pila para el orden de los nodos visitados
        vector<vector<int>> P(n); // Predecesores de cada nodo
        vector<int> sigma(n, 0); // Conteo de caminos más cortos desde s
        vector<int> d(n, -1); // Distancia desde s (-1 significa no visitado)

        sigma[s] = 1; 
        d[s] = 0; 

        queue<int> Q; // Cola para el bfs
        Q.push(s);

        // Iniciamos bfs
        while (!Q.empty()){
            int v = Q.front();
            Q.pop();
            S.push(v); // Guardamos el orden inverso de visitas

            for(const auto& arista : g.vecinosDe(v)){
                int w = arista.first; // Vecino de v

                // Si w no ha sido visitado, lo visitamos
                if(d[w] < 0){
                    Q.push(w);
                    d[w] = d[v] + 1;
                }

                // Si el camino más corto a 'w' pasa a través de 'v'
                if(d[w] == d[v] + 1){
                    sigma[w] += sigma[v];
                    P[w].push_back(v);
                }
            }
        }

        vector<double> delta(n, 0.0); // Dependencia acumulada
        while(!S.empty()){
            int w = S.top();
            S.pop();

            for(int v : P[w]){
                // Se calcula la dependencia de v sobre w
                delta[v] += (double(sigma[v]) / sigma[w]) * (1.0 + delta[w]);
            }

            // Solo sumamos a la centralidad de intermediación si w no es la fuente
            if(w != s){
                betweenness[w] += delta[w];
            }
        }
        
    }

    // Normalización
    // Tiene 2 porque cada camino se cuenta en ambas direcciones (de u a v y de v a u)
    double factorNormalizacion = 2.0 / ((n - 1) * (n - 2));

    for(int i = 0; i < n; i++){
        betweenness[i] *= factorNormalizacion;
    }

    return betweenness;

}