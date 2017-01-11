#include<iostream>
using namespace std;

//metoda generica de tip template prin care se verifica egalitatea a doua valori
template <typename T>
bool compara(T valoare1, T valoare2)
{
	return valoare1 == valoare2;
}


//specializare template pentru T  = char*
template <typename T=char*>
bool compara(char* valoare1, char* valoare2)
{
	if (strcmp(valoare1, valoare2) == 0)
	{
		return true;
	}
	return false;
}

template <typename T>
T suma(T valoare1, T valoare2)
{
	return valoare1 + valoare2;
}

template <typename T=char*>
char* suma(char* valoare1, char* valoare2)
{
	char* buffer = new char[strlen(valoare1) + strlen(valoare2) + 1];
	strcpy(buffer, valoare1);
	strcat(buffer, valoare2);
	return buffer;
}

enum Combustibil
{
	BENZINA=0,
	DIESEL,
	GPL
};

template <typename T>
class Masina
{
private:
	Combustibil combustibil;
	int nr_pasageri;
	T* pasageri;

public:
	Masina(Combustibil v_combustibil, int v_nr_pasageri, T* v_pasageri)
	{
		this->combustibil = v_combustibil;
		this->nr_pasageri = v_nr_pasageri;
		this->pasageri = new T[this->nr_pasageri];
		for (int i = 0; i < this->nr_pasageri; i++)
		{
			this->pasageri[i] = v_pasageri[i];
		}
	}

	Masina(const Masina& sursa)
	{
		this->combustibil = sursa.combustibil;
		this->nr_pasageri = sursa.nr_pasageri;
		this->pasageri = new T[this->nr_pasageri];
		for (int i = 0; i < this->nr_pasageri; i++)
		{
			this->pasageri[i] = sursa.pasageri[i];
		}

	}

	~Masina(){
		if (this->pasageri != NULL)
		{
			delete[] this->pasageri;
		}
	}

	Masina& operator=(const Masina& sursa)
	{
		if (this->pasageri != NULL)
		{
			delete[] this->pasageri;
		}

		this->combustibil = sursa.combustibil;
		this->nr_pasageri = sursa.nr_pasageri;
		this->pasageri = new T[this->nr_pasageri];
		for (int i = 0; i < this->nr_pasageri; i++)
		{
			this->pasageri[i] = sursa.pasageri[i];
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, Masina masina)
	{
		out << "Combustibil: " << masina.getCombustibil() << endl;
		out << "Numar pasageri: " << masina.nr_pasageri << endl;
		for (int i = 0; i < masina.nr_pasageri; i++)
		{
			out << "Pasager: " << masina.pasageri[i] << endl;
		}

		return out;
	}

	char* getCombustibil(){
		switch (this->combustibil){
		case BENZINA: 
			return "benzina";
		case DIESEL:
			return "diesel";
		case GPL:
			return "gpl";
		default:
			return "necunoscut";
		}
	}

	bool operator==(Masina masina)
	{
		return (this->combustibil == masina.combustibil && this->nr_pasageri == masina.nr_pasageri);
	}
};


class Pisica
{
private:
	char rasa[15];
	int varsta;

public:
	Pisica()
	{

	}
	Pisica(char* v_rasa, int v_varsta)
	{
		strcpy(this->rasa, v_rasa);
		this->varsta = v_varsta;
	}

	friend ostream& operator<<(ostream& out, Pisica pisica)
	{
		out << "Pisica rasa " << pisica.rasa << " cu varsta de " << pisica.varsta;
		return out;
	}

	friend ostream& operator<<(ostream& out, Pisica* pisica)
	{
		out << "Pisica rasa " << pisica->rasa << " cu varsta de " << pisica->varsta;
		return out;
	}
};


class Student{
private:
	char nume[50];
public:
	Student()
	{
		strcpy(this->nume, "Anonim");
	}

	Student(char* v_nume)
	{
		strcpy(this->nume, v_nume);
	}

	friend ostream& operator<<(ostream& out, Student student)
	{
		out << "Studentul: " << student.nume << endl;

		return out;
	}
};

void main()
{
	if (compara<int>(5, 7) == true)
	{
		cout << "Intregi egali." << endl;
	}
	else {
		cout << "Intregi diferiti." << endl;
	}

	if (compara<double>(5.6, 5.6) == true)
	{
		cout << "Numere reale egale." << endl;
	}
	else {
		cout << "Numere reale diferite." << endl;
	}

	if (compara<char*>("Irina", "Irina2") == true)
	{
		cout << "Siruri identice." << endl;
	}
	else {
		cout << "Siruri diferite." << endl;
	}

	cout << suma<int>(5, 11) << endl;
	cout << suma<char*>("Ana", "Maria") << endl;

	Student studenti[2] = { Student("Irina"), Student("Popescu") };
	Masina<Student> masina(Combustibil::DIESEL, 2, studenti);
	cout << masina << endl;

	//masina cu pisici
	Pisica* pisici[2] = { new Pisica("siameza", 3), new Pisica("persana", 5) };
	Masina<Pisica*> masina2(Combustibil::DIESEL, 2, pisici);
	cout << masina2;

	Masina<Student> masina3(Combustibil::BENZINA, 2, studenti);
	if (compara<Masina<Student>>(masina, masina3) == true)
	{
		cout << "Masini la fel." << endl;
	}
	else {
		cout << "Masini diferite" << endl;
	}
}