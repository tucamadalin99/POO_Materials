#include <iostream>
#include<string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
class Analiza {
private:
	const int idPacient;
protected:
	static int contor;
	static const int lungimeData = 8;
	string numePacient;
	int varsta;
	int* dataNastere;
	float cost;

public:
	Analiza():idPacient(contor++) {
		this->numePacient = "";
		this->varsta = 0;
		this->dataNastere = NULL;
		this->cost = 0.0f;
		//cout << "TEST" << endl;
	}

	Analiza(string numePacient, int varsta, int* dataNastere, float cost) :idPacient(contor++) {
		if (numePacient.length() < 3)
			throw new exception("Lungimea numelui trebuie sa aiba cel putin 3 caractere");
		else if (varsta < 0)
			throw new exception("Varsta nu poate fi negativa!");
		else if (dataNastere == NULL)
			throw new exception("Pacientul trebuie sa aiba o data de nastere");
		else if (cost < 0)
			throw new exception("Costul nu poate fi negativ");
		else {
			this->numePacient = numePacient;
			this->varsta = varsta;
			this->dataNastere = new int[lungimeData];
			for (int i = 0; i < lungimeData; i++) {
				this->dataNastere[i] = dataNastere[i];
			}
			this->cost = cost;
		}
		//cout << "TEST PARAMS" << endl;
	}

	Analiza(Analiza& a):idPacient(contor++) {
		this->numePacient = a.numePacient;
		this->varsta = a.varsta;
		this->dataNastere = new int[a.lungimeData];
		for (int i = 0; i < a.lungimeData; i++)
			this->dataNastere[i] = a.dataNastere[i];
		this->cost = a.cost;
		//cout << "TEST COPIERE" << endl;
	}
	
	~Analiza() {
		if (this->dataNastere != NULL)
			delete[]this->dataNastere;
	}

	friend ostream& operator<<(ostream& out, Analiza &a) {
		out << "Nume pacient: " << a.numePacient << endl;
		out << "Varsta: " << a.varsta << endl;
		out << "Data nastere: ";
		for (int i = 0; i < a.lungimeData; i++) {
			out << a.dataNastere[i];
		}
		out << endl;
		out << "Cost: " << a.cost << endl;
		return out;
	}

	Analiza& operator=(Analiza& a) {
		if (this != &a) {
			this->numePacient = a.numePacient;
			this->varsta = a.varsta;
			if (this->dataNastere != NULL)
				delete[]this->dataNastere;
			this->dataNastere = new int[a.lungimeData];
			for (int i = 0; i < a.lungimeData; i++)
				this->dataNastere[i] = a.dataNastere[i];
			this->cost = a.cost;
			return *this;
		}
		else throw new exception("Autoasignarea nu este permisa.");
	
	}

	//Operator matematic binar +
	//Majorare cost
	Analiza operator+(int majorare) {
		Analiza copie = *this;
		this->cost += majorare;
		return copie;
	}

	//Cost in euro
	explicit operator float() {
		return this->cost / 4.5f;
	}

	bool operator<(Analiza a) {
		if (this->cost < a.cost)
			return true;
		else
			return false;
	}

	bool operator==(Analiza a) {
		if (this->cost == a.cost)
			return true;
		else return false;
	}

	float getCost() {
		return this->cost;
	}

	int getVarsta() {
		return this->varsta;
	}

	void setDenumire(string denumire) {
		if (denumire.length() < 3) {
			throw new exception("Nu se poate seta un nume cu mai putin 3 caractere");
		}
		else
			this->numePacient = denumire;
	}

	int& operator[](int index) {
		if (index >= 0 && index <= lungimeData)
			return this->dataNastere[index];
		else
			throw new exception("Index in afara limitelor");
	}

	//Creste varsta postfixat
	Analiza operator++(int) {
		Analiza copie = *this;
		this->varsta += 1;
		return copie;
	}

	static float medieVarsta(Analiza* a, int n) {
		if (n < 0) {
			throw new exception("Lungimea nu poate fi negativa!");
		}
		else {
			float sum = 0;
			for (int i = 0; i < n; i++) {
				sum += a[i].getVarsta();
			}
			return sum / n;
		}

	}

	static void afiseazaNumePacienti(Analiza* a, int n) {
		if (n < 0) {
			cout << "Nu exista pacienti." << endl;
		}
		else {
			for (int i = 0; i < n; i++) {
				cout << "Nume pacient: " << i + 1 << " " <<  a[i].numePacient << endl;
			}
		}

	}


	void serializare() {
		ofstream fileOutput;
		fileOutput.open("pacient.bin", ios::out, ios::binary);
		int lungime = this->numePacient.length();
		fileOutput.write((char*)&lungime, sizeof(int));
		const char* denumire = this->numePacient.c_str();
		fileOutput.write(denumire, lungime + 1);
		fileOutput.write((char*)&this->varsta, sizeof(int));
		lungime = 0;
		lungime = lungimeData;
		for (int i = 0; i < lungime; i++) {
			fileOutput.write((char*)&this->dataNastere[i], sizeof(int));
		}
		fileOutput.write((char*)&this->cost, sizeof(float));
		cout << "Serializare reusita" << endl;
		fileOutput.close();
	}

	void deserializare() {
		ifstream fileInput;
		fileInput.open("pacient.bin", ios::in, ios::binary);
		int lungime = 0;
		fileInput.read((char*)&lungime, sizeof(int));
		char* denumire = new char[lungime + 1];
		fileInput.read(denumire, lungime + 1);
		string denStr = denumire;
		this->numePacient = denStr;
		fileInput.read((char*)&this->varsta, sizeof(int));
		lungime = lungimeData;
		if (this->dataNastere != NULL)
			delete[]this->dataNastere;
		this->dataNastere = new int[lungime];
		for (int i = 0; i < lungime; i++) {
			fileInput.read((char*)&this->dataNastere[i], sizeof(int));
		}
		fileInput.read((char*)&this->cost, sizeof(float));
		cout << "Obiect deserializat cu succes" << endl;
		fileInput.close();
	}

	virtual void afiseazaNume() {
		cout << "Numele pacientului este: " << this->numePacient << endl;
	}
};
int Analiza::contor = 0;

class ProceduraSpital : public Analiza {
private:
	string numeDoctor;
	int aniExperientaDoctor;
	
public:
	ProceduraSpital() :Analiza() {
		this->numeDoctor = "";
		this->aniExperientaDoctor = 0;
	}

	ProceduraSpital(string numePacient, int varsta, int* dataNastere, float cost, string numeDoctor, int aniExperientaDoctor)
		:Analiza(numePacient, varsta, dataNastere, cost) {
		this->numeDoctor = numeDoctor;
		this->aniExperientaDoctor = aniExperientaDoctor;
	}

	ProceduraSpital(ProceduraSpital& pr) :Analiza(pr) {
		this->numeDoctor = pr.numeDoctor;
		this->aniExperientaDoctor = pr.aniExperientaDoctor;
	}
	
	~ProceduraSpital() {

	}

	ProceduraSpital& operator=(ProceduraSpital& pr) {
		if (this != &pr) {
			Analiza::operator=(pr);
			this->numeDoctor = pr.numeDoctor;
			this->aniExperientaDoctor = pr.aniExperientaDoctor;
			return *this;
		}
		else {
			throw new exception("Autoasignarea nu este permisa!");
		}
	}

	friend ostream& operator<<(ostream& out, ProceduraSpital& pr) {
		out << (Analiza&)pr << endl;
		out << "Nume doctor: " << pr.numeDoctor << endl;
		out << "Ani experienta: " << pr.aniExperientaDoctor << endl;
		return out;
	}

	void afiseazaNume() {
		cout << "Numele doctorului care a efectuat analiza: " << this->numeDoctor << endl;
	}

	
	
};
int main() {
	try {
		Analiza a;
		Analiza a1("Cosmin", 20, new int[8]{ 1,1,0,9,1,9,9,9 }, 300.50);
		Analiza a2 = a1;
		cout << a2 << endl;
		a = a2;
		cout << "----------" << endl;
		cout << a << endl;
		cout << "Costul analizei in EUR: " << float(a) << endl;
		//Apel +
		a + 150;
		cout << "Majorare cost analiza: " << a << endl;
		cout << "-------------------------" << endl;
		cout << "Comparare cost mai mic: " << endl;
		Analiza a3("Dorian", 21, new int[8]{ 0,1,0,8,1,9,9,9 }, 250.5);
		if (a < a3) {
			cout << "Costul lui a este mai mic" << endl;
		}
		else
			cout << "Costul lui a este mai mare." << endl;

		cout << "Apel index: " << a[3] << endl;
		cout << "Apel ++ postfixat" << endl;
		a++;
		cout << a << endl;
		cout << "Apel setter: " << endl;
		a.setDenumire("Ionel");
		cout << a << endl;
		cout << "-------------------------" << endl;
		cout << "Apel metoda statica varsta medie pacienti: " << endl;
		cout << "Varsta medie: " << Analiza::medieVarsta(new Analiza[3]{ a, a2, a3 }, 3) << endl;
		cout << "-------------------------" << endl;
		cout << endl << "Afisare lista cu numele pacientilor: " << endl;
		Analiza::afiseazaNumePacienti(new Analiza[3]{ a,a2,a3 }, 3);
		cout << "-------------------------" << endl;
		cout << "Serializare: " << endl;
		a.serializare();
		Analiza aFisier;
		aFisier.deserializare();
		cout << aFisier << endl;
		cout << "-------------------------" << endl;
		cout << "CLASA DERIVATA ProceduraSpital: " << endl;
		ProceduraSpital pr("Ionut", 18, new int[8]{ 0,2,0,5,1,9,9,9 }, 350.5, "Popescu Marian", 5);
		ProceduraSpital pr2("Pavel", 17, new int[8]{ 0,6,0,2,1,9,9,9 }, 350.5, "Mariana Apostu", 10);
		cout << "Afisare procedura: " << endl;
		cout << pr2 << endl;
		cout << "-------------------------" << endl;
		Analiza** proceduri = new Analiza*[4];
		proceduri[0] = &a;
		proceduri[1] = &pr;
		proceduri[2] = &a3;
		proceduri[3] = &pr2;

		for (int i = 0; i < 4; i++) {
			proceduri[i]->afiseazaNume();
		}
		cout << "-------------------------" << endl;
		cout << "STL: " << endl;
		vector<Analiza*>analizeVector;
		analizeVector.push_back(&a);
		analizeVector.push_back(&a2);
		analizeVector.push_back(&a3);
		vector<Analiza*>::iterator iterare;
		for (iterare = analizeVector.begin(); iterare != analizeVector.end(); iterare++)
			cout << (**iterare) << endl;

 	}
	catch (exception* e) {
		cout << e->what() << endl;
	}
	return 0;
}