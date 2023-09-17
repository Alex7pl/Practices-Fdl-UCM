#include <fstream>
#include <string>
# include <unordered_map>
#include <sstream>
#include <iostream>
#include <deque>


using namespace std;

using tabla = unordered_map < int, int >;



void resuelveCaso() {

	int episodios, maximo = 0, ini = 0;

	int num;

	tabla listado;

	cin >> episodios;

	for (int i = 0; i < episodios; i++) {

		cin >> num;

		if (listado.count(num) && listado[num] >= ini) {

			ini = listado[num] + 1;
		}

		listado[num] = i;

		maximo = max(maximo, i - ini + 1);
	}


	cout << maximo << endl;
}

int main() {
# ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std :: cin to casos .txt
# endif

	int casos;

	cin >> casos;

	cin.ignore();

	for (int i = 0; i < casos; i++) {
		resuelveCaso();
	}

# ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system(" PAUSE ");
# endif
	return 0;
}