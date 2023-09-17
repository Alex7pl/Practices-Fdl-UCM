#ifndef double_linked_list_ed_plus_h
#define double_linked_list_ed_plus_h


#include "double_linked_list_ed.h"
#include <iostream>
using namespace std;

template<typename T>
class double_linked_list_ed_plus : public double_linked_list_ed<T> {
	using Nodo = typename double_linked_list_ed <T >::Nodo;

public:

	void print(std::ostream& o) const {
		Nodo* aux = this->fantasma->sig;
		if (aux != this->fantasma) {
			o << aux->elem;
			aux = aux->sig;
		}
		while (aux != this->fantasma) {
			o << ' ' << aux->elem;
			aux = aux->sig;
		}
		o << '\n';
	}

	void particion(int pivote) {

		Nodo* act = this->fantasma->ant;
		Nodo* aux = act->ant;

		while (aux != this->fantasma) {

			if (act->elem > pivote) {

				act = aux;
				aux = aux->ant;
			}
			else if (act->elem <= pivote && aux->elem <= pivote) {

				aux = aux->ant;
			}
			else if (act->elem <= pivote && aux->elem > pivote) {

				Nodo* mover = aux;

				aux = aux->ant;

				this->moverNodo(act, mover);
			}
		}
	}

	void eliminarIguales(double_linked_list_ed_plus& lista2) {

		Nodo* l1 = this->fantasma->sig;
		Nodo* l2 = lista2.fantasma->sig;

		while (l1 != this->fantasma) {

			if (l2 == lista2.fantasma || l1->elem < l2->elem) {

				Nodo* aux = l1;

				l1 = l1->sig;

				this->borra_elem(aux);
			}
			else if (l1->elem > l2->elem) {

				l2 = l2->sig;
			}
			else if (l1->elem == l2->elem) {

				l1 = l1->sig;
				l2 = l2->sig;
			}
		}
	}

	void intercambiar2() {

		Nodo* act = this->fantasma->sig;
		Nodo* si = act->sig;

		if (si != this->fantasma) this->fantasma->sig = si;

		while (si != this->fantasma) {

			Nodo* mov = si;

			si = si->sig;

			moverNodo(mov, act);

			if (si != this->fantasma) {

				act = si;
				si = si->sig;
			}
		}

		this->fantasma->ant = act;
	}

private:


	void moverNodo(Nodo* pos, Nodo* mover) {

		mover->sig->ant = mover->ant;
		mover->ant->sig = mover->sig;

		mover->sig = pos->sig;
		mover->ant = pos;
		pos->sig->ant = mover;
		pos->sig = mover;
	}


};

template <typename T >
inline std::ostream& operator<< (std::ostream& o, double_linked_list_ed_plus <T> const& l) {
	l.print(o);
	return o;
}

#endif
