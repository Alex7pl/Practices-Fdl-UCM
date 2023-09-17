//Grupo 05-Alejandro Paniagua López y Pablo Martínez Sánchez


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits> // para pausa()
#include <fstream>  // para cargar()
#ifdef _WIN32  // Se define automáticamente en Visual Studio
#include <windows.h>
// windows.h define max como macro y así impide llamar a otras funciones con ese nombre
#undef max // Para poder usar max() en pausa()
#endif
using namespace std;

const bool Debug = false; // true: modo depuración (carga de fichero, suministro de tiradas por teclado); false: (partida de cero, tirada aleatoria)
const string Archivo = "p3.txt";
const int NUM_JUGADORES = 4;
const int NUM_FICHAS = 4;
const int NUM_CASILLAS = 68;
typedef enum { Amarillo, Azul, Rojo, Verde, Gris, Ninguno } tColor;
typedef int tFichas[NUM_FICHAS]; // -1 = en casa; 0 a 67 = casillas normales; 101 a 107 = subiendo a la meta; 108 = meta
typedef int tCarga[21];
struct tJugador {
    tColor color;
    tFichas fichas;
};
typedef tJugador tJugadores[NUM_JUGADORES];
struct tCasilla {
    tColor calle1, calle2;
};
typedef tCasilla tCasillas[NUM_CASILLAS];
struct tJuego {
    tJugadores jugadores; // los jugadores
    tCasillas casillas; // las calles del tablero
    tColor jugadorTurno; // jugador actual (el que tiene el turno)  
    int tirada = 0; // valor de la tirada
    int premio = 0; // el premio por comerte a alguien
    int ultimaFichaMovida = -1;
    int seises = 0; // variable necesaria para saber cuantos seises se han sacado
};
tJuego juego;

// Subprogramas de inicialización...

void iniciar(tJuego& juego);
void cargar(tJuego& juego, string nombreFichero, tCarga tiradaCargada);


// Subprogramas de fichas y casillas...

bool puente(const tCasillas casillas, int casilla, tJuego juego);
int cuantasEn(const tFichas jugador, int casilla);
int primeraEn(const tFichas jugador, int casilla);
int segundaEn(const tFichas jugador, int casilla);
void saleFicha(int casilla, tJuego& juego);
void aCasita(tJuego& juego, int casilla);
bool todasEnMeta(const tFichas jugador);


// Subprogramas de la dinámica del jugadores...

bool procesa5(tJuego juego);
int procesaPuente(tJuego juego, int& ind);
bool puedeMover(const tJuego juego, int ficha, int& casilla);
void mover(tJuego& juego, int ficha, int casilla, tFichas puede);
int comportamientoTablero(tJuego juego, int casilla, int ficha);

// Visualización del tablero...

void pausa();
void mostrar(const tJugadores jugadores, const tCasillas casillas);
bool esSeguro(int casilla);
int salidaJugador(tColor jugador);
int zanataJugador(tColor jugador);
void iniciaColores();


// Subprogramas de manejo de los colores...

string colorACadena(tColor color);
void setColor(tColor color);


// Subprograma para depuración...

int lecturaDado();


/*-----------------------------------------------------------------------------------------------
                                   PROGRAMA PRINCIPAL
------------------------------------------------------------------------------------------------*/

int main() {

    bool fin = false; // Acaba la partida cuando unj jugador tiene todas las fichas en casa
    const int casa = -1; // Establece el valor de la casa de todas las fichas
    tFichas puede; // Sirve para saber cuantas fichas puede mover el jugador actual
    bool todasenMeta = false; // Con ella sabemos si ha ganado alguien o no 
    int ficha = 0; // establece la ficha del jugador actual
    bool turno = true; // Para conocer si se debe pasar turno o no
    int casilla = 0; // valor de la tirada más la casilla donde estaba la ficha del jugador
    int rondas = 0;
    tCarga tiradaCargada; //valor de las tiradas que se realizan por teclado 


   iniciaColores(); // Inicia los colores en versiones antiguas de Windows 10
   
   if (Debug) {
       
       cargar(juego, Archivo, tiradaCargada);
   }
   else {
      
       iniciar(juego);
   }

   while (todasenMeta == false) {

       // Muestra el tablero en la consola
       
       mostrar(juego.jugadores, juego.casillas);
       cout << "Le toca al jugador " << colorACadena(juego.jugadorTurno) << endl;

       // Codigo referente a la tirada del dado


       if (juego.premio == 10 || juego.premio == 20) {

            juego.tirada = juego.premio;
            juego.premio = 0;
       }
       else {

           if(Debug){

               if (tiradaCargada[rondas] == -1) { 

                   juego.tirada = lecturaDado();
                   cin.get(); // Saltar el Intro (para que la pausa funcione bien en modo Debug)
               }
               else {
                   juego.tirada = tiradaCargada[rondas];
               } 
           }
           else {
               juego.tirada = rand() % 6 + 1;
           }

           cout << "Ha salido un " << juego.tirada << endl;

           if (juego.tirada == 6 && cuantasEn(juego.jugadores[juego.jugadorTurno].fichas, casa) == 0) {

                juego.tirada = 7;
                cout << "Tu tirada se convierte en siete" << endl;
                juego.seises++;
           }
           else if (juego.tirada == 6) {
                juego.seises++;
           }
           else {

                juego.seises = 0;
           }
       }
       


       if ( juego.tirada == 0) {

           todasenMeta = true;
       }
       else {

           // Codigo referente a la repeticion por seises

           if ( juego.seises == 3) {

               if (juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida] > 100) {

                   juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida] = juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida];
                   cout << "Te has salvado por los pelos" << endl;
                   juego.seises = 0;
               }
               else {

                   if (juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida]].calle1 == juego.jugadorTurno) {

                       juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida]].calle1 = juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida]].calle2;
                       juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida]].calle2 = Ninguno;
                   }
                   else if (juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida]].calle2 == juego.jugadorTurno) {

                       juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida]].calle2 = Ninguno;
                   }

                   cout << "Te vuelves a casa por correr y si estabas en ella descansa que hace frio fuera" << endl;
                   juego.jugadores[juego.jugadorTurno].fichas[juego.ultimaFichaMovida] = -1;
                   juego.seises = 0;
               }
           }
           else {

               if (juego.tirada == 5 && procesa5(juego) == true) {

                   saleFicha(casilla, juego);
               }
               else {

                   mover(juego, ficha, casilla, puede);
               }
           }

           // Gracias a esto sabemos si se debe pasar turno o no

           if ( juego.premio == 10 ||  juego.premio == 20 ||  juego.seises == 1 ||  juego.seises == 2) {

               turno = false;
           }
           else {

               turno = true;
           }

           // Con esto se pasa el turno o no convenientemente

           if (turno == true) {

               if (juego.jugadorTurno == Amarillo) {
                    juego.jugadorTurno = Azul;
               }
               else if (juego.jugadorTurno == Azul) {
                    juego.jugadorTurno = Rojo;
               }
               else if (juego.jugadorTurno == Rojo) {
                    juego.jugadorTurno = Verde;
               }
               else if (juego.jugadorTurno == Verde) {
                    juego.jugadorTurno = Amarillo;
               }
           }
           else if (turno == false) {

                juego.jugadorTurno = juego.jugadorTurno;
           }

           todasenMeta = todasEnMeta(juego.jugadores[juego.jugadorTurno].fichas);   
       }

       if (tiradaCargada[rondas] != -1) {
           rondas++;
       } 
   }

   // Indica el ganador

   cout << "Ha ganado el jugador " << colorACadena(juego.jugadorTurno) << endl;
 
   return 0;
}


/*---------------------------------------------------------------------------------------------------------------
                                                  SUBPROGRAMAS
----------------------------------------------------------------------------------------------------------------*/


// SUBPROGRAMAS DE INICIALIZACIÓN

void iniciar(tJuego& juego) {

    int turno;
    
    srand(time(NULL));
    turno = rand() % 4;

    switch (turno) {
    case 0:
        juego.jugadorTurno = Amarillo;
        break;
    case 1:
        juego.jugadorTurno = Azul;
        break;
    case 2:
        juego.jugadorTurno = Rojo;
        break;
    case 3:
        juego.jugadorTurno = Verde;
    }


    for (int i = 0; i < NUM_JUGADORES; i++) {
        for (int f = 0; f < NUM_FICHAS; f++) {
            juego.jugadores[i].fichas[f] = -1;
        }
    }

    for (int h = 0; h < NUM_CASILLAS; h++) {
        juego.casillas[h].calle1 = Ninguno;
        juego.casillas[h].calle2 = Ninguno;
    }

    setColor(Gris);
}

void cargar(tJuego& juego, string nombreFichero, tCarga tiradaCargada) {
    ifstream archivo;
    int jugador, casilla, tiro;
    bool encontrado = false;
    int contador = 0;

    archivo.open(nombreFichero);
    if (archivo.is_open()) {
        setColor(Gris);
        for (int i = 0; i < NUM_CASILLAS; i++)
            juego.casillas[i].calle1 = juego.casillas[i].calle2 = Ninguno;
        for (int i = 0; i < NUM_JUGADORES; i++)
            for (int f = 0; f < NUM_FICHAS; f++) {
                archivo >> casilla;
                juego.jugadores[i].fichas[f] = casilla;
                if ((casilla >= 0) && (casilla < NUM_CASILLAS))
                    if (juego.casillas[casilla].calle1 == Ninguno)
                        juego.casillas[casilla].calle1 = tColor(i);
                    else
                        juego.casillas[casilla].calle2 = tColor(i);
            }
        archivo >> jugador;
        juego.jugadorTurno = tColor(jugador);

        while (contador < 15 && encontrado == false) {

            archivo >> tiro;
            tiradaCargada[contador] = tiro;

            if (tiro == -1) {
                encontrado = true;
            }

            contador++;
        }

        if (encontrado == false) {
            tiradaCargada[16] = -1;
        } 
        
        archivo.close();
    }
    else 
        iniciar(juego);
}


// SUBPROGRAMAS DE FICHAS Y CASILLAS

int cuantasEn(const tFichas jugador, int casilla) {

    int contador = 0;

    for (int i = 0; i < NUM_FICHAS; i++) {

        if (jugador[i] == casilla) contador = contador + 1;
    }

    return contador;
}

int primeraEn(const tFichas jugador, int casilla) {
    
    int ind = 0;
    bool encontrado = false;

    while (ind < NUM_FICHAS && encontrado == false) {

        if (jugador[ind] == casilla) {
            encontrado = true;
        }
        else {
            ind = ind + 1;
        }
    }

    if (encontrado == false) {
        ind = -1;
    }

    return ind;
}

int segundaEn(const tFichas jugador, int casilla) {
    
    int ind = 5;

    for (int h = 0; h < NUM_FICHAS; h++) {

        if (jugador[h] == casilla) {
            ind = h;
        }
        else {
            ind = ind;
        } 
    }

    if (ind == 5) {
        ind = -1;
    }
    
    return ind;
}

bool todasEnMeta(const tFichas jugador) {

    bool todasEnMeta = true;
    int i = 0;

    while (i < NUM_FICHAS && todasEnMeta == true) {

        if (jugador[i] == 108) {
            todasEnMeta = true;
        }
        else {
            todasEnMeta = false;
        }

        i++;
    }

    return todasEnMeta;
}

void saleFicha( int casilla, tJuego& juego) {

    int casa = -1;

    if (juego.casillas[salidaJugador(juego.jugadorTurno)].calle2 == Ninguno) {

        juego.casillas[salidaJugador(juego.jugadorTurno)].calle2 = juego.casillas[salidaJugador(juego.jugadorTurno)].calle1;

        juego.casillas[salidaJugador(juego.jugadorTurno)].calle1 = juego.jugadorTurno;

        juego.jugadores[juego.jugadorTurno].fichas[primeraEn(juego.jugadores[juego.jugadorTurno].fichas, casa)] = salidaJugador(juego.jugadorTurno);
    }
    else {

        casilla = salidaJugador(juego.jugadorTurno),

        aCasita(juego, casilla);

        juego.casillas[salidaJugador(juego.jugadorTurno)].calle2 = juego.casillas[salidaJugador(juego.jugadorTurno)].calle1;

        juego.casillas[salidaJugador(juego.jugadorTurno)].calle1 = juego.jugadorTurno;

        juego.jugadores[juego.jugadorTurno].fichas[primeraEn(juego.jugadores[juego.jugadorTurno].fichas, casa)] = salidaJugador(juego.jugadorTurno);

    }

}

void aCasita(tJuego& juego, int casilla) {

  
        juego.jugadores[juego.casillas[casilla].calle2].fichas[segundaEn(juego.jugadores[juego.casillas[casilla].calle2].fichas, casilla)] = -1;

        cout << "Te has comido a el jugador " << colorACadena(juego.casillas[casilla].calle2) << endl;

        juego.casillas[casilla].calle2 = Ninguno;

        juego.premio = 20;

}

bool puente(const tCasillas casillas, int casilla, tJuego juego) {

    bool puente = false;
    
    if ((juego.casillas[casilla].calle1 == juego.casillas[casilla].calle2) && (esSeguro(casilla) == true) && (juego.casillas[casilla].calle1 != Ninguno) && (juego.casillas[casilla].calle2 != Ninguno) && (juego.casillas[casilla].calle1 != juego.jugadorTurno ) && (juego.casillas[casilla].calle2 != juego.jugadorTurno) && (casilla < 100)) {
       
        puente = true;
    }
    else {
        puente = false;
    }
    
    return puente;
}


// VISUALIZACIÓN DEL TABLERO

void mostrar(const tJugadores jugadores, const tCasillas casillas) {
    int casilla, ficha;
    tColor jug;

    cout << "\x1b[2J\x1b[H"; // Se situa en la esquina superior izquierda
    setColor(Gris);
    cout << endl;

    // Filas con la numeración de las casillas...
    for (int i = 0; i < NUM_CASILLAS; i++)
        cout << i / 10;
    cout << endl;
    for (int i = 0; i < NUM_CASILLAS; i++)
        cout << i % 10;
    cout << endl;

    // Borde superior...
    for (int i = 0; i < NUM_CASILLAS; i++)
        cout << '>';
    cout << endl;

    // Primera fila de posiciones de fichas...
    for (int i = 0; i < NUM_CASILLAS; i++) {
        setColor(juego.casillas[i].calle2);
        if (juego.casillas[i].calle2 != Ninguno)
            cout << primeraEn(juego.jugadores[juego.casillas[i].calle2].fichas, i) + 1;
        else
            cout << ' ';
        setColor(Gris);
    }
    cout << endl;

    // "Mediana"   
    for (int i = 0; i < NUM_CASILLAS; i++)
        if (esSeguro(i))
            cout << 'o';
        else
            cout << '-';
    cout << endl;


    // Segunda fila de posiciones de fichas...
    for (int i = 0; i < NUM_CASILLAS; i++) {
        setColor(juego.casillas[i].calle1);
        if (juego.casillas[i].calle1 != Ninguno)
            cout << segundaEn(juego.jugadores[juego.casillas[i].calle1].fichas, i) + 1;
        else
            cout << ' ';
        setColor(Gris);
    }
    cout << endl;

    jug = Amarillo;
    // Borde inferior...
    for (int i = 0; i < NUM_CASILLAS; i++)
        if (i == zanataJugador(jug)) {
            setColor(jug);
            cout << "V";
            setColor(Gris);
        }
        else if (i == salidaJugador(jug)) {
            setColor(jug);
            cout << "^";
            setColor(Gris);
            jug = tColor(int(jug) + 1);
        }
        else
            cout << '>';
    cout << endl;

    // Metas y casas...
    for (int i = 0; i < NUM_FICHAS; i++) {
        casilla = 0;
        jug = Amarillo;
        setColor(jug);
        while (casilla < NUM_CASILLAS) {
            if (casilla == zanataJugador(jug)) {
                ficha = primeraEn(juego.jugadores[jug].fichas, 101 + i);
                if (ficha != -1) {
                    cout << ficha + 1;
                    if (cuantasEn(juego.jugadores[jug].fichas, 101 + i) > 1) {
                        ficha = segundaEn(juego.jugadores[jug].fichas, 101 + i);
                        if (ficha != -1) {
                            cout << ficha + 1;
                        }
                        else
                            cout << "V";
                    }
                    else
                        cout << "V";
                }
                else
                    cout << "VV";
                casilla++;
            }
            else if (casilla == salidaJugador(jug)) {
                if (juego.jugadores[jug].fichas[i] == -1) // En casa
                    cout << i + 1;
                else
                    cout << "^";
                jug = tColor(int(jug) + 1);
                setColor(jug);
            }
            else
                cout << ' ';
            casilla++;
        }
        cout << endl;
    }

    // Resto de metas...
    for (int i = 105; i <= 107; i++) {
        casilla = 0;
        jug = Amarillo;
        setColor(jug);
        while (casilla < NUM_CASILLAS) {
            if (casilla == zanataJugador(jug)) {
                ficha = primeraEn(juego.jugadores[jug].fichas, i);
                if (ficha != -1) {
                    cout << ficha + 1;
                    if (cuantasEn(juego.jugadores[jug].fichas, i) > 1) {
                        ficha = segundaEn(juego.jugadores[jug].fichas, i);
                        if (ficha != -1) {
                            cout << ficha + 1;
                        }
                        else
                            cout << "V";
                    }
                    else
                        cout << "V";
                }
                else
                    cout << "VV";
                casilla++;
                jug = tColor(int(jug) + 1);
                setColor(jug);
            }
            else
                cout << ' ';
            casilla++;
        }
        cout << endl;
    }

    casilla = 0;
    jug = Amarillo;
    setColor(jug);
    while (casilla < NUM_CASILLAS) {
        cout << ((juego.jugadores[jug].fichas[0] == 108) ? '1' : '.');
        cout << ((juego.jugadores[jug].fichas[1] == 108) ? '2' : '.');
        jug = tColor(int(jug) + 1);
        setColor(jug);
        cout << "               ";
        casilla += 17;
    }
    cout << endl;
    casilla = 0;
    jug = Amarillo;
    setColor(jug);
    while (casilla < NUM_CASILLAS) {
        cout << ((juego.jugadores[jug].fichas[2] == 108) ? '3' : '.');
        cout << ((juego.jugadores[jug].fichas[3] == 108) ? '4' : '.');
        jug = tColor(int(jug) + 1);
        setColor(jug);
        cout << "               ";
        casilla += 17;
    }
    cout << endl << endl;
    setColor(Gris);
}

void pausa() {
    cout << "Pulsa Intro para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool esSeguro(int casilla) {

    bool CasillaSegura;

    if (casilla == 0 || casilla == 5 || casilla == 12 || casilla == 17 || casilla == 22 || casilla == 29
        || casilla == 34 || casilla == 39 || casilla == 46 || casilla == 51 || casilla == 56 || casilla == 63) {

        CasillaSegura = true;
    }
    else {

        CasillaSegura = false;
    }

    return CasillaSegura;
}

int salidaJugador(tColor jugador) {

    int salida = 0;

    switch (jugador) {

    case 3: salida = 56;
        break;
    case 2: salida = 39;
        break;
    case 1: salida = 22;
        break;
    case 0: salida = 5;
    }

    return salida;
}

int zanataJugador(tColor jugador) {
    
    int zanata = 0;

    switch (jugador) {
    case 3: zanata = 51;
        break;
    case 2: zanata = 34;
        break;
    case 1: zanata = 17;
        break;
    case 0: zanata = 0;
    }

    return zanata;

}


// SUBPROGRAMA PARA DEPURACIÓN (TIRADA DESDE TECLADO)

int lecturaDado() {

    int tirada = 0;

    cout << "Introduzca el numero de casillas que desea avanzar(0 para salir): ";
    cin >> tirada;

    while (tirada < 0) {

        cout << "No puedes avanzar para atras en el parchis vuelve a intentarlo: ";
        cin >> tirada;
    }
    
    return tirada;
    
}


// SUBPROGRAMAS SOBRE COLORES

string colorACadena(tColor color) {
   string cad;

   switch (color) {
   case Rojo:
      cad = "Rojo";
      break;
   case Verde:
      cad = "Verde";
      break;
   case Azul:
      cad = "Azul";
      break;
   case Amarillo:
      cad = "Amarillo";
   }

   return cad;
}

void setColor(tColor color) {
    switch (color) {
    case Azul:
        cout << "\x1b[34;107m";
        break;
    case Verde:
        cout << "\x1b[32;107m";
        break;
    case Rojo:
        cout << "\x1b[31;107m";
        break;
    case Amarillo:
        cout << "\x1b[33;107m";
        break;
    case Gris:
    case Ninguno:
        cout << "\x1b[90;107m";
        break;
    }
}

void iniciaColores() {
#ifdef _WIN32
    for (DWORD stream : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE}) {
        DWORD mode;
        HANDLE handle = GetStdHandle(stream);

        if (GetConsoleMode(handle, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(handle, mode);
        }
    }
#endif
}


// SUBPROGRAMAS DE LA DINÁMICA DE JUGADORES

bool procesa5(tJuego juego) {

    bool procesa5;
    int casa = -1;

    if (cuantasEn(juego.jugadores[juego.jugadorTurno].fichas, casa) > 0 && juego.casillas[salidaJugador(juego.jugadorTurno)].calle2 != juego.jugadorTurno) {

        procesa5 = true;
    }
    else {

        procesa5 = false;
    }

    return procesa5;
}

int procesaPuente(tJuego juego, int& ind) {

    int puentes = 0;
    bool centinela = false;
    int casillaPuente = 0;

    for (int h = 0; h < NUM_CASILLAS; h++) {

        if (juego.casillas[h].calle1 == juego.casillas[h].calle2 && juego.casillas[h].calle1 == juego.jugadorTurno && juego.casillas[h].calle2 == juego.jugadorTurno) {

            puentes = puentes + 1;
            casillaPuente = h;
        }
    }

    if (puentes == 1) {

        while (ind < NUM_FICHAS && centinela == false) {

            if (juego.jugadores[juego.jugadorTurno].fichas[ind] == casillaPuente) {

                centinela = true;
            }

            ind++;
        }

        if (puedeMover(juego, ind, casillaPuente) == true) {

            puentes = 1;
        }
        else {

            puentes = 0;
        }
    }
    return puentes;
}

bool puedeMover(const tJuego juego, int ficha, int& casilla) {

    int contador = juego.jugadores[juego.jugadorTurno].fichas[ficha];
    bool puedeMover = true;
    
    if ((juego.jugadores[juego.jugadorTurno].fichas[ficha] == -1) || (juego.jugadores[juego.jugadorTurno].fichas[ficha] == 108)) {

        puedeMover = false;
    }
    else {

        casilla = juego.jugadores[juego.jugadorTurno].fichas[ficha] +  juego.tirada;
        casilla = comportamientoTablero(juego, casilla, ficha);
        while ((contador <= casilla) && (puedeMover == true)) {

            if (contador > 68 && contador < 99) {

                contador = 100;
            }
            
            if (puente(juego.casillas, contador, juego) == true) {

                puedeMover = false;
            }
            else if ((contador == casilla) && (juego.casillas[contador].calle1 == juego.casillas[contador].calle2) && (juego.casillas[contador].calle1 != Ninguno) && (juego.casillas[contador].calle2 != Ninguno) && (contador < 100)) {

                puedeMover = false;
            }
            else if ((contador == casilla) && (esSeguro(casilla) == true) && (juego.casillas[casilla].calle1 != Ninguno) && (juego.casillas[casilla].calle2 != Ninguno) && (casilla < 100) && ((juego.casillas[casilla].calle1 != juego.jugadorTurno) || (juego.casillas[casilla].calle2 != juego.jugadorTurno))) {

                puedeMover = false;
            }
            else if ((contador != casilla) && (contador == 108)) {

                puedeMover = false;
            }
         
            contador = contador + 1;
        }

    }

    return puedeMover;
}

int comportamientoTablero(tJuego juego, int casilla, int ficha) {

    if (casilla > 100) {

        casilla = casilla;
    }
    else if (casilla > 67) {

        casilla = 68 - juego.jugadores[juego.jugadorTurno].fichas[ficha];
        casilla =  juego.tirada - casilla;
    }
    else if ((casilla > zanataJugador(juego.jugadorTurno)) && (juego.jugadores[juego.jugadorTurno].fichas[ficha] <= zanataJugador(juego.jugadorTurno)) && (juego.jugadorTurno != 0)){

        casilla = zanataJugador(juego.jugadorTurno) - juego.jugadores[juego.jugadorTurno].fichas[ficha];
         juego.tirada =  juego.tirada - casilla;
        casilla =  juego.tirada + 100;
    }
    else if ((juego.jugadorTurno == 0) && (casilla > 68)) {

        casilla = zanataJugador(juego.jugadorTurno) - juego.jugadores[juego.jugadorTurno].fichas[ficha];
         juego.tirada =  juego.tirada - casilla;
        casilla =  juego.tirada + 100;
    }
    else {

        casilla = casilla;
    }

    return casilla;
}

void mover(tJuego& juego, int ficha, int casilla, tFichas puede) {

    int ind = 0; // Para saber las fichas que están en puentes con procesa puentes
    int i = 0;

    if (( juego.tirada == 6 ||  juego.tirada == 7) && procesaPuente(juego, ind) == 1) {

        ficha = ind - 1;
        ficha = segundaEn(juego.jugadores[juego.jugadorTurno].fichas, juego.jugadores[juego.jugadorTurno].fichas[ficha]);
        casilla = juego.jugadores[juego.jugadorTurno].fichas[ficha] +  juego.tirada;
        casilla = comportamientoTablero(juego, casilla, ficha);
        cout << "Tienes que abrir el puente" << endl;

        juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle1 = juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle2;
        juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle2 = Ninguno;

        if (juego.casillas[casilla].calle1 != Ninguno && juego.casillas[casilla].calle1 != juego.jugadorTurno && esSeguro(casilla) == false && !(casilla > 68)) {

            juego.casillas[casilla].calle2 = juego.casillas[casilla].calle1;

            aCasita(juego, casilla);

            juego.casillas[casilla].calle1 = juego.jugadorTurno;

            juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;
        }
        else if (esSeguro(casilla) == true || juego.casillas[casilla].calle1 == juego.jugadorTurno) {

            juego.casillas[casilla].calle2 = juego.jugadorTurno;

            juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;
        }
        else if (casilla == 108) {

            juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;

            cout << "Has metido una ficha dentro de casa y te cuentas 10" << endl;

             juego.premio = 10;
        }
        else {

            juego.casillas[casilla].calle1 = juego.jugadorTurno;

            juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;
        }
    

        juego.ultimaFichaMovida = ficha;

    }
    else {


        for (int i = 0; i < NUM_FICHAS; i++) {

            cout << i + 1 << ": ";
            if (puedeMover(juego, i, casilla) == true) {

                cout << "Puede ir a la casilla " << casilla << endl;
                puede[i] = true;
            }
            else {

                puede[i] = false;
                cout << "No puede mover con esta ficha" << endl;
            }
        }


        if (puede[0] == false && puede[1] == false && puede[2] == false && puede[3] == false) {

            cout << "No puedes mover ninguna ficha" << endl;
        }
        else {

            do {

                cout << "Ficha a mover:" << endl;
                cin >> ficha;
                ficha = ficha - 1;
            } while (puedeMover(juego, ficha, casilla) == false);


            if (juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle2 == Ninguno) {

                juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle1 = Ninguno;
            }
            else if (juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle2 != Ninguno) {

                juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle1 = juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle2;
                juego.casillas[juego.jugadores[juego.jugadorTurno].fichas[ficha]].calle2 = Ninguno;
            }

            if (juego.casillas[casilla].calle1 != Ninguno && juego.casillas[casilla].calle1 != juego.jugadorTurno && esSeguro(casilla) == false && !(casilla > 68)){

                juego.casillas[casilla].calle2 = juego.casillas[casilla].calle1;

                aCasita(juego, casilla);

                juego.casillas[casilla].calle1 = juego.jugadorTurno;

                juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;
            }
            else if ((esSeguro(casilla) == true && juego.casillas[casilla].calle1 != Ninguno) || juego.casillas[casilla].calle1 == juego.jugadorTurno) {

                juego.casillas[casilla].calle2 = juego.jugadorTurno;

                juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;
            }
            else if (casilla == 108) {

                juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;

                cout << "Has metido una ficha dentro de casa y te cuentas 10" << endl;

                 juego.premio = 10;
            }
            else {

                juego.casillas[casilla].calle1 = juego.jugadorTurno;

                juego.jugadores[juego.jugadorTurno].fichas[ficha] = casilla;
            }
        }

        juego.ultimaFichaMovida = ficha;
    }
}
