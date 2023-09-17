#ifndef listaproductos_h
#define listaproductos_h

#include "producto.h"
#include <string>
using namespace std;

const int MAX_PRODS = 30;

typedef tProducto tArrayProductos[MAX_PRODS];

typedef struct {
	tArrayProductos productos;
	int numProds;
} tInventario;


// subprogramas pedidos
void cargarInventario(string nombreFich, tInventario &inv, bool &ok);
//b)	Implementar un subprograma que coloque la información del archivo inventario.txt en las estructuras de datos correspondientes.
void guardarInventario(string nombreFich, const tInventario &inv);
//c)	Implementar un subprograma que guarde en un archivo inventario2.txt la información contenida en la lista del inventario.
int buscarProducto(tInventario inv, int codigoProd);
//d)	Implementar un subprograma que dado un código de producto devuelva su posición en la lista del inventario. Debe realizar una búsqueda binaria.
void procesarModificaciones(string nombreFich, tInventario &inv, bool &ok);
//e)	Implementar un subprograma que actualice la lista del inventario procesando los cambios del archivo modificaciones.txt (las ventas disminuyen el número de unidades y las compras y devoluciones lo aumentan).


// adicional para pruebas
void mostrarInventario(const tInventario& inv);

#endif