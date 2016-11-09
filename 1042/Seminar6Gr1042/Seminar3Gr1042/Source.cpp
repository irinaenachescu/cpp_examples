#include<iostream>
using namespace std;
class Carte
{
private:
	const int id_carte;
	char* autor;
	char* titlu;
	char gen[50];
	unsigned int numar_pagini;
	double pret;
	static unsigned int numar_carti;
public:
	Carte() :id_carte(Carte::numar_carti++)
	{
		this->autor = new char[strlen("Anonim") + 1];
		strcpy(this->autor, "Anonim");
		this->titlu = new char[strlen("Lipsa") + 1];
		strcpy(this->titlu, "Lipsa");
		strcpy(this->gen, "Lipsa");
		this->numar_pagini = 0;
		this->pret = 0;
	}

	Carte(char* autor, char* titlu, char* gen, unsigned int numar_pagini, double pret) :id_carte(Carte::numar_carti++)
	{
		this->autor = new char[strlen(autor) + 1];
		strcpy(this->autor, autor);

		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);

		strcpy(this->gen, gen);
		this->numar_pagini = numar_pagini;
		this->pret = pret;
	}


	Carte(char* titlu, char* autor, char* gen, unsigned int nr_pagini = 50) :numar_pagini(nr_pagini), id_carte(Carte::numar_carti++)
	{
		this->autor = new char[strlen(autor) + 1];
		strcpy(this->autor, autor);

		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);

		strcpy(this->gen, gen);
		this->pret = 100.0;

	}
	void afisare()
	{
		cout << "Id: " << this->id_carte << endl;
		cout << "Titlu: " << this->titlu << endl;
		cout << "Autor: " << this->autor << endl;
		cout << "Gen: " << this->gen << endl;
		cout << "Numar pagini: " << this->numar_pagini << endl;
		cout << "Pret: " << this->pret << endl;
	}

	~Carte()
	{
		cout << "In destructor" << endl;
		delete[] this->autor;
		delete[] this->titlu;
	}

	void setAutor(char* autor2)
	{
		if (this->autor != NULL)
		{
			delete[] this->autor;
		}
		this->autor = new char[strlen(autor2) + 1];
		strcpy(this->autor, autor2);
	}

	char* getAutor()
	{
		return this->autor;
	}

	void setTitlu(char* titlu)
	{
		if (this->titlu != NULL)
		{
			delete[] this->titlu;
		}
		if (strlen(titlu) >= 3)
		{
			this->titlu = new char[strlen(titlu) + 1];
			strcpy(this->titlu, titlu);
		}
		else
		{
			throw new exception("Titlu prea scurt!");
		}
	}

	char* getTitlu()
	{
		return this->titlu;
	}

	void setGen(char* gen)
	{
		strcpy(this->gen, gen);
	}

	char* getGen()
	{
		return this->gen;
	}

	unsigned int getNrPagini()
	{
		return this->numar_pagini;
	}

	void setNrPagini(unsigned int numar_pagini)
	{
		this->numar_pagini = numar_pagini;
	}

	double getPret()
	{
		return this->pret;
	}

	void setPret(double pret);

	Carte(const Carte& carte) :id_carte(carte.id_carte)
	{
		this->autor = new char[strlen(carte.autor) + 1];
		strcpy(this->autor, carte.autor);

		this->titlu = new char[strlen(carte.titlu) + 1];
		strcpy(this->titlu, carte.titlu);

		strcpy(this->gen, carte.gen);
		this->numar_pagini = carte.numar_pagini;
		this->pret = carte.pret;
	}

	//supraincarcarea operatorului = 
	Carte& operator=(const Carte& carte)
	{
		if (this->autor != NULL)
		{
			delete[] this->autor;
		}
		this->autor = new char[strlen(carte.autor) + 1];
		strcpy(this->autor, carte.autor);

		if (this->titlu != NULL)
		{
			delete[] this->titlu;
		}
		this->titlu = new char[strlen(carte.titlu) + 1];
		strcpy(this->titlu, carte.titlu);

		strcpy(this->gen, carte.gen);
		this->numar_pagini = carte.numar_pagini;
		this->pret = carte.pret;

		return *this;
	}

	//supraincarcare operator<<
	friend ostream& operator<<(ostream& o, Carte carte);

	//supraincarcare operator>>
	friend istream& operator>>(istream& i, Carte& carte);

	//supraincarcare operator+ care aduna un float la pretul cartii
	Carte operator+(float p)
	{
		Carte copie = *this;
		copie.pret += p;
		return copie;
	}

	//supraincarcarea operatorului -- (predecrementare) care scade numarul de pag
	Carte& operator--(){
		this->numar_pagini--;
		return *this;
	}

	//supraincarcarea operatorului -- (postdecrementare)
	Carte operator--(int)
	{
		Carte copie = *this;
		this->numar_pagini--;
		return copie;
	}
};

unsigned int Carte::numar_carti = 0;

ostream& operator<<(ostream& o, Carte carte)
{
	o << "Id-ul: " << carte.id_carte << endl;
	o << "Titlul: " << carte.titlu << endl;
	o << "Autor: " << carte.autor << endl;
	o << "Gen: " << carte.gen << endl;
	o << "Pret: " << carte.pret << endl;
	o << "Numar pagini: " << carte.numar_pagini << endl;

	return o;
}

istream& operator>>(istream& i, Carte& carte)
{
	char buffer[50];
	cout << "Dati titlul: ";
	i.getline(buffer, 50);
	if (carte.titlu != NULL) {
		delete[] carte.titlu; //evit memory leak
	}
	carte.titlu = new char[strlen(buffer) + 1];
	strcpy(carte.titlu, buffer);
	cout << "Dati autor: ";
	i.getline(buffer, 50);
	if (carte.autor != NULL)
	{
		delete[] carte.autor;
	}
	carte.autor = new char[strlen(buffer) + 1];
	strcpy(carte.autor, buffer);
	cout << "Dati genul: ";
	i.getline(carte.gen, 50);
	cout << "Dati pretul: ";
	i >> carte.pret;
	cout << "Dati numarul de pagini: ";
	i >> carte.numar_pagini;

	return i;
}

void Carte::setPret(double pret)
{
	this->pret = pret;
}

void main()
{
	Carte carte1;
	carte1.afisare();

	Carte* p_carte1 = new Carte();
	p_carte1->afisare();
	delete p_carte1;

	Carte carte2("Liviu Rebreanu", "Ion", "roman interbelic", 100, 150.5);
	carte2.afisare();

	cout << "Carte2 dupa operatorul +:" << endl;
	carte2 = carte2 + 49.5;
	cout << carte2;

	Carte carte8;
	carte8 = --carte2;
	cout << "Predecrementare: " << endl;
	cout << carte2;
	cout << carte8;

	cout << "Postdecrementare: " << endl;
	carte8 = carte2--;
	cout << carte2;
	cout << carte8;


	carte2.setAutor("Liviu R");
	carte2.setTitlu("Ionel");
	carte2.setGen("roman");
	carte2.setNrPagini(50);
	carte2.setPret(55.6);
	cout << carte2.getAutor() << endl;
	cout << carte2.getTitlu() << endl;
	cout << carte2.getGen() << endl;
	cout << carte2.getNrPagini() << endl;
	cout << carte2.getPret() << endl;

	//apelul constr de copiere
	Carte carte5 = carte2;
	carte5.afisare();

	Carte* p_carte2= new Carte("Camil Petrescu", "Ultima noapte...", "roman interbelic", 200, 250.5);
	p_carte2->afisare();
	delete p_carte2;

	Carte carte3("Morometii 2", "Marin Preda", "roman postbelic");
	carte3.afisare();

	Carte carte4("Morometii 2","Marin Preda", "roman postbelic", 500);
	carte4.afisare();
	carte4.setAutor("Ion Ion");
	carte4.afisare();

	cout << "Apelul operatorului=" << endl;
	Carte carte6;
	carte6 = carte4;
	//carte6.afisare();
	cout << carte6;

	/*Carte carte7;
	cin >> carte7;
	cout << carte7;*/
}