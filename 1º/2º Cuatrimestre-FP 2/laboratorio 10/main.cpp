#include "producto.h"
#include "listaproductos.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
   bool ok;
   tInventario inv;
   string archivo = "inventario.txt";
   
   cargarInventario(archivo, inv, ok);
   if (ok == true) {
	  cout << "Inventario cargado...\n";
	  mostrarInventario(inv);
      procesarModificaciones("modificaciones.txt", inv, ok); // ASUMIMOS QUE NO VA A DAR PROBLEMAS LA APERTURA
	  mostrarInventario(inv);
      if (ok) 
         guardarInventario("inventario2.txt", inv);
      else 
         cout << "No se pudo abrir el archivo inventario2.txt!" << endl; 
   }
   else {
       cout << "No se pudo abrir el archivo inventario.txt!" << endl;
   }
  
   return 0;
}


