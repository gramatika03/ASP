#ifndef _Stack_h
#define _Stack_h

class Stack {
	struct Node {
		int indeks;
		Node* sled;
		Node(int i, Node* s = nullptr) : indeks(i), sled(s) {};
	};

	Node* prvi = nullptr, *poslednji = nullptr;

	void kopiraj(const Stack& s);
	void premesti(Stack& s);
	void brisi();
public:
	Stack() = default;
	Stack(const Stack& s);
	Stack(Stack&& s);
	~Stack();
	Stack& operator=(const Stack& s);
	Stack& operator=(Stack&& s);

	void dodajElement(int i);

	int vrhSteka() const;
	int skiniSaSteka();

	bool stekPrazan() const;
};




#endif