#ifndef IPUD_H
#define UPUD_H

#include <iostream>
#include <unordered_map>
# include <list>

using namespace std;

class sistema {

private:

	struct tInfo
	{
		string artista;
		int duracion;
		list<string>::iterator listaP;
		list<string>::iterator listaR;
	};

	int duracionT;

	unordered_map<string, tInfo> canciones;

	list<string> playlist;
	list<string> recents;

public:

	sistema() { duracionT = 0; }

	void addSong(string s, string a, int d) {

		if (!canciones.insert({ s, {a, d, playlist.end(), recents.end()} }).second) {
			throw invalid_argument("addSong");
		}
	}

	void addToPlaylist(string s) {

		if (canciones.count(s) == 0) {
			throw invalid_argument("addToPlaylist");
		}

		if (canciones[s].listaP == playlist.end()) {

			canciones[s].listaP = playlist.insert(playlist.end(), s);

			duracionT += canciones[s].duracion;
		}
	}

	string current() {

		if (playlist.empty()) {
			throw invalid_argument("current");
		}

		return playlist.front();
	}

	pair<bool, string> play() {

		pair<bool, string> sol;

		if (!playlist.empty()) {

			string primera = playlist.front();

			playlist.pop_front();

			duracionT -= canciones[primera].duracion;

			canciones[primera].listaP = playlist.end();

			if (canciones[primera].listaR != recents.end()) {
				
				recents.erase(canciones[primera].listaR);
			}

			canciones[primera].listaR = recents.insert(recents.begin(), primera);
			
			sol.first = true;
			sol.second = primera;
		}
		else {
			sol.first = false;
			sol.second = "No hay canciones en la lista";
		}

		return sol;
	}

	int totalTime() {

		return duracionT;
	}

	list<string> reciente(int n) {

		list<string> lista;

		for (string const& c : recents) {
			lista.push_back(c);
			if (lista.size() == n) break;
		}
		return lista;
	}

	void deleteSong(string s) {

		auto it = canciones.find(s);

		if (it != canciones.cend()) {
			
			if (it->second.listaP != playlist.end()) {
				playlist.erase(it->second.listaP);
				duracionT -= it->second.duracion;
			}

			if (it->second.listaR != recents.end()) {
				recents.erase(it->second.listaR);
			}

			canciones.erase(it);
		}


	}
};


#endif
