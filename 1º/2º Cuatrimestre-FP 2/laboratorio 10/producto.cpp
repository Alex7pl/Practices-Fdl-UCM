#include "producto.h"
#include <iostream>
#include <iomanip> // para setw()
using namespace std;

void mostrarProducto(tProducto prod) {
	
	cout << "Codigo del producto: " << prod.codigo << endl;
	cout << "Nombre del producto: " << prod.nombre << endl;
	cout << "Numero de unidades disponibles: " << prod.numUnids << endl;
	cout << "Precio por unidad: " << prod.precio << " €" << endl;
}

void aArchivo(ofstream& fOut, tProducto prod) {
	
}