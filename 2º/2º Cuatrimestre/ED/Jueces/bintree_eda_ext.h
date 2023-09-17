#ifndef BINTREE_EDA_EXT_H_
#define BINTREE_EDA_EXT_H_

#include <queue>
#include <iostream>

#include "bintree_eda.h"

using namespace std;

template <typename T>
class bintree_eda_ext : public bintree<T> {
	using Link = typename bintree <T> ::Link;

public:

	bintree_eda_ext(){}

	bintree_eda_ext(bintree_eda_ext <T > const& l, T const& e, bintree_eda_ext <T > const& r) : bintree <T >(l, e, r) {}

	int level(T const& es) {
		return levelOrder(this->raiz, es);
	}

private:

	int levelOrder(Link raiz, T const& es) {

		int nivel = 0;

		if (raiz != nullptr) {

			queue <Link> pendientes; // Cola de pendientes

			pendientes.push(raiz); // Inicializamos la cola con el Link raiz

			bool encontrado = false;

			while (!pendientes.empty() && !encontrado) {

				
				pendientes = hijos(encontrado, pendientes, es);

				nivel++;
			}

			if (!encontrado) nivel = 0;
		}

		return nivel;
	}

	queue <Link> hijos(bool &encontrado, queue<Link> &pendientes, T const& es) {

		queue <Link> hijos;

		int repet = 0;

		while (!pendientes.empty() && !encontrado) {

			Link sig = pendientes.front(); // Obtenemos el primero de la cola

			pendientes.pop();

			if (sig->elem == es) repet++;

			if (repet >= 2) encontrado = true;


			if (sig->left != nullptr) // Anadimos el hijo izquierdo si no es nulo
				hijos.push(sig->left);
			if (sig->right != nullptr) // Anadimos el hijo derecho si no es nulo
				hijos.push(sig->right);
		}

		return hijos;
	}

};

template <typename T>
inline bintree_eda_ext<T> leerArbol_ext(T vacio) {
	T raiz;
	std::cin >> raiz;
	if (raiz == vacio) { // es un árbol vacío
		return {};
	}
	else { // leer recursivamente los hijos
		bintree_eda_ext<T> iz = leerArbol_ext(vacio);
		bintree_eda_ext<T> dr = leerArbol_ext(vacio);
		return { iz, raiz, dr };
	}
}






#endif