//Grupo 05-Alejandro Paniagua L�pez y Pablo Mart�nez S�nchez


#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

const int NUM_CASILLAS = 68;
typedef enum { Rojo = 1, Verde = 2, Amarillo = 3, Azul = 4 }tColor;

// visualiza el tablero posicionando correctamente a los jugadores en sus casillas (dentro del circuito o en casa)
void mostrar(int jugador1, int jugador2, int casilla1, int casilla2);

// lectura validada del color de un jugador (valor del 1 al 4)
int eligeJugador();

// devuelve true si la casilla "casilla" es un seguro; false c.c.
bool esSeguro(int casilla);

// devuelve el nÃºmero de la casilla de salida del jugador de color "num"
int salidaJugador(int num);

// devuelve una cadena equivalente al valor enumerado "color"
string colorACadena(tColor color);

// devuelve el carÃ¡cter con el que es representado el color "color" en pantalla
char letra(tColor color);

// lee de teclado y valida la tirada del dado
int lecturaDado();

// Indica las zanatas de los jugadores
int zanataJugadores(int num);

// Para dar la vuelta en el tablero si pasas de 67
int vuelta(int casilla, int tiradamascasilla, int tirada);

// Indica cuando un jugador ha llegado a su zanata y por ende acaba el juego
bool llegadaZanata(int casilla1, int jugador1, int casilla2, int jugador2);

//Indica cuantas veces has sacado un 6
int contadortirada(int contador);

//Indica cuando te comes a alguien
bool comerJugador(int casillaAct, int casillaNoAct, int tiradamascasilla, int jugadorAct);

//Sirve para cargar una partida a tu gusto
void cargarPartida(int& jugador1, int& casilla1, int& jugador2, int& casilla2, int& jugadorAct, int& casillaAct);

/*----------------------------------------------------------------------------------------------------------
                                           PROGRAMA PRINCIPAL
-----------------------------------------------------------------------------------------------------------*/								   


int main() {
    
	int jugador1, jugador2, jugadorAct, jugadorNoAct; // para almacenar los colores de cada jugador y el jugador actual y no actual
    int casilla1, casilla2, casillaAct, casillaNoAct; // para almacenar las casillas de cada jugador y la casilla de los jugadores 
    int tirada = 0; // para almacenar la tirada del dado
    int tiradamascasilla = 0; //para poder dar la vuelta una vez que llegemos a 67
    bool llegada = false; //para saber cuando uno de los jugadores ha llegado a casa
    int contadorde6, contador = 0; //Para la logistica del 6
    int tePasas; //Para saber si al contarte 20 después de comer te pasas de la zanata
	bool jugadortres; //Para saber si un jugador esta usando el color amarillo
	
	//Codigo para cargar una partida predise�ada
	
	cargarPartida(jugador1, casilla1, jugador2, casilla2, jugadorAct, casillaAct);
	
	/*
	
	// Codigo para elegir los colores de cada jugador 
	
    jugador1 = eligeJugador();
	jugador2 = eligeJugador();
	
	while (jugador1 == jugador2) {
		
		cout << "Ha ocurrido un error, vuelva a elegir el color del jugador dos." << endl;
		jugador2 = eligeJugador(); 
	}

    // Codigo para colocar a los dos jugadores en casa
	
	casilla1 = -1;
	casilla2 = -1;
	
	// Codigo para determinar aleatoriamente el jugador que va a empezar (i.e. el que tiene el turno)
	
    srand(time(NULL));
    jugadorAct = rand() % 2 + 1;
    
    */
   
   
   	// Codigo principal del bucle del juego
   
   	while (llegada == false){
			
		// Codigo para mostrar tablero e informar del color del jugador actual
		
		mostrar(jugador1, jugador2, casilla1, casilla2);
	
		//Codigo para cambiar de jugador al turno
		
		if (jugadorAct == jugador1 & contadorde6 == 2) {
			jugadorAct = 2;
		}else if (jugadorAct == jugador1 & contadorde6 == 1) {
			jugadorAct = 1;
		}else if (jugadorAct == jugador1) {
			jugadorAct = 2;
		}else if (jugadorAct == jugador2 & contadorde6 == 2) {
			jugadorAct = 1;
		}else if (jugadorAct == jugador2 & contadorde6 == 1) {
			jugadorAct = 2;
		}else if (jugadorAct == jugador2) {
			jugadorAct = 1;
		}
		
		if (jugadorAct == 1) {
    		
    		jugadorAct = jugador1;
    		casillaAct = casilla1;
    		casillaNoAct = casilla2;
    		jugadorNoAct = jugador2;
    	}else {
    		
    		jugadorAct = jugador2;
    		casillaAct = casilla2;
    		casillaNoAct = casilla1;
    		jugadorNoAct = jugador1;
		}
		
		cout << "Tiene el turno el jugador " << colorACadena(tColor(jugadorAct)) << endl;
    	
    	// Codigo para realizar una tirada (proporcionada por el usuario) y mostrarla
	
		tirada = lecturaDado();
		cout << "Ha salido un " << tirada << endl;
			
		//Codigo necesario para que el programa conozca cuantos seises has sacado
	
		if (tirada == 6) {
			contador++;
		}else {
			contador = 0;
		}
			
		contadorde6 = contadortirada(contador);
			
		if (contadorde6 == 2) {
			
			casillaAct = -1;
			cout << "Te vuelves a casa por correr y si estabas en ella descansa que hace frio fuera" << endl;
			contador = 0;
		}else {  
			
			//Codigo referente a las tiradas que se efectuan dentro de casa
	    	
			if (casillaAct == -1) {
	     		
	     		//Si sacas un 5
	     		
				if (tirada == 5) {
	     			
	     			//Si te comes a alguien
	     			
					if (comerJugador(casillaAct, casillaNoAct, tiradamascasilla, jugadorAct) == true) { 
	     			
						casillaNoAct = -1; 
						casillaAct = 20 + salidaJugador(jugadorAct);
						cout << "Te has comido al jugador " << colorACadena(tColor(jugadorNoAct)) << " y te cuentas 20" << endl;
					}else {
					
						casillaAct = salidaJugador(jugadorAct);
	     				cout << "El " << colorACadena(tColor(jugadorAct)) << " ha salido de casa" << endl;
				 	}
				}else{
					
					cout << "El " << colorACadena(tColor(jugadorAct)) << " no ha salido de casa" << endl;
				}
			}else {
				
				//Codigo necesario para conocer si el jugador actual es el jugador amarillo
				
				if (jugadorAct == 3) {
					
					jugadortres = true;
				}else if (jugadorAct == 1 || jugadorAct == 2 || jugadorAct == 4){
					
					jugadortres = false;
				}
					
					//Codigo referente a la tirada de los usuarios por las calles
					
					if (casillaAct > zanataJugadores(jugadorAct) && jugadortres == false) {
						
						tiradamascasilla = tirada + casillaAct;
						tiradamascasilla = vuelta(casillaAct, tiradamascasilla, tirada);
						tePasas = tiradamascasilla + 20;
						
						//Para saber si te comes a alguien o no ademas de saber si esta en un seguro
						
						if (tiradamascasilla == casillaNoAct) {
						
							if (comerJugador(casillaAct, casillaNoAct, tiradamascasilla, jugadorAct) == true) {
							
								casillaNoAct = -1;
								casillaAct = tePasas;
								cout << "Te comes al jugador " << colorACadena(tColor(jugadorNoAct)) << " y te cuentas 20" << endl;
							}else {
								
								casillaAct = casillaAct;
								cout << "No te puedes comer al jugador porque esta en un seguro" << endl;	
							}
						}else {
							
							casillaAct = tiradamascasilla;
						}
					}else {
					
						tiradamascasilla = tirada + casillaAct;
						
						if (tiradamascasilla > 68 && jugadortres == true) {
							
							cout << "No puedes mover porque te pasas de la zanata" << endl;
						}else {
							
							tiradamascasilla = vuelta(casillaAct, tiradamascasilla, tirada);
							tePasas = 20 + tiradamascasilla;
					
							if (tiradamascasilla > zanataJugadores(jugadorAct) && jugadortres == false) {
		    			
		    					cout << "No puedes mover porque te pasas de la zanata" << endl;
							}else {
							
								if (tiradamascasilla == casillaNoAct) {
						
									if (comerJugador( casillaAct, casillaNoAct, tiradamascasilla, jugadorAct) == true){
							
										if (tePasas > zanataJugadores(jugadorAct) && jugadortres == false) {
								
											casillaNoAct = -1;
											cout << "Te comes al jugador " << colorACadena(tColor(jugadorNoAct)) << " pero no te cuentas porque te pasas de la zanata" << endl;
										}else if (tePasas > 68 && jugadortres == true){
											
											casillaNoAct = -1;
											cout << "Te comes al jugador " << colorACadena(tColor(jugadorNoAct)) << " pero no te cuentas porque te pasas de la zanata" << endl;
										}else {
								
											casillaNoAct = -1;
											casillaAct = tePasas;
											cout << "Te comes al jugador " << colorACadena(tColor(jugadorNoAct)) << " y te cuentas 20" << endl;
										}
									}else {
								
										casillaAct = casillaAct;
										cout << "No te puedes comer al jugador porque esta en un seguro" << endl;
									}
								}else {
							
									casillaAct = tiradamascasilla;
								}
							}
						}	 
					}
			}
		}
		
	//Devuelve los valores de los jugadores y las casillas que se han utilizado durante el turno
	
	if (jugadorAct == jugador1) {
		
		casilla1 = casillaAct;
		casilla2 = casillaNoAct;
	}else {
		
		casilla2 = casillaAct;
		casilla1 = casillaNoAct;	
	}
	
	//Sirve para saber si al final de la tirada un jugador ha llegado a su zanata
	
	llegada = llegadaZanata(casilla1, jugador1, casilla2, jugador2);
}
   	
	//Indica el ganador
   
   	if (casilla1 == zanataJugadores(jugador1)) {
   		
		cout << "Ha ganado el " << colorACadena(tColor(jugador1)) << endl;
   	}else {
    	
		cout << "Ha ganado el " << colorACadena(tColor(jugador2)) << endl;
	}
	
    return 0;
}

/*-------------------------------------------------------------------------------------------------
                                        SUBPROGRAMAS
--------------------------------------------------------------------------------------------------*/										



void mostrar(int jugador1, int jugador2, int casilla1, int casilla2) {
   	// VisualizaciÃ³n del tablero...
   	
   	cout << endl << "      ";
   	
   	// Mostramos los nÃºmeros de las casillas...
   	
   	for (int pos = 0; pos < NUM_CASILLAS; pos++) {
      	cout << pos / 10;
   	}
   	
   	cout << endl << "      ";
   	
   	for (int pos = 0; pos < NUM_CASILLAS; pos++) {
      	cout << pos % 10;
   	}
   	
   	cout << endl << "      ";

   	// Mostramos la fila de seguros...
   	for (int pos = 0; pos <= 67; pos++) {
      	if (esSeguro(pos)) {
         	cout << "o";
      	} else {
			cout << "-";
      	}
   	}
   	cout << endl << "CALLE ";

   	// Mostramos las fichas que estÃ¡n fuera de casa...
	for (int pos = 0; pos < NUM_CASILLAS; pos++) {
		
      	if (pos == casilla1){
      		cout << letra(tColor(jugador1));
      	} else if (pos == casilla2){
			cout << letra(tColor(jugador2));
    	} else{
         	cout << " ";
 		}
   	}
   
   cout << endl << "      ";

   // Mostramos la otra fila de seguros...
   for (int pos = 0; pos <= 67; pos++) {
      if (esSeguro(pos)) {
         cout << "o";
      } else {
      		cout << "-";
      }
   }
   
   cout << endl << "CASA  ";

   for (int pos = 0; pos < NUM_CASILLAS; pos++) {
      char c = ' ';
      
      if (pos == salidaJugador(jugador1)) {
      	
        if (casilla1 == -1){
            c = letra(tColor(jugador1 ));
    	}
      }else if (pos == salidaJugador(jugador2))	
      		
         if (casilla2 == -1){
            c = letra(tColor(jugador2 ));
        }
        
      cout << c;
   }
   
   cout << endl;
   system("pause");
}

int eligeJugador() {
   
    string Colordado;
   
    tColor color;
    
    bool error;
	
	cout <<"Introduzca color que usted desea elegir (rojo, verde, amarillo o azul): ";
	
	cin >> Colordado;

    if (Colordado == "rojo" || Colordado == "amarillo" || Colordado == "verde" || Colordado == "azul") {
    	error = false;
	}else {
		
		error = true;
	}
	
	while (error == true) {
		
		cout << "Ha ocurrido un error vuelva a intentarlo de nuevo: ";
		
		cin >> Colordado;

    	if (Colordado == "rojo" || Colordado == "amarillo" || Colordado == "verde" || Colordado == "azul") {
    		error = false;
    		
		}else {
			
			error = true;
		}
	}
	
	if (Colordado == "rojo") {
		color = Rojo; 
	}else if (Colordado == "amarillo") {
		color = Amarillo;
	}else if (Colordado == "azul") {
		color = Azul;
	}else if (Colordado == "verde") {
		color = Verde;
	}
	
	return color;
}

bool esSeguro(int casilla) {
    
	bool CasillaSegura;
	
	if (casilla == 0 || casilla == 5 || casilla == 12 || casilla == 17 || casilla == 22 || casilla == 29 
	|| casilla == 34 || casilla == 39 || casilla == 46 || casilla == 51 || casilla == 56 || casilla == 63) {
		
		CasillaSegura = true;
	}else {
	 	
		 CasillaSegura = false;
	}
   
   return CasillaSegura;
}

int salidaJugador(int num) {
	
	int salida; 
	
	switch (num) {
		
		case 4: salida = 22; 
	  		break;
	  		
    	case 3: salida = 5;
	  		break;
	  
		case 2: salida = 56;
	  		break;
	  
		case 1: salida = 39;
	}
	
	return salida;
}

int lecturaDado() {
	
	int tirada = 0;
	
	cout << "Introduzca el numero de casillas que desea avanzar: "; 
	cin >> tirada;
	
	while (tirada < 0) {
		
		cout << "No puedes avanzar para atras en el parchis vuelve a intentarlo: "; 
		cin >> tirada; 
	}
		
	return tirada;
}

string colorACadena(tColor color) {
	
	string cad;

   	switch (color) {
   		
   		case Rojo: cad = "Rojo";
      		break;
      		
   		case Verde: cad = "Verde";
      		break;
      		
   		case Azul: cad = "Azul";
      		break;
      		
   		case Amarillo: cad = "Amarillo";
   }

   return cad;
}

char letra(tColor color) {
	
   char c = ' ';

   switch (color) {
   	case Rojo: c = 'R';
      break;
   case Verde: c = 'V';
      break;
   case Azul: c = 'A';
      break;
   case Amarillo: c = 'M';
   }

   return c;
}

int zanataJugadores(int num) {
	
	int zanata;
	
	switch (num) {
		case 4: zanata = 17;
			break;
		case 3: zanata = 0;
		    break;
		case 2: zanata = 51;		
		    break;
		case 1: zanata = 34;    	
	}
	
	return zanata;
}

int vuelta(int casilla, int tiradamascasilla, int tirada) {
	
	
	if (tiradamascasilla > 67) {
		
		tiradamascasilla = 68 - casilla;
		tiradamascasilla = tirada - tiradamascasilla;
	}else {
		
		tiradamascasilla = tiradamascasilla;
	}
	
	return tiradamascasilla;
}

bool llegadaZanata(int casilla1, int jugador1, int casilla2, int jugador2) {

	bool llegada;

	if (casilla1 == zanataJugadores(jugador1) || casilla2 == zanataJugadores(jugador2)) {
		
		llegada = true;
	}else {
		
		llegada = false;
	}
	
	return llegada;
}

int contadortirada(int contador) {
	
	int tresveces;
	
	switch (contador) {
		case 0: tresveces = 0;
			break;
		case 1: tresveces = 1;
			break;
		case 2: tresveces = 1;
			break;
		case 3: tresveces = 2;
	}
	
	return tresveces;
}

bool comerJugador(int casillaAct, int casillaNoAct, int tiradamascasilla, int jugadorAct) {
	
	bool comer;
	
	if (casillaAct == -1 && casillaNoAct == salidaJugador(jugadorAct)) {
		
		comer = true;
	}else if (tiradamascasilla == casillaNoAct && esSeguro(casillaNoAct) == false ) {
		
		comer = true;
	}else {
		
		comer = false;
	}
	
	return comer;
}

void cargarPartida(int& jugador1, int& casilla1, int& jugador2, int& casilla2, int& jugadorAct, int& casillaAct) {
    
	ifstream flujoIn;
	string nombreFichero;
	
	cout << "Introduce nombre del archivo de carga: ";
	getline(cin, nombreFichero);

    flujoIn.open(nombreFichero);
    if (flujoIn.is_open()) {
        
		flujoIn >> jugador1 >> casilla1 >> jugador2 >> casilla2 >> jugadorAct;
        casillaAct = (jugadorAct == 1) ? casilla1 : casilla2;
		flujoIn.close();
    }else { // por defecto juegan el rojo y el azul desde casa y teniendo el turno el azul
        
		jugador1 = 1;
        jugador2 = 4;
        casilla1 = casilla2 = -1;
        jugadorAct = 2;
        casillaAct = (jugadorAct == 1) ? casilla1 : casilla2;
    }
}
