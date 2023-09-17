#include <iostream>
#include <fstream>
#include <string>
#include "double_linked_list_ed_plus.h"
using namespace std;



bool resuelveCaso() {

	double_linked_list_ed_plus<int> lista;
	int casos, pivote;

	cin >> casos >> pivote;

	if (!cin) return false;

	int num;

	for (int i = 0; i < casos; i++) {

		cin >> num;
		lista.push_back(num);
	}

	lista.particion(pivote);

	cout << lista;

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