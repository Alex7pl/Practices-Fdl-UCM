#ifndef HORA
#define HORA

#include <iostream>
#include <array>
#include <stdexcept>

class Hora {

private:

	int horas, minutos, segundos;

	const int MIN_SEG = 60;
	const int HOR_DIAS = 24;

public:

	Hora(){}

	Hora(int h, int m, int s) {

		this->horas = h;
		this->minutos = m;
		this->segundos = s;

		if(h < 0 || h >= HOR_DIAS || 
			m < 0 || m >= MIN_SEG || s < 0 || s >= MIN_SEG) throw std::invalid_argument(" Hora invalida ");
	}

	int get_horas() const { return horas; }
	int get_minutos() const { return minutos; }
	int get_segundos() const { return segundos; }

	Hora& operator =(Hora const& other) {
		if (this != &other) {
			segundos = other.segundos; minutos = other.minutos; horas = other.horas;
		}
		return *this;
	}

	bool operator== (Hora const& a) const{
	
		return this->horas == a.horas && this->minutos == a.minutos && this->segundos == a.segundos;
	}

	bool operator< (Hora const& a) const {

		bool f = true;

		if (this->horas > a.horas) f = true;
		else if (this->horas < a.horas) f = false;
		else {
			if (this->minutos > a.minutos) f = true;
			else if (this->minutos < a.minutos) f = false;
			else {
				if (this->segundos > a.segundos) f = true;
				else f = false;
			}
		}

		return f;
	}

	bool operator <= (Hora const& f) const {
		return *this < f || *this == f;
	}

	bool operator > (Hora const& f) const {
		return !(*this <= f);
	}

	bool operator >= (Hora const& f) const {
		return !(*this < f);
	}


};


inline std::istream& operator>> (std::istream& in, Hora& h) {
	int a, m, d;
	in >> a >> m >> d;
	h = Hora(a, m, d);
	return in;
}

inline std::ostream& operator<< (std::ostream& out, Hora const& h) {
	out << h.get_horas() << ':' << h.get_minutos() << ':' << h.get_segundos() << '\n';
	return out;
}


#endif
