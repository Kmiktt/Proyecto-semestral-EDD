#include "grafos.h"
#include "algoritmos.h" 
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int main() {

    // yeast es el de las proteinas de levaduras
    Grafo yeast;
    cout << "Cargando yeast.edgelist (TSV, sin header, sin peso)..." << endl;
    auto t0 = chrono::high_resolution_clock::now();
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);
    auto t1 = chrono::high_resolution_clock::now();
    double msYeast = chrono::duration<double, milli>(t1-t0).count();
    cout << "Tiempo de construccion: " << msYeast << " ms\n" << endl;

    // imdb es el de los actores
    Grafo imdb;
    cout << "Cargando imdb_edgelist.csv (CSV, con header, con peso)..." << endl;
    auto t2 = chrono::high_resolution_clock::now();
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);
    auto t3 = chrono::high_resolution_clock::now();
    double msImdb = chrono::duration<double, milli>(t3-t2).count();
    cout << "Tiempo de construccion: " << msImdb << " ms\n" << endl;

    // ========================================================================

    cout << "=== Resumen ===" << endl;
    cout << "Yeast -> Nodos: " << yeast.numNodos() << " | Aristas: " << yeast.numAristas() << endl;
    cout << "IMDB  -> Nodos: " << imdb.numNodos() << " | Aristas: " << imdb.numAristas() << "\n" << endl;

    // ========================================================================
    // PageRank para Yeast y IMDB

    cout << "Calculando PageRank para Yeast..." << endl;
    auto startYeast = chrono::high_resolution_clock::now();
    vector<double> prYeast = calcPageRank(yeast, 0.85, 100, 1e-6);
    auto endYeast = chrono::high_resolution_clock::now();
    double timeYeast = chrono::duration<double, milli>(endYeast - startYeast).count();
    cout << "PageRank Yeast calculado en: " << timeYeast << " ms" << endl;
    
    // Mostrar el Top 5 de proteinas más importantes
    mostrarTopCentralidad(yeast, prYeast, "PageRank Ponderado (Yeast)", 5);

    cout << "\n--------------------------------------------------\n" << endl;

    // Ejecutar PageRank para IMDB
    cout << "Calculando PageRank para IMDB (Red de Actores)..." << endl;
    auto startImdb = chrono::high_resolution_clock::now();
    vector<double> prImdb = calcPageRank(imdb, 0.85, 100, 1e-6);
    auto endImdb = chrono::high_resolution_clock::now();
    double timeImdb = chrono::duration<double, milli>(endImdb - startImdb).count();
    cout << "PageRank IMDB calculado en: " << timeImdb << " ms" << endl;
    
    // Mostrar el Top 5 de actores más importantes
    mostrarTopCentralidad(imdb, prImdb, "PageRank Ponderado (IMDB)", 5);

    return 0;
}