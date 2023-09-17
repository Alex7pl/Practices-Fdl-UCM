#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void encontrarOptimo(vector<vector<int>> const& m, vector<int>& marca, int precioAct, int& mejorPrecio, int k, int fin) {
	for (size_t i = 0; i < marca.size(); i++) {

		if (marca[i] < 3) { //si no he comprado aun 3 objetos en ese supermercado
			precioAct += m[i][k];
			marca[i]++;

			if (k == fin - 1) {
				mejorPrecio = min(precioAct, mejorPrecio);
			}
			else {
				encontrarOptimo(m, marca, precioAct, mejorPrecio, k + 1, fin);
			}

			precioAct -= m[i][k];
			marca[i]--;
		}
	}
}

void resuelveCaso() {

	int f, c, e;

	//proceso la entrada

	cin >> f >> c;

	int mejorPrecio = 0;
	vector<vector<int>> m(f, vector<int>(c));

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			cin >> e;
			m[i][j] = e;
			mejorPrecio += e;
		}
	}

	vector<int> marca(f, 0);
	//resuelvo el problema y muestor la solucion

	encontrarOptimo(m, marca, 0, mejorPrecio, 0, c);

	cout << mejorPrecio << endl;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int n;
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++) {
		resuelveCaso();
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}