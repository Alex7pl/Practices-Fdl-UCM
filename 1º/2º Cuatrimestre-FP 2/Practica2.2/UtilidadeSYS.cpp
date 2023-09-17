#include "UtilidadesSYS.h"
#include "checkML.h"
#include <Windows.h>


void chcp1252(){
	system("chcp 1252");
}

void borrar(){
	system("cls");
}

void pausa(){
	system("pause");
}

// paleta de colores (privada)
// negro(0), rojo(12), verde(10), azul(9), amarillo(14), 
// magenta(13), cian2(3), blanco(15), gris(8), cian1(11) 
uint8 colores[10] = { 0, 12, 10, 9, 14, 13, 3, 15, 8, 11 };


void colorCTA(uint8 color, uint8 fondo){  // fondo es un dígito con el que indexar la paleta "colores"
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (colores[fondo] << 4));
}
