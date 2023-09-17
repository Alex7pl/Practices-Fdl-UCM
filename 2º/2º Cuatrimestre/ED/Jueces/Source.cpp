#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

using capitulo = long long int;

using clave = string;
using valor = int;

/*
 * A tener en cuenta:
 *
 * los mapas estan implementados usando arboles binarios equilibrados (por lo que el iterador
 * recorre el arbol en inorden)
 *
 * El orden de las strings es inverso a lo que se pueda pensar, es decir, b < c, a < b etc
 */

void actualizaDiccionario(map<clave, valor> const& d1, map<clave, valor> const& d2) {
	vector<string> add, change, remove;
	auto it1 = d1.cbegin(), it2 = d2.cbegin();

	while (it1 != d1.cend() && it2 != d2.cend()) {
		if (it1->first == it2->first) { //si en ambos diccionarios esta la clave
			if (it1->second != it2->second) { //pero tiene distinto valor
				change.push_back(it1->first);
			}
			it1++;
			it2++;
		}
		else if (it1->first < it2->first) { //si el valor de it1 es < que el valor de it2 quiere decir que el valor de it1 ya no existe en el nuevo diccionario
			remove.push_back(it1->first);
			it1++;
		}
		else if (it1->first > it2->first) { //si el valor de it1 es > que el valor de it2 quiere decir que el valor de it2 es nuevo y no existe en el antiguo diccionario
			add.push_back(it2->first);
			it2++;
		}
	}

	while (it1 != d1.cend()) { //si el diccionario viejo tiene todavia valores, dichos valores son valores quitados del nuevo
		remove.push_back(it1->first);
		it1++;
	}

	while (it2 != d2.cend()) { //si el diccionario nuevo tiene todavia valores, dichos valores son valores agregados al nuevo
		add.push_back(it2->first);
		it2++;
	}

	if (add.size() == 0 && remove.size() == 0 && change.size() == 0) {
		cout << "Sin cambios" << endl;
	}
	else {
		if (add.size() != 0) {
			cout << "+ ";
			for (size_t i = 0; i < add.size(); i++) {
				cout << add[i] << " ";
			}
			cout << endl;
		}
		if (remove.size() != 0) {
			cout << "- ";
			for (size_t i = 0; i < remove.size(); i++) {
				cout << remove[i] << " ";
			}
			cout << endl;
		}
		if (change.size() != 0) {
			cout << "* ";
			for (size_t i = 0; i < change.size(); i++) {
				cout << change[i] << " ";
			}
			cout << endl;
		}
	}

}


void resuelveCaso() {

	string linea, c;
	pair<clave, valor> elem;
	map<clave, valor> dicc1, dicc2;
	int v;

	getline(cin, linea);

	stringstream ss1(linea);

	while (ss1 >> c) {
		ss1 >> v;

		elem.first = c;
		elem.second = v;
		dicc1.insert(elem);
	}

	getline(cin, linea);

	stringstream ss2(linea);

	while (ss2 >> c) {
		ss2 >> v;
		elem.first = c;
		elem.second = v;
		dicc2.insert(elem);
	}

	actualizaDiccionario(dicc1, dicc2);
	cout << "---" << endl;
}

int main() {
# ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std :: cin to casos .txt
# endif

	string aux;
	int n;

	cin >> n;
	getline(cin, aux);

	for (int i = 0; i < n; i++) {
		resuelveCaso();
	}

# ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system(" PAUSE ");
# endif
	return 0;
}