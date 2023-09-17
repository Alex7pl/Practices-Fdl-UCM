#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int complementar(int num, int s, int d) {

	if (num < 10) {
		return (9 - num) * d + s;
	}
	else {

		s += (9 - (num % 10)) * d;

		d = d * 10;

		return complementar(num / 10, s, d);
	}

}

//num > 0
int invertir(int num, int s) {

	if (num < 10) {
		return s * 10 + (9 - num);
	}
	else {
		s = s * 10 + (9 - num % 10);
		return invertir(num / 10, s);
	}

}


void resuelveCaso() {

	// Lectura de los datos

	int num;
	cin >> num;

	// Calculo del resultado: una funcion aparte
	int sol = complementar(num, 0, 1);

	// Escritura del resultado

	cout << sol << " " << invertir(num, 0) << endl;
}


int main() {

	// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	unsigned int numCasos;
	cin >> numCasos;
	// Resolvemos
	while (numCasos--) {
		resuelveCaso();
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}