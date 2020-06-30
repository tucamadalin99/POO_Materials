//// RestantaRobert.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

class Examen {
private:
	const int id;
	static int contor;
	char* disciplina = NULL;
	float nota;

protected:
	string data;

public: 
	Examen():id(contor++) {
		this->disciplina = NULL;
		this->nota = 0.0f;
		this->data = "";
		//cout << "Constructor fara parametrii apelat." << endl;
	}

	Examen(const char* disciplina, float nota, string data):id(contor++) {
		if (this->disciplina != NULL)
			delete[] this->disciplina;
		this->disciplina = new char[strlen(disciplina) + 1];
		strcpy(this->disciplina, disciplina);
		this->nota = nota;
		this->data = data;
		//cout << "Constructor cu parametrii apelat." << endl;
	}

	 Examen(Examen& ex):id(contor++) {
		if (this->disciplina != NULL)
			delete[] this->disciplina;
		this->disciplina = new char[strlen(ex.disciplina) + 1];
		strcpy(this->disciplina, ex.disciplina);
		this->nota = ex.nota;
		this->data = ex.data;
		//cout << "Constructor de copiere apelat." << endl;
	}

	~Examen() {
		if (this->disciplina != NULL)
			delete[] this->disciplina;
		//cout << "Destructor apelat." << endl;
	}

	friend ostream& operator<<(ostream& out, Examen& ex) {
		out << "ID: " << ex.id << endl;
		out << "Disciplina: " << ex.disciplina << endl;
		out << "Nota: " << ex.nota << endl;
		out << "Data: " << ex.data << endl;
		return out;
	}

	Examen& operator=(const Examen& ex) {
		if (this->disciplina != NULL)
			delete[] this->disciplina;
		this->disciplina = new char[strlen(ex.disciplina) + 1];
		strcpy(this->disciplina, ex.disciplina);
		this->nota = ex.nota;
		this->data = ex.data;
		return *this;
	}

	bool operator==(const Examen ex) {
		if (strcmp(this->disciplina, ex.disciplina) == 0)
			return true;
		else
			return false;
	}

	explicit operator float() {
		return this->nota * 0.3;
	}

	Examen operator+(float val) {
		Examen copy = *this;
		copy.nota += val;
		return copy;
	}

	char* getDisciplina() {
		return this->disciplina;
	}

	void setDisciplina(const char* disciplina) {
		if (this->disciplina != NULL)
			delete[] this->disciplina;
		this->disciplina = new char[strlen(disciplina) + 1];
		strcpy(this->disciplina, disciplina);
	}

	string getData() {
		return this->data;
	}
	void setData(string data) {
		this->data = data;
	}

	static float medieExamene(int nr, Examen* examene) {
		if (examene == NULL)
			return 0.0f;
		else {
			if (nr > 0) {
				try {
					float result = 0;
					for (int i = 0; i < nr; i++) {
						result += examene[i].nota;
					}

					return result / nr;
				}
				catch (exception ex) {
					cout << "Numarul introdus este mai mare decat vectorul!" << endl;
				}
			}

		}
	}

	static void afisareExamene(int nr, Examen* examene) {
		if (examene == NULL)
			cout << "Nu exista examene programate." << endl;
		else {
			if(nr > 0)
				try {
				for (int i = 0; i < nr; i++) {
					cout << examene[i] << endl;
				}
			}
			catch (exception ex) {
				cout << "Array exceded" << endl;
			}
		}
	}

	void seraialize() {
		ofstream f;
		f.open("object.bin", ios::out | ios::binary);
		int len = strlen(this->disciplina);
		char* disc = new char[len + 1];
		strcpy(disc, this->disciplina);
		f.write((char*)&len, sizeof(int));
		f.write(disc, len + 1);
		f.write((char*)&this->nota, sizeof(float));
		len = data.length();
		const char* dat = data.c_str();
		f.write((char*)&len, sizeof(int));
		f.write(dat, len + 1);
		f.close();
		cout << "Serialized in object.bin" << endl;
	}

	void deserialize() {
		ifstream f;
		f.open("object.bin", ios::in | ios::binary);
		int len = 0;
		f.read((char*)&len, sizeof(int));
		char* disc = new char[len + 1];
		f.read(disc, len + 1);
		if (this->disciplina != NULL)
			delete[] this->disciplina;
		this->disciplina = new char[len + 1];
		strcpy(this->disciplina, disc);
		f.read((char*)&nota, sizeof(float));
		len = 0;
		f.read((char*)&len, sizeof(int));
		char* dat = new char[len + 1];
		f.read(dat, len + 1);
		this->data = dat;
		f.close();
		cout << "Deserialized current object!" << endl;
	}
};
int Examen::contor = 1;

template<class Examen>
class Student {
private:
	Examen* examene = NULL;
	string numeStudent;
	int nrExamene;

public:
	Student() {
		this->examene = NULL;
		string numeStudent = "";
		this->nrExamene = 0;
		cout << "Constructor colectie fara param." << endl;
	}

	Student(Examen* examene, string nume, int nr) {
		if (examene != NULL)
			delete[] this->examene;
		this->examene = new Examen[nr];
		for (int i = 0; i < nr; i++) {
			this->examene[i] = examene[i];
		}
		this->numeStudent = nume;
		this->nrExamene = nr;
		cout << "Constructor cu parametrii " << endl;
		
	}

	void operator+=(Examen& ex) {
		int nr = this->nrExamene;
		Examen* exameneCopy = new Examen[this->nrExamene + 1];
		this->nrExamene++;
		for (int i = 0; i < nr; i++) {
			exameneCopy[i] = this->examene[i];
		}
		exameneCopy[this->nrExamene-1] = ex;
		if (this->examene != NULL)
			delete[] this->examene;
		this->examene = new Examen[this->nrExamene];
		this->examene = exameneCopy;
	}

	void operator-=(int nr) {
		int nrNou = this->nrExamene - nr;
		Examen* vectNou = new Examen[nrNou];
		for (int i = 0; i < nrNou; i++) {
			vectNou[i] = this->examene[i];
		}

		if (this->examene != NULL)
			delete[] this->examene;
		this->examene = new Examen[nrNou];
		this->examene = vectNou;
		this->nrExamene -= nr;
	}

	friend ostream& operator<<(ostream& out, Student& s) {
		for (int i = 0; i < s.nrExamene; i++) {
			cout << s.examene[i] << endl;
		}
		out << "Nume: " << s.numeStudent << endl;
		return out;
	}

	~Student() {
		if (examene != NULL)
			delete[] this->examene;
	}
};
int main()
{
	Examen ex1;
	Examen ex2("Mate", 7.6, "11/09/2020");
	Examen ex3 = ex2;
	ex1 = ex3;
	cout << ex3 << endl;
	cout << ex1  << endl;
	cout << endl;
	cout << "Compararea lui ex3 cu ex2: " << (ex3 == ex2) << endl;
	ex3 = ex3 + 1.5;
	cout << "Marire nota: " << ex3 << endl;
	Examen* exs = new Examen[3];
	exs[0] = ex1;
	exs[1] = ex2;
	exs[2] = ex3;
	float result = Examen::medieExamene(3, exs);
	cout << "Media celor 3 examene: " << result << endl;
	ex1.setData("01/01/1999");
	cout << ex1 << endl;
	cout << "Afisarea examenelor: " << endl;
	Examen::afisareExamene(3, exs);
	ex2.seraialize();
	Examen ex4;
	ex4.deserialize();
	cout << ex4 << endl;
	ex2.deserialize();
	cout << ex2 << endl;

	cout << "--------------------- CLASA COLECTIE --------------------" << endl;
	Student<Examen> s1(exs, "Daniel", 3);
	cout << s1 << endl;
	Examen ex5("Chimie", 8.4, "11/02/2020");
	s1 += ex5;
	Examen ex6("Info", 8.4, "11/02/2020");
	s1 += ex6;
	cout << s1 << endl;
	s1 -= 1;
	cout << "Scoatere: " << endl;
	cout << s1 << endl;
	vector<Examen*> examene;
	examene.push_back(&ex1);
	examene.push_back(&ex2);
	examene.push_back(&ex3);
	examene.push_back(&ex4);
	examene.push_back(&ex5);
	for (int i = 0; i < examene.size(); i++) {
		cout << *examene[i] << endl;
	}
}

