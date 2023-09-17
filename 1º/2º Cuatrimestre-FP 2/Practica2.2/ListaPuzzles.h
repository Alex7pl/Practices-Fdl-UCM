#ifndef LISTAPUZZLES_H
#define LISTAPUZZLES_H

#include "Puzzle.h"

const int MAX_PUZZLES = 100;

typedef tPuzzle* puntPuzzle;
typedef struct {
	puntPuzzle lista[MAX_PUZZLES];
	int cont;
}tListaPuzzles;

typedef tListaPuzzles tPuzzlesReunidos[2];


void inicializar(tPuzzlesReunidos& pr);
bool cargar(tPuzzlesReunidos& pr);
int elegirPuzzle(tListaPuzzles& pr);
void mostrarLista(const tListaPuzzles& pr);
void mostrarCatalogo(const tPuzzlesReunidos& pr); //Para la funcion añadir puzzles
void liberar(tPuzzlesReunidos& pr);
void ordenarCrec(tListaPuzzles& pr);
void ordenarDecr(tListaPuzzles& pr);
void añadirPuzzle(tPuzzlesReunidos& pr);
bool insertarOrdenado(tListaPuzzles& pr, tPuzzle* temp);
bool buscar(const tListaPuzzles& pr, tPuzzle* temp, int& pos);
void guardar(const tPuzzlesReunidos& pr);
#endif
