# include < iostream >
# include < fstream >
# include < cstring >
# include < string >
# include "Hora.h"

using namespace std;

bool resuelveCaso() {


	int contador, h, m, s;

	string hora1, hora2;

	cin >> contador;

	try {

		for (int i = 0; i < contador; i++) {

			cin >> hora1 >> hora2;
		}

	}
	catch (std::invalid_argument& ia) {
		std::cout << ia.what() << '\n';
	}


	return false;
}

int main() {

	# ifndef DOMJUDGE
		std::ifstream in(" datos .txt ");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	# endif

	while (resuelveCaso()) {}

	#ifndef DOMJUDGE 
		std::cin.rdbuf(cinbuf);
		system(" PAUSE ");
	# endif



	return 0;
}