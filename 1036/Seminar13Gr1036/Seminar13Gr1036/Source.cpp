#include<iostream>
using namespace std;

//metoda generica de tip template prin care se verifica egalitatea a doua valori
template<typename T>
bool compara(T valoare1, T valoare2)
{
	return valoare1 == valoare2;
}


//specializare template pentru T  = char*
template<typename T=char*>
bool compara(char* valoare1, char* valoare2)
{
	if (strcmp(valoare1, valoare2) == 0)
	{
		return true;
	}
	return false;
}

template<typename T>
T aduna(T valoare1, T valoare2)
{
	return valoare1 + valoare2;
}

template<typename T=char*>
char* aduna(char* valoare1, char* valoare2)
{
	char* final = new char[strlen(valoare1) + strlen(valoare2) + 1];
	strcpy(final, valoare1);
	strcat(final, valoare2);
	return final;
}

enum Combustibil
{
	BENZINA,
	DIESEL,
	GPL
};

template<typename T>
class Masina{
public:
	Combustibil combustibil;
	int numar_pasageri;
	T* pasageri;

	Masina(Combustibil v_combustibil, int v_numar_pasageri, T* v_pasageri)
	{
		this->combustibil = v_combustibil;
		this->numar_pasageri = v_numar_pasageri;
		this->pasageri = new T[this->numar_pasageri];
		for (int i = 0; i < this->numar_pasageri; i++)
		{
			this->pasageri[i] = v_pasageri[i];
		}
	}

	Masina(const Masina& sursa)
	{
		this->combustibil =sursa.combustibil;
		this->numar_pasageri = sursa.numar_pasageri;
		this->pasageri = new T[this->numar_pasageri];
		for (int i = 0; i < this->numar_pasageri; i++)
		{
			this->pasageri[i] = sursa.pasageri[i];
		}
	}

	Masina& operator=(const Masina& sursa)
	{
		if (this->pasageri != NULL)
		{
			delete[] this->pasageri;
		}
		this->combustibil = sursa.combustibil;
		this->numar_pasageri = sursa.numar_pasageri;
		this->pasageri = new T[this->numar_pasageri];
		for (int i = 0; i < this->numar_pasageri; i++)
		{
			this->pasageri[i] = sursa.pasageri[i];
		}

		return *this;
	}

	~Masina()
	{
		if (this->pasageri != NULL)
		{
			delete[] this->pasageri;
		}
	}

	friend ostream& operator<<(ostream& out, Masina masina)
	{
		out << "Combustibil: " << masina.getCombustibil() << endl;
		out << "Numar pasageri: " << masina.numar_pasageri << endl;
		for (int i = 0; i < masina.numar_pasageri; i++)
		{
			out << "Pasagerul " << i + 1 << ": " << masina.pasageri[i] << endl;
		}

		return out;
	}

	char* getCombustibil()
	{
		switch (this->combustibil)
		{
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
		return (this->combustibil == masina.combustibil && this->numar_pasageri == masina.numar_pasageri);
	}
};

class Student
{
public:
	char nume[50];

	Student()
	{
		strcpy(this->nume, "Anonim");
	}
	Student(char* v_nume)
	{
		strcpy(this->nume, v_nume);
	}

	friend ostream& operator<<(ostream& out, Student s)
	{
		out << "Studentul: " << s.nume << endl;
		return out;
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

void main()
{
	if (compara<int>(5, 7) == true)
	{
		cout << "Intregi egali." << endl;
	}
	else {
		cout << "Intregi diferiti." << endl;
	}


	if (compara<double>(5.5, 5.5) == true)
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

	cout << aduna<int>(5, 7) << endl;
	cout << aduna<char*>("Irina", "Ioana") << endl;

	Student studenti[2] = { Student("Irina"), Student("Mihai") };
	Masina<Student> masina1(Combustibil::BENZINA, 2, studenti);
	cout << masina1;

	//masina cu pisici
	Pisica* pisici[2] = { new Pisica("siameza", 3), new Pisica("persana", 5) };
	Masina<Pisica*> masina2(Combustibil::DIESEL, 2, pisici);
	cout << masina2;

	Masina<Student> masina3(Combustibil::BENZINA, 2, studenti);
	if (compara<Masina<Student>>(masina1, masina3) == true)
	{
		cout << "Masini la fel." << endl;
	}
	else {
		cout << "Masini diferite" << endl;
	}
}