#ifndef linked_list_ed_plud_h
#define linked_list_ed_plus_h


#include "linked_list_ed.h"
#include <iostream>
#include <sstream>

using namespace std;

template <typename T >
class linked_list_ed_plus : public linked_list_ed <T > {
	using Nodo = typename linked_list_ed <T >::Nodo;


public:

	void print(std::ostream& o) const {
		Nodo* aux = this->prim;
		if (aux != nullptr) {
			o << aux->elem;
			aux = aux->sig;
		}
		while (aux != nullptr) {
			o << ' ' << aux->elem;
			aux = aux->sig;
		}
		o << '\n';
	}

	void borrarMenores() {

		Nodo* act = this->prim;
		Nodo* aux = act->sig;

		while (aux != nullptr) {

			if (act->elem <= aux->elem) {

				act = aux;
				aux = aux->sig;
			}
			else {

				Nodo* aux2 = aux;
				aux = aux->sig;
				act->sig = aux;
				delete aux2;
			}
		}
	}

	void borrarP() {

		Nodo* aux = this->prim;
		Nodo* aux1 = aux->sig;

		int i = 2;

		while (aux1 != nullptr) {

			if (i % 2 == 0) {
				Nodo* aux2 = aux1;
				aux1 = aux1->sig;
				aux->sig = aux1;
				delete aux2;

			}
			else {
				aux = aux1;
				aux1 = aux1->sig;
			}
			i++;
		}
	}

	void mix(linked_list_ed_plus<T>& lista2) {

		Nodo* prim1 = this->prim;
		Nodo* prim2 = lista2.prim;
		Nodo* aux;

		if (prim1 == nullptr) {
			this->prim = prim2;
		}
		else if (prim1 != nullptr && prim2 != nullptr) {

			
			if (prim1->elem <= prim2->elem) {
				aux = prim1;
				prim1 = prim1->sig;
			}
			else {
				this->prim = prim2;
				aux = prim2;
				prim2 = prim2->sig;
			}

			
			while (prim1 != nullptr && prim2 != nullptr) {
				if (prim1->elem <= prim2->elem) {
					aux->sig = prim1;
					prim1 = prim1->sig;
					aux = aux->sig;
				}
				else {
					aux->sig = prim2;
					prim2 = prim2->sig;
					aux = aux->sig;
				}
			}

			if (prim1 == nullptr) {
				aux->sig = prim2;
				prim2 = prim2->sig;
			}
			else if (prim2 == nullptr) {
				aux->sig = prim1;
				prim1 = prim1->sig;
			}

		}


		lista2.prim = nullptr;
		lista2.ult = nullptr;
		
	}

	void invertir() {

		if (this->prim != nullptr && this->prim->sig != nullptr) {

			Nodo* act = this->prim->sig;
			Nodo* prev = this->prim;
			Nodo* aux = act->sig;


			while (aux != nullptr) {

				act->sig = prev;

				prev = act;
				act = aux;
				aux = aux->sig;
			}

			act->sig = prev;

			this->ult = this->prim;
			this->ult->sig = nullptr;
			this->prim = act;
		}
	}

	void eliminarIguales() {

		if (!this->empty()) {

			Nodo* act = this->prim->sig;
			Nodo* prev = this->prim;

			while (act != nullptr) {

				if (act->elem == prev->elem) {

					this->pop(act, prev);
				}
				else {

					prev = act;
					act = act->sig;
				}
			}
		}

	}

	void duplicar() {

		if (!this->empty()) {

			Nodo* aux = this->prim;

			Nodo* aux2 = aux->sig;


			while (aux2 != nullptr) {

				push(aux, aux->elem);

				aux = aux2;
				aux2 = aux2->sig;
			}

			this->push_back(aux->elem);

		}
	}

	void pop(Nodo*& act, Nodo*& prev) {

		Nodo* e = act;

		if (act->sig == nullptr) this->ult = prev;

		act = act->sig;
		prev->sig = act;

		delete e;
	}

	void push(Nodo* n, T const& elem) {

		Nodo* aux = n;
		Nodo* aux2 = aux->sig;
		Nodo* nw = new Nodo(elem);

		aux->sig = nw;
		nw->sig = aux2;
	}

	string elegidas(char c) {

			stringstream ss;

			Nodo* pos = this->prim;

			while (pos != nullptr) {

				if (pos->elem[0] == c) {

					ss << pos->elem << " ";
				}

				pos = pos->sig;
			}

			ss << "\n";

			return ss.str();
	}

};

template <typename T >
inline std::ostream& operator<< (std::ostream& o, linked_list_ed_plus <T > const& l) {
	l.print(o);
	return o;
}

#endif
