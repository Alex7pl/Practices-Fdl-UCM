#include "listaproductos.h"
#include "producto.h"

#include <iostream>
#include <fstream>
using namespace std;



void cargarInventario(string nombreFich, tInventario &inv, bool &ok) {
   
	ifstream archivo;
	int i = 0;
	bool encontrado = false;
	int codigo = 0;
	inv.numProds = 0;
	
	archivo.open("inventario.txt");

	if (archivo.is_open()) {

		while (i < MAX_PRODS && encontrado == false) {

			archivo >> codigo;

			if (codigo == -1) {
				encontrado = true;
			}
			else {

				inv.productos[i].codigo = codigo;

				archivo >> inv.productos[i].nombre >> inv.productos[i].numUnids >> inv.productos[i].precio;

				i++;
				inv.numProds++;
			}

		}

		ok = true;
	}
	else {
		
		ok = false;
	}
	archivo.close();
}

void guardarInventario(string nombreFich, const tInventario& inv) {
    
}

int buscarProducto(tInventario inv, int codigoProd) {
   
	int posicion = 0;
	bool encontrado = false;

	while (posicion < inv.numProds && encontrado == false) {

		if (codigoProd == inv.productos[posicion].codigo) {
			encontrado = true;
		}
		else {
			posicion++;
		}
	}

	if (encontrado == false) {
		cout << "No se ha podido encontrar su producto \n";
	}
	
	return posicion;
}

// auxiliar usado en la implementación de procesarModificaciones
void procesarOperacion(tInventario &inv, char operacion, int codigo, int unidades) {
   
}

void procesarModificaciones(string nombreFich, tInventario &inv, bool &ok) {
   
}

// auxiliar para pruebas
void mostrarInventario(const tInventario& inv) {
	cout << endl << "------------------INVENTARIO------------------" << endl << endl;
	for (int i = 0; i < inv.numProds; i++) {
		mostrarProducto(inv.productos[i]);
		cout << endl;
	}
}