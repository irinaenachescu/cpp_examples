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
public:
	//constructor fara parametri
	Carte()
	{
		this->titlu = new char[strlen("Lipsa") + 1];
		strcpy(this->titlu, "Lipsa");
		this->autor = new char[strlen("Anonim") + 1];
		strcpy(this->autor, "Anonim");
		strcpy(this->gen, "Lipsa");
		this->numar_pagini = 0;
		this->pret = 0;
	}

	void afisare()
	{
		cout << "Titlul: " << this->titlu << endl;
		cout << "Autor: " << this->autor << endl;
		cout << "Gen: " << this->gen << endl;
		cout << "Numar_pagini: " << this->numar_pagini << endl;
		cout << "Pret: " << this->pret << endl;
	}

	~Carte(){
		cout << "In destructor!" << endl;
		delete[] this->autor;
		delete[] this->titlu;
	}

};

void main()
{
	Carte carte1;
	carte1.afisare();

	Carte* p_carte1 = new Carte();
	p_carte1->afisare();
	delete p_carte1;

}