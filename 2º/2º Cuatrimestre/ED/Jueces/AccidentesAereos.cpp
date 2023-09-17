#include <iostream>
#include <fstream>
#include <string>
#include "fecha.h"
#include "accidente.h"
using namespace std;



bool resuelveCaso() {

	stack<Accidentes> pila;

	int casos, dia, mes, ano, vict;

	cin >> casos;

	if (!cin) return false;

	char c;

	int i = 0;

	while (i < casos) {

		cin >> dia >> c >> mes >> c >> ano >> vict;

		Fecha f(dia, mes, ano);

		Accidentes acc(f, vict);

		bool encontrado = false;

		while (!encontrado && !pila.empty()) {

			if (vict < pila.top().getVictimas()) {

				cout << pila.top().getFechA();
				pila.push(acc);
				encontrado = true;
			}
			else pila.pop();
		}

		if (pila.empty()) {
			cout << "NO HAY" << endl;
			pila.push(acc);
		}

		i++;
	}

	cout << "---" << endl;

	return true;
}


int main() {
# ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std :: cin to casos .txt
# endif


	while (resuelveCaso()) {}

# ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system(" PAUSE ");
# endif
	return 0;
}