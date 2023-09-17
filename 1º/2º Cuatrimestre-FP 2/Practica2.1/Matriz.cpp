#include "Matriz.h"
#include "UtilidadesSYS.h"


using namespace std;



void cargar(tMatrizChar& mat, std::istream& archivo) {

	archivo >> mat.numFilas >> mat.numCols;

	for (int i = 0; i < mat.numFilas; i++) {

		for (int j = 0; j < mat.numCols; j++) {

			archivo >> mat.datos[i][j];
		}
	}
}

void mostrar(tMatrizChar const& mat) {

	cout << " ";

	for (int i = 0; i < mat.numCols; i++) {

		cout << setw(2) << i;
	}

	cout << endl;

	for (int j = 0; j < mat.numFilas; j++) {

		cout << setw(2) << j;

		for (int i = 0; i < mat.numCols; i++) {

			char x = mat.datos[j][i];
			int y = x - int('0');

			colorCTA(y, y);

			cout << setw(2) << "  ";

			
		}

		colorCTA(7, 0);		
		
		cout << endl;
	}
}

bool operator==(tMatrizChar const& mat1, tMatrizChar const& mat2) {

	bool iguales = true;
	int i = 0, j;

	while (i < mat1.numFilas && iguales == true) {

		j = 0;

		while (j < mat1.numCols && iguales == true) {

			if (mat1.datos[i][j] != mat2.datos[i][j]) {

				iguales = false;
			}
			else {
				j++;
			}
		}

		i++;
	}

	return iguales;
}

void swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {

	int temp;
	
	
	temp = mat.datos[pos1.fila][pos1.col];

	mat.datos[pos1.fila][pos1.col] = mat.datos[pos2.fila][pos2.col];

	mat.datos[pos2.fila][pos2.col] = temp;
}

bool swapF(tMatrizChar& mat, int f1, int f2) {

	bool cambio;
	tCoor pos1, pos2;

	if ((f1 >= 0 && f1 < mat.numFilas) && (f2 >= 0 && f2 < mat.numFilas)) {

		pos1.fila = f1;
		pos2.fila = f2;

		for (int i = 0; i < mat.numCols; i++) {

			pos1.col = i;
			pos2.col = i;

			swap(mat, pos1, pos2);
		}

		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;
}

bool swapC(tMatrizChar& mat, int c1, int c2) {

	bool cambio;
	tCoor pos1, pos2;

	if ((c1 >= 0 && c1 < mat.numCols) && (c2 >= 0 && c2 < mat.numCols)) {

		pos1.col = c1;
		pos2.col = c2;

		for (int i = 0; i < mat.numFilas; i++) {

			pos1.fila = i;
			pos2.fila = i;

			swap(mat, pos1, pos2);
		}

		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;
}

bool swapD(tMatrizChar& mat, int d) {

	bool cambio;
	int fila = 0;
	tCoor pos1, pos2;

	if ((d > 0 && d < mat.numFilas) && (mat.numFilas == mat.numCols)) {

		for (int i = d; i < mat.numCols; i++) {

			pos1.col = i;
			pos1.fila = fila;

			pos2.col = fila;
			pos2.fila = i;

			swap(mat, pos1, pos2);

			fila++;
		}

		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;
}

bool voltearF(tMatrizChar& mat, int fila) {

	bool cambio;
	int inicio = 0;
	int fin = mat.numCols - 1;
	tCoor pos1, pos2;
	
	if (fila >= 0 && fila < mat.numFilas) {
		
		pos1.fila = fila;
		pos2.fila = fila;

		while (inicio < fin) {

			pos1.col = inicio;
			pos2.col = fin;

			swap(mat, pos1, pos2);

			inicio++;
			fin--;
		}
		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;
}

bool voltearC(tMatrizChar& mat, int columna) {

	bool cambio;
	int inicio = 0;
	int fin = mat.numFilas - 1;
	tCoor pos1, pos2;

	if (columna >= 0 && columna < mat.numCols) {

		pos1.col = columna;
		pos2.col = columna;

		while (inicio < fin) {

			pos1.fila = inicio;
			pos2.fila = fin;

			swap(mat, pos1, pos2);

			inicio++;
			fin--;
		}
		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;

}

bool voltearD(tMatrizChar& mat, int d) {

	bool cambio;
	int fin = mat.numCols - 1;
	int fila = 0;

	tCoor pos1, pos2;

	if ((d >= 0 && d < mat.numCols) && (mat.numFilas == mat.numCols)) {

		pos1.fila = -1;
		
		for (int i = d; i < mat.numCols; i++) {
		
			fila++;
		}

		pos2.fila = fila;

		while (d < fin) {

			pos1.col = d;
			pos2.col = fin;
			pos1.fila++;
			pos2.fila--;
			
			swap(mat, pos1, pos2);

			d++;
			fin--;
		}

		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;
}

void voltearV(tMatrizChar& mat) {

	int inicio = 0;
	int fin = mat.numCols - 1;

	while (inicio < fin) {

		swapC(mat, inicio, fin);

		inicio++;
		fin--;
	}
}

void voltearH(tMatrizChar& mat) {

	int inicio = 0;
	int fin = mat.numFilas - 1;

	while (inicio < fin) {

		swapF(mat, inicio, fin);

		inicio++;
		fin--;
	}
}

bool voltearID(tMatrizChar& mat) {

	bool cambio;

	if (mat.numFilas == mat.numCols) {

		for (int d = 1; d < mat.numCols; d++) {

			swapD(mat, d);
		}

		cambio = true;
	}
	else {
		cambio = false;
	}

	return cambio;
}

void rotarD(tMatrizChar& mat) {

	tMatrizChar matemp;
	int temp = 0;
	int bajada = mat.numFilas - 1;;

	matemp.numFilas = mat.numFilas;
	matemp.numCols = mat.numCols;

	for (int i = 0; i < mat.numFilas; i++) {

		for (int j = 0; j < mat.numCols; j++) {

			matemp.datos[i][j] = mat.datos[i][j];

		}
	}

	temp = mat.numFilas;
	mat.numFilas = mat.numCols;
	mat.numCols = temp;

	for (int inicial = 0; inicial < matemp.numFilas; inicial++) {

		for (int i = 0; i < matemp.numCols; i++) {

			mat.datos[i][bajada] = matemp.datos[inicial][i];
		}

		bajada--;
	}
}

bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {

	const int NumDirs = 8;
	const tCoor adyacentes[NumDirs] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };
	tCoor pos1temp, pos2temp;
	bool sepuede = true;
	int i = 0, j;

	while (i < NumDirs && sepuede == true) {

		pos1temp = pos1 + adyacentes[i];

		j = 0;

		while (j < NumDirs && sepuede == true) {

			pos2temp = pos2 + adyacentes[j];

			if ((pos1temp != pos2temp) && ((pos1temp.fila >= 0 && pos1temp.fila < mat.numFilas) && (pos1temp.col >= 0 && pos1temp.col < mat.numCols) && (pos2temp.fila >= 0 && pos2temp.fila < mat.numFilas) && (pos2temp.col >= 0 && pos2temp.col < mat.numCols))) {

				sepuede = true;
			}
			else {
				sepuede = false;
			}

			j++;
		}

		i++;
	}

	if (sepuede == true) {

		for (int h = 0; h < NumDirs; h++) {

			pos1temp = pos1 + adyacentes[h];
			pos2temp = pos2 + adyacentes[h];

			swap(mat, pos1temp, pos2temp);
		}
	}

	return sepuede;
}