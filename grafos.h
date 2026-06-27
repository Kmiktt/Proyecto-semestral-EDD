#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Grafo{
private:
	//tiene como clave los nombres y como valor los indices de los nodos
	unordered_map<string, int> ids;
	//guarda el nombre real de cada nodo, indexado por su id
	vector<string> nombres;
	//lista de adyacencia con ady[i] = lista de pares (vecino, peso) del nodo i
	vector<vector<pair<int,int>>> ady;
	//para revisar si existe la arista sin tener que recorrer toda la lista
	vector<unordered_set<int>> vecinosSet;
    int cantAristas=0;
public:
	//si el nodo existe devuelve su id y si no lo crea y devuelve la id
	int agregarNodo(const string& nombre);
	void agregarArista(const string& u, const string& v, int peso=1, bool dirigido=false);
	//para eliminar aristas:
	void eliminarArista(const string& u, const string& v);
    bool existeArista(const string& u, const string& v) const;
    //nombre(id)->nombre
    string nombreNodo(int id) const;
    int idDe(const string& nombre) const;
    bool existeNodo(const string& nombre) const;
    int numNodos() const;
    int numAristas() const;
    int grado(const string& nombre) const;
    //recorrer vecinos de un nodo por id
    const vector<pair<int,int>>& vecinosDe(int id) const;
    void ArmarCsv(const string& archivo, char delim, bool tieneHeader, bool tienePeso, bool dirigido=false);
};
#endif