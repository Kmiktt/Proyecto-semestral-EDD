#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <fstream>
#include "grafos.h"
#include "algoritmos.h"

using namespace std;

// Función utilitaria para calcular el promedio de un vector de tiempos
double calcularPromedio(const vector<double> &tiempos)
{
    if (tiempos.empty())
        return 0.0;
    double suma = accumulate(tiempos.begin(), tiempos.end(), 0.0);
    return suma / tiempos.size();
}

double calcularVarianza(const vector<double> &tiempos, double promedio)
{
    if (tiempos.size() <= 1)
        return 0.0;

    double sumaVarianza = 0.0;
    for (double t : tiempos)
    {
        sumaVarianza += (t - promedio) * (t - promedio);
    }
    return sumaVarianza / (tiempos.size() - 1); // es varianza muestral
}

double estimarMemoriaGrafoMB(const Grafo &g)
{
    long long v = g.numNodos();
    long long e = g.numAristas();

    // Peso estimado por nodo (string nombres + unordered_map ids + overhead de vectores base)
    long long bytesNodos = v * 160;

    // Peso estimado por arista (2 veces en ady y 2 veces en vecinosSet por ser no dirigido)
    long long bytesAristas = e * 48;

    long long bytesTotales = bytesNodos + bytesAristas;
    return static_cast<double>(bytesTotales) / (1024.0 * 1024.0); // Convertir a MB
}

void ejecutarBenchmark(const Grafo &g, const string &nombreDataset, ofstream &logFile, double tiempoCarga)
{
    const int MUESTRAS = 15;

    // Vectores para almacenar los tiempos de cada iteración
    vector<double> tiemposDC, tiemposBC, tiemposCLC, tiemposPR, tiemposASPL, tiemposGCC, tiemposSC;

    double memoriaMB = estimarMemoriaGrafoMB(g);

    string header = "\n==================================================\n"
                    " INICIANDO BENCHMARK PARA: " +
                    nombreDataset + "\n"
                                    "==================================================";
    cout << "  Tiempo de carga en memoria: " << tiempoCarga << " ms" << endl;
    cout << "  Memoria RAM estimada:       " << memoriaMB << " MB" << endl;

    cout << header << endl;
    logFile << header << "\n"
            << "Tiempo de construccion: " << tiempoCarga << " ms\n"
            << "Memoria RAM estimada:   " << memoriaMB << " MB\n"
            << "\n--- TIEMPOS POR ITERACIÓN (ms) ---" << endl;

    for (int i = 1; i <= MUESTRAS; i++)
    {
        cout << "[Iteracion " << i << "/" << MUESTRAS << "] Ejecutando metricas..." << flush;

        // 1. Degree Centrality
        auto start = chrono::high_resolution_clock::now();
        volatile auto dc = calcDegreeCentrality(g);
        auto end = chrono::high_resolution_clock::now();
        tiemposDC.push_back(chrono::duration<double, milli>(end - start).count());

        // 2. Betweenness Centrality
        start = chrono::high_resolution_clock::now();
        volatile auto bc = calcBetweennessCentrality(g);
        end = chrono::high_resolution_clock::now();
        tiemposBC.push_back(chrono::duration<double, milli>(end - start).count());

        // 3. Closeness Centrality
        start = chrono::high_resolution_clock::now();
        volatile auto clc = calcClosenessCentrality(g);
        end = chrono::high_resolution_clock::now();
        tiemposCLC.push_back(chrono::duration<double, milli>(end - start).count());

        // 4. PageRank
        start = chrono::high_resolution_clock::now();
        volatile auto pr = calcPageRank(g, 0.85, 100, 1e-6);
        end = chrono::high_resolution_clock::now();
        tiemposPR.push_back(chrono::duration<double, milli>(end - start).count());

        // 5. Average Shortest Path Length (ASPL)
        start = chrono::high_resolution_clock::now();
        volatile double aspl = calcAverageShortestPath(g);
        end = chrono::high_resolution_clock::now();
        tiemposASPL.push_back(chrono::duration<double, milli>(end - start).count());

        // 6. Global Clustering Coefficient (GCC)
        start = chrono::high_resolution_clock::now();
        volatile double gcc = calcGlobalClusteringCoefficient(g);
        end = chrono::high_resolution_clock::now();
        tiemposGCC.push_back(chrono::duration<double, milli>(end - start).count());

        // 7. Subgraph Centrality (SC)
        start = chrono::high_resolution_clock::now();
        volatile auto sc = calcSubgraphCentrality(g);
        end = chrono::high_resolution_clock::now();
        tiemposSC.push_back(chrono::duration<double, milli>(end - start).count());

        cout << " OK" << endl;

        logFile << "[Iteracion " << i << "]\n"
                << "  DC:  " << tiemposDC.back() << " ms\n"
                << "  BC:  " << tiemposBC.back() << " ms\n"
                << "  CLC: " << tiemposCLC.back() << " ms\n"
                << "  PR:  " << tiemposPR.back() << " ms\n"
                << "  ASPL:" << tiemposASPL.back() << " ms\n"
                << "  GCC: " << tiemposGCC.back() << " ms\n"
                << "  SC:  " << tiemposSC.back() << " ms\n"
                << "--------------------------------------------------" << endl;
    }

    // promedios
    double avgDC = calcularPromedio(tiemposDC);
    double avgBC = calcularPromedio(tiemposBC);
    double avgCLC = calcularPromedio(tiemposCLC);
    double avgPR = calcularPromedio(tiemposPR);
    double avgASPL = calcularPromedio(tiemposASPL);
    double avgGCC = calcularPromedio(tiemposGCC);
    double avgSC = calcularPromedio(tiemposSC);

    // varianzas
    double varDC   = calcularVarianza(tiemposDC, avgDC);
    double varBC   = calcularVarianza(tiemposBC, avgBC);
    double varCLC  = calcularVarianza(tiemposCLC, avgCLC);
    double varPR   = calcularVarianza(tiemposPR, avgPR);
    double varASPL = calcularVarianza(tiemposASPL, avgASPL);
    double varGCC  = calcularVarianza(tiemposGCC, avgGCC);
    double varSC   = calcularVarianza(tiemposSC, avgSC);

    string resumen = "\n--------------------------------------------------\n"
                     " RESUMEN ESTADÍSTICO DE TIEMPOS (" + nombreDataset + ")\n"
                     "--------------------------------------------------\n"
                     " Metrica                 | Promedio (ms) | Varianza\n"
                     "--------------------------------------------------\n"
                     " Degree Centrality       | " + to_string(avgDC)   + " | " + to_string(varDC)   + "\n"
                     " Betweenness Centrality  | " + to_string(avgBC)   + " | " + to_string(varBC)   + "\n"
                     " Closeness Centrality    | " + to_string(avgCLC)  + " | " + to_string(varCLC)  + "\n"
                     " PageRank                | " + to_string(avgPR)   + " | " + to_string(varPR)   + "\n"
                     " Average Shortest Path   | " + to_string(avgASPL) + " | " + to_string(varASPL) + "\n"
                     " Global Clustering Coeff | " + to_string(avgGCC)  + " | " + to_string(varGCC)  + "\n"
                     " Subgraph Centrality     | " + to_string(avgSC)   + " | " + to_string(varSC)   + "\n"
                     "--------------------------------------------------";

    cout << resumen << endl;
    logFile << "\n=== TABLA DE RENDIMIENTO ===" << resumen << "\n" << endl;
}

int main()
{
    ofstream logFile("benchmark_log.txt", ios::out | ios::trunc);

    if (!logFile.is_open())
    {
        cerr << "Error crítico: No se pudo crear el archivo de registro log." << endl;
        return 1;
    }
    cout << "Cargando datasets para el benchmark..." << endl;

    // yeast
    auto startYeast = chrono::high_resolution_clock::now();
    Grafo yeast;
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);
    auto endYeast = chrono::high_resolution_clock::now();
    double tYeast = chrono::duration<double, milli>(endYeast - startYeast).count();

    // imdb
    auto startImdb = chrono::high_resolution_clock::now();
    Grafo imdb;
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);
    auto endImdb = chrono::high_resolution_clock::now();
    double tImdb = chrono::duration<double, milli>(endImdb - startImdb).count();

    ejecutarBenchmark(yeast, "YEAST", logFile, tYeast);
    ejecutarBenchmark(imdb, "IMDB", logFile, tImdb);

    logFile.close();

    cout << "\nEl archivo benchmark_log.txt ha sido creado con los resultados." << endl;

    return 0;
}