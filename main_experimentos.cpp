#include "grafos.h"
#include "algoritmos.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

// Función auxiliar para imprimir los resultados finales y sus tiempos de CPU de manera ordenada
void imprimirResultadoFinal(const string& metrica, const string& valorFinal, double tiempoMs) {
    cout << "  " << metrica;
    for (size_t i = metrica.length(); i < 35; i++) cout << " ";
    cout << "| " << valorFinal;
    for (size_t i = valorFinal.length(); i < 20; i++) cout << " ";
    cout << "| " << tiempoMs << " ms" << endl;
}

void ejecutarBloqueExperimentos(const string& nombreDataset, const Grafo& grafoOriginal) {

    cout << "=========================================================================" << endl;

    // Clonar el grafo original
    Grafo grafoMutado = grafoOriginal;

    // métrica base 
    vector<double> dcOriginal = calcBetweennessCentrality(grafoOriginal);


    cout << "Aplicando eliminaciones..." << endl;
    eliminarTopMetrica(grafoMutado, dcOriginal, 1000);


    cout << "Evaluando estado..." << endl;

    // Degree Centrality (Después)
    auto t0_dc = chrono::high_resolution_clock::now();
    vector<double> dcMutado = calcDegreeCentrality(grafoMutado);
    auto t1_dc = chrono::high_resolution_clock::now();
    double tDespuesDC = chrono::duration<double, milli>(t1_dc - t0_dc).count();

    // Betweenness Centrality (Después)
    auto t0_bc = chrono::high_resolution_clock::now();
    vector<double> bcDespues = calcBetweennessCentrality(grafoMutado);
    auto t1_bc = chrono::high_resolution_clock::now();
    double tDespuesBC = chrono::duration<double, milli>(t1_bc - t0_bc).count();

    // Closeness Centrality (Después)
    auto t0_clc = chrono::high_resolution_clock::now();
    vector<double> clcDespues = calcClosenessCentrality(grafoMutado);
    auto t1_clc = chrono::high_resolution_clock::now();
    double tDespuesCLC = chrono::duration<double, milli>(t1_clc - t0_clc).count();

    // PageRank (Después)
    auto t0_pr = chrono::high_resolution_clock::now();
    vector<double> prDespues = calcPageRank(grafoMutado, 0.85, 100, 1e-6);
    auto t1_pr = chrono::high_resolution_clock::now();
    double tDespuesPR = chrono::duration<double, milli>(t1_pr - t0_pr).count();

    // Subgraph Centrality (Después)
    auto t0_sc = chrono::high_resolution_clock::now();
    vector<double> scDespues = calcSubgraphCentrality(grafoMutado);
    auto t1_sc = chrono::high_resolution_clock::now();
    double tDespuesSC = chrono::duration<double, milli>(t1_sc - t0_sc).count();

    // ASPL (Después)
    auto t0_aspl = chrono::high_resolution_clock::now();
    double asplDespues = calcAverageShortestPath(grafoMutado);
    auto t1_aspl = chrono::high_resolution_clock::now();
    double tDespuesASPL = chrono::duration<double, milli>(t1_aspl - t0_aspl).count();

    // GCC (Después)
    auto t0_gcc = chrono::high_resolution_clock::now();
    double ccGlobalDespues = calcGlobalClusteringCoefficient(grafoMutado);
    auto t1_gcc = chrono::high_resolution_clock::now();
    double tDespuesGCC = chrono::duration<double, milli>(t1_gcc - t0_gcc).count();

    // ========================================================================
    // Reporte

    cout << "\n RESULTADOS OBTENIDOS (" << nombreDataset << ")" << endl;
    cout << "  -----------------------------------------------------------------------" << endl;
    cout << "  Métrica / Indicador                 | Valor Final         | Tiempo CPU" << endl;
    cout << "  -----------------------------------------------------------------------" << endl;
    
    imprimirResultadoFinal("Nodos Totales (V)", to_string(grafoMutado.numNodos()), 0.0);
    imprimirResultadoFinal("Aristas Activas (E)", to_string(grafoMutado.numAristas()), 0.0);
    imprimirResultadoFinal("Average Shortest Path (ASPL)", to_string(asplDespues), tDespuesASPL);
    imprimirResultadoFinal("Global Clustering Coeff (GCC)", to_string(ccGlobalDespues), tDespuesGCC);
    
    cout << "  -----------------------------------------------------------------------" << endl;
    imprimirResultadoFinal("Tiempo Degree Centrality", "[Calculado]", tDespuesDC);
    imprimirResultadoFinal("Tiempo Betweenness Centrality", "[Calculado]", tDespuesBC);
    imprimirResultadoFinal("Tiempo Closeness Centrality", "[Calculado]", tDespuesCLC);
    imprimirResultadoFinal("Tiempo PageRank", "[Calculado]", tDespuesPR);
    imprimirResultadoFinal("Tiempo Subgraph Centrality", "[Calculado]", tDespuesSC);
    cout << "  -----------------------------------------------------------------------" << endl;
    cout << "=========================================================================\n" << endl;
}

int main() {

    Grafo yeast;
    cout << "[1/2] Cargando dataset Yeast..." << endl;
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);

    Grafo imdb;
    cout << "[2/2] Cargando dataset IMDB..." << endl;
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);

    // ========================================================================

    ejecutarBloqueExperimentos("YEAST", yeast);
    ejecutarBloqueExperimentos("IMDB", imdb);

    return 0;
}