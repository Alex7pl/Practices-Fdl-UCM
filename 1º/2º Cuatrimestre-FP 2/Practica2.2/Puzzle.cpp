#include "Puzzle.h"
#include "Matriz.h"
#include "UtilidadesSYS.h"
#include "checkML.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool cargar(tPuzzle& jmp) {

	bool cargado;
	ifstream archivo;

	archivo.open(jmp.nombreFichero);

	if (archivo.is_open()) {

		cargar(jmp.matIni, archivo);
		cargar(jmp.matFin, archivo);

		archivo >> jmp.num;
		cargado = true;
	}
	else {
		cargado = false;
	}

	return cargado;
}

void mostrar(tPuzzle const& jmp) {

	cout << endl << "·Imagen a colocar·" << endl;

	mostrar(jmp.matIni);

	cout << endl << "Número de movimientos: " << jmp.num << endl;

	cout << endl << "·Imagen a conseguir·" << endl;

	mostrar(jmp.matFin);

	cout << endl;

}

void jugar(tPuzzle& jmp, int modo) {

	mostrar(jmp);

	if (modo == 1) {

		jmp.tipo = "1D";
	}
	else {
		jmp.tipo = "2D";
	}

	while (jmp.num > 0 && jmp.matIni == jmp.matFin == false) {

		if (accion(jmp) == true) {

			jmp.num = jmp.num - 1;

			mostrar(jmp);
		}
		else {
			cout << "Ha ocurrido un error o no se puede realizar el movimiento deseado, vuelva a intentarlo" << endl;
		}
	}

	if (jmp.matIni == jmp.matFin) {
		cout << endl << "·FELICIDADES, HAS GANADO·" << endl;
	}
	else {
		cout << "·Mas suerte para la próxima·" << endl;
	}
}

bool accion(tPuzzle& jmp) {

	string accion;
	string basura;
	bool i = true;
	int pos1 = 0, pos2 = 0;
	tCoor posicion1, posicion2;

	cout << "Escriba el comando de la accion a realizar (Ejemplo : SF 1 3): ";

	cin >> accion;

	while (((accion == "VD" || accion == "VC" || accion == "VF" || accion == "SD" || accion == "SC" || accion == "SF") && jmp.tipo != "1D") || ((accion == "VV" || accion == "VH" || accion == "VID" || accion == "RD" || accion == "SA") && jmp.tipo != "2D")) {

		getline(cin, basura);

		cout << "Vuelva a escribir la accion a realizar:";
		cin >> accion;
	}

	if (accion == "SF") {

		cin >> pos1 >> pos2;

		i = swapF(jmp.matIni, pos1, pos2);
	}
	else if (accion == "SC") {

		cin >> pos1 >> pos2;

		i = swapC(jmp.matIni, pos1, pos2);
	}
	else if (accion == "SD") {

		cin >> pos1;

		i = swapD(jmp.matIni, pos1);
	}
	else if (accion == "VF") {

		cin >> pos1;

		i = voltearF(jmp.matIni, pos1);
	}
	else if (accion == "VC") {

		cin >> pos1;

		i = voltearC(jmp.matIni, pos1);
	}
	else if (accion == "VD") {

		cin >> pos1;

		i = voltearD(jmp.matIni, pos1);
	}
	else if (accion == "VV") {

		voltearV(jmp.matIni);
	}
	else if (accion == "VH") {

		voltearH(jmp.matIni);
	}
	else if (accion == "VID") {

		i = voltearID(jmp.matIni);
	}
	else if (accion == "RD") {

		rotarD(jmp.matIni);
	}
	else {

		cin >> posicion1.fila >> posicion1.col >> posicion2.fila >> posicion2.col;

		i = swapAdy(jmp.matIni, posicion1, posicion2);
	}

	return i;
}
