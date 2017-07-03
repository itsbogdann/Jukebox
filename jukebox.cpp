#define _CRT_SECURE_NO_WARNINGS //ca sa nu apara unele warning-uri in visual studio
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Tonomat
{
	char* denumire;
	char* producator;
	int numar_produse;
	char** produse;

public:
	//constructor default
	Tonomat() {
		this->denumire = new char[strlen("Tonomat fara denumire") + 1];
		strcpy(this->denumire, "Tonomat fara denumire");
		this->producator = new char[strlen("Anonim") + 1];
		strcpy(this->producator, "Anonim");
		this->numar_produse = 1;
		this->produse = new char*[this->numar_produse];
		this->produse[0] = new char[strlen("Produs") + 1];
		strcpy(this->produse[0], "Produs");
	}

public:
	Tonomat(char* denumire, char* producator, int numar_produse, char **produse)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->producator = new char[strlen(producator) + 1];
		strcpy(this->producator, producator);
		this->numar_produse = numar_produse;
		this->produse = new char*[this->numar_produse];
		for (int i = 0; i < this->numar_produse; i++) {
			this->produse[i] = new char[strlen(produse[i]) + 1];
			strcpy(this->produse[i], produse[i]);
		}
	}

	~Tonomat() {
		delete[] denumire;
		delete[] producator;
		for (int i = 0; i < numar_produse; i++)
		//dezalocam fiecare linie din matrice
			delete[] produse[i];
		delete produse;
	}


	//constructor de copiere, pt ca are ca parametru un obiect tot din clasa Tonomat
	Tonomat(Tonomat &t)
	{
		this->denumire = new char[strlen(t.denumire) + 1];
		strcpy(this->denumire, t.denumire);
		this->producator = new char[strlen(t.producator) + 1];
		strcpy(this->producator, t.producator);
		this->numar_produse = t.numar_produse;
		produse = new char*[t.numar_produse];
		for (int i = 0; i < t.numar_produse; i++) {
			this->produse[i] = new char[strlen(t.produse[i]) + 1];
			strcpy(this->produse[i], t.produse[i]);
		}
	}


	void afis()
	{
		cout << "Tonomat: " << denumire << endl;
		cout << "Producator:" << producator << endl;
		cout << "Numar produse: " << numar_produse << endl;
		cout << "Produse: " << endl;
		for (int i = 0; i < numar_produse; i++)
			cout << produse[i] << endl;
	}

	void seteaza_denumire(char *denumire) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}

	char *returneaza_denumire() {
		return this->denumire;
	}


	friend ostream& operator<<(ostream& consola, Tonomat &t) {
		consola << "Denumire tonomat: " << t.denumire << endl;
		consola << "Denumire producator: " << t.producator << endl;
		return consola;
	}


};

class Produs
{

private:
	char* denumire;
	float pret;

	static int numar_produse_totale;
;
public:
	Produs()
	{
		this->denumire = new char[strlen("Produs fara denumire") + 1];
		strcpy(this->denumire, "Produs fara denumire");
		this->pret = 1;

		numar_produse_totale++;
	}


	Produs(char *denumire, float pret)
	{
		//new char[strlen(denumire) + 1] inseamna :
		//facem un vector nou de tip char, de lungime = lungimea vectorului denumire
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;


		numar_produse_totale++;
	}

	~Produs()
	{
		delete[] denumire;
		//numar_produse_totale nu cred ca are vreun rost aici, l-a pus leo din greseala
		numar_produse_totale--;
	}

	Produs(Produs& p)
	{
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;

	}

	void afis() {
		cout << "Produs: " << this->denumire << endl;
		cout << "Pret: " << this->pret << " lei" << endl;
	}

	void operator+(float valoare) {
		this->pret = this->pret + valoare;

	}
	//setter pt pret, pt ca e variabila privata
	void seteaza_pret(float pret) {
		this->pret = pret;
	}

	float returneaza_pret() {
		return this->pret;
	}


//operator pt scrierea unui obiect produs in consola
	friend ostream& operator<<(ostream& consola, Produs &p) {
		cout << "Denumire produs: " << p.denumire;
		return consola;

	}

	//operator pt citirea unui obiect de tip produs de la tastatura, cu toate atributele lui
	friend istream& operator >> (istream& consola_in, Produs &p) {
		
		char den[40];
		cout << "Denumire: ";
		delete[] p.denumire;
		consola_in >> den;
	
		p.denumire = new char[strlen(den) + 1];
		
		strcpy(p.denumire, den);
		cout<<"Pret:";
		consola_in >> p.pret;
		
		return consola_in;
	}
	
	//operator pt scrierea in fisier, adica sa stie cum sa procedeze cand vrem sa scriem un obiect intr-un fisier, cum am facut in main
	friend ofstream & operator<<(ofstream& output, Produs &prod)
	{
		output<<prod.denumire << " ";
		output<< prod.pret;
		output<< endl;
		return output;
	}
	
	//operator pt citirea din fisier a unui obiect
	friend ifstream & operator>>(ifstream &input, Produs &prod)
	{
		input>>prod.denumire>>prod.pret;
		return input;
	}


};

//variabila globala a clasei produs, pt a monitoriza cate produse avem per total
int Produs::numar_produse_totale = 0;

//clasa Bautura mosteneste clasa Produs, adica ii contine toate metodele si variabilele
class Bautura: public Produs {
	float litri;

	//aici nu cred ca mai era nevoie de ":Produs()" la final
	Bautura() :Produs() {
		litri = 0.5;
	}

	Bautura(float l, char* denumire, float pret): Produs(denumire, pret){
		litri = l;
	}

	// aici nu a fost nevoie de dezalocare a vreunui vector, deci destructorul ramane empty
	~Bautura() {

	}

	float returneazaLitri() {
		return this->litri;
	}

};


class Baton : public Produs
{
	float gramaj;
	char *aroma;

	//constructor default
	Baton() :Produs()
	{
		gramaj = 100;
		aroma = new char[strlen("Ciocolata") + 1];
		strcpy(aroma, "Ciocolata");
	}

	//constructor cu parametri, mosteneste constructorul cu parametri din clasa Produs
	Baton(float gr, char *arom, char *denumire, float pret) :Produs(denumire, pret)
	{
		gramaj = gr;
		aroma = new char[strlen(arom) + 1];
		strcpy(aroma, arom);
	}

	~Baton()
	{
		delete[]aroma;
	}

};

class Furnizor
{
	char* denumire;

public:

	Furnizor()
	{
		this->denumire = new char[strlen("Furnizor Anonim") + 1];
		strcpy(this->denumire, "Furnizor Anonim");
	}

	Furnizor(char *denumire)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}

	~Furnizor()
	{
		delete[] denumire;
	}

	Furnizor(Furnizor &f)
	{
		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy(this->denumire, f.denumire);
	}


	void afis() {
		cout << "Denumire furnizor: " << denumire << endl;
	}

};

//clasele template nu au tipuri de variabile gen int,char
//ci putem stabili noi la apelare ce tip sa aiba, de asta inlocuim cu "U"
template <class U> class Aprovizionare
{
	U *tip_transport;

public:
	template <U> Aprovizionare()
	{
		this->tip_transport = new char[strlen("Aerian") + 1];
		//strcpy(tip_transport, "Aerian"); se traduce:  tip_transport = "Aerian";
		strcpy(tip_transport, "Aerian");
	}

	template <U> Aprovizionare(U *tip_transport)
	{
		//this->tip_transport inseamna variabila tip_transport a obiectului curent
		this->tip_transport = new char[strlen(tip_transport) + 1];
		strcpy(this->tip_transport, tip_transport);
	}

//dezalocam vectorul "tip_transport" cu delete[]
	~Aprovizionare()
	{
		delete[] tip_transport;
	}



};




int main() {
	
	
	int choice = 0;

	//meniul principal
	if (choice == 0) {
	cout<<"ALEGETI:"<<'\n';
	cout<<"1.Adaugare Produs"<<endl;
	cout<<"2.Vizualizare Produse"<<endl;
	//citim ce alege utilizatorul
	cin>>choice;
	}
		// facem 15 obiecte de tip produs(putem sa facem oricate)
		// daca vrei sa faci mai mult de 15 obiecte de tip produs, pune gen 100 in loc de 15
		// ca altfel o sa iti dea eroare
		// sa golesti din cand in cand fisierul "produs.txt", sa nu aiba multe linii
		Produs prd [15];
		// k = indicele obiectului cu care lucram momentan
		int k=0;
		
		//daca utilizatorul alege varianta 1
	if (choice == 1)
	{
		cout<<"DATI PRODUSUL:";
		//citim produsul(obiectul de tip produs) - stie cum sa il citeasca singur pt ca 
		//am folosit supraincarcarea operatorului >> la clasa Produs
		cin>>prd[k];
			
		//deschidem fisierul produs.txt 
		//std::ios::app face ca de fiecare data sa putem scrie la sfarsitul fisierului
		ofstream scriere ("produs.txt", std::ios::app);
		
		//"scriere" e un fel de variabila
		// verificam daca fisierul e deschis
		if (scriere.is_open()) 
		 {
			//daca e deschis, scriem in el produsul curent(citit de la tastatura)
			scriere << prd[k];
		 }
		
		cout<<"Produsul a fost adaugat."<<"\n";
		//incrementam contorul
		k++;
		//inchidem fisierul "produs.txt"
		scriere.close();
		
	}
	
	if (choice == 2)
	{
		string produs_actual;
		//deschidem fisierul "produs.txt" pentru citire(input file stream = ifstream)
		ifstream citire ("produs.txt");
		//cititim produsul cu indicele k din fisier
		citire >> prd[k];
		
		cout<<"Lista de produse:"<<endl;
		
		if (citire.is_open())
		{
			//cat timp nu am ajuns la sfarsitul fisierului
			//bagam in string-ul "produs_actual" linia curenta din fisier
			while (getline(citire, produs_actual))
			{
				//scriem linia(produsul) in consola
				cout<<"Produs: "<<produs_actual<<"\n";
				
			}
		}
		//inchidem fisierul
		citire.close();

	}

	
	
	return 0;
}




