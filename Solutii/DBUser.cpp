#include<iostream>
#include<fstream>
#include<string>
using namespace std;
enum userType{Normal, DBAdmin, SuperUser};
class DBUser {
protected:
	char* userName;
	string parola;
	userType tip;
	char dataUltimuluiLogin[10];
	int nrAutentificariEsuate;
	bool esteBlocat = true;
	static int NR_MAXIM_LOGINURI;


public:
	DBUser() {
		this->userName = NULL;
		this->parola = "1234";
		this->tip = Normal;
		strcpy(this->dataUltimuluiLogin, "27/01/2020");
		this->nrAutentificariEsuate = 0;
		this->esteBlocat = false;
	//	cout << "Constructor default called" << endl;
	}

	DBUser(const char* userName, string parola, userType t, const char dataUltimuluiLog[10]) {
		if (userName == NULL || strlen(userName) < 3)
			throw new exception("Username-ul trebuie sa aiba minim 3 caractere.");
		else if (parola.length() < 4)
			throw new exception("Parola trebuie sa aiba minim 4 caractere.");
		else if (t != Normal && t != DBAdmin && t != SuperUser)
			throw new exception("Tipul poate fi doar Normal, DBAdmin sau SuperUser");
		else if (strlen(dataUltimuluiLog) < 8)
			throw new exception("Data ultimului login trebuie sa respecte formatul.");
		else {
			this->userName = new char[strlen(userName) + 1];
			strcpy(this->userName, userName);
			this->parola = parola;
			this->tip = t;
			strcpy(this->dataUltimuluiLogin, dataUltimuluiLog);
			this->nrAutentificariEsuate = 0;
			this->esteBlocat = false;
		//	cout << "Constructor cu param apelat" << endl;
		}	
	}

	DBUser(DBUser& dbu) {
		this->userName = new char[strlen(dbu.userName) + 1];
		strcpy(this->userName, dbu.userName);
		this->parola = dbu.parola;
		this->tip = dbu.tip;
		strcpy(this->dataUltimuluiLogin, "27/01/2020");
		this->nrAutentificariEsuate = dbu.nrAutentificariEsuate;
		this->esteBlocat = dbu.esteBlocat;
	//	cout << "Constructor copiere" << endl;
	}

	DBUser& operator=(DBUser& dbu) {
		if (this != &dbu) {
			if (this->userName != NULL)
				delete[]this->userName;
			this->userName = new char[strlen(dbu.userName) + 1];
			strcpy(this->userName, dbu.userName);
			this->parola = dbu.parola;
			this->tip = dbu.tip;
			strcpy(this->dataUltimuluiLogin, "27/01/2020");
			this->nrAutentificariEsuate = dbu.nrAutentificariEsuate;
			this->esteBlocat = dbu.esteBlocat;
		//	cout << "Operator =" << endl;
			return *this;
		}
		else throw new exception("Autoasignarea nu este permisa");
	}

	friend ostream& operator<<(ostream& out, DBUser& dbu)
	{
		if (dbu.userName == NULL)
			out << "N/A" << endl;
		else
		out << "User: " << dbu.userName << endl;
		out << "Parola: " << dbu.parola << endl;
		out << "Tip: " << dbu.tip << endl;
		out << "Data ultimului login: " << dbu.dataUltimuluiLogin << endl;
		out << "Autentificari esuate: " << dbu.nrAutentificariEsuate << endl;
		out << "Status blocat: " << dbu.esteBlocat << endl;
		return out;

	}

	~DBUser() {
		if (this->userName != NULL)
			delete[]this->userName;
		
	}

	int getNrAuthEsuate() {
		return this->nrAutentificariEsuate;
	}

	bool getEsteBlocat() {
		return this->esteBlocat;
	}

	void login(string parola) {
		if (this->nrAutentificariEsuate >= NR_MAXIM_LOGINURI) {
		this->esteBlocat = true;
		cout << "Contul a fost blocat" << endl;
		}
		else {
			if (this->parola.compare(parola) == 0) {
				strcpy(this->dataUltimuluiLogin, "27/01/2020");
				cout << "Autentificare cu succes" << endl;
			}
			else {
				this->nrAutentificariEsuate += 1;
				cout << "Parola este gresita, mai aveti " << NR_MAXIM_LOGINURI - this->nrAutentificariEsuate << " incercari. " << endl;
			}
		}
	
	}

	void operator!() {
		if (this->esteBlocat == true) {
			this->esteBlocat = false;
			this->nrAutentificariEsuate = 0;
			cout << "Cont deblocat si resetat. " << endl;
		}
		else
			cout << "Contul este deja deblocat." << endl;
	}

	bool operator[](string parola) {
		if (this->parola.compare(parola) == 0)
			return true;
		else
			throw new exception("Parola verificata nu este introdusa corect.");
	}

	friend ifstream& operator<<(ifstream& fin, DBUser& u) {
		fin.open("grup.txt", ios::in);
		if (u.userName != NULL)
			delete[]u.userName;
		int len = 0;
		fin >> len;
		u.userName = new char[len + 1];
		fin >> u.userName;
		fin >> u.parola;
		int tip = 0;
		fin >> tip;
		u.tip = (userType)tip;
		fin >> u.dataUltimuluiLogin;
		fin >> u.esteBlocat;
		fin.close();
		return fin;
	}

	char* getUserName() {
		return this->userName;
	}

	char* getData() {
		return this->dataUltimuluiLogin;
	}

	string getPass() {
		return this->parola;
	}

	void setData(char* data) {
		strcpy(this->dataUltimuluiLogin, data);
	}

	void setPass(string parola) {
		this->parola = parola;
	}

	void setLoginuri(int nrLoginuri) {
		this->nrAutentificariEsuate = nrLoginuri;
	}

	void setAccesibil(bool accesibil) {
		this->esteBlocat = accesibil;
	}

	void setUserName(char* userName) {
		if (this->userName != NULL)
			delete[]this->userName;
		this->userName = new char[strlen(userName) + 1];
		strcpy(this->userName, userName);
	}

	void setTip(userType t) {
		this->tip = t;
	}

		
};
int DBUser::NR_MAXIM_LOGINURI = 5;

class DBUserGroup {
private:
	string numeGrup;
	int nrUtilizatori;
	DBUser* users;
public:
	DBUserGroup(string numeGrup, int nrUtilizatori, DBUser* users) {
		this->numeGrup = numeGrup;
		this->nrUtilizatori = nrUtilizatori;
		this->users = new DBUser[this->nrUtilizatori];
		for (int i = 0; i < this->nrUtilizatori; i++)
			this->users[i] = users[i];
		cout << "Group constructor called" << endl;
	}

	DBUserGroup(DBUserGroup& dbg) {
		this->numeGrup = dbg.numeGrup;
		this->nrUtilizatori = dbg.nrUtilizatori;
		this->users = new DBUser[this->nrUtilizatori];
		for (int i = 0; i < this->nrUtilizatori; i++)
			this->users[i] = dbg.users[i];
		cout << "Copy constructor group called" << endl;
	}

	DBUserGroup& operator=(DBUserGroup& dbg) {
		if (this != &dbg) {
			this->numeGrup = dbg.numeGrup;
			this->nrUtilizatori = dbg.nrUtilizatori;
			if (this->users != NULL)
				delete[]this->users;
			this->users = new DBUser[this->nrUtilizatori];
			for (int i = 0; i < this->nrUtilizatori; i++)
				this->users[i] = dbg.users[i];
			return *this;
		}
		else throw new exception("Autoasignarea nu este permisa");

	}

	~DBUserGroup() {
		if (this->users != NULL)
			delete[]this->users;
	}

	void operator+=(DBUser& u) {
		DBUser* aux = new DBUser[this->nrUtilizatori + 1];
		for (int i = 0; i < this->nrUtilizatori; i++)
			aux[i] = this->users[i];
		aux[this->nrUtilizatori] = u;
		this->nrUtilizatori += 1;
		delete[]this->users;
		this->users = new DBUser[this->nrUtilizatori];
		for (int i = 0; i < this->nrUtilizatori; i++)
			this->users[i] = aux[i];
	}

	friend ostream& operator<<(ostream& out, DBUserGroup& u) {
		out << "Nume grup: " << u.numeGrup << endl;
		out << "Nr utilizatori: " << u.nrUtilizatori << endl;
		out << "Utilizatori: " << endl;
		for (int i = 0; i < u.nrUtilizatori; i++) {
			out << u.users[i] << endl;
		}
		return out;
	}
	
	int totalErori() {
		int total = 0;
		for (int i = 0; i < this->nrUtilizatori; i++) {
			if (this->users[i].getEsteBlocat() == false) {
				total += this->users[i].getNrAuthEsuate();
			}
		}
		return total;
	}

	void Raport() {
		ofstream file("raport.txt", ios::out);
		file << this->numeGrup << endl;
		for (int i = 0; i < this->nrUtilizatori; i++) {
			file << "Utilizatorul " << this->users[i].getUserName() << " cu parola " << this->users[i].getPass() << " s-a autentificat la data de " << this->users[i].getData() << " si";
			if (this->users[i].getEsteBlocat() == true)
				file << " este blocat" << endl;
			else
				file << " nu este blocat " << endl;
		}
		cout << "Raport generat!" << endl;
		file.close();
	}

	void incarcaGrup() {
		ifstream file("grup.txt", ios::in);
		file >> this->numeGrup;
		file >> this->nrUtilizatori;
		if (this->users != NULL)
			delete[]this->users;
		this->users = new DBUser[this->nrUtilizatori];
		char userbuff[20];
		string pass;
		char data[50];
		int nrLog;
		int blocat;
		int tip;
		for (int i = 0; i < this->nrUtilizatori; i++) {
			file >> userbuff;
			this->users[i].setUserName(userbuff);
			file >> pass;
			this->users[i].setPass(pass);
			file >> tip;
			this->users[i].setTip((userType)tip);
			file >> data;
			this->users[i].setData(data);
			file >> nrLog;
			this->users[i].setLoginuri(nrLog);
			file >> blocat;
			this->users[i].setAccesibil(blocat);
		}
		file.close();
		cout << "Grup incarcat." << endl;
	}

};

int main() {
	try {
		DBUser u1;
		DBUser u2("Mada95", "parola123", Normal, "10/03/2020");
		cout << u2 << endl;
		DBUser u3 = u2;
		u1 = u3;

		cout << "----------------------" << endl;
		cout << u1 << endl;
		cout << "----------------------" << endl;
		cout << u2 << endl;
		u2.login("caca");
		u2.login("da3d");
		u2.login("dwada");
		u2.login("2312");
		u2.login("parola");
		u2.login("dwadwa");
		u2.login("dwadaw");
		//u2.login("1311");
		cout << u2 << endl;
		//!u2;
		cout << u2["parola123"] << endl;


		DBUser ug("Robert23", "richard23", SuperUser, "10/02/2019");
		DBUser ug2("Cosmin84", "dan29", Normal, "10/10/2019");
		ug.login("dwafaw");
		ug.login("dwada");
		ug2.login("d2r1e2");
		DBUserGroup dbg("Utilizatori", 3, new DBUser[3]{ u2,ug,ug2 });
		DBUserGroup dbg2("Utils", 2, new DBUser[2]{ u1,u2 });
		dbg2 = dbg;
		cout << dbg << endl;
		DBUserGroup dbg3 = dbg2;
		dbg += u1;
		cout << dbg << endl;
		cout << ug << endl;
		cout << ug2 << endl;
		cout << "Numarul total de autentificari esuate: " << dbg.totalErori() << endl;

		dbg.Raport();
		cout << "-------------------------------" << endl;
		dbg.incarcaGrup();
		cout << dbg << endl;

	}
	catch (exception* e) {
		cout << e->what() << endl;
	}
	
	

	return 0;
}