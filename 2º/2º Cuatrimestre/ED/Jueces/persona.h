#ifndef persona_h
#define persona_h
# include <iostream>


using namespace std;

class persona {


private:

	int edad;
	string nombre;

public:

	persona() {}

	persona(int e, string n) : edad(e), nombre(n) {};

	int getEdad() const{

		return this->edad;
	}

	string getNombre() const{

		return this->nombre;
	}
};


#endif
