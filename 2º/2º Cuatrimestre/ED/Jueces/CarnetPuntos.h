#ifndef CARNETPUNTOS_H
#define CARNETPUNTOS_H


#include <iostream>
#include <unordered_map>

using namespace std;
using dni = string;
using puntos = int;

class carnetPuntos {

private:

	unordered_map<dni, puntos> dgt;
	unordered_map<puntos, int> cuantosP;

public:

	carnetPuntos(){}

	void nuevo(string DNI) {

		if (dgt.count(DNI) == 1) {
			throw domain_error("Conductor duplicado");
		}
		else {

			dgt.insert({ DNI, 15 });
			cuantosP[15]++;
		}
	}

	void quitar(string DNI, int puntos) {

		auto it = dgt.find(DNI);

		if (it == dgt.cend()) {
			throw domain_error("Conductor inexistente");
		}
		else {

			cuantosP[it->second]--;

			it->second -= puntos;

			if(it->second < 0) it->second = 0;

			cuantosP[it->second]++;
		}
	}

	int consultar(string DNI) {

		auto it = dgt.find(DNI);

		if (it == dgt.cend()) {
			throw domain_error("Conductor inexistente");
		}
		else {

			return it->second;
		}
	}

	int cuantos_con_puntos(int p) {

		if (p < 0 || p >15) {
			throw domain_error("Puntos no validos");
		}
		else {

			if (cuantosP.count(p) == 0) {
				cuantosP[p] = 0;
			}

			return cuantosP[p];
		}
	}

};

#endif
