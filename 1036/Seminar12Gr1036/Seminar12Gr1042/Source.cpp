#include<iostream>
using namespace std;

class Produs
{
protected:
	unsigned int cod;
	double pret;

public:
	Produs()
	{
		this->cod = 0;
		this->pret = 0;
	}

	Produs(unsigned int v_cod, double v_pret)
	{
		this->cod = v_cod;
		this->pret = v_pret;
	}

	 void afisare()
	{
		cout << "Produsul cu codul " << this->cod << " are pretul: " << this->pret << "." << endl;
	}

	virtual void getInfo() = 0;
};

class IDeVanzare{
public:
	virtual double getPret() = 0;
	virtual void aplicaDiscount(int discount) = 0;
};

class Aliment: public Produs, public IDeVanzare{
private:
	int termen_valabilitate;
public:
	Aliment(unsigned int v_cod, double v_pret, int v_termen_valabilitate)
		:Produs(v_cod, v_pret)
	{
		this->termen_valabilitate = v_termen_valabilitate;
	}

	//overriding
	void afisare()
	{
		cout << "Produsul cu codul " << this->cod << " are pretul: " << this->pret 
			<< " si expira in " <<this->termen_valabilitate<<" zile."<< endl;
	}

	//overloading
	void afisare(char* mesaj)
	{
		cout << "S-a primit mesajul: " << mesaj << endl;
		this->afisare();
	}

	void getInfo()
	{
		this->afisare();
	}

	double getPret()
	{
		return this->pret;
	}

	void aplicaDiscount(int discount)
	{
		this->pret = (1 - (float)discount / 100)*this->pret;
	}
};

class AparatElectrocasnic : public Produs, public IDeVanzare
{
private:
	int garantie;
public:
	AparatElectrocasnic(unsigned int v_cod, double v_pret, int v_garantie)
		:Produs(v_cod, v_pret){
		this->garantie = v_garantie;
	}

	//overriding
	void afisare()
	{
		cout << "Produsul cu codul " << this->cod << " are pretul: " << this->pret
			<< " si are o garantie de " << this->garantie << " zile." << endl;
	}


	void getInfo()
	{
		this->afisare();
	}

	double getPret()
	{
		return this->pret;
	}

	void aplicaDiscount(int discount)
	{
		this->pret = (1 - (float)discount / 100)*this->pret;
	}
};

void main()
{
	//nu se pot instantia obiecte ale claselor abstracte
	//Produs p;

	Aliment aliment1(10, 12.3, 6);
	aliment1.getInfo();
	aliment1.aplicaDiscount(10);
	cout << "Pretul dupa discount este: " << aliment1.getPret() << endl;

	
	Produs* lista[3];
	lista[0] = &aliment1;
	lista[1] = new AparatElectrocasnic(20, 563.2, 365);
	lista[2] = new Aliment(11, 56.3, 30);

	for (int i = 0; i < 3; i++)
	{
		lista[i]->afisare();
		lista[i]->getInfo();
		
	}

	//down-casting
	((Aliment*)lista[0])->aplicaDiscount(20);
	cout << "Pretul dupa discount este: " << ((Aliment*)lista[0])->getPret() << endl;

	IDeVanzare* listaObiecte[3];
	listaObiecte[0] = &aliment1;
	listaObiecte[1] = new Aliment(12, 12, 12);
	listaObiecte[2] = new AparatElectrocasnic(21, 5647.3, 600);

	for (int i = 0; i < 3; i++)
	{
		cout << "Pretul inainte de reducere: " << listaObiecte[i]->getPret() << endl;
		listaObiecte[i]->aplicaDiscount(20);
		cout << "Pretul dupa reducere: " << listaObiecte[i]->getPret() << endl;
	}

}