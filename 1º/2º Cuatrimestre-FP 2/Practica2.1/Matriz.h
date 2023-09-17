#ifndef MATRIZ_H
#define MATRIZ_H

#include "UtilidadesSYS.h"
#include "Coordenada.h"
#include <fstream>
#include <iostream>
#include <iomanip>


const int DIM_MAX = 64;
typedef struct {
	int numFilas, numCols;
	uint8 datos[DIM_MAX][DIM_MAX];
} tMatrizChar;

void cargar(tMatrizChar& mat, std::istream& archivo);
bool operator==(tMatrizChar const& mat1, tMatrizChar const& mat2);
void mostrar(tMatrizChar const& mat);

//1D

bool swapF(tMatrizChar& mat, int f1, int f2);
bool swapC(tMatrizChar& mat, int c1, int c2);
bool swapD(tMatrizChar& mat, int d);
bool voltearF(tMatrizChar& mat, int fila);
bool voltearC(tMatrizChar& mat, int columna);
bool voltearD(tMatrizChar& mat, int d);

//2D

void voltearV(tMatrizChar& mat);
void voltearH(tMatrizChar& mat);
bool voltearID(tMatrizChar& mat);
void rotarD(tMatrizChar& mat);
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2);



#endif