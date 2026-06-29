#include <iostream>
#include <algorithm>
#include "algoritmos.h"

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
