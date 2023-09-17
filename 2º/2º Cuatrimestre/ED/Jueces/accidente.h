#ifndef accidente_h
#define accidente_h


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include "fecha.h"


class Accidentes {

private:

	Fecha accF;
	int victimas;

public:

	Accidentes() {};
	Accidentes(Fecha acc, int v) : accF(acc), victimas(v) {};

	int getVictimas() const {
		return victimas;
	}

	Fecha getFechA() const {
		return accF;
	}

};

#endif
