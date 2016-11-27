#include<iostream>
#include<fstream>
using namespace std;

class Student
{
public:
	char* nume;
	unsigned int varsta;
	int numar_luni;
	float* buget;

	Student()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 20;
		this->numar_luni = 0;
		this->buget = NULL;
	}

	Student(char* v_nume, unsigned int v_varsta, int v_numar_luni, float* v_buget)
	{
		this->nume = new char[strlen(v_nume) + 1];
		strcpy(this->nume, v_nume);
		this->varsta = v_varsta;
		this->numar_luni = v_numar_luni;
		this->buget = new float[v_numar_luni];
		for (int i = 0; i < v_numar_luni; i++)
		{
			this->buget[i] = v_buget[i];
		}
	}

	Student(const Student& sursa)
	{
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->varsta = sursa.varsta;
		this->numar_luni = sursa.numar_luni;
		this->buget = new float[sursa.numar_luni];
		for (int i = 0; i < sursa.numar_luni; i++)
		{
			this->buget[i] = sursa.buget[i];
		}
	}

	Student& operator=(const Student& sursa)
	{
		if (this->nume != NULL)
		{
			delete[] this->nume;
		}
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->varsta = sursa.varsta;
		this->numar_luni = sursa.numar_luni;

		if (this->buget != NULL)
		{
			delete[] this->buget;
		}
		this->buget = new float[sursa.numar_luni];
		for (int i = 0; i < sursa.numar_luni; i++)
		{
			this->buget[i] = sursa.buget[i];
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, Student student)
	{
		os << "Nume: " << student.nume << endl;
		os << "Varsta: " << student.varsta << endl;
		os << "Numar luni: " << student.numar_luni << endl;
		for (int i = 0; i < student.numar_luni; i++)
		{
			os << "Bugetul in luna " << i + 1 << " este: " << student.buget[i] << endl;
		}
		return os;
	}
	~Student()
	{
		if (this->nume!=NULL)
		{
			delete[] this->nume;
		}
		if (this->buget != NULL)
		{
			delete[] this->buget;
		}
	}

};

Student* incarcaStudentiDinTxt(char* nume_fisier, int& numar_studenti)
{
	Student* lista = NULL;
	ifstream fisier;
	fisier.open(nume_fisier, ifstream::in);
	if (fisier.is_open())
	{
		fisier >> numar_studenti;
		lista = new Student[numar_studenti];
		int numar_studenti_cititi = 0;
		while (!fisier.eof() && numar_studenti_cititi < numar_studenti)
		{
			char buffer[50];
			fisier.ignore();
			fisier.getline(buffer, 50);
			unsigned int varsta;
			fisier >> varsta;
			int numar_luni;
			fisier >> numar_luni;
			float* buget = new float[numar_luni];
			for (int i = 0; i < numar_luni; i++)
			{
				fisier >> buget[i];
			}
			lista[numar_studenti_cititi] = Student(buffer, varsta, numar_luni, buget);
			numar_studenti_cititi++;
		}
		fisier.close();
	}
	else
	{
		cout << "Nu s-a putut deschide fisierul!" << endl;
	}

	return lista;
}

void genereazaFisier(char* nume_fisier, Student* lista, int numar_studenti)
{
	ofstream fisier;
	fisier.open(nume_fisier, ofstream::out);
	if (fisier.is_open()){
		for (int i = 0; i < numar_studenti; i++)
		{
			fisier << lista[i].nume << ", ";
			float suma = 0;
			for (int j = 0; j < lista[i].numar_luni; j++)
			{
				suma += lista[i].buget[j];
			}
			fisier << "Bugetul: " << suma << endl;
		}
		fisier.close();
	}
	else
	{
		cout << "Nu s-a putut genera raportul!" << endl;
	}
}

//metoda pentru a scrie studenti intr-un fisier binar
void salveazaStudentiInBinar(char* nume_fisier, Student* studenti, int numar_studenti)
{
	ofstream fisier;
	fisier.open(nume_fisier, ofstream::out | ofstream::binary);
	if (fisier.is_open())
	{
		//scriu numarul de studenti
		fisier.write((char*)&numar_studenti, sizeof(int)); //adresa care se scrie si numarul de bytes ocupati
		for (int i = 0; i < numar_studenti; i++)
		{
			//scriu numarul de caractere din nume
			int lungime = strlen(studenti[i].nume) + 1;
			fisier.write((char*)&lungime, sizeof(int));
			//scriu numele
			fisier.write(studenti[i].nume, lungime*sizeof(char));
			//scriu varsta
			fisier.write((char*)&studenti[i].varsta, sizeof(unsigned int));

			//scriu bugetul
			fisier.write((char*)&studenti[i].numar_luni, sizeof(int));
			for (int j = 0; j < studenti[i].numar_luni; j++)
			{
				fisier.write((char*)&studenti[i].buget[j], sizeof(float));
			}
		}
		fisier.close();
	}
	else
	{
		cout << "Eroare la scrierea fisierului binar." << endl;
	}
}

//metoda pentru a citi studenti dintr-un fisier binar
Student* incarcaStudentiDinBinar(char* nume_fisier, int& numar_studenti)
{
	Student* studenti;
	ifstream fisier;
	fisier.open(nume_fisier, ifstream::in | ifstream::binary);
	if (fisier.is_open())
	{
		fisier.read((char*)&numar_studenti, sizeof(int));
		studenti = new Student[numar_studenti];
		for (int i = 0; i < numar_studenti; i++)
		{
			int lungime;
			char buffer[50];
			fisier.read((char*)&lungime, sizeof(int));
			fisier.read(buffer, sizeof(char)*lungime);
			int varsta;
			fisier.read((char*)&varsta, sizeof(unsigned int));
			int numar_luni;
			fisier.read((char*)&numar_luni, sizeof(int));
			float* buget = new float[numar_luni];
			for (int j = 0; j < numar_luni; j++)
			{
				fisier.read((char*)&buget[j], sizeof(float));
			}
			studenti[i] = Student(buffer, varsta, numar_luni, buget);
		}
		fisier.close();
		return studenti;
	}
	else
	{
		return NULL;
	}
}

void main()
{
	Student s1;
	cout << s1;
	float buget[] = { 158.6, 589.3 };
	Student s2("Popescu Ion", 25, 2, buget);
	cout << s2;

	Student* studenti = NULL;
	int numar_studenti;

	studenti = incarcaStudentiDinTxt("Studenti.txt", numar_studenti);
	if (studenti != NULL)
	{
		for (int i = 0; i < numar_studenti; i++)
		{
			cout << studenti[i] << endl;
		}
	}

	genereazaFisier("Raport.txt", studenti, numar_studenti);

	salveazaStudentiInBinar("Studenti.dat", studenti, numar_studenti);

	Student* studenti2 = NULL;
	int numar_studenti2 = 0;
	studenti2 = incarcaStudentiDinBinar("Studenti.dat", numar_studenti2);
	if (studenti2 != NULL)
	{
		cout << "Au fost incarcati din fisierul binar urmatorii studenti: " << endl;
		for (int i = 0; i < numar_studenti2; i++)
		{
			cout << studenti2[i] << endl;
		}
	}
}