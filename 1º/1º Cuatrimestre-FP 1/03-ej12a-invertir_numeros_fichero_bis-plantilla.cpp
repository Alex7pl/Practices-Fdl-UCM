#include <iostream>
#include <fstream>
using namespace std;


int main() {

    int valor;
    ifstream archivoInput;
    ofstream archivoOutput;

    // apertura del fichero de entrada
    archivoInput.open("input.txt");
    if (!archivoInput.is_open())
        cout << "ERROR DE APERTURA DE ARCHIVO DE ENTRADA" << endl;
    else {
        // apertura del fichero de salida
        archivoOutput.open("output.txt");

        if (!archivoOutput.is_open()) {
            cout << "ERROR DE APERTURA DE ARCHIVO DE SALIDA" << endl;
            archivoInput.close();
        }
        else { // abiertos ambos archivos

            // INTRODUCE AQUÍ TU CÓDIGO
			
			while (!archivoInput.eof()) {
				
				archivoInput >> valor;
				
				if (valor < 0) {
				
					valor = 0;
            		
				}
				else {
					
					while (valor != 0) {
					
            			archivoOutput << valor % 10 ;
            			valor = valor / 10;
            		
					}
					
					archivoOutput << endl;
				}
			}
            // cierre del fichero de salida       
            archivoOutput.close();
        }

        // cierre del archivo de entrada
        archivoInput.close();
    }
    return 0;

}

