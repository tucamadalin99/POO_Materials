#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Tramvai {
protected:
	const int nrTramvai;
	string numeVatman;
	int nrStatii;
	int* minutePerStatie;
	static int contor;
public:
	Tramvai():nrTramvai(contor++) {
		this->numeVatman = "";
		this->nrStatii = 0;
		this->minutePerStatie = NULL;
	}

	void setStatii(int nrStatii) {
		this->nrStatii = nrStatii;
	}

	void setMinuteStatie(int* minute) {
		if (this->minutePerStatie != NULL)
			delete[]this->minutePerStatie;
		this->minutePerStatie = new int[this->nrStatii];
		for (int i = 0; i < this->nrStatii; i++)
			this->minutePerStatie[i] = minute[i];
	}

	Tramvai(int nrTramvai, string numeVatman) :nrTramvai(nrTramvai) {
		if (this->nrTramvai < 1) {
			throw new exception("Numar invalid.");
		}
		else if (numeVatman.length() < 3) {
			throw new exception("Numele vatmanului trebuie sa aiba cel putin 3 caractere");
		}
		else {
			this->numeVatman = numeVatman;
			this->nrStatii = 0;
			this->minutePerStatie = NULL;
		}

		
	}

	Tramvai(Tramvai& t) :nrTramvai(contor++) {
		this->numeVatman = t.numeVatman;
		this->nrStatii = t.nrStatii;
		if (t.nrStatii > 0) {
			this->minutePerStatie = new int[t.nrStatii];
			for (int i = 0; i < this->nrStatii; i++)
				this->minutePerStatie[i] = t.minutePerStatie[i];
		}
		else
			this->minutePerStatie = NULL;
	}

	Tramvai& operator=(Tramvai& t) {
		if (this != &t) {
			this->numeVatman = t.numeVatman;
			this->nrStatii = t.nrStatii;
			if (t.nrStatii > 0) {
				if (this->minutePerStatie != NULL)
					delete[]this->minutePerStatie;
				this->minutePerStatie = new int[t.nrStatii];
				for (int i = 0; i < this->nrStatii; i++)
					this->minutePerStatie[i] = t.minutePerStatie[i];
			}
			else
				this->minutePerStatie = NULL;
			return *this;
		}
		else throw new exception("Autoasignarea nu este permisa!");
		
	}

	~Tramvai() {
		if (this->minutePerStatie != NULL)
			delete[]this->minutePerStatie;
	}

	int calculMinuteStationate(int indexStatieStart, int indexStatieEnd) {
		int sum = 0;
		if (indexStatieStart >= 0 && indexStatieEnd <= this->nrStatii) {
			for (int i = indexStatieStart; i <= indexStatieEnd; i++) {
				sum += this->minutePerStatie[i];
			}

			return sum;
		}
		else
			throw new exception("Index in afara limitelor");
	}

	virtual int totalMinuteStationate() {
		int sum = 0;
		if (this->nrStatii > 0) {
			for (int i = 0; i < this->nrStatii; i++) {
				sum += this->minutePerStatie[i];
			}

			return sum;
		}
		else throw new exception("Tramvaiul nu a ajuns in nicio satatie.");
	}

	void adaugaStatie(int minute) {
			int* aux = new int[this->nrStatii + 1];
			for (int i = 0; i < this->nrStatii; i++) {
				aux[i] = this->minutePerStatie[i];
			}
			aux[this->nrStatii] = minute;
			this->nrStatii++;
			delete[]this->minutePerStatie;
			this->minutePerStatie = new int[this->nrStatii];
			for (int i = 0; i < this->nrStatii; i++)
				this->minutePerStatie[i] = aux[i];
			delete[]aux;
			cout << "Statie adaugata" << endl;

	}

	friend ostream& operator<<(ostream& out, Tramvai& t) {
		out << "ID: " << t.nrStatii << endl;
		out << "Nume vatman: " << t.numeVatman << endl;
		out << "Numar statii: " << t.nrStatii << endl;
		out << "Minute stationate per statie: " << endl;
		for (int i = 0; i < t.nrStatii; i++)
			out << "Statia: " << i + 1 << ": " << t.minutePerStatie[i] << " minute" << endl;

		return out;
	}
	
	int operator[](int index) {
		if (index >= 0 && index <= this->nrStatii) {
			cout << "Pe pozitia: " << index << " se afla valoarea de: " << this->minutePerStatie[index] << endl;
			cout << "Modificati numarul: " << endl;
			cin >> this->minutePerStatie[index];
			return this->minutePerStatie[index];
		}
		else
			throw new exception("Index in afara limitelor");
	}

	friend ofstream& operator<<(ofstream& fout, Tramvai& t) {
		fout << t.nrTramvai << endl;
		fout << t.numeVatman << endl;
		fout << t.nrStatii << endl;
		for (int i = 0; i < t.nrStatii; i++)
			fout << t.minutePerStatie[i] << " ";
		cout << "Scriere in fisier text succes. " << endl;
		return fout;
	}

	friend ifstream& operator>>(ifstream& fin, Tramvai& t) {
		fin >> t.contor;
		fin >> t.numeVatman;
		fin >> t.nrStatii;
		if (t.minutePerStatie != NULL)
			delete[]t.minutePerStatie;
		t.minutePerStatie = new int[t.nrStatii];
		for (int i = 0; i < t.nrStatii; i++)
			fin >> t.minutePerStatie[i];
		cout << "Obiect citit din fisier text!" << endl;
		return fin;
	}
};
int Tramvai::contor = 1;

class TramvaiHibrid :public Tramvai {
private:
	int capacitateBaterie;
	int timpIncarcare;

public:
	TramvaiHibrid() :Tramvai() {
		this->capacitateBaterie = 0;
		this->timpIncarcare = 0;
	}

	TramvaiHibrid(int nrTramvai, string numeVatman, int capacitateBaterie, int timpIncarcare) :Tramvai(nrTramvai, numeVatman) {
		this->capacitateBaterie = capacitateBaterie;
		this->timpIncarcare = timpIncarcare;
	}

	TramvaiHibrid& operator=(TramvaiHibrid& t) {
		if (this != &t) {
			this->capacitateBaterie = t.capacitateBaterie;
			this->timpIncarcare = t.timpIncarcare;

			return *this;
		}
		else throw new exception("Nu se poate autoasigna.");
	}

	~TramvaiHibrid() {
	}

	friend ostream& operator<<(ostream& out, TramvaiHibrid& t) {
		out << "Nume vatman: " << t.numeVatman << endl;
		out << "Nr. statii: " << t.nrStatii << endl;
		for (int i = 0; i < t.nrStatii; i++)
			out << t.minutePerStatie[i] << " ";
		out << endl;
		out << "Capacitate: " << t.capacitateBaterie << endl;
		out << "Timp incarcare: " << t.timpIncarcare << endl;
		return out;
	}

	int totalMinuteStationate() {
		int sum = 0;
		for (int i = 0; i < this->nrStatii; i++)
			sum += this->minutePerStatie[i];
		return sum;
	}
};

int main() {
	try {
		Tramvai t1;
		Tramvai t2(2, "Cosmin");
		Tramvai t3 = t2;
		t1 = t3;
		t2.setStatii(4);
		t2.setMinuteStatie(new int[4]{ 10,5,15,8 });
		cout << "Minute totale stationate in intreval: " << t2.calculMinuteStationate(0, 2) << endl;
		cout << "Minute totale stationate: " << t2.totalMinuteStationate() << endl;
		t2.adaugaStatie(20);
		cout << "Minute totale: " << t2.totalMinuteStationate() << endl;
		cout << t2 << endl;
		t2[2];
		cout << t2 << endl;
		cout << "Scriere in fisier: " << endl;
		ofstream fileOut;
		fileOut.open("raport.txt", ios::out);
		fileOut << t2;
		fileOut.close();

		cout << "Citire din fisier in obiect." << endl;
		ifstream fileIn;
		Tramvai tg;
		fileIn.open("raport.txt", ios::in);
		fileIn >> tg;
		fileOut.close();
		cout << tg << endl;

		cout << "Tramvai hibrid: " << endl;
		TramvaiHibrid th;
		TramvaiHibrid th2(21, "Dorel", 100, 50);
		TramvaiHibrid th3 = th2;
		th = th3;
		th2.setStatii(3);
		th2.setMinuteStatie(new int[3]{ 10,20,10 });
		cout << th2 << endl;
		vector<pair<Tramvai*, TramvaiHibrid*>>tramvaie;
		t1.setStatii(3);
		t1.setMinuteStatie(new int[3]{ 10,10,10 });
		th.setStatii(2);
		th.setMinuteStatie(new int[2]{ 5,10 });
		tramvaie.push_back(make_pair(&t1, &th));
		tramvaie.push_back(make_pair(&t2, &th2));
		int total = 0;
		for (int i = 0; i < tramvaie.size(); i++) {
			total += tramvaie[i].first->totalMinuteStationate();
			total += tramvaie[i].second->totalMinuteStationate();
		}

		cout << "TOTAL: " << total << endl;
		
	}
	catch (exception* e) {
		cout << e->what() << endl;
	}

	return 0;
}