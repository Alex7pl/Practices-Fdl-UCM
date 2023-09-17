#ifndef producto_h
#define producto_h

#include <string>
#include <fstream>  // para uso de ofstream
using namespace std;

typedef struct {
   int codigo;
   string nombre;
   int numUnids;
   float precio;
} tProducto;

void mostrarProducto(tProducto prod); // muestra por pantalla
void aArchivo(ofstream& fOut, tProducto prod); // vuelca a archivo

#endif
