#include "grafos.h"
#include "algoritmos.h"
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int main()
{

    // yeast es el de las proteinas de levaduras
    Grafo yeast;
    cout << "Cargando yeast.edgelist (TSV, sin header, sin peso)..." << endl;
    auto t0 = chrono::high_resolution_clock::now();
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);
    auto t1 = chrono::high_resolution_clock::now();
    double msYeast = chrono::duration<double, milli>(t1 - t0).count();
    cout << "Tiempo de construccion: " << msYeast << " ms\n"
         << endl;

    // imdb es el de los actores
    Grafo imdb;
    cout << "Cargando imdb_edgelist.csv (CSV, con header, con peso)..." << endl;
    auto t2 = chrono::high_resolution_clock::now();
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);
    auto t3 = chrono::high_resolution_clock::now();
    double msImdb = chrono::duration<double, milli>(t3 - t2).count();
    cout << "Tiempo de construccion: " << msImdb << " ms\n"
         << endl;

    // ========================================================================

    cout << "=== Resumen ===" << endl;
    cout << "Yeast -> Nodos: " << yeast.numNodos() << " | Aristas: " << yeast.numAristas() << endl;
    cout << "IMDB  -> Nodos: " << imdb.numNodos() << " | Aristas: " << imdb.numAristas() << "\n"
         << endl;

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

    cout << "\n--------------------------------------------------\n"
         << endl;

    // Ejecutar PageRank para IMDB
    cout << "Calculando PageRank para IMDB (Red de Actores)..." << endl;
    auto startImdb = chrono::high_resolution_clock::now();
    vector<double> prImdb = calcPageRank(imdb, 0.85, 100, 1e-6);
    auto endImdb = chrono::high_resolution_clock::now();
    double timeImdb = chrono::duration<double, milli>(endImdb - startImdb).count();
    cout << "PageRank IMDB calculado en: " << timeImdb << " ms" << endl;

    // Mostrar el Top 5 de actores más importantes
    mostrarTopCentralidad(imdb, prImdb, "PageRank Ponderado (IMDB)", 5);

    cout << "\n--------------------------------------------------\n"
         << endl;

    // ========================================================================
    // Global Clustering Coefficient para Yeast y IMDB

    cout << "Calculando Coeficiente de Agrupamiento Global para Yeast..." << endl;
    auto startYeastCC = chrono::high_resolution_clock::now();
    double ccGlobalYeast = calcGlobalClusteringCoefficient(yeast);
    auto endYeastCC = chrono::high_resolution_clock::now();
    double timeYeastCC = chrono::duration<double, milli>(endYeastCC - startYeastCC).count();

    cout << "Clustering Coefficient Yeast calculado en: " << timeYeastCC << " ms" << endl;
    cout << "Coeficiente Global (Transitividad) de Yeast: " << ccGlobalYeast
         << " (" << ccGlobalYeast * 100.0 << "%)\n"
         << endl;

    cout << "--------------------------------------------------\n"
         << endl;

    cout << "Calculando Coeficiente de Agrupamiento Global para IMDB..." << endl;
    auto startImdbCC = chrono::high_resolution_clock::now();
    double ccGlobalImdb = calcGlobalClusteringCoefficient(imdb);
    auto endImdbCC = chrono::high_resolution_clock::now();
    double timeImdbCC = chrono::duration<double, milli>(endImdbCC - startImdbCC).count();

    cout << "Clustering Coefficient IMDB calculado en: " << timeImdbCC << " ms" << endl;
    cout << "Coeficiente Global (Transitividad) de IMDB: " << ccGlobalImdb
         << " (" << ccGlobalImdb * 100.0 << "%)\n"
         << endl;

    cout << "\n--------------------------------------------------\n"
         << endl;

    // ========================================================================
    // Centralidad de Grado para Yeast y IMDB

    cout << "Calculando Centralidad de Grado para Yeast..." << endl;
    auto startYeastDC = chrono::high_resolution_clock::now();
    vector<double> dcYeast = calcDegreeCentrality(yeast);
    auto endYeastDC = chrono::high_resolution_clock::now();
    double timeYeastDC = chrono::duration<double, milli>(endYeastDC - startYeastDC).count();
    cout << "Centralidad de Grado Yeast calculada en: " << timeYeastDC << " ms" << endl;
    mostrarTopCentralidad(yeast, dcYeast, "Centralidad de Grado Normalizada (Yeast)", 5);

    cout << "\n--------------------------------------------------\n"
         << endl;

    cout << "Calculando Centralidad de Grado para IMDB..." << endl;
    auto startImdbDC = chrono::high_resolution_clock::now();
    vector<double> dcImdb = calcDegreeCentrality(imdb);
    auto endImdbDC = chrono::high_resolution_clock::now();
    double timeImdbDC = chrono::duration<double, milli>(endImdbDC - startImdbDC).count();
    cout << "Centralidad de Grado IMDB calculada en: " << timeImdbDC << " ms" << endl;
    mostrarTopCentralidad(imdb, dcImdb, "Centralidad de Grado Normalizada (IMDB)", 5);

    cout << "\n--------------------------------------------------\n"
         << endl;

    // ========================================================================
    // Centralidad de Intermediación para Yeast y IMDB

    cout << "Calculando Centralidad de Intermediación para Yeast..." << endl;
    auto startYeastBC = chrono::high_resolution_clock::now();
    vector<double> bcYeast = calcBetweennessCentrality(yeast);
    auto endYeastBC = chrono::high_resolution_clock::now();
    double timeYeastBC = chrono::duration<double, milli>(endYeastBC - startYeastBC).count();
    cout << "Centralidad de Intermediación Yeast calculada en: " << timeYeastBC << " ms" << endl;
    mostrarTopCentralidad(yeast, bcYeast, "Centralidad de Intermediacion (Yeast)", 5);

    cout << "\n--------------------------------------------------\n"
         << endl;

    cout << "Calculando Centralidad de Intermediación para IMDB..." << endl;
    auto startImdbBC = chrono::high_resolution_clock::now();
    vector<double> bcImdb = calcBetweennessCentrality(imdb);
    auto endImdbBC = chrono::high_resolution_clock::now();
    double timeImdbBC = chrono::duration<double, milli>(endImdbBC - startImdbBC).count();
    cout << "Centralidad de Intermediación IMDB calculada en: " << timeImdbBC << " ms" << endl;
    mostrarTopCentralidad(imdb, bcImdb, "Centralidad de Intermediacion (IMDB)", 5);

    cout << "\n--------------------------------------------------\n"
         << endl;

    // ========================================================================
    // Centralidad de Cercanía para Yeast y IMDB

    cout << "Calculando Centralidad de Cercanía para Yeast..." << endl;
    auto startYeastCLC = chrono::high_resolution_clock::now();
    vector<double> clcYeast = calcClosenessCentrality(yeast);
    auto endYeastCLC = chrono::high_resolution_clock::now();
    double timeYeastCLC = chrono::duration<double, milli>(endYeastCLC - startYeastCLC).count();
    cout << "Centralidad de Cercanía Yeast calculada en: " << timeYeastCLC << " ms" << endl;
    mostrarTopCentralidad(yeast, clcYeast, "Centralidad de Cercania (Yeast)", 5);

    cout << "\n--------------------------------------------------\n"
         << endl;

    cout << "Calculando Centralidad de Cercanía para IMDB..." << endl;
    auto startImdbCLC = chrono::high_resolution_clock::now();
    vector<double> clcImdb = calcClosenessCentrality(imdb);
    auto endImdbCLC = chrono::high_resolution_clock::now();
    double timeImdbCLC = chrono::duration<double, milli>(endImdbCLC - startImdbCLC).count();
    cout << "Centralidad de Cercanía IMDB calculada en: " << timeImdbCLC << " ms" << endl;
    mostrarTopCentralidad(imdb, clcImdb, "Centralidad de Cercania (IMDB)", 5);

    return 0;
}