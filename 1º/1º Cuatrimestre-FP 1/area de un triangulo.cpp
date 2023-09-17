
#include <iostream>
using namespace std;
#include <cmath>

int main(){
	
	const double PI = 3.14159;
	
	double lado1, lado2, area, angulo, radianes;
	
	cout << "Introduzca el primer lado del triangulo: ";
	
	cin >> lado1;
	
	cout << "Introduzca el segundo lado del triangulo: ";
	
	cin >> lado2;
	
	cout << "Por ultimo, introduzca el angulo del triangulo expresado en grados: ";
	
	cin >> angulo;
	
	radianes = (angulo * PI) / 180;        //Sirve para pasar el ángulo de grados a radianes
	
	area = ((0.5 * lado1) * lado2) * sin(radianes);
	
	cout << "El area de un triangulo de lados " << lado1 << " y " << lado2 << " y de angulo " << angulo << " es " << area << endl;
	
	return 0;
}