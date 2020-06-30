#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

enum functie{servant, sefFormatie, voluntar, sofer};
class Pompier {
private:
	const int idPompier;
	static int contor;
	char* nume = NULL;
	functie funct;
	int nrInterventii = 0;
	float* durate = NULL;

public:
	Pompier() :idPompier(contor++) {
		this->nume = NULL;
		this->funct = servant;
		this->nrInterventii = 0;
		this->durate = NULL;
	}

	Pompier(const char* nume, functie f) :idPompier(contor++){
		if (this->nume != NULL)
			delete[] this->nume;
		if (strlen(nume) < 3) {
			throw new exception("Numele este prea mic");
		}
		else {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}

		if (f == NULL) {
			throw new exception("Pompierul trebuie sa aiba o functie.");
		}
		else {
			this->funct = f;
		}
	}

	Pompier(Pompier& p) :idPompier(contor++) {
		if (this->nume != NULL)
			delete[] this->nume;
		this->nume = new char[strlen(p.nume) + 1];
		strcpy(this->nume, p.nume);
		this->funct = p.funct;
		this->nrInterventii = p.nrInterventii;
		if (this->durate != NULL)
			delete[]this->durate;
		this->durate = new float[p.nrInterventii];
		for (int i = 0; i < p.nrInterventii; i++) {
			this->durate[i] = p.durate[i];
		}
	}

	Pompier& operator=(Pompier& p) {
		if (this != &p) {

			if (this->nume != NULL)
				delete[] this->nume;
			this->nume = new char[strlen(p.nume) + 1];
			strcpy(this->nume, p.nume);
			this->funct = p.funct;
			this->nrInterventii = p.nrInterventii;
			if (this->durate != NULL)
				delete[]this->durate;
			this->durate = new float[p.nrInterventii];
			for (int i = 0; i < p.nrInterventii; i++) {
				this->durate[i] = p.durate[i];
			}

			return *this;
		}
		else throw new exception("Obiectul a fost auto-atribuit!");
	}

	friend ostream& operator<<(ostream& out, Pompier& p) {
		out << "Nume: " << p.nume << endl;
		out << "Functie: " << p.funct << endl;
		out << "Numar interventii: " << p.nrInterventii << endl;
		for (int i = 0; i < p.nrInterventii; i++) {
			out << p.durate[i] << " ore" << endl;
		}

		return out;
	}

	float* getDurate() {
		return this->durate;
	}

	int getNrInverv() {
		return this->nrInterventii;
	}

	void adaugaInterventie(float durata) {
		float* copieDurate = new float[this->nrInterventii + 1];
		for (int i = 0; i < this->nrInterventii; i++)
			copieDurate[i] = this->durate[i];
		this->nrInterventii++;
		copieDurate[this->nrInterventii - 1] = durata;
		if (this->durate != NULL)
			delete[]this->durate;
		this->durate = new float[this->nrInterventii];
		for (int i = 0; i < this->nrInterventii; i++)
			this->durate[i] = copieDurate[i];
		delete[]copieDurate;
	}

	float durataMedieInterventii() {
		float sum = 0;
		if (this->nrInterventii > 0) {
			for (int i = 0; i < this->nrInterventii; i++) {
				sum += this->durate[i];
			}

			return sum / this->nrInterventii;
		}
		else
			return 0;
		
	}

	int nrInterv(float durata) {
		int contor = 0;
		if (this->nrInterventii > 0) {
			for (int i = 0; i < this->nrInterventii; i++) {
				if (this->durate[i] > durata)
					contor++;
			}
			return contor;
		}
		else
			return 0;
	}

	float& operator[](int index) {
		float val = 0;
		if (index >= 0 && index < this->nrInterventii) {
			float valInit = this->durate[index];
			cout << "La pozitia: " << index << " este valoarea: " << valInit << endl;
			cout << "Modificati valoarea: ";
			cin >> val;
			if (val < 1)
				throw new exception("Durata invalida! Introduceti din nou!");
			else {
				this->durate[index] = val;
				return this->durate[index];
			}

		}
		else
			throw new exception("Index in afara limitelor!");
	 }

	friend ofstream& operator<<(ofstream& file, Pompier& p){
		int len = strlen(p.nume);
		char* nume = new char[len + 1];
		strcpy(nume, p.nume);
		file.write((char*)&len, sizeof(int));
		file.write(nume, len + 1);
		file.write((char*)&p.funct, sizeof(functie));
		file.write((char*)&p.nrInterventii, sizeof(int));
		for (int i = 0; i < p.nrInterventii; i++) {
			file.write((char*)&p.durate[i], sizeof(float));
		}

		cout << "Obiect scris in object.bin!" << endl;
		return file;
	}

	friend ifstream& operator>>(ifstream& file, Pompier& p) {

		int len = 0;
		file.read((char*)&len, sizeof(int));
		char* nume = new char[len + 1];
		file.read(nume, len + 1);
		if (p.nume != NULL)
			delete[]p.nume;
		p.nume = new char[len + 1];
		strcpy(p.nume, nume);
		file.read((char*)&p.funct, sizeof(functie));
		int nrInterv = 0;
		file.read((char*)&nrInterv, sizeof(int));
		p.nrInterventii = nrInterv;
		if (p.durate != NULL)
			delete[]p.durate;
		p.durate = new float[p.nrInterventii];
		for (int i = 0; i < nrInterv; i++) {
			file.read((char*)&p.durate[i], sizeof(float));
		}
		cout << "Obiect citit cu succes! " << endl;
		return file;
	}

	~Pompier() {
		if (this->nume != NULL)
			delete[]this->nume;
		if (this->durate != NULL)
			delete[]this->durate;
	}
	
};
int Pompier::contor = 0;

class FormatieInterventie {
private:
	char idFormatie[30];
	int nrPompieri;
	Pompier** pomps;

public:
	FormatieInterventie() {
		this->nrPompieri = 0;
		this->pomps = NULL;
	}

	FormatieInterventie(const char* idFormatie, int nrPompieri, Pompier* vp[]) {
		strcpy(this->idFormatie, idFormatie);
		this->nrPompieri = nrPompieri;
		this->pomps = new Pompier*[this->nrPompieri];
		for (int i = 0; i < this->nrPompieri; i++) {
			this->pomps[i] = vp[i];
		}

		cout << "Formatie pompieri instantiata ! " << endl;
	}

	FormatieInterventie(FormatieInterventie& fi) {
		strcpy(this->idFormatie, fi.idFormatie);
		this->nrPompieri = fi.nrPompieri;
		if (this->pomps != NULL)
			delete[] this->pomps;
		this->pomps = new Pompier*[fi.nrPompieri];
		for (int i = 0; i < fi.nrPompieri; i++)
			this->pomps[i] = fi.pomps[i];
		cout << "Formatie interventie copiata!" << endl;
	}

	FormatieInterventie& operator=(FormatieInterventie& fi) {
		strcpy(this->idFormatie, fi.idFormatie);
		this->nrPompieri = fi.nrPompieri;
		if (this->pomps != NULL)
			delete[] this->pomps;
		this->pomps = new Pompier*[fi.nrPompieri];
		for (int i = 0; i < fi.nrPompieri; i++)
			this->pomps[i] = fi.pomps[i];
		cout << "Formatie operator = " << endl;
		return *this;
	}

	friend ostream& operator<<(ostream& out, FormatieInterventie& f) {
		out << "ID Formatie: " << f.idFormatie << endl;
		out << "Numar pompieri: " << f.nrPompieri << endl;
		out << "Pompieri: " << endl;
		for (int i = 0; i < f.nrPompieri; i++) {
			cout << *f.pomps[i] << endl;
		}

		return out;
	}

	friend ofstream& operator<<(ofstream& file, FormatieInterventie& f) {
		int len = strlen(f.idFormatie);
		char* idForm = new char[len + 1];
		strcpy(idForm, f.idFormatie);
		file.write((char*)&len, sizeof(int));
		file.write(idForm, len + 1);
		file.write((char*)&f.nrPompieri, sizeof(int));
		for (int i = 0; i < f.nrPompieri; i++)
			file.write((char*)&f.pomps[i], sizeof(Pompier*));

		cout << "Obiect scris in objForm.bin!" << endl;
		return file;
	}

	friend ifstream& operator>>(ifstream& file, FormatieInterventie& f) {
		int len = 0;
		file.read((char*)&len, sizeof(int));
		char* idForm = new char[len + 1];
		file.read(idForm, len + 1);
		strcpy(f.idFormatie, idForm);
		int nrPomp = 0;
		file.read((char*)&nrPomp, sizeof(int));
		f.nrPompieri = nrPomp;
		if (f.pomps != NULL)
			delete[] f.pomps;
		f.pomps = new Pompier*[f.nrPompieri];
		for (int i = 0; i < f.nrPompieri; i++)
			file.read((char*)&f.pomps[i], sizeof(Pompier*));
		cout << "Obiect citit cu succes! " << endl;
		return file;
	}

};

int main() {

	Pompier p1;
	try {
		Pompier p2("Ion", sofer);
		Pompier p3 = p2;
		p1 = p2;
		//p3 = p3;
		cout << p2 << endl;
		p2.adaugaInterventie(30.5);
		p2.adaugaInterventie(50.3);
		p2.adaugaInterventie(10.2);
		cout << p2 << endl;
		cout << "-------------------------------------" << endl;
		cout << "Calcul durata medie interventie: " << p2.durataMedieInterventii() << " ore" << endl;
		float durata = 10.5;
		cout << "-------------------------------------" << endl;
		cout << "Inverentiile care depasesc durata de " << durata << " ore: " << p2.nrInterv(durata) << endl;
		cout << "-------------------------------------" << endl;
		cout << "Apelare indexare si modificare: " << endl;
		cout << p2[2] << endl;
		cout << "Obiectul cu valoarea modificata: " << endl << p2 << endl;
		cout << "-------------------------------------" << endl;
		cout << "Fisiere binare << >> " << endl;
		cout << "-------------------------------------" << endl;
		cout << "Scriere binara: " << endl;
		ofstream binObj("object.bin", ios::out | ios::binary);
		binObj << p2;
		binObj.close();
		cout << endl << "Citire binar: " << endl;
		ifstream objBin("object.bin", ios::in | ios::binary);
		Pompier p5;
		objBin >> p5;
		objBin.close();
		cout << endl << p5 << endl; 


		cout << endl << "-----------------CLASA FORMATIE POMPIERI--------------------" << endl;
		Pompier* pomps[3];
		Pompier pf1("Cosmin", sefFormatie);
		pf1.adaugaInterventie(20.4);
		pf1.adaugaInterventie(30.5);
		Pompier pf2("Andrei", voluntar);
		pf2.adaugaInterventie(40.2);
		pf2.adaugaInterventie(10.4);
		pf2.adaugaInterventie(5.4);
		Pompier pf3("Dorel", sofer);
		pf3.adaugaInterventie(20.1);
		pf3.adaugaInterventie(10.1);
		pomps[0] = &pf1;
		pomps[1] = &pf2;
		pomps[2] = &pf3;


		FormatieInterventie fi1;
		FormatieInterventie fi2("stingatori", 3, pomps);
		FormatieInterventie fi3 = fi2;
		fi1 = fi3;

		cout << endl << fi2 << endl;
		cout << "-------------------------------------" << endl;
		cout << endl << "Serializare: " << endl;
		ofstream binFile("objForm.bin", ios::out | ios::binary);
		binFile << fi2;
		binFile.close();

		ifstream binFileIn("objForm.bin", ios::in | ios::binary);
		FormatieInterventie fb;
		binFileIn >> fb;
		binFileIn.close();
		
		cout << endl << fb << endl;
		
		cout << "-------------------------------------" << endl;
		cout << "-----------------STL-----------------" << endl;
		vector<Pompier*>pompieri;
		pompieri.push_back(&pf3);
		pompieri.push_back(&p2);
		pompieri.push_back(&pf1);
		pompieri.push_back(&pf2);


		vector<Pompier*>::iterator it;
		for (it = pompieri.begin(); it != pompieri.end(); it++) {
			cout << **it << endl;
		}
		float medieTotala = 0;
		float sumDurate = 0;
		int sumInterventii = 0;
		for (int i = 0; i < pompieri.size(); i++) {
			float* durate = pompieri[i]->getDurate();
			for (int j = 0; j < pompieri[i]->getNrInverv(); j++) {
				sumDurate += durate[j];
				
			}

			medieTotala = sumDurate / pompieri[i]->getNrInverv();
			cout << "Media tuturor interventiilor pompier  " << i + 1 << ": " << medieTotala << endl;
			sumDurate = 0;
		}

	}
	catch(exception* e){
		cout << e->what() << endl;
	}



	return 0;
}