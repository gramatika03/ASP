#ifndef _PrioritetniRed_h
#define _PrioritetniRed_h
#include <string>

using namespace std;

struct Elem {
	string ime;
	double povezanost;
	Elem* sled;
	Elem(string i, double p = 0, Elem* s = nullptr) : povezanost(p), ime(i), sled(s) {};
};

class PrioritetniRed {
	Elem* prvi = nullptr;
	Elem* poslednji = nullptr;
	int brojCvorova;

	bool* poseceno;

	void kopiraj(const PrioritetniRed& pr);
	void premesti(PrioritetniRed& pr);
	void brisi();
public:
	PrioritetniRed(int k) {
		poseceno = new bool[k];
		for (int i = 0; i < k; i++) poseceno[i] = false;
		brojCvorova = k;
	};
	PrioritetniRed(const PrioritetniRed& pr);
	PrioritetniRed(PrioritetniRed&& pr);
	~PrioritetniRed();
	PrioritetniRed& operator=(const PrioritetniRed& pr);
	PrioritetniRed& operator=(PrioritetniRed&& pr);

	void dodajCvor(string imeCvora, double pov, int poz);
	Elem* skiniCvor();

	void postaviPosecenost(int i);

	bool prazan() const;
};

#endif