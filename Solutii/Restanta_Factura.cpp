#include <iostream>
#include <string>
#include<cstring>
#include<fstream>
#include <vector>
using namespace std;

class Produs {
private:
	const int numarProd;
	static int contor;
	char* numeProd = NULL;
	int cantitate;
	float pretUnitar;
	string data;

public:
	Produs():numarProd(contor++) {
		this->numeProd = NULL;
		this->cantitate = 0;
		this->pretUnitar = 0.0f;
		this->data = "";
	}

	Produs(const char* numeProd, int cantitate, float pretUnitar, string data) :numarProd(contor++) {
		if (this->numeProd != NULL)
			delete[] this->numeProd;
		this->numeProd = new char[strlen(numeProd) + 1];
		strcpy(this->numeProd, numeProd);
		this->cantitate = cantitate;
		this->pretUnitar = pretUnitar;
		this->data = data;
	}

	Produs(const Produs& pr):numarProd(contor++) {
		if (this->numeProd != NULL)
			delete[] this->numeProd;
		this->numeProd = new char[strlen(pr.numeProd) + 1];
		strcpy(this->numeProd, pr.numeProd);
		this->cantitate = pr.cantitate;
		this->pretUnitar = pr.pretUnitar;
		this->data = pr.data;

	}

	Produs& operator=(const Produs& pr) {
		if (this->numeProd != NULL)
			delete[] this->numeProd;
		this->numeProd = new char[strlen(pr.numeProd) + 1];
		strcpy(this->numeProd, pr.numeProd);
		this->cantitate = pr.cantitate;
		this->pretUnitar = pr.pretUnitar;
		this->data = pr.data;

		return *this;
	}

	bool operator==(Produs p) {
		if (this->pretUnitar == p.pretUnitar)
			return true;
		else
			return false;
	}

	friend ostream& operator<<(ostream& out, Produs& pr) {
		out << "Numar produs: " << pr.numarProd << endl;
		out << "Nume: " << pr.numeProd << endl;
		out << "Cantitate: " << pr.cantitate << " BUC " << endl;
		out << "Pret Unitar: " << pr.pretUnitar << endl;
		out << "Data: " << pr.data << endl;
		return out;
	}



	explicit operator float() {
		return this->pretUnitar * 1.19;
	}

	Produs operator-(float reducere) {
		Produs copy = *this;
		copy.pretUnitar -= reducere;
		return copy;
	}

	float getPret() {
		return this->pretUnitar;
	}

	void setPret(float pret) {
		this->pretUnitar = pret;
	}

	char* getNume() {
		return this->numeProd;
	}

	void setData(string data) {
		this->data = data;
	}

	void setNume(const char* nume) {
		if (this->numeProd != NULL)
			delete[] this->numeProd;
		this->numeProd = new char[strlen(nume) + 1];
		strcpy(this->numeProd, nume);
	}

	static Produs* afisareDupaAn(Produs* prods, int anRef, int nr) {
		Produs* produseData = new Produs[nr];
		for (int i = 0; i < nr; i++) {
			char* data =(char*) prods[i].data.c_str();
			char an[4];
			for (int k = 6, j = 0; k < strlen(data); k++, j++) {
				an[j] = data[k];
			}
			int anConv = stoi(an);

			if (anConv == anRef) {
				produseData[i] = prods[i];
			}
			else
				throw new exception;
		}
		return produseData;
	}

	static float pretTotal(Produs* prods, int nrProd) {
		float sum = 0;
		for (int i = 0; i < nrProd; i++) {
			sum +=  prods[i].pretUnitar;
		}
		return sum;
	}

	friend ofstream& operator<<(ofstream& out, Produs p) {
		out << p.numarProd << endl;
		out << p.numeProd << endl;
		out << p.cantitate << endl;
		out << p.pretUnitar << endl;
		out << p.data << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Produs& p) {
		in >> p.contor;
		char buffer[30];
		in >> buffer;
		if (p.numeProd != NULL)
			delete[] p.numeProd;
		p.numeProd = new char[strlen(buffer) + 1];
		strcpy(p.numeProd, buffer);
		in >> p.cantitate;
		in >> p.pretUnitar;
		in >> p.data;
		return in;
	}


	~Produs() {
		if (this->numeProd != NULL)
			delete[]this->numeProd;
	}
};
int Produs::contor = 0;

class Factura {
private:
	int cod;
	int nrProduse;
	Produs* produse = NULL;

public:
	Factura() {
		this->cod = 0;
		this->nrProduse = 0;
		this->produse = NULL;
	}

	Factura(int cod, int nrProd, Produs* produse) {
		this->cod = cod;
		this->nrProduse = nrProd;
		if (this->produse != NULL)
			delete[] this->produse;
		this->produse = new Produs[nrProd];
		for (int i = 0; i < nrProd; i++)
			this->produse[i] = produse[i];
	}

	~Factura() {
		if (this->produse != NULL)
			delete[] this->produse;
	}

	int getNrProd() {
		this->nrProduse;
	}

	friend ostream& operator<<(ostream& out, Factura& f) {
		out << "COD Factura: " << f.cod << endl;
		out << "Nr. prod: " << f.nrProduse << endl;
		for (int i = 0; i < f.nrProduse; i++) {
			cout << f.produse[i] << endl;
		}

		return out;
	}

	Factura& operator+(Produs prod) {
		Produs* copy = new Produs[this->nrProduse + 1];
		for (int i = 0; i < this->nrProduse; i++)
			copy[i] = this->produse[i];
		this->nrProduse++;
		copy[this->nrProduse - 1] = prod;
		if (this->produse != NULL)
			delete[]this->produse;
		this->produse = new Produs[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
			this->produse[i] = copy[i];
		
		return *this;
	}

	Factura& operator()(int min, int max, float reducere) {
		float sum = 0;
		float redConv = 1 - (reducere / 100);
		for (int i = 0; i < this->nrProduse; i++) {
			if (this->produse[i].getPret() >= min && this->produse[i].getPret() <= max) {
				this->produse[i].setPret(this->produse[i].getPret() * redConv);
			}
		}

		return *this;
	}
};

template<typename T>
class Gestiune {
private: 
	int nr;
	T* elems;

public:
	Gestiune(int nr, T* elems) {
		this->nr = nr;
		this->elems = new T[this->nr];
		for (int i = 0; i < nr; i++) {
			this->elems[i] = elems[i];
		}
	}

	~Gestiune() {
		if (this->elems != NULL)
			delete[] this->elems;
	}

	T* getElems() {
		return this->elems;
	}

	int getNumar() {
		return this->nr;
	}

	friend ostream& operator<<(ostream& out, Gestiune& g) {
		out << "Numar elemente: " << g.getNumar() << endl;
		out << "ELEMENTE: " << endl;
		for (int i = 0; i < g.getNumar(); i++) {
			cout << g.getElems()[i] << endl;
		}

		return out;
	}
};

int main() {

	Produs p1;
	Produs p2("Cafea", 3, 24.53, "11/02/2020");
	Produs p3 = p2;
	p1 = p3;

	cout << p2 << endl;
	cout << p3 << endl;
	cout << p1 << endl;
	if (p1 == p2) {
		cout << "Pret egal " << endl;
	}
	else {
		cout << "Preturi diferite " << endl;
	}

	float pretTVA = (float)p2;
	cout << "Pretul cu TVA: " << pretTVA << endl;
	p2 = p2 - 3.5;
	cout << p2 << endl;

	Produs* produse = new Produs[6];
	p1.setData("01/20/2019");
	p2.setData("01/01/2009");
	produse[0] = p1;
	produse[1] = p2;
	produse[2] = p3;
	produse[3] = p1;
	produse[4] = p3;
	produse[5] = p2;
	cout << "Pretul total: " << Produs::pretTotal(produse, 6) << endl;

	try {
		Produs* produseData = Produs::afisareDupaAn(produse, 2020, 3);
		cout << "Produse dupa o data specificata: " << endl;
		for (int i = 0; i < 3; i++) {
			cout << produseData[i] << endl;
		}
	}
	catch (exception* e) {
		cout << "Nu exista produse dupa acest an!" << endl;
	}

	ofstream textRep("textRep.txt");
	textRep << p1;
	textRep.close();

	Produs pf;
	ifstream textRep2("textRep.txt");
	textRep2 >> pf;
	textRep2.close();

	Factura f(101, 3, produse);
	Factura f2(105, 3, produse);
	Factura f3(110, 2, produse);
	
	cout << endl << endl;
	cout << f << endl;

	f = f + p1;
	f = f + p2;

	cout << "Adaugat: " << endl;
	cout << f << endl;

	cout << "REDUCERE FACTURA: " << endl;
	
	f = f(22, 30, 50.0);
	cout << f << endl;
	cout << endl << endl << "STL: " << endl;
	vector<Produs*> prods;
	vector<Produs*>::iterator it;
	prods.push_back(&p1);
	prods.push_back(&p2);
	prods.push_back(&p3);
	prods.push_back(&p2);
	for (it = prods.begin(); it != prods.end(); it++) {
		cout << **it << endl;
	}

	Factura* facts = new Factura[3];
	facts[0] = f;
	facts[1] = f2;
	facts[2] = f3;

	Gestiune<Produs> gestProd(4, produse);
	cout << gestProd << endl;

	return 0;
}