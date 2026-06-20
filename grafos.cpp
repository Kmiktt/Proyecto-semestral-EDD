#include "grafo.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

//busca en el map, si existe devuelve el id, si no lo crea
int Grafo::agregarNodo(const string& nombre) {
    auto it=ids.find(nombre);
    if (it!=ids.end())
        return it->second;
    int nuevoID=nombres.size();
    ids[nombre]=nuevoID;
    nombres.push_back(nombre);
    ady.push_back({});
    vecinosSet.push_back({});
    return nuevoID;
}
void Grafo::agregarArista(const string& u, const string& v, int peso, bool dirigido) {
    if (u==v) return; //para no tener self-loops
    int iu=agregarNodo(u);
    int iv=agregarNodo(v);
    //para no duplicar aristas ya existentes
    if (vecinosSet[iu].count(iv)) return;
    //ady[u][v] = peso; if(!dirigido) ady[v][u] = peso;
    //pero agregando a la lista de vecinos en vez de escribir en una matriz.
    ady[iu].push_back({iv, peso});
    vecinosSet[iu].insert(iv);
    if (!dirigido) {
        ady[iv].push_back({iu, peso});
        vecinosSet[iv].insert(iu);
    }
    cantAristas++;
}
void Grafo::eliminarArista(const string& u, const string& v) {
    int iu=idDe(u);
    int iv=idDe(v);
    if (iu==-1 || iv==-1) return;
    if (!vecinosSet[iu].count(iv)) return;
    auto borrarDe=[](vector<pair<int,int>>& lista, int objetivo) {
        for (size_t i=0; i<lista.size(); i++) {
            if (lista[i].first==objetivo) {
                lista[i]=lista.back();
                lista.pop_back();
                return;
            }
        }
    };
    borrarDe(ady[iu], iv);
    borrarDe(ady[iv], iu);
    vecinosSet[iu].erase(iv);
    vecinosSet[iv].erase(iu);
    cantAristas--;
}
bool Grafo::existeArista(const string& u, const string& v) const {
    int iu=idDe(u);
    int iv=idDe(v);
    if (iu==-1 || iv==-1) return false;
    return vecinosSet[iu].count(iv) > 0;
}
string Grafo::nombreNodo(int id) const {
    return nombres[id];
}
int Grafo::idDe(const string& nombre) const {
    auto it=ids.find(nombre);
    if (it==ids.end()) return-1;
    return it->second;
}
bool Grafo::existeNodo(const string& nombre) const {
    return ids.count(nombre)>0;
}
int Grafo::numNodos() const {
    return nombres.size();
}
int Grafo::numAristas() const {
    return cantAristas;
}
int Grafo::grado(const string& nombre) const {
    int id=idDe(nombre);
    if (id==-1) return -1;
    return ady[id].size();
}
const vector<pair<int,int>>& Grafo::vecinosDe(int id) const {
    return ady[id];
}
//ArmarCvs(): lee un archivo y arma el grafo 
void Grafo::ArmarCsv(const string& archivo, char delim, bool tieneHeader, bool tienePeso, bool dirigido) {
    ifstream arc(archivo);
    if (!arc.is_open()){
        throw runtime_error("No se pudo abrir el archivo: "+archivo);
    }
    string linea;
    if (tieneHeader) {
        getline(arc, linea); // se descarta el encabezado
    }
    long lineasLeidas=0;
    long lineasDescartadas=0;
    while (getline(arc, linea)) {
        if (linea.empty()) continue;
        lineasLeidas++;
        // separar la linea por el delimitador (reemplaza el parseo
        // caracter-por-caracter del ArmarCsv original)
        string from, to, strength;
        size_t pos1=linea.find(delim);
        if (pos1==string::npos) {lineasDescartadas++; continue; }
        from=linea.substr(0, pos1);
        size_t pos2=linea.find(delim, pos1+1);
        if (tienePeso){
            if(pos2==string::npos){ lineasDescartadas++; continue; }
            to=linea.substr(pos1+1, pos2-pos1-1);
            strength=linea.substr(pos2+1);
        } else {
            to=(pos2==string::npos)?linea.substr(pos1+1):linea.substr(pos1+1,pos2-pos1-1);
            strength = "1";
        }
        // regla acordada: descartar nodos invalidos como "-"
        if (from=="-" || to=="-" || from.empty() || to.empty()) {
            lineasDescartadas++;
            continue;
        }
        int peso=1;
        if (tienePeso) {
            try {
                peso=stoi(strength);
            } catch (...) {
                peso=1;
            }
        }
        agregarArista(from, to, peso, dirigido);
    }
    cout << "[" <<archivo<<"] Lineas leidas: " <<lineasLeidas<< " | Descartadas: " <<lineasDescartadas<<" | Nodos: " << numNodos()<<" | Aristas: "<<numAristas()<<endl;
}

//modifique cositas jeje