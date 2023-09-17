#ifndef HORAS_H
#define HORAS_H

#include <stdexcept>
#include <iostream>
//#include <fstream>

using namespace std;

class horas {
private:
	int _horas, _minutos, _segundos;

public:
	//a la hora de crear un objeto hay que comprobar si se puede crear, es decir
	//si los datos que se dan son correctos o validos
	horas(int h = 0, int m = 0, int s = 0) :_horas(h), _minutos(m), _segundos(s)
	{
		if (h < 0 || h>23 || m < 0 || m>59 || s < 0 || s>59) {
			throw invalid_argument("ERROR");
		}

	}
	//observadoras
	int hora() {
		return _horas;
	}
	int minutos() {
		return _minutos;
	}
	int segundos() {
		return _segundos;
	}

	//definicion de operadores (sobrecarga)
	bool operator <(const horas& h) const {
		//primero miramos las horas
		if (_horas < h._horas) {
			return true;
		}
		else if (_horas > h._horas) {
			return false;
		}
		else {
			//si son iguales, pasamos a los minutos
			if (_minutos < h._minutos) {
				return true;
			}
			else if (_minutos > h._minutos) {
				return false;
			}
			else {
				//miramos los segundos
				if (_segundos < h._segundos) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}

	void print(ostream& out = cout) const {

		if (_horas < 10) {
			out << "0" << _horas << ":";
		}
		else {
			out << _horas << ":";
		}

		if (_minutos > 0) {
			if (_minutos < 10) {
				out << "0" << _minutos << ":";
			}
			else {
				out << _minutos << ":";
			}

		}
		else {
			out << "00:";
		}
		if (_segundos > 0) {
			if (_segundos < 10) {
				out << "0" << _segundos;
			}
			else {
				out << _segundos;
			}

		}
		else {
			out << "00";
		}

	}

	horas operator+ (const horas& h) const {
		horas sum;

		sum._segundos = _segundos + h._segundos;
		if (sum._segundos > 59) {
			sum._minutos++;
			sum._segundos -= 60;
		}

		sum._minutos += _minutos + h._minutos;
		if (sum._minutos > 59) {
			sum._horas++;
			sum._minutos -= 60;
		}

		//si la suma sobrepasa 24h
		sum._horas += _horas + h._horas;
		if (sum._horas > 23) {
			throw invalid_argument("sobrepasa el día");
		}

		return sum;
	}

	bool operator == (const horas& h)const {
		if (h._horas == _horas && h._minutos == _minutos && h._segundos == _segundos) {
			return true;
		}
		else {
			return false;
		}
	}



};

//mostrar

inline ostream& operator<<(ostream& salida, horas const& hora) {
	hora.print(salida);
	return salida;
}

inline istream& operator>> (istream& salida, horas& hora) {
	int h, m, s;
	char aux;
	salida >> h >> aux >> m >> aux >> s;

	hora = horas(h, m, s);
	return salida;
}

#endif
