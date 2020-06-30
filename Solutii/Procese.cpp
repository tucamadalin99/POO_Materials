#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
class Proces {
private:
	const int idProces;
	static int contor;
	char* denumire;
	bool esteActiv;
	int durata;
	int prioritate;

public:
	Proces() :idProces(contor++) {
		this->denumire = NULL;
		this->esteActiv = false;
		this->durata = 0;
		this->prioritate = 3;
	}

	Proces(const char* denumire, int durata, int prioritate) :idProces(contor++) {
		if (denumire == NULL || strlen(denumire) < 3)
			throw new exception("Denumirea nu respecta validarea.");
		else if (durata < 0)
			throw new exception("Durata nu poate fi negativa");
		else if (prioritate != 1 && prioritate != 2 && prioritate != 3)
			throw new exception("Prioritatea poate fi doar 1 2 sau 3");
		else {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
			this->esteActiv = false;
			this->durata = durata;
			this->prioritate = prioritate;
		}
	}

	Proces(Proces& p) :idProces(contor++) {
		if (p.esteActiv) {
			throw new exception("Procesele active nu pot fi copiate.");
		}
		else {
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
			this->esteActiv = p.esteActiv;
			this->durata = p.durata;
			this->prioritate = p.prioritate;
		}
	}

	Proces& operator=(Proces& p) {
		if (this != &p) {
			if (p.esteActiv) {
				throw new exception("Procesele active nu pot fi copiate.");
			}
			else {
				if (this->denumire != NULL)
					delete[]this->denumire;
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy(this->denumire, p.denumire);
				this->esteActiv = p.esteActiv;
				this->durata = p.durata;
				this->prioritate = p.prioritate;
			}

			return *this;
		}
		else throw new exception("Autoasignarea nu este permisa");
	
	}

	char* getDenumire() {
		return this->denumire;
	}

	bool getEsteActiv() {
		return this->esteActiv;
	}

	void setEsteActiv(bool activ) {
		this->esteActiv = activ;
	}

	friend ostream& operator<<(ostream& out, Proces& p) {
		out << "ID PROCES: " << p.idProces << " ";
		out << "DENUMIRE: " << p.denumire <<  " ";
		out << "ESTE ACTIV: " << p.esteActiv << " ";
		out << "DURATA: " << p.durata << " ";
		out << "PRIORITATE: " << p.prioritate << " ";
		return out;
	}

	~Proces() {
		if (this->esteActiv)
			this->esteActiv = false;
		if (this->denumire != NULL)
			delete[]this->denumire;
	}

	virtual void executa() {
		if (this->esteActiv)
			throw new exception("Procesul este activ nu se poate executa.");
		else {
			this->esteActiv = true;
			if (this->prioritate == 1) {
				int ticks = 10;
				for (int i = 0; i < this->durata * ticks; i++) {
					cout << "Procesul " << this->denumire << " se executa. " << endl;
				}
				this->esteActiv = false;
			}
			else if (this->prioritate == 2) {
				int ticks = 5;
				for (int i = 0; i < this->durata * ticks; i++)
					cout << "Procesul " << this->denumire << " se executa.." << endl;
				this->esteActiv = false;
			}
			else {
				int ticks = 2;
				for (int i = 0; i < this->durata * ticks; i++)
					cout << "Procesul " << this->denumire << " se executa.." << endl;
				this->esteActiv = false;
			}
		}
	}

};
int Proces::contor = 0;

class Antivirus : public Proces {
private:
	int nrVirusiDetectati;
	string* denumiriVirusi;
	static long MAX_INT;

public:
	Antivirus(const char* denumire, int durata, int prioritate, int nrVirusiDetectati, string* denumiriVirusi) :Proces(denumire, durata, prioritate) {
		if (prioritate != 1) {
			throw new exception("Prioritatea trebuie sa fie 1!");
		}
		else if (durata < MAX_INT)
			throw new exception("Durata trebuie sa fie de cel putin 999");
		else {
			this->nrVirusiDetectati = nrVirusiDetectati;
			this->denumiriVirusi = new string[nrVirusiDetectati];
			for (int i = 0; i < this->nrVirusiDetectati; i++)
				this->denumiriVirusi[i] = denumiriVirusi[i];
		}
	
	}

	Antivirus(Antivirus& a):Proces(a) {
		this->nrVirusiDetectati = a.nrVirusiDetectati;
		this->denumiriVirusi = new string[a.nrVirusiDetectati];
		for (int i = 0; i < this->nrVirusiDetectati; i++)
			this->denumiriVirusi[i] = a.denumiriVirusi[i];
	}

	Antivirus& operator=(Antivirus& a) {
		Proces::operator=(a);
		this->nrVirusiDetectati = a.nrVirusiDetectati;
		if (this->denumiriVirusi != NULL)
			delete[]this->denumiriVirusi;
		this->denumiriVirusi = new string[a.nrVirusiDetectati];
		for (int i = 0; i < this->nrVirusiDetectati; i++)
			this->denumiriVirusi[i] = a.denumiriVirusi[i];

		return *this;
	}

	friend ostream& operator<<(ostream& out, Antivirus& a) {
		out << (Proces&)a;
		out << "Nr.virusi: " << a.nrVirusiDetectati << endl;
		out << "Denumiri virusi: " << endl;
		for (int i = 0; i < a.nrVirusiDetectati; i++)
			out << a.denumiriVirusi[i] + " ";
		out << endl;
		return out;
	}

	~Antivirus() {
		if (this->denumiriVirusi != NULL)
			delete[]this->denumiriVirusi;
	}

	void executa() {
		if (this->getEsteActiv() == false) {
			this->setEsteActiv(true);
		}
		cout << "Antivirusul " << this->getDenumire() << " este activ." << endl;
	}

	bool operator!() {
		if (this->nrVirusiDetectati == 0)
			return true;
		else return false;
	}

	void exportCSV(int dim ,Proces ps[]) {
		ofstream fileCSV("raport.csv", ios::out);
		for (int i = 0; i < dim; i++) {
			fileCSV << ps[i] << "," << endl;
		}
		fileCSV.close();
		cout << "RAPORT CSV FACUT." << endl;
	}

};
long Antivirus::MAX_INT = 999;
int main() {
	//TRY-CATCH PRINDE EXCEPTIILE ARUNCATE UNDE SUNT VALIDARI CU THROW NEW EXCEPTION
	try {
		Proces p1;
		Proces p2("Facebook", 1, 1);
		Proces p3 = p2;
		p1 = p3;
		cout << p1 << endl;
		cout << p2 << endl;
		p2.executa();

		cout << endl << endl << "CLASA ANTIVIRUS: " << endl << endl;

		Antivirus a("Bitdefender", 999, 1, 3, new string[3]{ "Trojan", "Worm", "AdBot" });
		Antivirus a1("Kaspersky", 999, 1, 2, new string[2]{ "Trojan", "Worm" });
		Antivirus a2("Avasat", 999, 1, 2, new string[2]{ "Trojan", "Worm" });
		//a = a1;
		a1 = a2;
		cout << a1 << endl;
		a1.executa();
		//Apel !
		if (!a1) {
			cout << "Nu exista virusi" << endl;
		}
		else {
			cout << "S-au depistat virusi." << endl;
		}

		cout << "EXPORT CSV: " << endl; 
		Proces* procese = new Proces[3]{ p1,p2,p3 };
		a1.exportCSV(3, procese);

		//Demonstrare virtualizare fara STL
	/*	Proces** proceseV = new Proces*[2];
		proceseV[0] = &p1;
		proceseV[1] = &a2;
		proceseV[0]->executa();
		proceseV[1]->executa();*/

		//Metoda cu pair
		/*vector<pair<Proces*, Antivirus*>>proceseSTL;
		proceseSTL.push_back(make_pair(&p1, &a));
		proceseSTL.push_back(make_pair(&p2, &a1));
		proceseSTL.push_back(make_pair(&p3, &a2));
		for (int i = 0; i < proceseSTL.size(); i++) {
			proceseSTL[i].first->executa();
			proceseSTL[i].second->executa();
		}*/

		//Metoda stl simplu
		vector<Proces*>procSTL;
		procSTL.push_back(&p1);
		procSTL.push_back(&a);
		procSTL.push_back(&p2);
		procSTL.push_back(&a2);
		for (int i = 0; i < procSTL.size(); i++) {
			procSTL[i]->executa();
		}

	}
	catch (exception *e) {
		cout << e->what() << endl;
	}


	return 0;
}