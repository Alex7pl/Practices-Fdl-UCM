#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;



bool resuelveCaso() {

    int s, k, aux;
    cin >> s >> k;

    if (!cin) return false;

    deque<int> lista, mayores;

    for (int i = 0; i < k; ++i) {
        cin >> aux;
        lista.push_back(aux);
        while (!mayores.empty() && mayores.back() < aux) mayores.pop_back();
        mayores.push_back(aux);
    }

    for (int i = k; i < s; ++i) {
        cout << mayores.front() << " ";
        cin >> aux;
        lista.push_back(aux);
        if (mayores.front() == lista.front()) mayores.pop_front();
        lista.pop_front();
        while (!mayores.empty() && mayores.back() < aux) mayores.pop_back();
        mayores.push_back(aux);
    }

    cout << mayores.front() << '\n';

    return true;
}


int main() {
# ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std :: cin to casos .txt
# endif


	while (resuelveCaso()) {}

# ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system(" PAUSE ");
# endif
	return 0;
}