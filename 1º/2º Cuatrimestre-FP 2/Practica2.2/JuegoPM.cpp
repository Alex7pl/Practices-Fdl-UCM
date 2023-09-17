#include "JuegoPM.h"
#include "Puzzle.h"
#include "ListaPuzzles.h"
#include "Matriz.h"
#include "UtilidadesSYS.h"

#include <iostream>
#include <string>
#include <fstream>
#include "checkML.h"
using namespace std;


void mainPuzzlesReunidos() {

	int modo = 1;
	int opcion;
	bool cargado;
	tPuzzlesReunidos pr;

	inicializar(pr);
	cargado = cargar(pr);

	for (int i = 0; i < 2; i++) {
		for (int h = 0; h < pr[i].cont; h++) {
			cargado = cargar(*pr[i].lista[h]);
		}
	}

	while (modo != 0) {

		modo = menu();

		if (modo == 0) { 
			cout << "Saliendo del juego...." << endl;
		}

		if (modo == 3) {

			añadirPuzzle(pr);
		}
		
		if (modo == 1 || modo == 2) {
			
			opcion = elegirPuzzle(pr[modo - 1]);
			
			if (opcion != 0) {

				jugar(*pr[modo - 1].lista[opcion - 1], modo);
				cargar(*pr[modo - 1].lista[opcion - 1]);
			}
		}
	}

	guardar(pr);
	liberar(pr);
}

int menu() {

	int modo;

	cout << "------------------------------MENU DEL JUEGO-------------------------------" << endl;
	cout << "0: Salir de la aplicación" << endl;
	cout << "1: Jugar al modo 1D" << endl;
	cout << "2: Jugar al modo 2D" << endl;
	cout << "3: Añadir un nuevo puzzle" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "Seleccione un modo: ";

	cin >> modo;

	return modo;
}

