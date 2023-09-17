#ifndef JUEGOPM_H
#define JUEGOPM_H

#include <string>
#include "Matriz.h"

typedef struct {
	std::string tipo;
	int num;
	tMatrizChar matIni, matFin;
} tJuegoPM;

void mainJuegoPM(tJuegoPM& jmp);
int menu();
bool iniciar(tJuegoPM& jmp, int modo);
bool cargar(tJuegoPM& jmp);
void mostrar(tJuegoPM const& jmp);
void jugar(tJuegoPM& jmp);
bool accion(tJuegoPM& jmp);

#endif