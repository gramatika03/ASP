#include "Stack.h"

void Stack::kopiraj(const Stack& s){
	Node* tek = s.prvi;
	while (tek) {
		Node* novi = new Node(s.prvi->indeks);
		if (!prvi) prvi = novi;
		else poslednji->sled = novi;
		poslednji = novi;
		tek = tek->sled;
	}

}

void Stack::premesti(Stack& s){
	prvi = s.prvi;
	poslednji = s.poslednji;
	s.prvi = s.poslednji = nullptr;
}

void Stack::brisi(){
	while (prvi) {
		Node* brisi = prvi;
		prvi = prvi->sled;
		delete brisi;
	}
}

Stack::Stack(const Stack& s){
	kopiraj(s);
}

Stack::Stack(Stack&& s){
	premesti(s);
}

Stack::~Stack(){
	brisi();
}

Stack& Stack::operator=(const Stack& s){
	if (this != &s) {
		brisi();
		kopiraj(s);
	}
	return *this;
}

Stack& Stack::operator=(Stack&& s){
	if (this != &s) {
		brisi();
		premesti(s);
	}
	return *this;
}

void Stack::dodajElement(int i){
	prvi = new Node(i, prvi);
	if (!poslednji) poslednji = prvi;
}

int Stack::vrhSteka() const{
	return prvi->indeks;
}

int Stack::skiniSaSteka(){
	int broj = prvi->indeks;
	Node* stari = prvi;
	prvi = prvi->sled;
	if (!prvi) prvi = poslednji = nullptr;
	delete stari;
	return broj;
}

bool Stack::stekPrazan() const{
	return !prvi;
}
