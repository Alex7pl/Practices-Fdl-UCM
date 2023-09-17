#include <iostream>
#include <climits>
using namespace std;

int main(){

	const int N = 10;
	int max = INT_MIN; // inicializamos con el menor número entero
	int num, vueltas;


	cout << "Introduzca " << N << " numeros, separados por espacios: ";
	
	for (vueltas = 1; vueltas <= N; vueltas++) {
		
		cin >> num;
		
		if (num >= max) max = num;
		
		else max = max;
		
	}
	
	
	cout << "El maximo es el " << max << endl;
  
	
	return 0;

}