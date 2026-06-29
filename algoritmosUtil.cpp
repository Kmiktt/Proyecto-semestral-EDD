#include <iostream>
#include <algorithm>
#include "algoritmos.h"
#include <random>

void mostrarTopCentralidad(const Grafo &g, const vector<double> &valores, const string &nombreMetrica, int topN)
{
    // Almacenamos los nodos junto a sus valores
    vector<NodoRanking> ranking;
    for (int i = 0; i < g.numNodos(); i++)
    {
        ranking.push_back({i, g.nombreNodo(i), valores[i]});
    }

    // Ordenamos de mayor a menor según el valor de la métrica
    sort(ranking.begin(), ranking.end(), [](const NodoRanking &a, const NodoRanking &b)
         { return a.valor > b.valor; });

    // Imprimimos el top
    cout << "\n========================================" << endl;
    cout << "  TOP " << topN << " - " << nombreMetrica << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < topN && i < ranking.size(); i++)
    {
        cout << i + 1 << ". ID: " << ranking[i].id
             << " | Nodo: " << ranking[i].nombre
             << " | Valor: " << ranking[i].valor << endl;
    }
}

void eliminarTopMetrica(Grafo &g, const vector<double> &valores, int topN)
{
    int n = g.numNodos();
    if (n <= 0)
        return;

    vector<NodoRanking> ranking;
    for (int i = 0; i < g.numNodos(); i++)
    {
        ranking.push_back({i, g.nombreNodo(i), valores[i]});
    }

    // Ordenamos de mayor a menor según el valor de la métrica
    sort(ranking.begin(), ranking.end(), [](const NodoRanking &a, const NodoRanking &b)
         { return a.valor > b.valor; });

    int limite = min(topN, n);

    for (int i = 0; i < limite; i++)
    {
        int nodoId = ranking[i].id;
        double valorMetrica = ranking[i].valor;
        string nombreNodoOriginal = ranking[i].nombre;

        // Obtenemos una copia segura de sus vecinos antes de remover enlaces
        auto vecinos = g.vecinosDe(nodoId); //
        int gradoAbsoluto = vecinos.size();

        for (const auto &arista : vecinos)
        {
            int vecinoId = arista.first;
            string nombreVecino = g.nombreNodo(vecinoId); //

            g.eliminarArista(nombreNodoOriginal, nombreVecino); //
        }
    }

    cout << "Se han eliminado los " << limite << " nodos con mayor valor de la métrica." << endl;
}

void agregarNodosAlAzar(Grafo &g, int cantidad, int k)
{
    int nOriginal = g.numNodos();
    if (nOriginal == 0 || cantidad <= 0 || k < 1)
        return;

    // para evitar bucles infinitos con k muy alto
    if (k > nOriginal)
    {
        k = nOriginal;
    }

    // config de random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, nOriginal - 1); // solo entre los q ya existen


    int primerNodoNuevoId = nOriginal;

    for (int i = 0; i < cantidad; ++i)
    {
        string nombreNodo = "Nodo_" + to_string(g.numNodos());
        g.agregarNodo(nombreNodo);
    }


    int totalNodos = g.numNodos();
    for (int i = primerNodoNuevoId; i < totalNodos; ++i)
    {
        std::unordered_set<int> vecinosConectados;
        string nombreNodoNuevo = g.nombreNodo(i);

        while (vecinosConectados.size() < (size_t)k)
        {
            // elegimos vecino al azar entre los nodos originales
            int vecinoOriginalId = dis(gen);

            // evitar duplicados y auto-conexiones
            if (vecinosConectados.find(vecinoOriginalId) == vecinosConectados.end())
            {
                g.agregarArista(nombreNodoNuevo, g.nombreNodo(vecinoOriginalId));
                vecinosConectados.insert(vecinoOriginalId);
            }
        }
    }
}
