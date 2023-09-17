#ifndef AUTOESCUELA_H
#define AUTOESCUELA_H

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

class autoescuela {

private:

	unordered_map<string, pair<string, int>> consultarA;
	unordered_map<string, map<string, int>> consultarP;

public:

	autoescuela(){}

	void alta(string a, string p) {

		if (!consultarA.count(a)) { 
			consultarP[p].insert({ a, 0 }); 
			consultarA.insert({ a, {p, 0} }); 
		}
		else {
			consultarP[consultarA.find(a)->second.first].erase(a); 
			consultarP[p].insert({ a, consultarA.find(a)->second.second });
			consultarA.find(a)->second.first = p;
		}
	}

	bool es_alumno(string a, string p) {

		return consultarA.at(a).first == p;
	}

	int puntuacion(string a) {

		auto it = consultarA.find(a);

		if (it == consultarA.cend()) {
			throw domain_error("El alumno " + a + " no esta matriculado");
		}
		else {
			return it->second.second;
		}
	}

	void actualizar(string a, int n) {

		if (!consultarA.count(a)) { 
			throw domain_error("El alumno " + a + " no esta matriculado");
		}
		else if (n != 0) {
			consultarA[a].second += n; 
			consultarP[consultarA[a].first].find(a)->second = consultarA[a].second; 
		}
	}

	void aprobar(string a) {

		auto it = consultarA.find(a);

		if (it == consultarA.cend()) {
			throw domain_error("El alumno " + a + " no esta matriculado");
		}
		else {

			consultarP[it->second.first].erase(a);
			consultarA.erase(a);
		}
	}

	vector<string> examen(string p, int n) const {

		vector<string> alumnos;

		if (consultarP.count(p) == 1) {

			for (auto const& a : consultarP.find(p)->second) {

				if (a.second >= n) {
					alumnos.push_back(a.first);
				}
			}
		}

		return alumnos;
	}
};


#endif
