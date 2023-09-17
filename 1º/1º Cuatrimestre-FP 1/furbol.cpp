/* Introduce aquí tus datos
NOMBRE Y APELLIDOS: Alejandro Paniagua López
DNI/NIE: 49150121H
*/


#include <iostream>
#include<string>
#include<fstream>
using namespace std;


// define aquí las CONSTANTES Y TIPOS PEDIDOS 

const int MAX_EQUIPOS = 20;
struct tEquipo {
	string nombre;
	int puntos;
};
typedef tEquipo tLiga[MAX_EQUIPOS];

struct tPartido {
	string equipo1, equipo2;
	int goles1, goles2;
	int puntos1, puntos2;
};
typedef tPartido tJornada[MAX_EQUIPOS];


// prototipos de los subprogramas pedidos en el enunciado (salvo buscar)

bool cargarLiga(tLiga& liga, int& participantes);
bool cargarJornada(tJornada& jornada, int numEquipos, int& partidos);
void mostrarLiga(const tLiga& liga, int participantes);
void actualizarLiga(const tJornada& jornada, tLiga& liga, int partidos, int participantes);
void primeroYultimo(const tLiga& liga, string& primero, string& ultimo, int participantes);
void buscar(const tLiga liga, string equipoBuscado, int participantes);



int main(){
	tLiga liga;
	tJornada jornada;
	string primero, ultimo;
	int participantes = 0;
	int partidos;
	string equipoBuscado, busqueda;
	 

	if (cargarLiga(liga, participantes) == false || cargarJornada(jornada, participantes, partidos) == false) {
		cout << "carga fallida" << endl;
	}
	else {
		cout << "CLASIFICACION...\n";
		mostrarLiga(liga, participantes);
		actualizarLiga(jornada, liga, partidos, participantes);
		cout << "\nCLASIFICACION ACTUALIZADA...\n";
		mostrarLiga(liga, participantes);
		primeroYultimo(liga, primero, ultimo, participantes);
		cout << endl;
		cout << "Primer clasificado: " << primero << endl;
		cout << "Ultimo clasificado: " << ultimo << endl;
		cout << "Quieres buscar la clasificacion de algun equipo(si o no): ";
		cin >> busqueda;

		if (busqueda == "si") {

			cout << "Cual es el equipo que quieres buscar en la clasificacion: ";
			cin >> equipoBuscado;
			
			buscar(liga, equipoBuscado, participantes);
		}
	}
	
	return 0;
}



/*------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------SUBPROGRAMAS--------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------*/


bool cargarLiga(tLiga& liga, int& participantes){

	bool seAbre;
	bool fin = false;
	ifstream archivo;
	string CENTINELA = "FIN";
	string nombre;
	int puntos;

	archivo.open("liga.txt");

	if (archivo.is_open()) {
		seAbre = true;

		while (participantes < MAX_EQUIPOS && fin == false) {

			archivo >> nombre;
			archivo >> puntos;

			if (nombre == CENTINELA) {
				fin = true;
			}
			else {
				liga[participantes].nombre = nombre;
				liga[participantes].puntos = puntos;

				participantes++;
			}
		}
	}
	else {
		seAbre = false;
	}

	return seAbre;
}

bool cargarJornada(tJornada & jornada, int numEquipos, int& partidos){
	
	ifstream archivo;
	bool seAbre;
	int i = 0;

	partidos = numEquipos / 2;

	archivo.open("jornada.txt");

	if (archivo.is_open()) {
		seAbre = true;

		while(i <= partidos) {

			archivo >> jornada[i].equipo1 >> jornada[i].goles1 >> jornada[i].equipo2 >> jornada[i].goles2;
			i++;
		}

		for (int h = 0; h <= i; h++) {

			if (jornada[h].goles1 > jornada[h].goles2) {

				jornada[h].puntos1 = 3;
				jornada[h].puntos2 = 0;
			}
			else if (jornada[h].goles1 < jornada[h].goles2) {

				jornada[h].puntos1 = 0;
				jornada[h].puntos2 = 3;
			}
			else if (jornada[h].goles1 == jornada[h].goles2) {

				jornada[h].puntos1 = 1;
				jornada[h].puntos2 = 1;
			}
		}
		
	}
	else {
		seAbre = false;
	}

	return seAbre;
}

void mostrarLiga(const tLiga & liga, int participantes){ 
	
	for (int i = 0; i < participantes; i++) {

		cout << liga[i].nombre << " " << liga[i].puntos << endl;
	}

}

void actualizarLiga(const tJornada& jornada, tLiga& liga, int partidos, int participantes) { 
	
	for (int i = 0; i < partidos; i++) {

		for (int h = 0; h < participantes; h++) {

			if (jornada[i].equipo1 == liga[h].nombre) {

				liga[h].puntos = jornada[i].puntos1 + liga[h].puntos;
			}
			else if (jornada[i].equipo2 == liga[h].nombre) {

				liga[h].puntos = jornada[i].puntos2 + liga[h].puntos;
			}
		}
	}
}

void primeroYultimo(const tLiga & liga, string & primero, string & ultimo, int participantes){ 
	
	int mayor = 0;
	int menor = 100;

	for (int i = 0; i < participantes; i++) {

		if (liga[i].puntos >= mayor) {

			mayor = liga[i].puntos;
			primero = liga[i].nombre;
		}
	}

	for (int h = 0; h < participantes; h++) {

		if (liga[h].puntos <= menor) {

			menor = liga[h].puntos;
			ultimo = liga[h].nombre;
		}
	}
}

void buscar(const tLiga liga, string equipoBuscado, int participantes) {

	int i = 0;
	bool encontrado = false;
	int clasificacion = participantes + 1;

	while (i <= participantes && encontrado == false) {

		if (equipoBuscado == liga[i].nombre) {

			encontrado = true;
		}
		else {

			i++;
		}
	}

	for (int h = 0; h <= participantes; h++) {

		if (liga[i].puntos >= liga[h].puntos && liga[i].nombre != liga[h].nombre) {

			clasificacion = clasificacion - 1;
		}
	}

	cout << "Tu equipo se encuentra en el puesto " << clasificacion << endl;
}

