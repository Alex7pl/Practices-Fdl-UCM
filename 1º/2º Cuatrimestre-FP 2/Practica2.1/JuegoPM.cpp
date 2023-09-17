#include "JuegoPM.h"
#include "Matriz.h"
#include "UtilidadesSYS.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void mainJuegoPM(tJuegoPM& jmp) {

	int modo = 1;
	bool jugable = true;

	while (modo != 0) {

		modo = menu();
		
		if (modo != 0) {
			
			jugable = iniciar(jmp, modo);

			if (jugable == true) {

				jugar(jmp);
			}
			else {
				cout << "(Error) No se ha podido abrir el juego..." << endl;
			}
		}
	}

}

int menu() {

	int modo;

	cout << "------------------------------MENU DEL JUEGO-------------------------------" << endl;
	cout << "0: Salir de la aplicación" << endl;
	cout << "1: Jugar al modo 1D" << endl;
	cout << "2: Jugar al modo 2D" << endl;
	cout << "---------------------------------------------------------------------------" << endl;

	cin >> modo;

	return modo;
}

bool iniciar(tJuegoPM& jmp, int modo) {

	bool cargado;

	switch (modo) {
	case 0: cout << "Saliendo del juego...." << endl;
		break;
	case 1: jmp.tipo = "_1D.txt";
		break;
	case 2: jmp.tipo = "_2D.txt";
	}

	cargado = cargar(jmp);
	
	return cargado;
}

bool cargar(tJuegoPM& jmp) {

	bool cargado;
	ifstream archivo;
	string nombre;

	cout << "Escriba el nombre del fichero a cargar:" << endl;

	cin >> nombre;

	nombre = nombre + jmp.tipo;

	archivo.open(nombre);

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

void mostrar(tJuegoPM const& jmp) {

	cout << endl << "·Imagen a colocar·" << endl;

	mostrar(jmp.matIni);

	cout << endl << "Número de movimientos: " << jmp.num << endl;

	cout << endl << "·Imagen a conseguir·" << endl;

	mostrar(jmp.matFin);

	cout << endl;

}

void jugar(tJuegoPM& jmp) {

	mostrar(jmp);

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

bool accion(tJuegoPM& jmp) {

	string accion;
	string basura;
	bool i = true;
	int pos1 = 0, pos2 = 0;
	tCoor posicion1, posicion2;

	cout << "Escriba el comando de la accion a realizar (Ejemplo : SF 1 3): ";

	cin >> accion;

	while (((accion == "VD" || accion == "VC" || accion == "VF" || accion == "SD" || accion == "SC" || accion == "SF") && jmp.tipo != "_1D.txt") || ((accion == "VV" || accion == "VH" || accion == "VID" || accion == "RD" || accion == "SA") && jmp.tipo != "_2D.txt")) {

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