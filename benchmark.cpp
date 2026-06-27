#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include "grafos.h"
#include "algoritmos.h"

using namespace std;


double calcularPromedio(const vector<double>& tiempos) {
    if (tiempos.empty()) return 0.0;
    double suma = accumulate(tiempos.begin(), tiempos.end(), 0.0);
    return suma / tiempos.size();
}

void ejecutarBenchmark(const Grafo& g, const string& nombreDataset) {
    const int MUESTRAS = 15;
    
    vector<double> tiemposPR, tiemposGCC, tiemposDC, tiemposBC, tiemposCLC;

    cout << "\n==================================================" << endl;
    cout << " INICIANDO BENCHMARK PARA: " << nombreDataset << endl;
    cout << "==================================================" << endl;

    for (int i = 1; i <= MUESTRAS; i++) {
        cout << "[Iteracion " << i << "/" << MUESTRAS << "] Ejecutando metricas..." << flush;

        // 1. PageRank
        auto start = chrono::high_resolution_clock::now();
        volatile auto pr = calcPageRank(g, 0.85, 100, 1e-6); // Usa el nombre exacto de tu funcion
        auto end = chrono::high_resolution_clock::now();
        tiemposPR.push_back(chrono::duration<double, milli>(end - start).count());

        // 2. Global Clustering Coefficient
        start = chrono::high_resolution_clock::now();
        volatile double gcc = calcGlobalClusteringCoefficient(g);
        end = chrono::high_resolution_clock::now();
        tiemposGCC.push_back(chrono::duration<double, milli>(end - start).count());

        // 3. Degree Centrality
        start = chrono::high_resolution_clock::now();
        volatile auto dc = calcDegreeCentrality(g);
        end = chrono::high_resolution_clock::now();
        tiemposDC.push_back(chrono::duration<double, milli>(end - start).count());

        // 4. Betweenness Centrality
        start = chrono::high_resolution_clock::now();
        volatile auto bc = calcBetweennessCentrality(g);
        end = chrono::high_resolution_clock::now();
        tiemposBC.push_back(chrono::duration<double, milli>(end - start).count());

        // 5. Closeness Centrality
        start = chrono::high_resolution_clock::now();
        volatile auto clc = calcClosenessCentrality(g);
        end = chrono::high_resolution_clock::now();
        tiemposCLC.push_back(chrono::duration<double, milli>(end - start).count());

        cout << " OK" << endl;
    }


    cout << "\n--------------------------------------------------" << endl;
    cout << " RESUMEN DE TIEMPOS PROMEDIO (" << nombreDataset << ")" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "  PageRank:               " << calcularPromedio(tiemposPR) << " ms" << endl;
    cout << "  Global Clustering Coeff: " << calcularPromedio(tiemposGCC) << " ms" << endl;
    cout << "  Degree Centrality:       " << calcularPromedio(tiemposDC) << " ms" << endl;
    cout << "  Betweenness Centrality:  " << calcularPromedio(tiemposBC) << " ms" << endl;
    cout << "  Closeness Centrality:    " << calcularPromedio(tiemposCLC) << " ms" << endl;
    cout << "--------------------------------------------------" << endl;
}

int main() {

    cout << "Cargando datasets para el benchmark..." << endl;  
    Grafo yeast;
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);  
    Grafo imdb;
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);

    ejecutarBenchmark(yeast, "YEAST");
    ejecutarBenchmark(imdb, "IMDB");

    return 0;
}