#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
enum tipVagon{ClasaI, ClasaII, Cuseta};
class VagonPasageri {
private:
	string codVagon;
	tipVagon tip;
	int nrLocuri;
	int* locuriOcupate = NULL;
	bool esteOcupat = false;
	static int NR_MAXIM_LOCURI;

public:
	VagonPasageri() {
		this->codVagon = "";
		this->tip = ClasaII;
		this->nrLocuri = 0;
		this->locuriOcupate = NULL;
		this->esteOcupat = false;
	}

	VagonPasageri(string codVagon, tipVagon tip, int nrLocuri, int* locuriOcupate) {
		if (codVagon == "" || codVagon.length() < 2)
			throw new exception("Codul vagonului trebuie sa respecte formatul valid.");
		else if (nrLocuri > NR_MAXIM_LOCURI)
			throw new exception("S-a depasit numarul maxim de locuri");
		else if (locuriOcupate == NULL)
			throw new exception("Vectorul trebuie sa fie alocat");
		else {
			this->codVagon = codVagon;
			this->tip = tip;
			this->nrLocuri = nrLocuri;
			this->locuriOcupate = new int[nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				this->locuriOcupate[i] = locuriOcupate[i];
		}
	}

	VagonPasageri(VagonPasageri& v) {
		this->codVagon = v.codVagon;
		this->codVagon.append("_duplicat");
		this->tip = v.tip;
		this->nrLocuri = v.nrLocuri;
		this->locuriOcupate = new int[v.nrLocuri];
		for (int i = 0; i < v.nrLocuri; i++)
			this->locuriOcupate[i] = v.locuriOcupate[i];
	}

	VagonPasageri& operator=(VagonPasageri& v) {
		if (this != &v) {
			this->codVagon = v.codVagon;
			this->codVagon.append("_duplicat");
			this->tip = v.tip;
			this->nrLocuri = v.nrLocuri;
			if (this->locuriOcupate != NULL)
				delete[]this->locuriOcupate;
			this->locuriOcupate = new int[v.nrLocuri];
			for (int i = 0; i < v.nrLocuri; i++)
				this->locuriOcupate[i] = v.locuriOcupate[i];
		}
		else throw new exception("Autoatribuirea nu este permisa");

	}
	
	~VagonPasageri() {
		if (this->locuriOcupate != NULL)
			delete[] this->locuriOcupate;
	}

	int* getLocuriOcupate() {
		return this->locuriOcupate;
	}
	
	bool getOcupare() {
		return this->esteOcupat;
	}

	int getTip() {
		return this->tip;
	}

	int getNrLocuri() {
		return this->nrLocuri;
	}

	string getCodVagon() {
		return this->codVagon;
	}

	explicit operator float() {
		int sum = 0;
		for (int i = 0; i < this->nrLocuri; i++) {
			if (this->locuriOcupate[i] != 0)
				sum += 1;
		}
		return ((float)sum / this->nrLocuri) * 100;
	}

	friend ostream& operator<<(ostream& out, VagonPasageri& v) {
		out << "Cod vagon: " << v.codVagon << endl;
		out << "Tip vagon: " << v.tip << endl;
		out << "Nr. locuri: " << v.nrLocuri << endl;
		out << "Locuri ocupate: " << endl;
		for (int i = 0; i < v.nrLocuri; i++)
			out << v.locuriOcupate[i] << " ";
		return out;
	}

	void esteOcupatVagonul() {
		int contor = 0;
		for (int i = 0; i < this->nrLocuri; i++)
			if (this->locuriOcupate[i] != 0)
				contor += 1;
		if (contor == this->nrLocuri)
			this->esteOcupat = true;
		else
			this->esteOcupat = false;
	}

	bool operator[](int index){
		bool ocupare = false;
		if (index >= 0 && index <= this->nrLocuri) {
			if (this->locuriOcupate[index] < 0)
				throw new exception("Numarul este gresit!");
			if (this->locuriOcupate[index] != 0)
				ocupare = true;
		}
		else
			throw new exception("Numarul este in fara limitelor!");

		return ocupare;
	}

	void Raport() {
		ofstream fileOut;
		fileOut.open("radport.txt", ios::out);
		fileOut << this->codVagon << " ";
		fileOut << "Tip: " << this->tip << endl;
		fileOut << "Locuri ocupate: ";
		for (int i = 0; i < this->nrLocuri; i++)
			if (this->locuriOcupate[i] != 0)
				fileOut << i + 1 << " ";
		fileOut << endl;
		fileOut << "Locuri libere: ";
		for (int i = 0; i < this->nrLocuri; i++)
			if (this->locuriOcupate[i] == 0)
				fileOut << i + 1 << " ";
		fileOut.close();
		cout << "Raport text generat!" << endl;

	}


};
int VagonPasageri::NR_MAXIM_LOCURI = 250;

class GarnituraTren {
private:
	string numeTren;
	int nrVagoane;
	VagonPasageri* vagoane = NULL;

public:
	GarnituraTren(string numeTren, int nrVagoane, VagonPasageri* vagoane) {
		this->numeTren = numeTren;
		this->nrVagoane = nrVagoane;
		if (this->vagoane != NULL)
			delete[]this->vagoane;
		this->vagoane = new VagonPasageri[nrVagoane];
		for (int i = 0; i < this->nrVagoane; i++) {
			this->vagoane[i] = vagoane[i];
		}
	}

	GarnituraTren(GarnituraTren& gt) {
		this->numeTren = gt.numeTren;
		this->nrVagoane = gt.nrVagoane;
		if (this->vagoane != NULL)
			delete[]this->vagoane;
		this->vagoane = new VagonPasageri[gt.nrVagoane];
		for (int i = 0; i < gt.nrVagoane; i++)
			this->vagoane[i] = gt.vagoane[i];
	}

	GarnituraTren& operator=(GarnituraTren& gt) {
		if (this != &gt) {
			this->numeTren = gt.numeTren;
			this->nrVagoane = gt.nrVagoane;
			if (this->vagoane != NULL)
				delete[]this->vagoane;
			this->vagoane = new VagonPasageri[gt.nrVagoane];
			for (int i = 0; i < gt.nrVagoane; i++)
				this->vagoane[i] = gt.vagoane[i];
		}
		else throw new exception("Autoatribuirea nu este permisa");
	}

	void operator+=(VagonPasageri &v) {
		VagonPasageri* aux = new VagonPasageri[this->nrVagoane + 1];
		for (int i = 0; i < this->nrVagoane; i++) {
			aux[i] = this->vagoane[i];
		}
		this->nrVagoane += 1;
		aux[this->nrVagoane - 1] = v;
		if (this->vagoane != NULL)
			delete[]this->vagoane;
		this->vagoane = new VagonPasageri[this->nrVagoane];
		for (int i = 0; i < this->nrVagoane; i++)
			this->vagoane[i] = aux[i];
		if (aux != NULL)
			delete[]aux;
	}

	float totalIncasari(float pretBazaBilet) {
		float sum = 0;
		for (int i = 0; i < this->nrVagoane; i++) {
			if (this->vagoane[i].getTip() == 0) {
				for (int j = 0; j < this->vagoane[i].getNrLocuri(); j++)
					if (this->vagoane[i].getLocuriOcupate()[j] != 0)
						sum += 1.5 * pretBazaBilet;

			}

			else if (this->vagoane[i].getTip() == 1) {
				for (int j = 0; j < this->vagoane[i].getNrLocuri(); j++)
					if (this->vagoane[i].getLocuriOcupate()[j] != 0)
						sum += pretBazaBilet;
			}

			else
				for (int j = 0; j < this->vagoane[i].getNrLocuri(); j++) {
					if (this->vagoane[i].getLocuriOcupate()[j] != 0)
						sum += 2 * pretBazaBilet;

			}
		}
		return sum;
	}

	~GarnituraTren() {

		if (this->vagoane != NULL)
			delete[]this->vagoane;
	}

	friend ostream& operator<<(ostream& out, GarnituraTren& gt) {
		out << "Nume tren: " << gt.numeTren << endl;
		out << "Numar vagoane: " << gt.nrVagoane << endl;
		out << endl;
		for (int i = 0; i < gt.nrVagoane; i++)
			out << gt.vagoane[i] << endl << endl;
		out << endl;
		return out;
	}
};

class GarnituraTren_v2 {
	string numeTren;
	int nrVagoane;
	vector<VagonPasageri*>vagoane;

public:
	GarnituraTren_v2(string numeTren, int nrVagoane, VagonPasageri* vagoane) {
		this->numeTren = numeTren;
		this->nrVagoane = nrVagoane;
		
		for (int i = 0; i < this->nrVagoane; i++) {
			this->vagoane.push_back(&vagoane[i]);
		}
	}

	vector<VagonPasageri*> getVagoane() {
		return vagoane;
	}
};

int main() {
	try {
		VagonPasageri v1;
		int* locuriOcupate = new int[30];
		for (int i = 0; i < 30; i++) {
			if (i % 2 == 0)
				locuriOcupate[i] = 0;
			else
				locuriOcupate[i] = i + 1;
		}
		VagonPasageri v2("Vagon", ClasaII, 30, locuriOcupate);
		VagonPasageri v4 = v2;
		v1 = v4;
		cout << v4 << endl;
		float gradOcupare = (float)v4;
		cout << "Gradul de ocupare al vagonului este de: " << gradOcupare << "%" << endl;
		v4.esteOcupatVagonul();
		
		int* locuriOcupateComplet = new int[20];
		for (int i = 0; i < 20; i++) {
			locuriOcupateComplet[i] = i + 1;
		}
		VagonPasageri vp("CFR", ClasaI, 20, locuriOcupateComplet);
		cout << "--------------------------------" << endl;
		cout << vp << endl;
		cout << "Grad de ocupare: " << (float)vp << "%" << endl;
		vp.esteOcupatVagonul();
		cout << "Vagon ocupat: " << vp.getOcupare() << endl;
		cout << "--------------------------------" << endl;
		//Apel indexare
		if (v4[3]) {
			cout << "Locul este ocupat. " << endl;
		}
		else
			cout << "Locul este liber" << endl;
		v4.Raport();

		GarnituraTren gt("CFRCalatori", 3, new VagonPasageri[3]{ v1,v2,v4 });
		GarnituraTren gt2 = gt;
		cout << gt << endl;
		gt += vp;
		cout << gt << endl;
		cout << "-----------------------------------" << endl;
		cout << "Total incasari: " << gt.totalIncasari(30) << " RON " << endl;
		GarnituraTren_v2 gtv2("CFRBucuresti", 3, new VagonPasageri[3]{ v1,v2,v4 });
		for (int i = 0; i < gtv2.getVagoane().size(); i++) {
			cout << *gtv2.getVagoane()[i] << endl;
		}

	}
	catch (exception* e) {
		cout << e->what() << endl;
	}

	return 0;
}