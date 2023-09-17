// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <list>
#include "stack_eda.h"

using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso(ifstream& ar) {

    stack<char> lista;
    string frase;
    if (ar.eof()) return false;

    getline(ar, frase);
    
     int i = 0;
     int tam = frase.size();

    while (i < tam) {

        if (frase[i] == '(' || frase[i] == '[' || frase[i] == '{') {

            lista.push(frase[i]);
        }

        if (frase[i] == ')') {

            if (!lista.empty() && lista.top() == '(') {

                lista.pop();
            }
            else {
                lista.push(frase[i]);
            }
        }

        if (frase[i] == ']') {

            if (!lista.empty() && lista.top() == '[') {

                lista.pop();
            }
            else {
                lista.push(frase[i]);
            }
        }

        if (frase[i] == '}') {

            if (!lista.empty() && lista.top() == '{') {

                lista.pop();
            }
            else {
                lista.push(frase[i]);
            }
        }

        i++;
    }

    if (lista.empty()) cout << "SI\n";
    else cout << "NO\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
     ifstream ar("datos.txt");
    while (resuelveCaso(ar))
        ;
        

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
