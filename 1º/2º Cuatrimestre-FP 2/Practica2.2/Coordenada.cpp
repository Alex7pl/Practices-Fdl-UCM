#include "Coordenada.h"
#include "checkML.h"

using namespace std;

bool operator==(tCoor c1, tCoor c2) {

	bool iguales;

	if (c1.fila == c2.fila && c1.col == c2.col) {

		iguales = true;
	}
	else {
		iguales = false;
	}

	return iguales;
}

bool operator!=(tCoor c1, tCoor c2) {

	bool noiguales;

	if (c1.fila != c2.fila || c1.col != c2.col) {

		noiguales = true;
	}
	else {
		noiguales = false;
	}

	return noiguales;
}

tCoor operator+(tCoor c1, tCoor c2) {

	tCoor c3;

	c3.fila = c1.fila + c2.fila;
	c3.col = c1.col + c2.col;

	return c3;
}