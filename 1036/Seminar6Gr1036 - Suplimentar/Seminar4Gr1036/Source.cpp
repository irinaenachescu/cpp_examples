#include<iostream>
using namespace std;

class Carte
{
private:
	char* titlu;
	char* autor;
	char gen[50];
	unsigned int numar_pagini;
	double pret;

	const int id_carte;
	static unsigned int numar_carti;

public:
	Carte() :id_carte(Carte::numar_carti++)
	{
		this->titlu = new char[strlen("Lipsa") + 1];
		strcpy(this->titlu, "Lipsa");
		this->autor = new char[strlen("Lipsa") + 1];
		strcpy(this->autor, "Lipsa");
		strcpy(this->gen, "Lipsa");
		this->numar_pagini = 0;
		this->pret = 0;
	}

	Carte(char* titlu, char* autor, char gen[50], unsigned int numar_pagini, double pret) :id_carte(Carte::numar_carti++)
	{
		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);

		this->autor = new char[strlen(autor) + 1];
		strcpy(this->autor, autor);

		strcpy(this->gen, gen);
		this->numar_pagini = numar_pagini;
		this->pret = pret;
	}

	Carte(char* titlu, char* autor, char* gen, unsigned int nr_pagini = 10) :numar_pagini(nr_pagini), id_carte(Carte::numar_carti++)
	{
		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);

		this->autor = new char[strlen(autor) + 1];
		strcpy(this->autor, autor);

		strcpy(this->gen, gen);

		this->pret = 0;
	}

	//constructor de copiere
	Carte(const Carte& carte) :id_carte(carte.id_carte)
	{
		this->titlu = new char[strlen(carte.titlu) + 1];
		strcpy(this->titlu, carte.titlu);

		this->autor = new char[strlen(carte.autor) + 1];
		strcpy(this->autor, carte.autor);

		strcpy(this->gen, carte.gen);
		this->numar_pagini = carte.numar_pagini;
		this->pret = carte.pret;
	}

	//supraincarcarea operatorului=
	Carte& operator=(const Carte& carte)
	{
		if (this->titlu != NULL){
			delete[] this->titlu;
		}
		this->titlu = new char[strlen(carte.titlu) + 1];
		strcpy(this->titlu, carte.titlu);
		if (this->autor != NULL){
			delete[] this->autor; //evit memory leaks
		}
		this->autor = new char[strlen(carte.autor) + 1];
		strcpy(this->autor, carte.autor);

		strcpy(this->gen, carte.gen);
		this->numar_pagini = carte.numar_pagini;
		this->pret = carte.pret;

		return *this;
	}

	~Carte()
	{
		delete[] this->titlu;
		delete[] this->autor;
	}

	void afisare();

	char* getAutor()
	{
		return this->autor;
	}

	void setAutor(char* autor)
	{
		if (this->autor != NULL)
		{
			delete[] this->autor;
		}
		this->autor = new char[strlen(autor) + 1];
		strcpy(this->autor, autor);
	}

	unsigned int getNrPagini()
	{
		return this->numar_pagini;
	}

	void setNrPagini(unsigned int numar_pagini)
	{
		this->numar_pagini = numar_pagini;
	}

	char* getGen()
	{
		return this->gen;
	}

	void setGen(char gen[50])
	{
		strcpy(this->gen, gen);
	}

	int getIdCarte()
	{
		return this->id_carte;
	}

	static unsigned int getNumarCarti()
	{
		return Carte::numar_carti;
	}

	char* getTitlu()
	{
		return this->titlu;
	}

	double getPret()
	{
		return this->pret;
	}

	friend istream& operator>>(istream& i, Carte& carte)
	{
		cout << "Dati titlul: ";
		char buffer[50];
		i.getline(buffer, 50);
		if (carte.titlu != NULL)
		{
			delete[] carte.titlu;
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

		cout << "Dati gen: ";
		i >> carte.gen;

		cout << "Dati pret: ";
		i >> carte.pret;

		cout << "Dati numar pagini: ";
		i >> carte.numar_pagini;

		return i;
	}

	Carte operator+(float pret)
	{
		Carte copie = *this;
		copie.pret = copie.pret + pret;
		return copie;
	}

	//operatorul de pre-decrementare
	//scade nr de pag cu 1
	Carte& operator--()
	{
		this->numar_pagini--;
		return *this;
	}

	//operatorul de post-decrementare
	Carte operator--(int)
	{
		Carte copie = *this;
		this->numar_pagini--;
		return copie;
	}
	
};

ostream& operator<<(ostream& o, Carte carte)
{
	o << "Id: " << carte.getIdCarte() << endl;
	o << "Titlul: " << carte.getTitlu() << endl;
	o << "Autor: " << carte.getAutor() << endl;
	o << "Genul: " << carte.getGen() << endl;
	o << "Numar pagini: " << carte.getNrPagini() << endl;
	o << "Pret: " << carte.getPret() << endl;

	return o;
}

unsigned int Carte::numar_carti = 1;

void Carte::afisare()
{
	cout << "Id: " << this->id_carte << endl;
	cout << "Titlu: " << this->titlu << endl;
	cout << "Autor: " << this->autor << endl;
	cout << "Gen: " << this->gen << endl;
	cout << "Numar pagini: " << this->numar_pagini << endl;
	cout << "Pret: " << this->pret << endl;
}


void main()
{
	Carte carte1;
	//cout << carte1.titlu;
	carte1.afisare();

	Carte carte2("Ion", "Liviu Rebreanu", "roman", 400, 10.5);
	carte2.afisare();

	Carte carte3("Morometii", "Marin Preda", "roman");
	carte3.afisare();
	Carte carte4 = carte3; //constructor de copiere
	carte4.afisare();

	carte3.setAutor("Autor Nou");
	carte3.setNrPagini(50);
	carte3.setGen("poezie");

	cout << carte3.getAutor() << endl;
	cout << carte3.getNrPagini() << endl;
	cout << carte3.getGen() << endl;

	Carte carte5;
	carte5 = carte2; //op =
	carte5.afisare();

	cout << "=================" << endl;
	cout << carte5;

	//testarea operatorului+
	Carte carte6;
	carte6 = carte5 + 15.5;
	cout << carte5;
	cout << carte6;

	Carte carte7;
	//testare -- (pre-decrementare)
	carte7 = --carte6;
	cout << carte6;
	cout << carte7;

	//testare -- (post-decrementare)
	carte7 = carte6--;
	cout << carte6;
	cout << carte7;

	//testare operatorul >>
	/*Carte carte6;
	cin >> carte6;
	cout << carte6;*/

}