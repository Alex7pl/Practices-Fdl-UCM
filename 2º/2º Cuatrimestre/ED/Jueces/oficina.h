#ifndef OFICINA_H
#define OFICINA_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>

using namespace std;

class oficinaEmpleo {

private:

	unordered_map<string, list<string>> empleosL; 
	unordered_map<string, map<string, list<string>::iterator>> personasL;

public:

	oficinaEmpleo(){}

	void altaOficina(string nombre, string empleo) { //O(log n)

		if (personasL[nombre].count(empleo) == 0) {

			auto it = empleosL[empleo].insert(empleosL[empleo].end(), nombre); //O(1)
			personasL[nombre].insert({ empleo, it }); //O(log n)
		}
	}

	string ofertaEmpleo(string empleo) { //O(n)

		auto it = empleosL.find(empleo); //O(1)

		if (it == empleosL.cend()) {
			throw domain_error("No existen personas apuntadas a este empleo"); //O(1)
		}

		string per;

		per = it->second.front(); //O(1)

		for (auto const& a : personasL[per]) { //O(n)

			empleosL[a.first].erase(a.second); //O(1)

			if (empleosL[a.first].empty()) empleosL.erase(a.first); //O(1)
		}

		personasL.erase(per); //O(1)

		return per;
	}

	vector<string> listadoEmpleos(string persona) { //O(n)

		auto it = personasL.find(persona); //O(1)

		if (it == personasL.cend()) {
			throw domain_error("Persona inexistente"); //O(1)
		}

		int i = 0;
		vector<string> sol;

		for (auto const& a : it->second) { //O(n)

			sol.push_back(a.first); //O(1)
			i++;
		}

		return sol;
	}
};
#endif
