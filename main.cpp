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

     cout << "=== Resumen ===" << endl;
     cout << "Yeast -> Nodos: " << yeast.numNodos() << " | Aristas: " << yeast.numAristas() << endl;
     cout << "IMDB   -> Nodos: " << imdb.numNodos() << " | Aristas: " << imdb.numAristas() << "\n"
          << endl;

     // ========================================================================
     // 1. Degree Centrality
     // ========================================================================
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
     // 2. Betweenness Centrality
     // ========================================================================
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
     // 3. Closeness Centrality
     // ========================================================================
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

     cout << "\n--------------------------------------------------\n"
          << endl;

     // ========================================================================
     // 4. PageRank
     // ========================================================================
     cout << "Calculando PageRank para Yeast..." << endl;
     auto startYeastPR = chrono::high_resolution_clock::now();
     vector<double> prYeast = calcPageRank(yeast, 0.85, 100, 1e-6);
     auto endYeastPR = chrono::high_resolution_clock::now();
     double timeYeastPR = chrono::duration<double, milli>(endYeastPR - startYeastPR).count();
     cout << "PageRank Yeast calculado en: " << timeYeastPR << " ms" << endl;
     mostrarTopCentralidad(yeast, prYeast, "PageRank Ponderado (Yeast)", 5);

     cout << "\n--------------------------------------------------\n"
          << endl;

     cout << "Calculando PageRank para IMDB (Red de Actores)..." << endl;
     auto startImdbPR = chrono::high_resolution_clock::now();
     vector<double> prImdb = calcPageRank(imdb, 0.85, 100, 1e-6);
     auto endImdbPR = chrono::high_resolution_clock::now();
     double timeImdbPR = chrono::duration<double, milli>(endImdbPR - startImdbPR).count();
     cout << "PageRank IMDB calculado en: " << timeImdbPR << " ms" << endl;
     mostrarTopCentralidad(imdb, prImdb, "PageRank Ponderado (IMDB)", 5);

     cout << "\n--------------------------------------------------\n"
          << endl;

     // ========================================================================
     // 5. Average Shortest Path Length (ASPL)
     // ========================================================================
     cout << "Calculando Longitud Promedio del Camino Mas Corto para Yeast..." << endl;
     auto startYeastASPL = chrono::high_resolution_clock::now();
     double asplYeast = calcAverageShortestPath(yeast);
     auto endYeastASPL = chrono::high_resolution_clock::now();
     double timeYeastASPL = chrono::duration<double, milli>(endYeastASPL - startYeastASPL).count();
     cout << "ASPL Yeast calculado en: " << timeYeastASPL << " ms" << endl;
     cout << "Distancia promedio entre proteinas en Yeast: " << asplYeast << " saltos\n"
          << endl;

     cout << "--------------------------------------------------\n"
          << endl;

     cout << "Calculando Longitud Promedio del Camino Mas Corto para IMDB..." << endl;
     auto startImdbASPL = chrono::high_resolution_clock::now();
     double asplImdb = calcAverageShortestPath(imdb);
     auto endImdbASPL = chrono::high_resolution_clock::now();
     double timeImdbASPL = chrono::duration<double, milli>(endImdbASPL - startImdbASPL).count();
     cout << "ASPL IMDB calculado en: " << timeImdbASPL << " ms" << endl;
     cout << "Distancia promedio entre actores en IMDB: " << asplImdb << " saltos\n"
          << endl;

     cout << "--------------------------------------------------\n"
          << endl;

     // ========================================================================
     // 6. Global Clustering Coefficient (Transitividad)
     // Evalúa la probabilidad global de que si A se conecta con B y B con C,
     // entonces A se conecte con C, indicando la densidad de comunidades cerradas.
     // ========================================================================
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
     // 7. Subgraph Centrality
     // Mide la importancia de un nodo según cuántas veces es parte de un ciclo.
     // ========================================================================
     cout << "Calculando Centralidad de Subgrafo para Yeast..." << endl;
     auto startYeastSC = chrono::high_resolution_clock::now();
     vector<double> scYeast = calcSubgraphCentrality(yeast);
     auto endYeastSC = chrono::high_resolution_clock::now();
     double timeYeastSC = chrono::duration<double, milli>(endYeastSC - startYeastSC).count();
     cout << "Centralidad de Subgrafo Yeast calculada en: " << timeYeastSC << " ms" << endl;
     mostrarTopCentralidad(yeast, scYeast, "Centralidad de Subgrafo (Yeast)", 5);

     cout << "\n--------------------------------------------------\n"
          << endl;

     cout << "Calculando Centralidad de Subgrafo para IMDB..." << endl;
     auto startImdbSC = chrono::high_resolution_clock::now();
     vector<double> scImdb = calcSubgraphCentrality(imdb);
     auto endImdbSC = chrono::high_resolution_clock::now();
     double timeImdbSC = chrono::duration<double, milli>(endImdbSC - startImdbSC).count();
     cout << "Centralidad de Subgrafo IMDB calculada en: " << timeImdbSC << " ms" << endl;
     mostrarTopCentralidad(imdb, scImdb, "Centralidad de Subgrafo (IMDB)", 5);

     cout << "\n--------------------------------------------------\n"
          << endl;
     return 0;
}