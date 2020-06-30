#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
enum type {BACKUP,TEST,PRODUCTIE};
class BazaDeDate {
private:
	const int idDB;
	char* denumire;
	bool esteAccesibila;
	unsigned int nrInregistrari;
	type tip;
	static int NR_INREGISTRARI;

public:
	BazaDeDate():idDB(-1) {
		this->denumire = NULL;
		this->esteAccesibila = false;
		this->nrInregistrari = 0;
		this->tip = TEST;
	}

	BazaDeDate(const int idDB, const char* denumire, type t) :idDB(idDB) {
		if (denumire == NULL || strlen(denumire) < 3)
			throw new exception("Baza de date trebuie sa aiba denumirea de cel putin 3 caractere.");
		else if (t != BACKUP && t != TEST && t != PRODUCTIE)
			throw new exception("Tipul poate fi doar BACKUP, TEST SAU PRODUCTIE.");
		else {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
			this->esteAccesibila = false;
			this->nrInregistrari = 0;
			this->tip = t;
		}
	}

	BazaDeDate(const int idDB, const char* denumire, type t, bool esteAccesibila, int nrInreg) :idDB(idDB) {
		if (denumire == NULL || strlen(denumire) < 3)
			throw new exception("Baza de date trebuie sa aiba denumirea de cel putin 3 caractere.");
		else if (t != BACKUP && t != TEST && t != PRODUCTIE)
			throw new exception("Tipul poate fi doar BACKUP, TEST SAU PRODUCTIE.");
		else {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
			this->esteAccesibila = esteAccesibila;
			this->nrInregistrari = nrInreg;
			this->tip = t;
		}
	}

	BazaDeDate(BazaDeDate& bd):idDB(bd.idDB) {
		if (bd.idDB < 0)
			throw new exception("Nu se poate face copierea pt baze de date cu id -1");
		else {
			this->denumire = new char[strlen(bd.denumire) + 1];
			strcpy(this->denumire, bd.denumire);
			this->esteAccesibila = bd.esteAccesibila;
			this->nrInregistrari = bd.nrInregistrari;
			this->tip = bd.tip;
		}
	}

	BazaDeDate& operator=(BazaDeDate& bd) {
		if (this != &bd) {
			if (bd.idDB < 0)
				throw new exception("Nu se poate face copierea pt baze de date cu id -1");
			else {
				if (this->denumire != NULL)
					delete[]this->denumire;
				this->denumire = new char[strlen(bd.denumire) + 1];
				strcpy(this->denumire, bd.denumire);
				this->esteAccesibila = bd.esteAccesibila;
				this->nrInregistrari = bd.nrInregistrari;
				this->tip = bd.tip;
				return *this;
			}
		}
		else throw new exception("Autoasignarea nu este permisa");
	}

	~BazaDeDate() {
		this->esteAccesibila = false;
		if (this->denumire != NULL)
			delete[]this->denumire;
	}

	char* getDenumire() {
		return this->denumire;
	}

	int getNrInreg() {
		return this->nrInregistrari;
	}

	void setNrInreg(int nr) {
		if (nr > NR_INREGISTRARI)
			throw new exception("Numarul nu poate depasi valoarea maxima permisa");
		else {
			this->nrInregistrari = nr;
		}
	}
	
	void setAccesibila(bool val) {
		this->esteAccesibila = val;
	}

	friend ostream& operator<<(ostream& out, BazaDeDate& bd) {
		out << "DENUMIRE BD: " << bd.denumire << endl;
		out << "ESTE ACCESIBILA: " << bd.esteAccesibila << endl;
		out << "NUMAR INREGISTRARI: " << bd.nrInregistrari << endl;
		out << "TIP BD: " << bd.tip << endl;
		return out;
	}

	BazaDeDate operator++(int) {
		BazaDeDate copy = *this;
		this->nrInregistrari += 1;
		return copy;
	}

	virtual void backup() {
		if (this->esteAccesibila) {
			cout << "Backup pentru baza de date: " << this->denumire << " se executa..." << endl;
			if(this->nrInregistrari > 10)
				for (int i = 1; i <= this->nrInregistrari; i++) {
					if(i % 10 == 0)
					cout << "Backup grup de inregistrari: " << i << endl;
				}
			else
				cout << "Baza de date nu are un grup de cel putin 10 inregistrari. " << endl;
		}
		else {
			throw new exception("Baza de date este inaccesibila.");
		}
	}

	void save() {
		ofstream bin;
		bin.open("bd.bin", ios::out, ios::binary);
		int len = 0;
		len = strlen(this->denumire);
		bin.write((char*)&len, sizeof(int));
		char* den = new char[len + 1];
		strcpy(den, this->denumire);
		bin.write(den, len + 1);
		bin.write((char*)&this->esteAccesibila, sizeof(bool));
		bin.write((char*)&this->nrInregistrari, sizeof(int));
		bin.write((char*)&this->tip, sizeof(type));
		bin.close();
		cout << "Serializat!" << endl;
	}

	static BazaDeDate& load() {
		ifstream bin;
		bin.open("bd.bin", ios::in, ios::binary);
		int len = 0;
		bin.read((char*)&len, sizeof(int));
		char* den = new char[len + 1];
		bin.read(den, len + 1);
		bool accesibila;
		int nrInreg;
		type t;
		bin.read((char*)&accesibila, sizeof(bool));
		bin.read((char*)&nrInreg, sizeof(int));
		bin.read((char*)&t, sizeof(type));
		bin.close();
		cout << "Load succesful" << endl;
		return *new BazaDeDate(10, den, t, accesibila, nrInreg);
	}
};
int BazaDeDate::NR_INREGISTRARI = 999;

class BazaDeDateCloud :public BazaDeDate {
private:
	int nrUtilizatori;
	string* utilizatori;

public:
	BazaDeDateCloud(const int idDB, const char* denumire, int nrUtilizatori, string* utilizatori)
		:BazaDeDate(idDB, denumire, PRODUCTIE, true, 1000) {
		this->nrUtilizatori = nrUtilizatori;
		this->utilizatori = new string[nrUtilizatori];
		for (int i = 0; i < this->nrUtilizatori; i++)
			this->utilizatori[i] = utilizatori[i];
	}

	BazaDeDateCloud(BazaDeDateCloud& bdc) :BazaDeDate(bdc) {
		this->nrUtilizatori = bdc.nrUtilizatori;
		this->utilizatori = new string[bdc.nrUtilizatori];
		for (int i = 0; i < bdc.nrUtilizatori; i++) {
			this->utilizatori[i] = bdc.utilizatori[i];
		}
	}

	BazaDeDateCloud& operator=(BazaDeDateCloud& bdc) {
		if (this != &bdc) {
			BazaDeDate::operator=(bdc);
			this->nrUtilizatori = bdc.nrUtilizatori;
			if (this->utilizatori != NULL)
				delete[]this->utilizatori;
			this->utilizatori = new string[bdc.nrUtilizatori];
			for (int i = 0; i < this->nrUtilizatori; i++)
				this->utilizatori[i] = bdc.utilizatori[i];
			return *this;
		}
		else throw new exception("Autoasignare nu merge!");
	}

	~BazaDeDateCloud() {
		if (this->utilizatori != NULL)
			delete[]this->utilizatori;
	}

	friend ostream& operator<<(ostream& out, BazaDeDateCloud& bdc) {
		out << (BazaDeDate&)bdc;
		out << "NR UTIL: " << bdc.nrUtilizatori << endl;
		out << "UTILIZATORI: " << endl;
		for (int i = 0; i < bdc.nrUtilizatori; i++)
			out << bdc.utilizatori[i] + " ";
		out << endl;
		return out;
	}

	void backup() {
			cout << "Backup pentru baza de date cloud: " << this->getDenumire() << " se executa..." << endl;
			if (this->getNrInreg() > 10) {
				for (int i = 1; i <= this->getNrInreg(); i++) {
					if (i % 10 == 0)
						cout << "Backup grup de inregistrari: " << i << endl;
				}
				for (int i = 0; i < this->nrUtilizatori; i++)
					cout << "Utilizator: " << i + 1 << ": " << this->utilizatori[i] << ", ";
				cout << endl;
			}
			else
				cout << "Baza de date nu are un grup de cel putin 10 inregistrari. " << endl;
		}
};

class BDAbstract: public BazaDeDateCloud {
private:
	int nrBazeDeDate;
public:
	BDAbstract(int id, const char* denumire, type t, int nrBazeDeDate) :BazaDeDateCloud(1, "TEST", 2, new string[2]{ "DORIN","ANDREI" }) {
		this->nrBazeDeDate = nrBazeDeDate;
	}
	virtual void backup() = 0;
};

int main() {
	try {
		BazaDeDate bd;
		BazaDeDate bd2(2, "Amazon", PRODUCTIE);
		BazaDeDate bd1(1, "Oracle", TEST);
		//BazaDeDate bdCopie = bd1;
		//bd2 = bdCopie;
		/*cout << bd << endl;
		cout << bd1 << endl;
		cout << bdCopie << endl;*/
		bd2++;
		bd2++;
		cout << bd2 << endl;
		bd2.setNrInreg(100);
		bd2.setAccesibila(true);
		bd2.backup();
		bd2.save();

		bd1 = BazaDeDate::load();
		cout << bd1 << endl;

		BazaDeDateCloud bdc(30, "TomaSRL", 4, new string[4]{ "Cosmin", "Andrei", "Richard", "Raluca" });
		BazaDeDateCloud bdcc = bdc;
		bdc = bdcc;

		cout << bdc << endl;

		bdc.backup();
		
		cout << "STELEU: " << endl;
		vector<BazaDeDate*>baze;
		//Up casting
		baze.push_back(&bd1);
		baze.push_back(&bdc);
		baze.push_back(&bd2);
		baze.push_back(&bdcc);
		vector<BazaDeDate*>::iterator it;
		for (it = baze.begin(); it != baze.end(); it++) {
			(*it)->backup();
		}

		//Downcasting
		cout << ((BazaDeDateCloud*)baze[0])->getDenumire() << endl;

	}
	catch (exception* e) {
		cout << e->what() << endl;
	}

	return 0;
};