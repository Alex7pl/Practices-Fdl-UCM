#include <iostream>
using namespace std;
#include <cmath>

int main(){
	
	double fahrenheit, celsius;
	
	cout << "Introduzca la temperatura en fahrenheit: ";

	cin >> fahrenheit;
	
	celsius = ((fahrenheit - 32) * 5) / 9;
	
	cout << "La temperatura en grados celsius respecto a grados fahrenheit es: " << celsius << endl;
	
	return 0;
	
	
}