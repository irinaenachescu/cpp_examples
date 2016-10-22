#include<iostream>
using namespace std;
class Carte
{
private:
	char* autor;
	char* titlu;
	char gen[50];
	unsigned int numar_pagini;
	double pret;

public:
	Carte()
	{
		this->autor = new char[strlen("Anonim") + 1];
		strcpy(this->autor, "Anonim");
		this->titlu = new char[strlen("Lipsa") + 1];
		strcpy(this->titlu, "Lipsa");
		strcpy(this->gen, "Lipsa");
		this->numar_pagini = 0;
		this->pret = 0;
	}

	Carte(char* autor, char* titlu, char* gen, unsigned int numar_pagini, double pret)
	{
		this->autor = new char[strlen(autor) + 1];
		strcpy(this->autor, autor);

		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);

		strcpy(this->gen, gen);
		this->numar_pagini = numar_pagini;
		this->pret = pret;
	}


	Carte(char* titlu, char* autor, char* gen, unsigned int nr_pagini = 50) :numar_pagini(nr_pagini)
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
};

void main()
{
	Carte carte1;
	carte1.afisare();

	Carte* p_carte1 = new Carte();
	p_carte1->afisare();
	delete p_carte1;

	Carte carte2("Liviu Rebreanu", "Ion", "roman interbelic", 100, 150.5);
	carte2.afisare();

	Carte* p_carte2= new Carte("Camil Petrescu", "Ultima noapte...", "roman interbelic", 200, 250.5);
	p_carte2->afisare();
	delete p_carte2;

	Carte carte3("Morometii 2", "Marin Preda", "roman postbelic");
	carte3.afisare();

	Carte carte4("Morometii 2","Marin Preda", "roman postbelic", 500);
	carte4.afisare();
	carte4.setAutor("Ion Ion");
	carte4.afisare();
}