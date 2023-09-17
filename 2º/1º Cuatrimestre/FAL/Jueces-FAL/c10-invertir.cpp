#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//num > 0
int invertir(int num, int s) {

	if (num < 10) {
		return s * 10 + num;
	}
	else {
		s = s * 10 + num % 10;
		return invertir(num / 10, s);
	}
	
}


bool resuelveCaso() {

	// Lectura de los datos

	int num;
	cin >> num;

	if (num == 0) return false;


	// Calculo del resultado: una funcion aparte
	int sol = invertir(num, 0);

	// Escritura del resultado

	cout << sol << endl;

	return true;
}


int main() {

	// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	// Resolvemos
	while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}