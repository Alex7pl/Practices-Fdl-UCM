#ifndef list_eda_plus_h
#define list_eda_plus_h


#include <iostream>
#include <stdexcept>
#include <cassert>

#include "deque_eda.h"
#include "list_eda.h"

using namespace std;

template <class T>
class list_eda_plus : public list<T> {

protected:

    using Nodo = typename deque<T>::Nodo;

    template <class Apuntado>
    class reverse_iterator {
        // puntero al nodo actual del recorrido
        Nodo* act;
        // puntero al nodo fantasma (para saber cuándo estamos fuera)
        Nodo* fan;
    public:

        reverse_iterator() : act(nullptr), fan(nullptr) {}

        // para acceder al elemento apuntado
        Apuntado& operator*() const {
            if (act == fan) throw std::out_of_range("fuera de la lista");
            return act->elem;
        }

        // para acceder a un método del elemento apuntado
        // it->metodo() en vez de (*it).metodo()
        Apuntado* operator->() const {
            return &(operator*());
        }

        reverse_iterator& operator++() { // ++ prefijo (recomendado)
            if (act == fan) throw std::out_of_range("fuera de la lista");
            act = act->ant;
            return *this;
        }

        reverse_iterator operator++(int) { // ++ postfijo
            reverse_iterator ret(*this);
            operator++();
            return ret;
        }

        bool operator==(reverse_iterator const& that) const {
            return act == that.act && fan == that.fan;
        }

        bool operator!=(reverse_iterator const& that) const {
            return !(*this == that);
        }

    private:
        // para que list pueda construir objetos del tipo iterador
        friend class list_eda_plus;

        // constructora privada
        reverse_iterator(Nodo* ac, Nodo* fa) : act(ac), fan(fa) {}
    };


public:

   
    using reverse_iterator = reverse_iterator<T>;

    reverse_iterator rbegin() {
        return reverse_iterator(this->fantasma->ant, this->fantasma);
    }

    reverse_iterator rend() {
        return reverse_iterator(this->fantasma, this->fantasma);
    }

    void ex() {

    }



};



#endif
