#include "Graf.h"


int main() {
	Graf graf;
	bool kraj = false;

	while (!kraj) {
		cout << "IZABERITE OPCIJU:" << endl;
		cout << "\t 1. FORMIRANJE I MANIPULACIJA GRAFOM" << endl << "\t 2. INTERAKCIJA SA BAZOM ZNANJA" << endl << "\t 3. ZAVRSI PROGRAM" << endl;
		cout << "IZBOR: ";
		int opcija;
		cin >> opcija;
		switch (opcija) {
		case 1:
			cout << "IZABERITE RADNJU: " << endl;
			cout << "\t 1. UCITAJ NOVI GRAF" << endl << "\t 2. DODAJ CVOR" << endl << "\t 3. UKLONI CVOR" << endl << "\t 4. DODAJ GRANU" << endl << "\t 5. UKLONI GRANU" << endl << "\t 6. ISPISI GRAF" << endl << "\t 7. OBRISI GRAF IZ MEMORIJE" << endl;
			cout << "IZBOR: ";
			int izbor;
			cin >> izbor;
			switch (izbor) {
			case 1:
				graf.obrisiIzMemorije();
				graf.ucitajGraf();
				break;
			case 2:
				graf.dodajCvor();
				break;
			case 3:
				graf.ukolniCvor();
				break;
			case 4:
				graf.dodajGranu();
				break;
			case 5:
				graf.ukloniGranu();
				break;
			case 6:
				graf.ispisiGraf();
				break;
			case 7:
				graf.obrisiIzMemorije();
				break;
			default:
				cout << "POGRESAN IZBOR" << endl;
				break;
			}
			break;
		case 2:
			cout << "IZABERITE RADNJU: " << endl;
			cout << "\t 1. NALAZENJE K NAJSLICNIJIH RECI" << endl << "\t 2. NAJKRACI PUT IZMEDJU ZADATIH RECI" << endl << "\t 3. NALAZENJE JAKO POVEZANIH RECI" << endl;
			cout << "IZBOR: ";
			cin >> izbor;
			switch (izbor) {
			case 1:
				graf.nadjiNajslicnijeReci();
				break;
			case 2:
				graf.pronadjiNajkraciPut();
				break;
			case 3:
				graf.jakoPovezaneKomponente();
				break;
			default:
				cout << "POGRESAN IZBOR" << endl;
				break;
			}
			break;
		case 3:
			break;
		default:
			cout << "POGRESAN IZBOR" << endl;
			break;
		}
		if (opcija == 3) { 
			graf.obrisiIzMemorije();
			kraj = true;
			break;
		}

	}

	return 0;
}