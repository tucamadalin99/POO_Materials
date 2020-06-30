#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Fisier {
private:
	static int contor;
	string denumire;
	int ziuaCrearii;
	int dimensiune;
	char* bytes = NULL;

public:
	Fisier() {
		this->denumire = "fisier";
		this->denumire.append(to_string(contor));
		this->ziuaCrearii = 1;
		this->dimensiune = 0;
		this->bytes = NULL;
		contor++;
	}

	Fisier(string denumire, int ziuaCrearii, int dimensiune, char* bytes) {
		if (denumire.compare("fisier") != 0)
			throw new exception("Poate avea doar numele fisier");
		else if (ziuaCrearii < 1 || ziuaCrearii > 31)
			throw new exception("Ziua crearii trebuie sa fie cuprinsa intre 1-31");
		else if (dimensiune < 1)
			throw new exception("Vectorul trebuie sa aiba o dimensiune de cel putin un element.");
		else {
			this->denumire = denumire;
			this->denumire.append(to_string(contor));
			this->ziuaCrearii = ziuaCrearii;
			this->dimensiune = dimensiune;
			this->bytes = new char[dimensiune];
			for (int i = 0; i < this->dimensiune; i++)
				this->bytes[i] = bytes[i];
			contor++;
		}
	}

	Fisier(Fisier& f) {
		this->denumire = f.denumire;
		this->denumire.append("_copy");
		this->ziuaCrearii = f.ziuaCrearii;
		this->dimensiune = f.dimensiune;
		this->bytes = new char[f.dimensiune];
		for (int i = 0; i < this->dimensiune; i++)
			this->bytes[i] = f.bytes[i];
	}

	Fisier& operator=(Fisier& f) {
		if (this != &f) {
			this->denumire = f.denumire;
			this->denumire.append("_copy");
			this->ziuaCrearii = f.ziuaCrearii;
			this->dimensiune = f.dimensiune;
			if (this->bytes != NULL)
				delete[]this->bytes;
			this->bytes = new char[f.dimensiune];
			for (int i = 0; i < this->dimensiune; i++)
				this->bytes[i] = f.bytes[i];
			return *this;
		}
		else throw new exception("Fisierul nu poate fi reatribuit.");
	}

	char* getBytes() {
		return this->bytes;
	}

	int getDim() {
		return this->dimensiune;
	}


	string getDenumire() {
		return this->denumire;
	}

	~Fisier() {
		if (this->bytes != NULL)
			delete[]this->bytes;
	}

	friend ostream& operator<<(ostream& out, Fisier& f) {
		out << "Denumire fisier: " << f.denumire << endl;
		out << "Ziua crearii: " << f.ziuaCrearii << endl;
		out << "Dimensiune: " << f.dimensiune << endl;
		out << "Bytes: " << endl;
		for (int i = 0; i < f.dimensiune; i++)
			out << f.bytes[i] << " ";
		out << endl;
		out << "--------------------------------------" << endl;
		return out;
	}

	void arhiveaza() {
		char* aux = NULL;
		int dimNoua = this->dimensiune;
		for (int i = 0; i < this->dimensiune; i++) {
			if (this->bytes[i] - '0' == this->bytes[i + 1] - '0') {
				dimNoua--;
			}
		}

		aux = new char[dimNoua];
		int j = 0;
		for(int i = 0; i < this->dimensiune; i++){
			if (this->bytes[i] != this->bytes[i + 1]) {
				aux[j] = this->bytes[i];
				j += 1;
			}
				
		}

		delete[]this->bytes;
		//this->bytes = aux;
		this->dimensiune = dimNoua;
		this->bytes = new char[dimNoua];
		for (int i = 0; i < dimNoua; i++)
			this->bytes[i] = aux[i];
	}

	explicit operator long() {
		return (long)this->dimensiune;
	}

	char operator[](int index) {
		if (index >= 0 &&  index <= this->dimensiune) {
			char consult = this->bytes[index];
			cout << "La pozitia: " << index << " se afla valoarea: " << consult << endl;
			cout << "Modificati valoarea: ";
			cin >> this->bytes[index];
			return this->bytes[index];
		}
		else throw new exception("Index in afara limitelor!");
	}

	void operator+=(Fisier& f) {
		int dimNoua = this->dimensiune + f.dimensiune;
		char* aux = new char[dimNoua];
		for(int i = 0; i < this->dimensiune; i++){
			aux[i] = this->bytes[i];
		}
		int j = 0;
		for (int i = this->dimensiune; i < dimNoua; i++) {
			aux[i] = f.bytes[j];
			j++;
		}

		this->dimensiune = dimNoua;
		delete[]this->bytes;
		this->bytes = new char[dimNoua];
		for (int i = 0; i < dimNoua; i++)
			this->bytes[i] = aux[i];
	}
	
};
int Fisier::contor = 1;

class Director {
private:
	char denumire[20];
	int nrFisiere;
	Fisier* fisiere;

public:
	Director(const char denumire[20], int nrFisiere, Fisier* fisiere) {
		strcpy(this->denumire, denumire);
		this->nrFisiere = nrFisiere;
		this->fisiere = new Fisier[nrFisiere];
		for (int i = 0; i < nrFisiere; i++)
			this->fisiere[i] = fisiere[i];
	}

	Director(Director& d) {
		strcpy(this->denumire, d.denumire);
		this->nrFisiere = d.nrFisiere;
		this->fisiere = new Fisier[d.nrFisiere];
		for (int i = 0; i < d.nrFisiere; i++)
			this->fisiere[i] = d.fisiere[i];
	}

	Director& operator=(Director& d) {
		if (this != &d) {
			strcpy(this->denumire, d.denumire);
			this->nrFisiere = d.nrFisiere;
			if (this->fisiere != NULL)
				delete[]this->fisiere;
			this->fisiere = new Fisier[d.nrFisiere];
			for (int i = 0; i < d.nrFisiere; i++)
				this->fisiere[i] = d.fisiere[i];
		}
		else throw new exception("Nu este permisa atribuirea.");
	}

	~Director() {
		if (this->fisiere != NULL)
			delete[]this->fisiere;
	}

	void Paste() {
		ofstream file;
		for (int i = 0; i < this->nrFisiere; i++) {
			file.open(this->fisiere[i].getDenumire().append(".txt"), ios::out);
			for (int j = 0; j < this->fisiere[i].getDim(); j++) {
				file << this->fisiere[i].getBytes()[j] << " ";
			}
			file.close();
		}

		cout << "Fisiere text create!" << endl;
	}
};

int main() {
	try {
		Fisier f1;
		cout << f1 << endl;
		Fisier f2("fisier", 20, 10, new char[10]{ '1','1','1','0','1','1','0','1','1','0' });
		cout << f2 << endl;
		Fisier f2c = f2;
		cout << f2c << endl;
		f1 = f2c;
		cout << f1 << endl;
		cout << f2 << endl;
		f2.arhiveaza();
		cout << "ARHIVARE: " << endl;
		cout << f2 << endl;
		cout << "----Fisier arhivat-----" << endl;
		cout << "-----------------------" << endl;
		cout << "Dimensiunea fisierului: " << (long)f2 << " bytes" << endl;
		cout << "Indexare: " << endl;
		cout << f2[2] << endl;
		cout << "Afisare dupa modificare: " << endl;
		cout << endl << f2 << endl;
		cout << "Concatenarea fisierelor: " << endl;
		f2 += f2c;
		cout << f2 << endl;

		cout << "CLASA DIRECTOR: " << endl;
		Fisier fd("fisier", 21, 3, new char[3]{ '1','0','1' });
		Director d("Important", 3, new Fisier[3]{ fd,f2c,f1 });
		Director d2 = d;
		Director di("LessImportant", 2, new Fisier[2]{ f2, f2c });
		di = d2;

		d.Paste();
	}
	catch (exception* e) {
		cout << e->what() << endl;
	}
		

	return 0;
}