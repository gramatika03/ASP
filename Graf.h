#ifndef _Graf_h
#define _Graf_h
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "PrioritetniRed.h"
#include "Stack.h"

using namespace std;

class Graf {
	int brojCvorova = 0;
	string* imenaCvorova = nullptr;
	double** matricaOdnosa = nullptr;
	bool ucitan = false;

	bool proveriDaLiJeDodat(string* niz, int br, string rec) const;
	int pronadjiPoziciju(string ime) const;
	int nadjiMaksimum(double* niz, int br, bool* nizU) const;
public:
	Graf() = default;
	Graf(const Graf&) = delete;
	~Graf() = default;
	Graf& operator=(const Graf&) = delete;
	
	bool ucitajGraf();

	void dodajCvor();
	void ukolniCvor();

	void dodajGranu();
	void ukloniGranu();

	void ispisiGraf() const;

	void obrisiIzMemorije();

	void nadjiNajslicnijeReci() const;

	void pronadjiNajkraciPut() const;

	void jakoPovezaneKomponente() const;
};





#endif