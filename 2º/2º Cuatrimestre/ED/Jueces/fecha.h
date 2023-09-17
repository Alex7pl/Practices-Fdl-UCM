#ifndef FECHA_H
#define FECHA_H


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>

using namespace std;

class Fecha {

private:

	int dia, mes, ano;

public:

	Fecha() {};

	Fecha(int d, int m, int a) : dia(d), mes(m), ano(a) {}

	int getDia() const {
		return dia;
	}

	int getMes() const {
		return mes;
	}

	int getAno() const {
		return ano;
	}

};

inline std::ostream& operator<< (std::ostream& out, Fecha const& h) {
	out << std::setfill('0') << std::setw(2) << h.getDia() << '/' << std::setfill('0') << std::setw(2) << h.getMes() << '/' << std::setfill('0') << std::setw(4) << h.getAno() << endl;
	return out;
}


#endif
