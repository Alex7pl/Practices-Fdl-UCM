#ifndef stack_eda_plus_h
#define stack_eda_plus_h

#include <iostream>
#include <string>
#include "stack_eda.h"
using namespace std;


template <typename T>
class stack_eda_plus : public stack<T> {


public:

	void analizaP(const string cadena) {

		unsigned int i = 0;

		while (i < cadena.size()) {

			if (cadena[i] == '(' || cadena[i] == '[' || cadena[i] == '{') {

				this->push(cadena[i]);
			}
			else {

				if (cadena[i] == ')') {

					if (!this->empty() && this->top() == '(') {
						this->pop();
					}
					else {
						this->push(cadena[i]);
					}
				}
				else if (cadena[i] == ']') {

					if (!this->empty() && this->top() == '[') {
						this->pop();
					}
					else {
						this->push(cadena[i]);
					}
				}
				else if (cadena[i] == '}') {

					if (!this->empty() && this->top() == '{') {
						this->pop();
					}
					else {
						this->push(cadena[i]);
					}
				}
			}

			i++;
		}

		if (this->empty()) cout << "SI\n";
		else cout << "NO\n";
	}
};




#endif
