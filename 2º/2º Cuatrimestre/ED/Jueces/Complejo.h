#ifndef COMPLEJO_H
#define COMPLEJO_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <exception>

using namespace std;

class complejo {

private: float _numR, _numIm; int _numIt;
public:
	complejo(float numReal = 0, float numImag = 0, int numIter = 0) :_numR(numReal), _numIm(numImag), _numIt(numIter) {
		/*if (numReal < -2 || numReal >2 || numImag < -2 || numImag >2 || numIter < 100 || numIter > 500){
			throw invalid_argument("ERROR");
		}*/
	}

	float numReal() {
		return _numR;
	}

	float numImag() {
		return _numIm;
	}

	int numIter() {
		return _numIt;
	}

	complejo operator +(const complejo& c) const {
		float nR, nI;

		nR = _numR + c._numR;
		nI = _numIm + c._numIm;

		return complejo(nR, nI, _numIt);

	}

	complejo operator * (const complejo& c)const {
		float nR, nI;

		nR = (_numR * c._numR) - (_numIm * c._numIm);
		nI = (_numR * c._numIm) + (_numIm * c._numR);

		return complejo(nR, nI, _numIt);
	}

	int operator%(const complejo& c)const {
		int sol;

		sol = sqrt((_numR * _numR) + (_numIm * _numIm));

		return sol;
	}
};

inline istream& operator>>(istream& in, complejo& c) {
	float r, i;
	int t;

	cin >> r >> i >> t;

	c = complejo(r, i, t);

	return in;
}

#endif
