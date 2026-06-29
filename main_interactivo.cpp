#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include "grafos.h"
#include "algoritmos.h"

int main()
{
    cout << "Cargando datasets en memoria..." << endl;

    auto startYeast = chrono::high_resolution_clock::now();
    Grafo yeast;
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);
    auto endYeast = chrono::high_resolution_clock::now();
    double tYeast = chrono::duration<double, milli>(endYeast - startYeast).count();
    cout << "YEAST cargado exitosamente (" << tYeast << " ms)." << endl;

    auto startImdb = chrono::high_resolution_clock::now();
    Grafo imdb;
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);
    auto endImdb = chrono::high_resolution_clock::now();
    double tImdb = chrono::duration<double, milli>(endImdb - startImdb).count();
    cout << "IMDB cargado exitosamente (" << tImdb << " ms).\n"
         << endl;

    int opcionDataset = 0;

    while (true)
    {
        cout << "==========================================" << endl;
        cout << "   MENÚ SELECCIÓN DE DATASET" << endl;
        cout << "==========================================" << endl;
        cout << "  1. Trabajar con YEAST" << endl;
        cout << "  2. Trabajar con IMDB" << endl;
        cout << "  3. Salir del Programa" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionDataset;

        if (opcionDataset == 3)
        {
            cout << "\nSaliendo del programa." << endl;
            break;
        }
        if (opcionDataset != 1 && opcionDataset != 2)
        {
            cout << "\n!! Opción no válida. Intente nuevamente.\n"
                 << endl;
            continue;
        }

        const Grafo &g_actual = (opcionDataset == 1) ? yeast : imdb;
        string nombreDS = (opcionDataset == 1) ? "YEAST" : "IMDB";

        int opcionMetrica = 0;
        while (true)
        {
            cout << "------------------------------------------" << endl;
            cout << " MÉTRICAS DISPONIBLES PARA: " << nombreDS << endl;
            cout << "------------------------------------------" << endl;
            cout << "  1. Degree Centrality" << endl;
            cout << "  2. Betweenness Centrality" << endl;
            cout << "  3. Closeness Centrality" << endl;
            cout << "  4. PageRank" << endl;
            cout << "  5. Average Shortest Path Length (ASPL)" << endl;
            cout << "  6. Global Clustering Coefficient (GCC)" << endl;
            cout << "  7. Subgraph Centrality" << endl;
            cout << "  8. Volver al menú de Datasets" << endl;
            cout << "Seleccione una métrica: ";
            cin >> opcionMetrica;

            if (opcionMetrica == 8)
                break;
            if (opcionMetrica < 1 || opcionMetrica > 7)
            {
                cout << "\n!! Métrica inválida.\n"
                     << endl;
                continue;
            }

            // Métricas Globales
            if (opcionMetrica == 5)
            {
                cout << "\n[*] Calculando Average Shortest Path..." << flush;
                auto t_start = chrono::high_resolution_clock::now();
                double aspl = calcAverageShortestPath(g_actual);
                auto t_end = chrono::high_resolution_clock::now();
                cout << " OK (" << chrono::duration<double, milli>(t_end - t_start).count() << " ms)" << endl;
                cout << " >> El ASPL de " << nombreDS << " es: " << aspl << "\n"
                     << endl;
                continue;
            }
            if (opcionMetrica == 6)
            {
                cout << "\n[*] Calculando Global Clustering Coefficient..." << flush;
                auto t_start = chrono::high_resolution_clock::now();
                double gcc = calcGlobalClusteringCoefficient(g_actual);
                auto t_end = chrono::high_resolution_clock::now();
                cout << " OK (" << chrono::duration<double, milli>(t_end - t_start).count() << " ms)" << endl;
                cout << " >> El GCC de " << nombreDS << " es: " << gcc << "\n"
                     << endl;
                continue;
            }

            int topN = 5;
            cout << "¿Cuántos elementos deseas desplegar en el Top?: ";
            cin >> topN;
            if (topN <= 0)
                topN = 5;

            vector<double> resultados;
            string nombreMetricaStr = "";
            auto t_start = chrono::high_resolution_clock::now();

            switch (opcionMetrica)
            {
            case 1:
                cout << "\n[*] Calculando Degree Centrality..." << flush;
                resultados = calcDegreeCentrality(g_actual);
                nombreMetricaStr = "Degree Centrality";
                break;
            case 2:
                cout << "\n[*] Calculando Betweenness Centrality (Esto puede tardar)..." << flush;
                resultados = calcBetweennessCentrality(g_actual);
                nombreMetricaStr = "Betweenness Centrality";
                break;
            case 3:
                cout << "\n[*] Calculando Closeness Centrality..." << flush;
                resultados = calcClosenessCentrality(g_actual);
                nombreMetricaStr = "Closeness Centrality";
                break;
            case 4:
                cout << "\n[*] Calculando PageRank..." << flush;
                resultados = calcPageRank(g_actual, 0.85, 100, 1e-6);
                nombreMetricaStr = "PageRank";
                break;
            case 7:
                cout << "\n[*] Calculando Subgraph Centrality..." << flush;
                resultados = calcSubgraphCentrality(g_actual);
                nombreMetricaStr = "Subgraph Centrality";
                break;
            }

            auto t_end = chrono::high_resolution_clock::now();
            cout << " OK (" << chrono::duration<double, milli>(t_end - t_start).count() << " ms)" << endl;


            mostrarTopCentralidad(g_actual, resultados, nombreMetricaStr + " (" + nombreDS + ")", topN);
        }
    }

    return 0;
}