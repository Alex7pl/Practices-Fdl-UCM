// Tema 2 - Ejercicio 26-22

#include <iostream>
using namespace std;

   
int solicitud_dato ();
int calculaProducto (int a, int b);


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
                      CUERPO PRINCIPAL DEL PROGRAMA                        
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
int main(){
   int num1, num2, producto;

   num1 = solicitud_dato ();
   
   num2 = solicitud_dato ();
   
   producto = calculaProducto (num1, num2);
   
   cout << "El producto es " << producto << endl;

   return 0;
}
   
 /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                SUBPROGRAMAS 
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */


  
int solicitud_dato () {
   
   int numero;
   
   do {
	   
	   cout << "Introduzca el numero entero positivo: "; cin >> numero; }
	   
	   while (numero <= 0);
	    
	   return numero;
}

int calculaProducto (int a, int b) {
   
   int contador = 0;
   
   int suma = 0;
   
   
   do {
	   
	   suma = suma + a;
	   
	   contador++;  }
	   
	  while (contador < b);
	   
   return suma;
}