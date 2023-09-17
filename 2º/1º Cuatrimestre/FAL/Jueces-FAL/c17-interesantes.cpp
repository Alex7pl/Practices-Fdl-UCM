#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*COSTE (caso peor):
*
*			k				n = 0
*	T(n):
*			T(n/2) + k'		n >= 1
*
*
*	O(logn)
*/

//Pre: 0 <= i <= j <= N - 1 && forall u: 0 <= u < longitud(lista) - 1: lista[u] < lista[u + 1]
bool interesante(int num, int& suma) {

	if (num < 10) {

		bool es = true;

		if (suma % num != 0) {

			es = false;
		}

		suma = num;

		return es;
	}
	else {

		bool es = true;

		int toca = num % 10;

		if (toca == 0) {

			es = false;
		}

		if (suma != 0) {

			if (suma % toca != 0) {

				es = false;
			}
		}

		suma += toca;

		bool sol = interesante(num / 10, suma);

		bool es2 = true;

		if (suma % toca != 0) {

			es2 = false;
		}

		suma += toca;

		return es && sol && es2;
	}
}
//Post: {(forone u: 0 ≤ u < num: v[u] = b + u && sol = u) || (forall z: 0 ≤ z < num : b != v[z] && sol = −1)}


void resuelveCaso() {

	// Lectura de los datos

	int num;
	cin >> num;

	int suma = 0;

	// Calculo del resultado: una funcion aparte
	bool sol = interesante(num, suma);

	// Escritura del resultado
	if (sol)
		cout << "SI" << endl;
	else
		cout << "NO" << endl;
}


int main() {

	// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	// Resolvemos
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}