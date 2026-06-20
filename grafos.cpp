#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

class Grafo {
private:
    //aqui guarda una tabla hash que tiene como llave los nombres y como valor los indices de los nodos
    unordered_map<string, int> ids;
    //aqui guarda la info de los grafos
    vector<string> nombres;
public:
    vector<vector<int>> ady;

    int agregarNodo(const string& nombre) {

        auto it = ids.find(nombre);

        if(it != ids.end())
            return it->second;

        int nuevoID = nombres.size();

        ids[nombre] = nuevoID;
        nombres.push_back(nombre);
        ady.push_back(vector<int>(nuevoID, 0));
        for(auto& fila : ady)
            fila.push_back(0);


        return nuevoID;
    }

    void agregarArista(const int u, const int v,int peso,bool dirigido = false) {

        ady[u][v]=peso;

        if (!dirigido)
            ady[v][u]=peso;
    }

    void ArmarCsv(const string& archivo, bool dirigido=false){
        ifstream arc(archivo);
        char c;
        string from;
        string to;
        string strength;
        from.reserve(32);
        to.reserve(32);
        strength.reserve(8);

        while (arc.get(c)) {

            if(c=='\n'){
                from="";
                to="";
                strength="";
                while (arc.get(c) && c!=','){
                    from+=c;
                }

                while (arc.get(c) && c!=','){
                    to+=c;
                }
                while (arc.get(c) && c!='\n'){
                    strength+=c;
                }
                if (c=='\n') {arc.seekg(-1, ios::cur);}

                if (arc.peek() == EOF)  {break;}
                agregarArista(agregarNodo(from),agregarNodo(to),stoi(strength),dirigido);
            }

        }

    }

    //si es que decidimos colocarle mas informacion podriamos cambiar a que retorne un nodo con su propia info
    string nombreNodo(int id) const {
        return nombres[id];
    }
};

int main() {

    Grafo g;

    g.ArmarCsv("test.csv");

    cout << "Nodos:\n";
    for (int i = 0; i < g.ady.size(); i++) {
        cout << i << ": " << g.nombreNodo(i) << '\n';
    }

    cout << "\nMatriz de adyacencia:\n";
    for (int i = 0; i < g.ady.size(); i++) {
        for (int j = 0; j < g.ady[i].size(); j++) {
            cout << g.ady[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
//oli, es muy tardesito asique mañana modificare este codigo para implementar
//lo de grafos.h ;")