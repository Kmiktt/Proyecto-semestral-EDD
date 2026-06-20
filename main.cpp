#include "grafo.h"
#include <iostream>
#include <chrono>

using namespace std;
int main() {
    //yeast es el de las proteinas de levaduras
    //nombre archivo yeast.edgelist
    Grafo yeast;
    cout<<"Cargando yeast.edgelist (TSV, sin header, sin peso)..."<<endl;
    auto t0=chrono::high_resolution_clock::now();
    yeast.ArmarCsv("data/yeast.edgelist", '\t', false, false);
    auto t1=chrono::high_resolution_clock::now();
    double msYeast=chrono::duration<double, milli>(t1-t0).count();
    cout<<"Tiempo de construccion: "<<msYeast<<" ms\n"<<endl;
    //imdb es el de los actores
    //nombre archivo imdb_edgelist.csv
    Grafo imdb;
    cout<<"Cargando imdb_edgelist.csv (CSV, con header, con peso)..."<<endl;
    auto t2=chrono::high_resolution_clock::now();
    imdb.ArmarCsv("data/imdb_edgelist.csv", ',', true, true);
    auto t3=chrono::high_resolution_clock::now();
    double msImdb=chrono::duration<double, milli>(t3-t2).count();
    cout<<"Tiempo de construccion: "<<msImdb<<" ms\n"<<endl;
    //mostrar algunos nodos de ejemplo se imprimen solo los primeros 5 de cada grafo
    cout<<"=== Primeros 5 nodos de yeast ==="<<endl;
    for (int i=0; i<5 && i<yeast.numNodos();i++) {
        cout<<i<<": "<<yeast.nombreNodo(i)<<'\n';
    }
    cout<<"\n=== Primeros 5 nodos de imdb ==="<<endl;
    for (int i=0; i<5 && i<imdb.numNodos(); i++){
        cout<<i<<": "<<imdb.nombreNodo(i)<<'\n';
    }
    cout<<"\n=== Resumen ==="<<endl;
    cout<<"Yeast -> Nodos: "<< yeast.numNodos()<< " | Aristas: "<< yeast.numAristas()<<endl;
    cout<<"IMDB  -> Nodos: "<<imdb.numNodos()<<" | Aristas: "<<imdb.numAristas()<<endl;
    return 0;
}
//si subo los dataset al repositorio se va a buggear ya que pesan mucho :c