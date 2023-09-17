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

const bool Debug = true; // true: modo depuración (carga de fichero, suministro de tiradas por teclado); false: (partida de cero, tirada aleatoria)
const int NUM_JUGADORES = 4;
const int NUM_FICHAS = 4;
const int NUM_CASILLAS = 68;
typedef enum { Amarillo, Azul, Rojo, Verde, Gris, Ninguno } tColor;
typedef int tFichas[NUM_FICHAS]; // -1 = en casa; 0 a 67 = casillas normales; 101 a 107 = subiendo a la meta; 108 = meta
typedef tFichas tJugadores[NUM_JUGADORES];
typedef tColor tCasillas[NUM_CASILLAS];


// Subprogramas de inicialización...

void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, tColor& jugadorTurno);
void cargar(tJugadores jugadores, tColor& jugadorTurno, tCasillas calle1, tCasillas calle2);


// Subprogramas de fichas y casillas...

bool puente(const tCasillas calle1, const tCasillas calle2, int casilla, tColor jugadorTurno);
int cuantasEn(const tFichas jugador, int casilla);
int primeraEn(const tFichas jugador, int casilla);
int segundaEn(const tFichas jugador, int casilla);
void saleFicha(tJugadores jugadores, tColor jugadorTurno, int casilla, int& premio, tCasillas calle1, tCasillas calle2);
void aCasita(tJugadores jugadores, int casilla, int& premio, tCasillas calle2);
bool todasEnMeta(const tFichas jugador);


// Subprogramas de la dinámica del jugadores...

bool procesa5(tJugadores jugadores, tColor jugadorTurno, tCasillas calle2);
int procesaPuente(tJugadores jugadores, tColor jugadorTurno, int& ultimaFichaMovida, int& tirada, int& ind, tCasillas calle1, tCasillas calle2);
bool puedeMover(const tJugadores jugadores, tColor jugadorTurno, int ficha, int& casilla, int tirada, const tCasillas calle1, const tCasillas calle2);
void mover(tJugadores jugadores, tColor jugadorTurno, int ficha, int casilla, int& premio, int tirada, int& ultimaFichaMovida, tFichas puede, tCasillas calle1, tCasillas calle2);
int comportamientoTablero(int casilla, const tJugadores jugadores, tColor jugadorTurno, int ficha, int tirada);

// Visualización del tablero...

void pausa();
void mostrar(const tJugadores jugadores, const tCasillas calle1, const tCasillas calle2);
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
   tJugadores jugadores; // los jugadores
   tCasillas calle1, calle2; // las calles del tablero
   tColor jugadorTurno; // jugador actual (el que tiene el turno)  
   int tirada; // valor de la tirada
   int premio = 0; // el premio por comerte a alguien
   int casilla = 0; // valor de la tirada más la casilla donde estaba la ficha del jugador
   int ficha = 0; // establece la ficha del jugador actual
   bool turno = true; // Para conocer si se debe pasar turno o no
   int ultimaFichaMovida;
   int seises = 0; // variable necesaria para saber cuantos seises se han sacado
   bool fin = false; // Acaba la partida cuando unj jugador tiene todas las fichas en casa
   const int casa = -1; // Establece el valor de la casa de todas las fichas
   tFichas puede; // Sirve para saber cuantas fichas puede mover el jugador actual
   bool todasenMeta = false; // Con ella sabemos si ha ganado alguien o no 


   iniciaColores(); // Inicia los colores en versiones antiguas de Windows 10
   
   if (Debug) {
       
       cargar(jugadores, jugadorTurno, calle1, calle2);
   }
   else {
      
       iniciar(jugadores, calle1, calle2, jugadorTurno);
   }

   while (todasenMeta == false) {

       // Muestra el tablero en la consola
       
       mostrar(jugadores, calle1, calle2);
       cout << "Le toca al jugador " << colorACadena(jugadorTurno) << endl;

       // Codigo referente a la tirada del dado

       if (Debug) {

           if (premio == 10 || premio == 20) {

               tirada = premio;
               premio = 0;
           }
           else {

               tirada = lecturaDado();
               cin.get(); // Saltar el Intro (para que la pausa funcione bien en modo Debug)

               if (tirada == 6 && cuantasEn(jugadores[jugadorTurno], casa) == 0) {

                   tirada = 7;
                   cout << "Tu tirada se convierte en siete" << endl;
                   seises++;
               }
               else if (tirada == 6) {
                   seises++;
               }
               else {

                   seises = 0;
               }
           }
       }
       else {

           if (premio == 10 || premio == 20) {

               tirada = premio;
               premio = 0;
           }
           else {

               tirada = rand() % 6 + 1;
               cout << "Ha salido un " << tirada << endl;

               if (tirada == 6 && cuantasEn(jugadores[jugadorTurno], casa) == 0) {

                   tirada = 7;
                   cout << "Tu tirada se convierte en siete" << endl;
                   seises++;
               }
               else if (tirada == 6) {
                   seises++;
               }
               else {

                   seises = 0;
               }
           }
       }

       if (tirada == 0) {

           todasenMeta = true;
       }
       else {

           // Codigo referente a la repeticion por seises

           if (seises == 3) {

               if (jugadores[jugadorTurno][ultimaFichaMovida] > 100) {

                   jugadores[jugadorTurno][ultimaFichaMovida] = jugadores[jugadorTurno][ultimaFichaMovida];
                   cout << "Te has salvado por los pelos" << endl;
                   seises = 0;
               }
               else {

                   if (calle1[jugadores[jugadorTurno][ultimaFichaMovida]] == jugadorTurno) {

                       calle1[jugadores[jugadorTurno][ultimaFichaMovida]] = calle2[jugadores[jugadorTurno][ultimaFichaMovida]];
                       calle2[jugadores[jugadorTurno][ultimaFichaMovida]] = Ninguno;
                   }
                   else if (calle2[jugadores[jugadorTurno][ultimaFichaMovida]] == jugadorTurno) {

                       calle2[jugadores[jugadorTurno][ultimaFichaMovida]] = Ninguno;
                   }

                   cout << "Te vuelves a casa por correr y si estabas en ella descansa que hace frio fuera" << endl;
                   jugadores[jugadorTurno][ultimaFichaMovida] = -1;
                   seises = 0;
               }
           }
           else {

               if (tirada == 5 && procesa5(jugadores, jugadorTurno, calle2) == true) {

                   saleFicha(jugadores, jugadorTurno, casilla, premio, calle1, calle2);
               }
               else {

                   mover(jugadores, jugadorTurno, ficha, casilla, premio, tirada, ultimaFichaMovida, puede, calle1, calle2);
               }
           }

           // Gracias a esto sabemos si se debe pasar turno o no

           if (premio == 10 || premio == 20 || seises == 1 || seises == 2) {

               turno = false;
           }
           else {

               turno = true;
           }

           // Con esto se pasa el turno o no convenientemente

           if (turno == true) {

               if (jugadorTurno == Amarillo) {
                   jugadorTurno = Azul;
               }
               else if (jugadorTurno == Azul) {
                   jugadorTurno = Rojo;
               }
               else if (jugadorTurno == Rojo) {
                   jugadorTurno = Verde;
               }
               else if (jugadorTurno == Verde) {
                   jugadorTurno = Amarillo;
               }
           }
           else if (turno == false) {

               jugadorTurno = jugadorTurno;
           }

           todasenMeta = todasEnMeta(jugadores[jugadorTurno]);   
       }
   }

   // Indica el ganador

   cout << "Ha ganado el jugador " << colorACadena(jugadorTurno) << endl;
 
   return 0;
}


/*---------------------------------------------------------------------------------------------------------------
                                                  SUBPROGRAMAS
----------------------------------------------------------------------------------------------------------------*/


// SUBPROGRAMAS DE INICIALIZACIÓN

void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, tColor& jugadorTurno) {

    int turno;
    
    srand(time(NULL));
    turno = rand() % 4;

    switch (turno) {
    case 0:
        jugadorTurno = Amarillo;
        break;
    case 1:
        jugadorTurno = Azul;
        break;
    case 2:
        jugadorTurno = Rojo;
        break;
    case 3:
        jugadorTurno = Verde;
    }


    for (int i = 0; i < NUM_JUGADORES; i++) {
        for (int f = 0; f < NUM_FICHAS; f++) {
            jugadores[i][f] = -1;
        }
    }

    for (int h = 0; h < NUM_CASILLAS; h++) {
        calle1[h] = Ninguno;
        calle2[h] = Ninguno;
    }

    setColor(Gris);
}

void cargar(tJugadores jugadores, tColor& jugadorTurno, tCasillas calle1, tCasillas calle2) {
    ifstream archivo;
    int jugador, casilla;
    string nombreFichero;

    cout << "Introduce nombre del archivo de carga: ";
    getline(cin, nombreFichero);
    archivo.open(nombreFichero);
    if (archivo.is_open()) {
        setColor(Gris);
        for (int i = 0; i < NUM_CASILLAS; i++)
            calle1[i] = calle2[i] = Ninguno;
        for (int i = 0; i < NUM_JUGADORES; i++)
            for (int f = 0; f < NUM_FICHAS; f++) {
                archivo >> casilla;
                jugadores[i][f] = casilla;
                if ((casilla >= 0) && (casilla < NUM_CASILLAS))
                    if (calle1[casilla] == Ninguno)
                        calle1[casilla] = tColor(i);
                    else
                        calle2[casilla] = tColor(i);
            }
        archivo >> jugador;
        jugadorTurno = tColor(jugador);
        archivo.close();
    }
    else 
        iniciar(jugadores, calle1, calle2, jugadorTurno);
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

void saleFicha(tJugadores jugadores, tColor jugadorTurno, int casilla, int& premio, tCasillas calle1, tCasillas calle2) {

    int casa = -1;

    if (calle2[salidaJugador(jugadorTurno)] == Ninguno) {

        calle2[salidaJugador(jugadorTurno)] = calle1[salidaJugador(jugadorTurno)];

        calle1[salidaJugador(jugadorTurno)] = jugadorTurno;

        jugadores[jugadorTurno][primeraEn(jugadores[jugadorTurno], casa)] = salidaJugador(jugadorTurno);
    }
    else {

        casilla = salidaJugador(jugadorTurno),

        aCasita(jugadores, casilla, premio, calle2);

        calle2[salidaJugador(jugadorTurno)] = calle1[salidaJugador(jugadorTurno)];

        calle1[salidaJugador(jugadorTurno)] = jugadorTurno;

        jugadores[jugadorTurno][primeraEn(jugadores[jugadorTurno], casa)] = salidaJugador(jugadorTurno);

    }

}

void aCasita(tJugadores jugadores, int casilla, int& premio, tCasillas calle2) {

  
        jugadores[calle2[casilla]][segundaEn(jugadores[calle2[casilla]], casilla)] = -1;

        cout << "Te has comido a el jugador " << colorACadena(calle2[casilla]) << endl;

        calle2[casilla] = Ninguno;

        premio = 20;

}

bool puente(const tCasillas calle1, const tCasillas calle2, int casilla, tColor jugadorTurno) {

    bool puente = false;
    
    if ((calle1[casilla] == calle2[casilla]) && (esSeguro(casilla) == true) && (calle1[casilla] != Ninguno) && (calle2[casilla] != Ninguno) && (calle1[casilla] != jugadorTurno ) && (calle2[casilla] != jugadorTurno)) {
       
        puente = true;
    }
    else {
       
        puente = false;
    }
    
    return puente;
}


// VISUALIZACIÓN DEL TABLERO

void mostrar(const tJugadores jugadores, const tCasillas calle1, const tCasillas calle2) {
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
        setColor(calle2[i]);
        if (calle2[i] != Ninguno)
            cout << primeraEn(jugadores[calle2[i]], i) + 1;
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
        setColor(calle1[i]);
        if (calle1[i] != Ninguno)
            cout << segundaEn(jugadores[calle1[i]], i) + 1;
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
                ficha = primeraEn(jugadores[jug], 101 + i);
                if (ficha != -1) {
                    cout << ficha + 1;
                    if (cuantasEn(jugadores[jug], 101 + i) > 1) {
                        ficha = segundaEn(jugadores[jug], 101 + i);
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
                if (jugadores[jug][i] == -1) // En casa
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
                ficha = primeraEn(jugadores[jug], i);
                if (ficha != -1) {
                    cout << ficha + 1;
                    if (cuantasEn(jugadores[jug], i) > 1) {
                        ficha = segundaEn(jugadores[jug], i);
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
        cout << ((jugadores[jug][0] == 108) ? '1' : '.');
        cout << ((jugadores[jug][1] == 108) ? '2' : '.');
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
        cout << ((jugadores[jug][2] == 108) ? '3' : '.');
        cout << ((jugadores[jug][3] == 108) ? '4' : '.');
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
    
    cout << "Ha salido un " << tirada << endl;
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

bool procesa5(tJugadores jugadores, tColor jugadorTurno, tCasillas calle2) {

    bool procesa5;
    int casa = -1;

    if (cuantasEn(jugadores[jugadorTurno], casa) > 0 && calle2[salidaJugador(jugadorTurno)] != jugadorTurno) {

        procesa5 = true;
    }
    else {

        procesa5 = false;
    }

    return procesa5;
}

int procesaPuente(tJugadores jugadores, tColor jugadorTurno, int& ultimaFichaMovida, int& tirada, int& ind, tCasillas calle1, tCasillas calle2) {

    int puentes = 0;
    bool centinela = false;
    int casillaPuente = 0;

    for (int h = 0; h < NUM_CASILLAS; h++) {

        if (calle1[h] == calle2[h] && calle1[h] == jugadorTurno && calle2[h] == jugadorTurno) {

            puentes = puentes + 1;
            casillaPuente = h;
        }
    }

    if (puentes == 1) {

        while (ind < NUM_FICHAS && centinela == false) {

            if (jugadores[jugadorTurno][ind] == casillaPuente) {

                centinela = true;
            }

            ind++;
        }

        if (puedeMover(jugadores, jugadorTurno, ind, casillaPuente, tirada, calle1, calle2) == true) {

            puentes = 1;
        }
        else {

            puentes = 0;
        }
    }
    return puentes;
}

bool puedeMover(const tJugadores jugadores, tColor jugadorTurno, int ficha, int& casilla, int tirada, const tCasillas calle1, const tCasillas calle2) {

    int contador = jugadores[jugadorTurno][ficha];
    bool puedeMover = true;
    
    if ((jugadores[jugadorTurno][ficha] == -1) || (jugadores[jugadorTurno][ficha] == 108)) {

        puedeMover = false;
    }
    else {

        casilla = jugadores[jugadorTurno][ficha] + tirada;
        casilla = comportamientoTablero(casilla, jugadores, jugadorTurno, ficha, tirada);
        while ((contador <= casilla) && (puedeMover == true)) {

            if (contador > 68 && contador < 99) {

                contador = 100;
            }
            
            if (puente(calle1, calle2, contador, jugadorTurno) == true) {

                puedeMover = false;
            }
            else if ((contador == casilla) && (calle1[contador] == calle2[contador]) && (calle1[contador] != Ninguno) && (calle2[contador] != Ninguno)) {

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

int comportamientoTablero(int casilla, const tJugadores jugadores, tColor jugadorTurno, int ficha, int tirada) {

    if (casilla > 100) {

        casilla = casilla;
    }
    else if (casilla > 67) {

        casilla = 68 - jugadores[jugadorTurno][ficha];
        casilla = tirada - casilla;
    }
    else if ((casilla > zanataJugador(jugadorTurno)) && (jugadores[jugadorTurno][ficha] <= zanataJugador(jugadorTurno)) && (jugadorTurno != 0)){

        casilla = zanataJugador(jugadorTurno) - jugadores[jugadorTurno][ficha];
        tirada = tirada - casilla;
        casilla = tirada + 100;
    }
    else if ((jugadorTurno == 0) && (casilla > 68)) {

        casilla = zanataJugador(jugadorTurno) - jugadores[jugadorTurno][ficha];
        tirada = tirada - casilla;
        casilla = tirada + 100;
    }
    else {

        casilla = casilla;
    }

    return casilla;
}

void mover(tJugadores jugadores, tColor jugadorTurno, int ficha, int casilla, int& premio, int tirada, int& ultimaFichaMovida, tFichas puede, tCasillas calle1, tCasillas calle2) {

    int ind = 0; // Para saber las fichas que están en puentes con procesa puentes
    int i = 0;

    if ((tirada == 6 || tirada == 7) && procesaPuente(jugadores, jugadorTurno, ultimaFichaMovida, tirada, ind, calle1, calle2) == 1) {

        ficha = ind - 1;
        casilla = jugadores[jugadorTurno][ficha] + tirada;
        casilla = comportamientoTablero(casilla, jugadores, jugadorTurno, ficha, tirada);
        cout << "Tienes que abrir el puente" << endl;

        calle1[jugadores[jugadorTurno][ficha]] = calle2[jugadores[jugadorTurno][ficha]];
        calle2[jugadores[jugadorTurno][ficha]] = Ninguno;

        if (calle1[casilla] != Ninguno && calle1[casilla] != jugadorTurno && esSeguro(casilla) == false && !(casilla > 68)) {

            calle2[casilla] = calle1[casilla];

            aCasita(jugadores, casilla, premio, calle2);

            calle1[casilla] = jugadorTurno;

            jugadores[jugadorTurno][ficha] = casilla;
        }
        else if (esSeguro(casilla) == true || calle1[casilla] == jugadorTurno) {

            calle2[casilla] = jugadorTurno;

            jugadores[jugadorTurno][ficha] = casilla;
        }
        else if (casilla == 108) {

            jugadores[jugadorTurno][ficha] = casilla;

            cout << "Has metido una ficha dentro de casa y te cuentas 10" << endl;

            premio = 10;
        }
        else {

            calle1[casilla] = jugadorTurno;

            jugadores[jugadorTurno][ficha] = casilla;
        }
    

        ultimaFichaMovida = ficha;

    }
    else {


        for (int i = 0; i < NUM_FICHAS; i++) {

            cout << i + 1 << ": ";
            if (puedeMover(jugadores, jugadorTurno, i, casilla, tirada, calle1, calle2) == true) {

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
            } while (puedeMover(jugadores, jugadorTurno, ficha, casilla, tirada, calle1, calle2) == false);


            if (calle2[jugadores[jugadorTurno][ficha]] == Ninguno) {

                calle1[jugadores[jugadorTurno][ficha]] = Ninguno;
            }
            else if (calle2[jugadores[jugadorTurno][ficha]] != Ninguno) {

                calle1[jugadores[jugadorTurno][ficha]] = calle2[jugadores[jugadorTurno][ficha]];
                calle2[jugadores[jugadorTurno][ficha]] = Ninguno;
            }

            if (calle1[casilla] != Ninguno && calle1[casilla] != jugadorTurno && esSeguro(casilla) == false && !(casilla > 68)){

                calle2[casilla] = calle1[casilla];

                aCasita(jugadores, casilla, premio, calle2);

                calle1[casilla] = jugadorTurno;

                jugadores[jugadorTurno][ficha] = casilla;
            }
            else if ((esSeguro(casilla) == true && calle1[casilla] != Ninguno) || calle1[casilla] == jugadorTurno) {

                calle2[casilla] = jugadorTurno;

                jugadores[jugadorTurno][ficha] = casilla;
            }
            else if (casilla == 108) {

                jugadores[jugadorTurno][ficha] = casilla;

                cout << "Has metido una ficha dentro de casa y te cuentas 10" << endl;

                premio = 10;
            }
            else {

                calle1[casilla] = jugadorTurno;

                jugadores[jugadorTurno][ficha] = casilla;
            }
        }

        ultimaFichaMovida = ficha;
    }
}
