#include "PrioritetniRed.h"

PrioritetniRed::PrioritetniRed(const PrioritetniRed& pr){
	kopiraj(pr);
}

PrioritetniRed::PrioritetniRed(PrioritetniRed&& pr){
	premesti(pr);
}

PrioritetniRed::~PrioritetniRed(){
	brisi();
}

PrioritetniRed& PrioritetniRed::operator=(const PrioritetniRed& pr){
	if (this != &pr) {
		brisi();
		kopiraj(pr);
	}
	return *this;
}

PrioritetniRed& PrioritetniRed::operator=(PrioritetniRed&& pr){
	if (this != &pr) {
		brisi();
		premesti(pr);
	}
	return *this;
}

void PrioritetniRed::dodajCvor(string imeCvora, double pov, int poz){
	if (!poseceno[poz]) {
		Elem* novi = new Elem(imeCvora, pov);
		if (!prvi) prvi = novi;
		else poslednji->sled = novi;
		poslednji = novi;
		poseceno[poz] = true;
	}
	else {
		Elem* tek = prvi;
		while (tek) {
			if (tek->ime == imeCvora) break;
			tek = tek->sled;
		}
		if (tek) {
			if (tek->povezanost < pov) tek->povezanost = pov;
		}
	}
}

Elem* PrioritetniRed::skiniCvor(){
	if (!prazan()) {
		Elem* max = prvi;
		Elem* tek = prvi, * prethodni = nullptr, *stari = prvi;
		while (tek) {
			if (tek->povezanost > max->povezanost) max = tek;
			tek = tek->sled;
		}
		tek = prvi;
		while (tek) {
			if (tek->sled == max) {
				prethodni = tek;
				break;
			}
			tek = tek->sled;
		}
		if (max == prvi) {
			if (prvi == poslednji) {
				prvi = poslednji = nullptr;
				max->sled = nullptr;
				return max;
			}
			else {
				prvi = prvi->sled;
				max->sled = nullptr;
				return max;
			}
		}
		else if (max == poslednji) {
			poslednji = prethodni;
			poslednji->sled = nullptr;
			max->sled = nullptr;
			return max;
		}
		else {
			prethodni->sled = max->sled;
			max->sled = nullptr;
			return max;
		}
	}
}

void PrioritetniRed::postaviPosecenost(int i){
	poseceno[i] = true;
}

bool PrioritetniRed::prazan() const{
	if (prvi == nullptr && poslednji == nullptr) return true;
	return false;
}

void PrioritetniRed::kopiraj(const PrioritetniRed& pr){
	Elem* tek = pr.prvi;
	brojCvorova = pr.brojCvorova;
	while (tek) {
		Elem* novi = new Elem(tek->ime, tek->povezanost);
		if (!prvi) prvi = novi;
		else poslednji->sled = novi;
		poslednji = novi;
		tek = tek->sled;
	}
	poseceno = new bool[brojCvorova];
	for (int i = 0; i < brojCvorova; i++) poseceno[i] = pr.poseceno[i];
}

void PrioritetniRed::premesti(PrioritetniRed& pr){
	prvi = pr.prvi;
	poslednji = pr.poslednji;
	brojCvorova = pr.brojCvorova;
	poseceno = pr.poseceno;

	pr.prvi = pr.poslednji = nullptr; 
	pr.poseceno = nullptr;
}

void PrioritetniRed::brisi(){
	while (prvi) {
		Elem* stari = prvi;
		prvi = prvi->sled;
		delete stari;
	}
	delete[] poseceno;
	prvi = poslednji = nullptr;
	poseceno = nullptr;
	brojCvorova = 0;
}
