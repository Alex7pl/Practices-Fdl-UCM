#ifndef PELICULA_H
#define PELICULA_H

#include <string>
#include <iostream>
#include "horas.h"

using namespace std;

class pelicula {
private: horas _horaComienzo, _duracion, _horaFin; string _titulo;

public:
	pelicula(horas horaC = 0, horas dur = 0, string title = "") :_horaComienzo(horaC), _duracion(dur), _titulo(title) {

		_horaFin = horaC + dur;
	}

	horas horaComienzo() {
		return _horaComienzo;
	}

	horas duracion() {
		return _duracion;
	}

	horas horaFin() {
		return _horaFin;
	}

	string titulo() {
		return _titulo;
	}


	void print(ostream& out = cout)const {
		cout << _horaComienzo << " " << _titulo;
	}

	bool operator <(const pelicula& p) const {
		if (p._horaFin < _horaFin) {
			return false;
		}
		else {
			if (p._horaFin == _horaFin) {
				//para ordenar alfabeticamente en caso de "empate"
				if (p._titulo < _titulo) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return true;
			}
		}

	}
};

/*
inline ostream &operator<<(ostream & out, pelicula const &p){
	p.print(out);
	return out;
}
inline istream &operator >>(istream &out, pelicula &p){
	horas c, d;
	string t;
	cin >> c >> d >> t;
	p = pelicula(c, d, t);
	return out;
}*/
#endif