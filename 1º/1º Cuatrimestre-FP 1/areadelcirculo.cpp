#include <iostream>
using namespace std;
#include <cmath>

int main(){

double radio, area;

const double PI = 3.141592;

cout << "Introduzca el radio del circulo: ";

cin >>radio;

area = PI * pow(radio, 2);


cout << "El area de un circulo de radio " << radio << "es: " << area << endl;

return 0;
}

