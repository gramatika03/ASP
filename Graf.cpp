#include "Graf.h"

bool Graf::proveriDaLiJeDodat(string* niz, int br, string rec) const {
	for (int i = 0; i < br; i++) {
		if (niz[i] == rec) return true;
	}
	return false;
}

int Graf::pronadjiPoziciju(string ime) const {
	for (int i = 0; i < brojCvorova; i++) {
		if (imenaCvorova[i] == ime) return i;
	}
	return -1;
}

int Graf::nadjiMaksimum(double* niz, int br, bool* nizU) const {
	double max = -10000;
	int maxPoz = 0;
	for (int i = 0; i < br; i++) {
		if (niz[i] > max) {
			if (!nizU[i]) {
				maxPoz = i;
				max = niz[i];
			}
		}
	}
	if (!nizU[maxPoz]) return maxPoz;
	return -1;
}

bool Graf::ucitajGraf() {
	ifstream fajl;
	string imeFajla;
	cout << "UNESITE IME FAJLA: ";
	cin >> imeFajla;
	fajl.open(imeFajla, ios::in);
	while (!ucitan) {
		if (fajl) {
			ucitan = true;
			int brojGrana;
			fajl >> brojCvorova >> brojGrana;
			imenaCvorova = new string[brojCvorova];
			for (int i = 0; i < brojCvorova; i++) fajl >> imenaCvorova[i];
			matricaOdnosa = (double**)calloc(brojCvorova, sizeof(double*));
			if (!matricaOdnosa) exit(1);
			for (int i = 0; i < brojCvorova; i++) {
				matricaOdnosa[i] = (double*)calloc(brojCvorova, sizeof(double));
				if (!matricaOdnosa[i]) exit(1);
			}
			for (int i = 0; i < brojGrana; i++) {
				string prviCvor, drugiCvor;
				double odnos;
				fajl >> prviCvor >> drugiCvor >> odnos;
				int vrsta = pronadjiPoziciju(prviCvor);
				int kolona = pronadjiPoziciju(drugiCvor);
				matricaOdnosa[vrsta][kolona] = odnos;
			}
			return true;
		}
		else {
			cout << "FAJL SA ZADATIM IMENOM NE POSTOJI" << endl;
			return false;
		}
	}
}

void Graf::dodajCvor() {
	if (ucitan) {
		cout << "UNESITE IME CVORA: ";
		string ime;
		cin >> ime;
		int postoji = pronadjiPoziciju(ime);
		if (postoji == -1) {
			brojCvorova++;
			matricaOdnosa = (double**)realloc(matricaOdnosa, brojCvorova * sizeof(double*));
			if (!matricaOdnosa) exit(1);
			for (int i = 0; i < brojCvorova - 1; i++) {
				matricaOdnosa[i] = (double*)realloc(matricaOdnosa[i], brojCvorova * sizeof(double));
				if (!matricaOdnosa[i]) exit(1);
				matricaOdnosa[i][brojCvorova - 1] = 0;
			}
			matricaOdnosa[brojCvorova - 1] = (double*)calloc(brojCvorova, sizeof(double));
			if (!matricaOdnosa[brojCvorova - 1]) exit(1);
			string* novaImena = new string[brojCvorova];
			for (int i = 0; i < brojCvorova - 1; i++) novaImena[i] = imenaCvorova[i];
			novaImena[brojCvorova - 1] = ime;
			delete[] imenaCvorova;
			imenaCvorova = novaImena;
		}
		else {
			cout << "CVOR VEC POSTOJI" << endl;
		}
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::ukolniCvor() {
	if (ucitan) {
		cout << "UNESITE IME CVORA KOJI ZELITE DA UKLONITE: ";
		string ime;
		cin >> ime;
		int pozicija = pronadjiPoziciju(ime);
		if (pozicija >= 0) {
			free(matricaOdnosa[pozicija]);
			for (int i = pozicija; i < brojCvorova - 1; i++) {
				matricaOdnosa[i] = matricaOdnosa[i + 1];
			}
			for (int i = 0; i < brojCvorova - 1; i++) {
				for (int j = pozicija; j < brojCvorova - 1; j++) matricaOdnosa[i][j] = matricaOdnosa[i][j + 1];
				matricaOdnosa[i] = (double*)realloc(matricaOdnosa[i], sizeof(double) * (brojCvorova - 1));
			}
			matricaOdnosa = (double**)realloc(matricaOdnosa, sizeof(double*) * (brojCvorova - 1));

			string* novaImena = new string[brojCvorova - 1];
			for (int i = 0; i < brojCvorova - 1; i++) {
				if (i >= pozicija) novaImena[i] = imenaCvorova[i + 1];
				else novaImena[i] = imenaCvorova[i];
			}
			delete[] imenaCvorova;
			imenaCvorova = novaImena;

			brojCvorova--;
		}
		else {
			cout << "NE POSTOJI CVOR SA ZADATIM IMENOM" << endl;
		}
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::dodajGranu() {
	if (ucitan) {
		string prviCvor, drugiCvor;
		double odnos;
		cout << "UNESITE IME PRVOG CVORA: ";
		cin >> prviCvor;
		cout << "UNESITE IME DRUGOG CVORA: ";
		cin >> drugiCvor;
		cout << "UNESTIE ODNOS: ";
		cin >> odnos;
		int vrsta = pronadjiPoziciju(prviCvor);
		int kolona = pronadjiPoziciju(drugiCvor);
		if (vrsta >= 0 && kolona >= 0) {
			matricaOdnosa[vrsta][kolona] = odnos;
		}
		else if (vrsta == -1) cout << "POGRESNO IME PRVOG CVORA" << endl;
		else if (kolona == -1) cout << "POGRESNO IME DRUGOG CVORA" << endl;
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::ukloniGranu() {
	if (ucitan) {
		string prviCvor, drugiCvor;
		cout << "UNESITE IME PRVOG CVORA: ";
		cin >> prviCvor;
		cout << "UNESITE IME DRUGOG CVORA: ";
		cin >> drugiCvor;
		int vrsta = pronadjiPoziciju(prviCvor);
		int kolona = pronadjiPoziciju(drugiCvor);
		if (vrsta >= 0 && kolona >= 0) {
			matricaOdnosa[vrsta][kolona] = 0;
		}
		else if (vrsta == -1) cout << "POGRESNO IME PRVOG CVORA" << endl;
		else if (kolona == -1) cout << "POGRESNO IME DRUGOG CVORA" << endl;
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::ispisiGraf() const {
	if (ucitan) {
		int maxDuzina = imenaCvorova[0].length();
		for (int i = 0; i < brojCvorova; i++) if (maxDuzina < imenaCvorova[i].length()) maxDuzina = imenaCvorova[i].length();
		for (int i = 0; i < brojCvorova; i++) {
			cout << setw(maxDuzina) << imenaCvorova[i] << '\t';
			for (int j = 0; j < brojCvorova; j++) {
				cout << setw(2) << matricaOdnosa[i][j] << '\t';
			}
			cout << endl;
		}
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::obrisiIzMemorije() {
	if (ucitan) {
		ucitan = false;
		delete[] imenaCvorova;
		for (int i = 0; i < brojCvorova; i++) free(matricaOdnosa[i]);
		brojCvorova = 0;
		free(matricaOdnosa);
	}
}

void Graf::nadjiNajslicnijeReci() const {
	if (ucitan) {
		int k;
		string rec;
		PrioritetniRed preQ(brojCvorova);
		string* trazeniCvorovi = nullptr;
		cout << "UNESITE KOLIKO NAJSLICNIJIH RECI TRAZITE: ";
		cin >> k;
		cout << "UNESITE REC ZA KOJU TRAZITE SLICNOST: ";
		cin >> rec;
		bool postojiIme = false;
		for (int i = 0; i < brojCvorova; i++) {
			if (imenaCvorova[i] == rec) postojiIme = true;
		}
		if (postojiIme) {
			int poz = pronadjiPoziciju(rec), brojPronadjenih = 0;
			trazeniCvorovi = new string[k];
			for (int i = 0; i < brojCvorova; i++) {
				if (matricaOdnosa[poz][i]) preQ.dodajCvor(imenaCvorova[i], matricaOdnosa[poz][i], i); //if (matricaOdnosa[i][poz]) preQ.dodajCvor(imenaCvorova[i], matricaOdnosa[i][poz], i);
			}
			preQ.postaviPosecenost(poz);
			if (k > brojCvorova) k = brojCvorova;
			while (brojPronadjenih != k && !preQ.prazan()) {
				Elem* tek = preQ.skiniCvor();
				int tekPoz = pronadjiPoziciju(tek->ime);
				for (int i = 0; i < brojCvorova; i++) {
					if (matricaOdnosa[tekPoz][i]) preQ.dodajCvor(imenaCvorova[i], tek->povezanost * matricaOdnosa[tekPoz][i], i); //if (matricaOdnosa[i][tekPoz]) preQ.dodajCvor(imenaCvorova[i], tek->povezanost * matricaOdnosa[i][tekPoz], i);
				}
				if (!proveriDaLiJeDodat(trazeniCvorovi, brojPronadjenih, tek->ime)) trazeniCvorovi[brojPronadjenih++] = tek->ime;
				delete tek;
			}
			cout << "NAJSLICNIJIH " << brojPronadjenih << " CVOROVA ZA CVOR " << imenaCvorova[poz] << ": ";
			for (int i = 0; i < brojPronadjenih; i++) {
				cout << trazeniCvorovi[i] << " ";
			}
			cout << endl;
			delete[] trazeniCvorovi;
		}
		else {
			cout << "CVOR SA ZADATIM IMENOM NE POSTOJI" << endl;
		}
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::pronadjiNajkraciPut() const {
	if (ucitan) {
		double* duzinaPuta = new double[brojCvorova];
		int* prethodniCvor = new int[brojCvorova];
		bool* vecUzet = new bool[brojCvorova];

		string prviCvor, drugiCvor;
		cout << "UNESITE IME PRVOG CVORA: ";
		cin >> prviCvor;
		cout << "UNESITE IME DRUGOG CVORA: ";
		cin >> drugiCvor;
		int pocetak = pronadjiPoziciju(prviCvor);
		int kraj = pronadjiPoziciju(drugiCvor);

		if (pocetak >= 0 && kraj >= 0) {
			for (int i = 0; i < brojCvorova; i++) {
				if (matricaOdnosa[pocetak][i]) {
					double k = matricaOdnosa[pocetak][i];
					duzinaPuta[i] = k;
					prethodniCvor[i] = pocetak;
				}
				else {
					duzinaPuta[i] = -10000000;
					prethodniCvor[i] = -1;
				}
				vecUzet[i] = false;
			}
			vecUzet[pocetak] = true;

			for (int i = 0; i < brojCvorova - 1; i++) {
				int trenutniCvor = nadjiMaksimum(duzinaPuta, brojCvorova, vecUzet);
				if (trenutniCvor >= 0) {
					double minDuzina = duzinaPuta[trenutniCvor];
					vecUzet[trenutniCvor] = true;
					for (int j = 0; j < brojCvorova; j++) {
						if (matricaOdnosa[trenutniCvor][j]) {
							if (minDuzina * matricaOdnosa[trenutniCvor][j] > duzinaPuta[j]) { //minDuzina + matricaOdnosa[trenutniCvor][j]
								double tr = minDuzina * matricaOdnosa[trenutniCvor][j]; //minDuzina + matricaOdnosa[trenutniCvor][j]
								duzinaPuta[j] = tr;
								prethodniCvor[j] = trenutniCvor;
							}
						}
					}
				}
			}

			if (duzinaPuta[kraj] >  -	10000000) {
				int* nizCvorova = new int[brojCvorova];
				int brojPrethodnika = 0;
				bool jednom = true;
				while (kraj != pocetak || jednom) {
					jednom = false;
					nizCvorova[brojPrethodnika++] = kraj;
					kraj = prethodniCvor[kraj];
				}
				nizCvorova[brojPrethodnika] = pocetak;
				cout << "NAJKRACI PUT JE: ";
				for (int i = brojPrethodnika; i > 0; i--) {
					cout << imenaCvorova[nizCvorova[i]] << " -(" << matricaOdnosa[nizCvorova[i]][nizCvorova[i - 1]] << ")";
					if (i > 0) cout << "->";
				}
				cout << imenaCvorova[nizCvorova[0]] << endl;
				delete[] nizCvorova;
			}
			else {
				cout << "NEMA PUTA IZMEDJU ZADATIH CVOROVA" << endl;
			}

			delete[] duzinaPuta;
			delete[] prethodniCvor;
			delete[] vecUzet;
		}
		else {
			cout << "POGRESNA IMENA CVOROVA" << endl;
		}
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}

void Graf::jakoPovezaneKomponente() const {
	if (ucitan) {
		cout << "UNESITE IME CVORA: ";
		string cvor;
		cin >> cvor;

		int pocetak = pronadjiPoziciju(cvor);



		if (pocetak >= 0) {
			Stack stek;
			int* povezani = new int[brojCvorova];
			int* povezaniTransponovano = new int[brojCvorova];
			int brojDodatih = 0, brojDodatihTransponovano = 0;
			bool* poseceno = new bool[brojCvorova];

			for (int i = 0; i < brojCvorova; i++) poseceno[i] = false;

			int pozicija = pocetak;
			stek.dodajElement(pozicija);
			while (!stek.stekPrazan()) {
				pozicija = stek.skiniSaSteka();
				if (!poseceno[pozicija]) {
					povezani[brojDodatih++] = pozicija;
					for (int i = 0; i < brojCvorova; i++) {
						if (matricaOdnosa[pozicija][i]) stek.dodajElement(i);
					}
					poseceno[pozicija] = true;
				}
			}

			for (int i = 0; i < brojCvorova; i++) poseceno[i] = false;

			pozicija = pocetak;
			stek.dodajElement(pozicija);
			while (!stek.stekPrazan()) {
				pozicija = stek.skiniSaSteka();
				if (!poseceno[pozicija]) {
					povezaniTransponovano[brojDodatihTransponovano++] = pozicija;
					for (int i = 0; i < brojCvorova; i++) {
						if (matricaOdnosa[i][pozicija]) stek.dodajElement(i);
					}
					poseceno[pozicija] = true;
				}
			}

			int brojZajednickih = 0;
			for (int i = 0; i < brojDodatih; i++) {
				for (int j = 0; j < brojDodatihTransponovano; j++) {
					if (povezani[i] == povezaniTransponovano[j]) povezani[brojZajednickih++] = povezani[i];
				}
			}

			cout << "JAKO POVEZANE KOMPONENTE ZA REC " << imenaCvorova[pocetak] << " SU: ";

			for (int i = 0; i < brojZajednickih; i++) cout << imenaCvorova[povezani[i]] << " ";
			cout << endl;

			delete[] povezani;
			delete[] povezaniTransponovano;
			delete[] poseceno;
		}
		else {
			cout << "CVOR SA ZADATIM IMENOM NE POSTOJI" << endl;
		}
	}
	else {
		cout << "GRAF NIJE UCITAN" << endl;
	}
}