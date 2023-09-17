#ifndef COORDENADA_H
#define COORDENADA_H

typedef struct {
	int fila, col;
} tCoor;


bool operator==(tCoor c1, tCoor c2);
bool operator!=(tCoor c1, tCoor c2);
tCoor operator+(tCoor c1, tCoor c2);
















#endif // !COORDENADA_H

