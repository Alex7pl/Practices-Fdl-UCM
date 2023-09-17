#ifndef PUZZLE_H
#define PUZZLE_H

#include "Matriz.h"

typedef struct {
	std::string tipo;
	int num;
	tMatrizChar matIni, matFin;
	std::string nombrePuzzle;
	std::string nombreFichero;
} tPuzzle;

bool cargar(tPuzzle& jmp);
void mostrar(const tPuzzle& jmp);
void jugar(tPuzzle& jmp, int modo);
bool accion(tPuzzle& jmp);






#endif
