#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class CursaAvion {
private:
	const int idAvion;
	static int contor;
	string orasPlecare;
	string orasDestinatie;
	bool inDerulare = 0;
	int nrBilete = 0;
	float* preturiBilete = NULL;

public:


	CursaAvion() :idAvion(contor++) {
		this->orasPlecare = "";
		this->orasDestinatie = "";
		this->inDerulare = 0;
		this->nrBilete = 0;
		this->preturiBilete = NULL;
	}

	CursaAvion(string orasPlecare, string orasDestinatie):idAvion(contor++) {
		if (orasPlecare.length() < 3 || orasDestinatie.length() < 3)
			throw new exception("Numele orasului are minim 3 caractere.");
		else {
			this->orasPlecare = orasPlecare;
			this->orasDestinatie = orasDestinatie;
		}

	}

	CursaAvion(CursaAvion& c):idAvion(contor++) {
		if (c.inDerulare == true)
			throw new exception("Nu se poate copia o cursa in derulare!");
		else {
			this->orasPlecare = c.orasPlecare;
			this->orasDestinatie = c.orasDestinatie;
			this->inDerulare = c.inDerulare;
			this->nrBilete = nrBilete;
			if (c.preturiBilete > 0) {
				if (this->preturiBilete != NULL)
					delete[]this->preturiBilete;
				this->preturiBilete = new float[this->nrBilete];
				for (int i = 0; i < this->nrBilete; i++)
					this->preturiBilete[i] = c.preturiBilete[i];
			}
			else
				this->preturiBilete = NULL;
		}
	}

	CursaAvion& operator=(CursaAvion& c) {
		if (this != &c) {
			if (c.inDerulare == true)
				throw new exception("Nu se poate copia o cursa in derulare!");
			else {
				this->orasPlecare = c.orasPlecare;
				this->orasDestinatie = c.orasDestinatie;
				this->inDerulare = c.inDerulare;
				this->nrBilete = nrBilete;
				if (c.preturiBilete > 0) {
					if (this->preturiBilete != NULL)
						delete[]this->preturiBilete;
					this->preturiBilete = new float[this->nrBilete];
					for (int i = 0; i < this->nrBilete; i++)
						this->preturiBilete[i] = c.preturiBilete[i];
				}
				else
					this->preturiBilete = NULL;
			}
		
		}
		else throw new exception("Auto asignarea nu este permisa.");
		
	}

	~CursaAvion() {
		this->inDerulare = 0;
		if (this->preturiBilete != NULL)
			delete[]this->preturiBilete;
	}

	string getOrasPlecare() {
		return this->orasPlecare;
	}

	string getOrasDestinatie() {
		return this->orasDestinatie;
	}

	bool getDerulare() {
		return this->inDerulare;
	}

	int getNrBilete() {
		return this->nrBilete;
	}

	float* getPreturiBilete() {
		return this->preturiBilete;
	}
	
	//SETTERI
	void setOrasPlecare(string orasPlecare) {
		this->orasPlecare = orasPlecare;
	}

	void setOrasDestinatie(string orasDestinatie) {
		this->orasDestinatie = orasDestinatie;
	}

	void setNrBilete(int nrBilete) {
		this->nrBilete = nrBilete;
	}

	void setDerulare(bool derulare) {
		this->inDerulare = derulare;
	}

	void setPreturiBilete(float* preturiBilete) {
		if (this->preturiBilete != NULL)
			delete[]this->preturiBilete;
		this->preturiBilete = new float[this->nrBilete];
		for (int i = 0; i < this->nrBilete; i++)
			this->preturiBilete[i] = preturiBilete[i];
	}

	friend ostream& operator<<(ostream& out, CursaAvion& c) {
		out << "ID: " << c.idAvion << endl;
		out << "Oras plecare: " << c.orasPlecare << endl;
		out << "Oras destinatie: " << c.orasDestinatie << endl;
		out << "In derulare: " << c.inDerulare << endl;
		out << "Nr Bilete: " << c.nrBilete << endl;
		out << "Preturi bilete: " << endl;
		for (int i = 0; i < c.nrBilete; i++)
			out << c.preturiBilete[i] << " ";
		out << endl;
		return out;
	}

	virtual float calculVenitBusiness() {
		float sum = 0;
		if (this->nrBilete > 0) {
			for (int i = 0; i < this->nrBilete; i++) {
				if (this->preturiBilete[i] > 99)
					sum += this->preturiBilete[i];
			}

			return sum;
		}
		else
			throw new exception("Cursa pentru care se calculeaza nu are niciun bilet!");
	}
};
int CursaAvion::contor = 0;

class InterfataCatering {
	virtual int totalCostMese() = 0;
};


class CursaTransOceanica : public CursaAvion, InterfataCatering {
private:
	int durata;
	int nrMesePasager[300];

public:
	CursaTransOceanica(string orasPlecare, string orasDestinatie, int durata) :CursaAvion(orasPlecare, orasDestinatie) {
		this->durata = durata;
	}

	~CursaTransOceanica() {

	}

	void salveazaLoguri(string numeFisier) {
		ofstream file;
		file.open(numeFisier);
		for (int i = 0; i < this->durata; i++) {
			file << "Cursa de la: " + this->getOrasPlecare() + " la: " + this->getOrasDestinatie() + ", va pleca cu: " + to_string(this->getNrBilete()) + " pasageri\n";
		}
		file.close();

		cout << "Log scris cu succes." << endl;
	}

	void setNrMesePasager(int* nrMesePasager) {
		for (int i = 0; i < this->getNrBilete(); i++) {
			this->nrMesePasager[i] = nrMesePasager[i];
		}
	}

	 float calculVenitBusiness() {
		 float sum = 0;
		 float procent = 0;
		 if (this->getNrBilete() > 0) {
			 for (int i = 0; i < this->getNrBilete(); i++) {
				 if (this->getPreturiBilete()[i] > 99)
					 sum += this->getPreturiBilete()[i] + ((0.1 * this->nrMesePasager[i]) * this->getPreturiBilete()[i]);
			 }
		 }

		 return sum;
	}

	 explicit operator int() {
		 return this->durata / 60;
	 }

	 int totalCostMese() {
		 int sum = 0;
		 if (this->getNrBilete() > 0) {
			 for (int i = 0; i < this->getNrBilete(); i++) {
				 if (this->getPreturiBilete()[i] > 99)
					 sum += (0.1 * this->nrMesePasager[i]) * this->getPreturiBilete()[i];
			 }
		 }

		 return sum;
	 }
};


int main() {
	try {
		//Apel constructori si operator =
		CursaAvion c;
		CursaAvion c1("Bucuresti", "Italia");
		CursaAvion c2 = c1;
		c = c2;
		//Apel setteri
		c.setDerulare(true);
		c.setNrBilete(4);
		float* preturi = new float[4];
		preturi[0] = 301.23;
		preturi[1] = 403.21;
		preturi[2] = 550.10;
		preturi[3] = 630.53;
		c.setPreturiBilete(preturi);
		CursaAvion c3("Targu Jiu", "Bulgaria");
		c3.setDerulare(true);
		c3.setNrBilete(3);
		c3.setPreturiBilete(new float[3]{ 302.14,596.53,291.43 });
		//Apel operator <<
		cout << c;
		cout << "-----------------------------" << endl;
		cout << c3;
		cout << "-----------------------------" << endl;
		//Apel metoda virtuala
		c3.setNrBilete(5);
		c3.setPreturiBilete(new float[5]{ 19.32, 92.00, 101.43, 250.43, 83.04 });
		cout << "Suma biletelor de clasa Business: " << c3.calculVenitBusiness() << " RON " << endl;
		cout << "-----------------------------" << endl;
		//Apel CursaTransOceanica
		CursaTransOceanica cto("Brasov", "China", 120);
		cout << "-----------------------------" << endl;
		//Apel citire fisier
		cto.setNrBilete(5);
		cto.setPreturiBilete(new float[5]{ 19.32, 92.00, 101.43, 250.43, 83.04 });
		cto.salveazaLoguri("logs.txt");
		//Supra definire metoda calculBusiness
		cto.setNrMesePasager(new int[5]{ 2,1,4,2,1 });
		cout <<"Pretul cu mese per pasager: " << cto.calculVenitBusiness() << " RON " << endl;
		cout << "-----------------------------" << endl;
		//Apel cast la int
		cout << "Durata in ore este: " << (int)cto << " ore " << endl;
		cout << "-----------------------------" << endl;
		//Interfata Catering
		cout << "Total cost mese: " << cto.totalCostMese() << " RON " << endl;

		//STL
		cout << "--------------STL------------" << endl;
		vector<CursaAvion*>curse;
		c1.setNrBilete(2);
		c1.setPreturiBilete(new float[2]{ 345.12,10.0 });
		c2.setNrBilete(3);
		c2.setPreturiBilete(new float[3]{ 31.40,291.43,101.54 });
		c3.setNrBilete(2);
		c3.setPreturiBilete(new float[2]{ 384.123,292.30 });
		curse.push_back(&c1);
		curse.push_back(&c2);
		curse.push_back(&c3);
		for (int i = 0; i < curse.size(); i++) {
			cout << curse[i]->calculVenitBusiness() << endl;
		}
	}
	catch (exception* e) {
		cout << e->what() << endl;
	}


	return 0;
}