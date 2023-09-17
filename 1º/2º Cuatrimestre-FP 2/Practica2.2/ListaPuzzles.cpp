#include "ListaPuzzles.h"
#include "checkML.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void inicializar(tPuzzlesReunidos& pr) {

	pr[0].cont = 0;
	pr[1].cont = 0;
}

bool cargar(tPuzzlesReunidos& pr) {

	ifstream datos;
	bool abierto = true;

	datos.open("datosPuzzles.txt");

	if (datos.is_open()) {

		for (int i = 0; i < 2; i++) {

			datos >> pr[i].cont;

			for (int h = 0; h < pr[i].cont; h++) {

				char c;

				pr[i].lista[h] = new tPuzzle;
				datos.get(c);

				getline(datos, pr[i].lista[h]->nombrePuzzle);
				datos >> pr[i].lista[h]->nombreFichero;

			}
		}
		abierto = true;
	}
	else {
		abierto = false;
	}

	return abierto;
}

void mostrarLista(const tListaPuzzles& pr) {

	cout << "En esta versión están disponibles los siguientes retos:" << endl << endl;

	for (int i = 0; i < pr.cont; i++) {

		cout << i + 1 << " " << pr.lista[i]->nombrePuzzle << " con un máximo de " << pr.lista[i]->num << " movimientos" << endl;
	}

	cout << endl << "0 Salir" << endl;
	cout << "-1 Mostrar la lista ordenada de menor a mayor" << endl;
	cout << "-2 Mostrar la lista ordenada de mayor a menor" << endl;
}

void mostrarCatalogo(const tPuzzlesReunidos& pr) {

	cout << "Puzzles 1D: " << endl;

	for (int i = 0; i < pr[0].cont; i++) {

		cout << i + 1 << " " << pr[0].lista[i]->nombrePuzzle << " con un máximo de " << pr[0].lista[i]->num << " movimientos" << endl;
	}

	cout << "Puzzles 2D: " << endl;

	for (int i = 0; i < pr[1].cont; i++) {

		cout << i + 1 << " " << pr[1].lista[i]->nombrePuzzle << " con un máximo de " << pr[1].lista[i]->num << " movimientos" << endl;
	}

}

int elegirPuzzle(tListaPuzzles& pr) {

	int opcion = -1;

	while (opcion == -1 || opcion == -2) {

		mostrarLista(pr);

		cout << "Elige un reto: ";
		cin >> opcion;

		switch (opcion) {
		case -1: ordenarCrec(pr);
			break;
		case -2: ordenarDecr(pr);
			break;
		}

	
	}

	return opcion;
}

void liberar(tPuzzlesReunidos& pr) {

	for (int i = 0; i < 2; i++) {
		for (int h = 0; h < pr[i].cont; h++) {

			delete pr[i].lista[h];
		}
	}
}

void ordenarCrec(tListaPuzzles& pr) {


	bool inter = true;
	int i = 0;

	while (i < pr.cont - 1 && inter == true) {

		inter = false;

		for (int j = pr.cont - 1; j > i; j--) {
			if (pr.lista[j]->nombrePuzzle < pr.lista[j - 1]->nombrePuzzle) {

				puntPuzzle tmp;

				tmp = pr.lista[j];
				pr.lista[j] = pr.lista[j - 1];
				pr.lista[j - 1] = tmp;
				inter = true;
			}

		}

		if (inter == true) {
			i++;
		}
	}
}

void ordenarDecr(tListaPuzzles& pr) {

	puntPuzzle temp;
	bool inter = true;
	int i = 0;

	while (i < pr.cont&& inter == true) {

		inter = false;

		for (int j = pr.cont - 1; j > i; j--) {
			if (pr.lista[j]->nombrePuzzle > pr.lista[j - 1]->nombrePuzzle) {
				temp = pr.lista[j];
				pr.lista[j] = pr.lista[j - 1];
				pr.lista[j - 1] = temp;
				inter = true;
			}

		}
		if (inter == true) {
			i++;
		}
	}
}

void añadirPuzzle(tPuzzlesReunidos& pr) {

	puntPuzzle temp;
	bool cargado = true;
	string i;
	temp = new tPuzzle;

	mostrarCatalogo(pr);

	cout << endl << "Escribe el nombre del nuevo puzzle: ";

	char c;
	cin.get(c);
	getline(cin,temp->nombrePuzzle);

	cout << endl << "Ecribe ahora el nombre del fichero que contiene el puzzle: ";
	cin >> temp->nombreFichero;

	cout << endl << "Escribe ahora el tipo de puzzle que desea introducir(1D o 2D): ";
	cin >> temp->tipo;

	cargado = cargar(*temp);

	if (temp->tipo == "1D") {

		cargado = insertarOrdenado(pr[0], temp);
	}
	else {
		cargado = insertarOrdenado(pr[1], temp);
	}

	if (cargado == false) {
		mostrarCatalogo(pr);
	}
	else {
		cout << "No se ha podido cargar el puzzle deseado" << endl;
	}

}

bool insertarOrdenado(tListaPuzzles& pr, tPuzzle* temp) {

	bool sePuede = true;
	int lugar = 0;

	sePuede = buscar(pr, temp, lugar);

	if (sePuede == false && pr.cont < 100) {

		pr.lista[pr.cont] = new tPuzzle;

		pr.lista[pr.cont] = temp;

		pr.cont = pr.cont + 1;
	}

	return sePuede;

}

bool buscar(const tListaPuzzles& pr, tPuzzle* temp, int& pos) {

	int inicio = 0;
	int final = pr.cont - 1;
	int mitad = 0;
	bool encontrado = false;

	while (inicio < final && encontrado == false) {

		mitad = (final + inicio) / 2;

		if (temp->nombrePuzzle == pr.lista[mitad]->nombrePuzzle) {
			
			encontrado = true;
		}
		else if (temp->nombrePuzzle < pr.lista[mitad]->nombrePuzzle) {

			final = mitad - 1;
		}
		else {

			inicio = mitad + 1;
		}
	}

	pos = mitad;

	return encontrado;

}

void guardar(const tPuzzlesReunidos& pr) {

	ofstream archivo;

	archivo.open("datosPuzzles.txt");

	if (archivo.is_open()) {

		for (int i = 0; i < 2; i++) {

			archivo << pr[i].cont << endl;

			for (int h = 0; h < pr[i].cont; h++) {


				archivo << pr[i].lista[h]->nombrePuzzle << endl;
				archivo << pr[i].lista[h]->nombreFichero << endl;

			}
		}

	}

	archivo.close();
}
