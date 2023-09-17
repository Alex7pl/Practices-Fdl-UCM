#ifndef list_eda_plus_h
#define list_eda_plus_h

# include <iostream>
# include <list>

template <class T>

T Mysearch(T const& ini1, T const& fin1, T const& ini2, T const& fin2) {
	auto it1 = ini1; auto it2 = ini2;
	while (it1 != fin1 && it2 != fin2) {
		if (*it1 == *ini2) { // recorre el subrango
			auto aux1 = it1; it2 = ini2;
			while (aux1 != fin1 && it2 != fin2 && *aux1 == *it2) {
				++aux1;
				++it2;
			}
			if (it2 != fin2) ++it1;
		}
		else ++it1;
	}
	return it1;
}








#endif