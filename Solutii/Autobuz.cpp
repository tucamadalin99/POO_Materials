#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Autobuz {
private:
	int nrLinie;
	static float pretBilet;
	char* marcaAutobuz;
	int numarCurseZilnice;
	int numarLocuri;

public:

	char* getMarca() {
		return this->marcaAutobuz;
	}

	Autobuz() {
		this->nrLinie = 0;
		this->marcaAutobuz = NULL;
		this->numarCurseZilnice = 0;
		this->numarLocuri = 0;
	}

	Autobuz(int nrLinie, const char* marcaAutobuz) {
		if (nrLinie < 0) {
			throw new exception("Numarul liniei nu poate fi negativ.");
		}
		else if (marcaAutobuz == NULL || strlen(marcaAutobuz) < 2) 
			throw new exception("Marca autobuzului trebuie sa exista si sa aiba o lungime mai mare de 2 caractere");
		else {
			this->nrLinie = nrLinie;
			this->marcaAutobuz = new char[strlen(marcaAutobuz) + 1];
			strcpy(this->marcaAutobuz, marcaAutobuz);
			this->numarCurseZilnice = 10;
			this->numarLocuri = 50;
		}
	}

	Autobuz(Autobuz& a) {
		this->nrLinie = a.nrLinie;
		this->marcaAutobuz = new char[strlen(a.marcaAutobuz) + 1];
		strcpy(this->marcaAutobuz, a.marcaAutobuz);
		this->numarCurseZilnice = a.numarCurseZilnice;
		this->numarLocuri = a.numarLocuri;
	}

	Autobuz& operator=(Autobuz& a) {
		if (this != &a) {
			this->nrLinie = a.nrLinie;
			if (this->marcaAutobuz != NULL)
				delete[]this->marcaAutobuz;
			this->marcaAutobuz = new char[strlen(a.marcaAutobuz) + 1];
			strcpy(this->marcaAutobuz, a.marcaAutobuz);
			this->numarCurseZilnice = a.numarCurseZilnice;
			this->numarLocuri = a.numarLocuri;
			return *this;
		}
		else throw new exception("Obiectul nu poate fi autoasignat");
	}

	float venitMaxim() {
		return this->numarCurseZilnice * this->numarLocuri * pretBilet;
	}

	bool poateRealizaCursa(int nr) {
		if (nr > this->numarLocuri)
			return false;
		else
			return true;
	}

	friend ostream& operator<<(ostream& out, Autobuz& a) {
		out << "Nr. linie: " << a.nrLinie << endl;
		out << "Pret bilet: " << a.pretBilet << " RON." << endl;
		out << "Marca autobuz: " << a.marcaAutobuz << endl;
		out << "Curse zilnice: " << a.numarCurseZilnice << endl;
		out << "Numar locuri: " << a.numarLocuri << endl;
		return out;
	}

	friend Autobuz& operator+(int nr, Autobuz& a) {
		a.numarCurseZilnice += nr;
		return a;
	}

	friend Autobuz& operator+(Autobuz& a, int nr) {
		a.numarCurseZilnice += nr;
		return a;
	}

	friend ofstream& operator<<(ofstream& fout, Autobuz& a) {
		fout.write((char*)&a.nrLinie,sizeof(int));
		fout.write((char*)&pretBilet, sizeof(float));
		int len = strlen(a.marcaAutobuz);
		fout.write((char*)&len, sizeof(int));
		char* marca = new char[len + 1];
		strcpy(marca, a.marcaAutobuz);
		fout.write(marca, len + 1);
		fout.write((char*)&a.numarCurseZilnice, sizeof(int));
		fout.write((char*)&a.numarLocuri, sizeof(int));
		cout << "Serilizat" << endl;

		return fout;
	}
	

	friend ifstream& operator>>(ifstream& fin, Autobuz& a) {
		fin.read((char*)&a.nrLinie, sizeof(int));
		fin.read((char*)&pretBilet, sizeof(float));
		int len = 0;
		fin.read((char*)&len, sizeof(int));
		char* marca = new char[len + 1];
		fin.read(marca, len + 1);
		a.marcaAutobuz = new char[len + 1];
		strcpy(a.marcaAutobuz, marca);
		fin.read((char*)&a.numarCurseZilnice, sizeof(int));
		fin.read((char*)&a.numarLocuri, sizeof(int));
		cout << "Deserializat" << endl;

		return fin;
	}

};
float Autobuz::pretBilet = 3;

class Autobaza {
	int nrAutobuze;
	Autobuz** autobuze;

public:
	Autobaza() {
		this->nrAutobuze = 0;
		this->autobuze = NULL;
	}

	Autobaza(int nrAutobuze, Autobuz** autobuze) {
		if (nrAutobuze < 0)
			throw new exception("Numarul de autobuze nu poate fi negativ.");
		else if (autobuze == NULL)
			throw new exception("Statia trebuie sa aiba autobuze.");
		else {
			this->nrAutobuze = nrAutobuze;
			this->autobuze = new Autobuz*[this->nrAutobuze];
			for (int i = 0; i < this->nrAutobuze; i++)
				this->autobuze[i] = autobuze[i];
		}

	}

	Autobaza(Autobaza& ab) {
		this->nrAutobuze = ab.nrAutobuze;
		this->autobuze - new Autobuz*[ab.nrAutobuze];
		for (int i = 0; i < this->nrAutobuze; i++)
			this->autobuze[i] = ab.autobuze[i];
	}

	Autobaza& operator=(Autobaza& ab) {
		if (this != &ab) {
			this->nrAutobuze = ab.nrAutobuze;
			this->autobuze - new Autobuz*[ab.nrAutobuze];
			if (this->autobuze != NULL)
				delete[]this->autobuze;
			for (int i = 0; i < this->nrAutobuze; i++)
				this->autobuze[i] = ab.autobuze[i];

			return *this;
		}
		else throw new exception("Autoatribuirea nu este permisa");
	}

	int numarAutobuzeProduseDe(const char* marca) {
		int nr = 0;
		for (int i = 0; i < this->nrAutobuze; i++) {
			if (strcmp(this->autobuze[i]->getMarca(), marca) == 0) {
				nr += 1;
			}
		}

		return nr;
	}


	void adaugaAutobuz(Autobuz& a) {
		Autobuz** aux = new Autobuz*[this->nrAutobuze + 1];
		for (int i = 0; i < this->nrAutobuze; i++)
			aux[i] = this->autobuze[i];
		aux[this->nrAutobuze] = &a;
		this->nrAutobuze++;
		delete[]this->autobuze;
		this->autobuze = new Autobuz*[this->nrAutobuze];
		for (int i = 0; i < this->nrAutobuze; i++)
			this->autobuze[i] = aux[i];
		delete[]aux;
		cout << "Autobuz adaugat" << endl;
	}

	//void adaugaAutobuz(Autobuz a) {
	//	Autobuz* aux = new Autobuz[this->nrAutobuze + 1];
	//	for (int i = 0; i < this->nrAutobuze; i++)
	//		aux[i] = *autobuze[i];
	//	aux[this->nrAutobuze] = a;
	//	this->nrAutobuze++;
	//	delete[]this->autobuze;
	//	this->autobuze = new Autobuz*[this->nrAutobuze];
	//	for (int i = 0; i < this->nrAutobuze; i++)
	//		this->autobuze[i] = &aux[i];
	//	delete[]aux;
	//	cout << "Autobuz adaugat" << endl;
	//}

	friend ostream& operator<<(ostream& out, Autobaza& ab) {
		for (int i = 0; i < ab.nrAutobuze; i++)
			out << *ab.autobuze[i] << endl;
		return out;
	}
};

template<class T>
class AutobazaTemplate {
	int nrAutovehicule;
	T** autovehicule;

public:
	AutobazaTemplate() {
		this->nrAutovehicule = 0;
		this->autovehicule = NULL;
	}

	AutobazaTemplate(int nrAutovehicule, T** autovehicule) {
		this->nrAutovehicule = nrAutovehicule;
		this->autovehicule = new T*[nrAutovehicule];
		for (int i = 0; i < this->nrAutovehicule; i++)
			this->autovehicule[i] = autovehicule[i];
	}

	AutobazaTemplate(AutobazaTemplate& at) {
		this->nrAutovehicule = at.nrAutovehicule;
		this->autovehicule = new T*[at.nrAutovehicule];
		for (int i = 0; i < this->nrAutovehicule; i++)
			this->autovehicule[i] = at.autovehicule[i];
	}

	AutobazaTemplate& operator=(AutobazaTemplate& at) {
		if (this != &at) {
			this->nrAutovehicule = at.nrAutovehicule;
			if (this->autovehicule != NULL)
				delete[]this->autovehicule;
			this->autovehicule = new T*[at.nrAutovehicule];
			for (int i = 0; i < this->nrAutovehicule; i++)
				this->autovehicule[i] = at.autovehicule[i];

			return *this;
		}
		else throw new exception("Autoasignare!");
	}

};

int main() {

	Autobuz a1;
	Autobuz a2(3, "BMW");
	Autobuz a3 = a2;
	a1 = a2;
	cout << a1 << endl;
	Autobuz autobuz_nou;
	autobuz_nou = a1 + 5;
	autobuz_nou = 10 + a1;
	a2 = a1 + 10;
	cout << a1 << endl;

	ofstream fileOut("object.bin", ios::out, ios::binary);
	fileOut << a2;
	fileOut.close();
	Autobuz af;
	ifstream fileIn("object.bin", ios::in, ios::binary);
	fileIn >> af;
	fileIn.close();

	cout << autobuz_nou << endl;
	cout << "Autobaza: " << endl;
	Autobuz** autobuze = new Autobuz*[3];
	autobuze[0] = &a1;
	autobuze[1] = &a2;
	autobuze[2] = &a3;
	Autobaza ab(3, autobuze);
	cout << ab << endl;
	ab.adaugaAutobuz(autobuz_nou);
	cout << ab << endl;

	cout << "Numar autobuze produse de BMW: " << ab.numarAutobuzeProduseDe("BMW") << endl;
	
	cout << "CLASA TEMPLATE: " << endl;
	AutobazaTemplate<Autobuz> temp;
	AutobazaTemplate<Autobuz> temp2(3,autobuze);
	AutobazaTemplate<Autobuz> temp3 = temp2;
	temp = temp2;

	return 0;
}