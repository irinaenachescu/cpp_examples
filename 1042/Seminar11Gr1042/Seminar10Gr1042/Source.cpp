#include<iostream>
#include<fstream>
using namespace std;

class Student {
public:
	char* nume;
protected:
	bool integralist;
public:
	Student()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->integralist = true;
	}

	Student(char* v_nume, bool v_integralist)
	{
		this->nume = new char[strlen(v_nume) + 1];
		strcpy(this->nume, v_nume);
		this->integralist = v_integralist;
	}

	Student(const Student& sursa)
	{
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;
	}

	Student& operator=(const Student& sursa)
	{
		delete[] this->nume;
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;

		return *this;
	}

	friend ostream& operator<<(ostream& out, Student s)
	{
		out << "Nume: " << s.nume << endl;
		out << "Integralist: " << ((s.integralist == true) ? "Da" : "Nu") << endl;

		return out;
	}

	~Student(){
		delete[] this->nume;
	}

	virtual void afisare()
	{
		cout << *this;
	}
};
//class StudentBursier : private Student 
class StudentBursier : public Student {
private:
	double bursa;
	int nr_materii_preferate;
	char** materii;
public:
	StudentBursier() :Student()
	{
		this->bursa = 0;
		this->nr_materii_preferate = 0;
		this->materii = NULL;
	}

	StudentBursier(char* v_nume, bool v_integralist, double v_bursa, int v_numar, char** v_materii)
		:Student(v_nume,v_integralist)
	{
		this->bursa = v_bursa;
		this->nr_materii_preferate = v_numar;
		this->materii = new char*[v_numar];
		for (int i = 0; i < v_numar; i++)
		{
			this->materii[i] = new char[strlen(v_materii[i]) + 1];
			strcpy(this->materii[i], v_materii[i]);
		}
	}

	friend ostream& operator<<(ostream& out, StudentBursier s)
	{
		out << (Student)s;
		out << "Bursa: " << s.bursa << endl;
		out << "Materiile preferate sunt: " << endl;
		for (int i = 0; i < s.nr_materii_preferate; i++)
		{
			out << "\t Materia " << i + 1 << ": " << s.materii[i] << endl;
		}

		return out;

	}

	~StudentBursier()
	{
		if (this->materii != NULL)
		{
			for (int i = 0; i < this->nr_materii_preferate; i++)
			{
				if (this->materii[i] != NULL)
				{
					delete[] this->materii[i];
				}
			}
			delete[] this->materii;
		}
	}

	//Constructor de copiere
	StudentBursier(const StudentBursier& sursa)
		:Student(sursa.nume,sursa.integralist)
	{
		this->bursa = sursa.bursa;
		this->nr_materii_preferate = sursa.nr_materii_preferate;
		this->materii = new char*[sursa.nr_materii_preferate];
		for (int i = 0; i < sursa.nr_materii_preferate; i++)
		{
			this->materii[i] = new char[strlen(sursa.materii[i]) + 1];
			strcpy(this->materii[i], sursa.materii[i]);
		}
	}

	//operatorul = 
	StudentBursier& operator=(const StudentBursier& sursa)
	{
		delete[] this->nume;
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;

		if (this->materii != NULL)
		{
			for (int i = 0; i < this->nr_materii_preferate; i++)
			{
				if (this->materii[i] != NULL)
				{
					delete[] this->materii[i];
				}
			}
			delete[] this->materii;
		}

		this->bursa = sursa.bursa;
		this->nr_materii_preferate = sursa.nr_materii_preferate;
		this->materii = new char*[sursa.nr_materii_preferate];
		for (int i = 0; i < sursa.nr_materii_preferate; i++)
		{
			this->materii[i] = new char[strlen(sursa.materii[i]) + 1];
			strcpy(this->materii[i], sursa.materii[i]);
		}

		return *this;
	}

	bool operator<(StudentBursier sb)
	{
		return this->bursa < sb.bursa;
	}

	//overriding - suprascriere
	void afisare()
	{
		cout << *this;
	}

};

class Grupa
{
public:
	int numar_studenti;
	Student* studenti;
	char denumire[10];

	Grupa(int v_numar_studenti, Student* v_studenti, char* v_denumire)
	{
		this->numar_studenti = v_numar_studenti;
		strcpy(this->denumire, v_denumire);
		this->studenti = new Student[v_numar_studenti];
		for (int i = 0; i < v_numar_studenti; i++)
		{
			this->studenti[i] = v_studenti[i];
		}
	}

	//operatorul<< de scriere in fisier
	friend ofstream& operator<<(ofstream& out, Grupa& grupa)
	{
		out << "Catalogul grupei " << grupa.denumire << endl;
		for (int i = 0; i < grupa.numar_studenti; i++)
		{
			out << grupa.studenti[i].nume << endl;
		}

		return out;
	}
};

void main()
{
	Student s1;
	cout << s1;
	Student s2("Enachescu irina", true);
	cout << s2;

	StudentBursier sb1;
	cout << sb1;

	char* materii[2] = { "C++", "Java" };
	StudentBursier sb2("Popescu", false, 100, 2, materii);
	cout << sb2;

	//constr de copiere
	StudentBursier sb3 = sb2;
	cout << sb3;

	StudentBursier sb4;
	sb4 = sb2;
	cout << sb4;

	if (sb2 < sb1){
	
		cout << sb2.nume << " are bursa mai mica decat " << sb1.nume << endl;
	}
	else
	{
		cout << sb1.nume << " are bursa mai mica decat " << sb2.nume << endl;
	}

	Student list[3] = { s2, sb2, sb1 };

	Grupa grupa1042(3, list, "Grupa 1042");

	ofstream fisier;
	fisier.open("Catalog.txt", ofstream::out);
	fisier << grupa1042;
	fisier.close();

	for (int i = 0; i < grupa1042.numar_studenti; i++)
	{
		cout << grupa1042.studenti[i] << endl;
	}

	Student* list_pointeri[3] = { new Student(s2), new StudentBursier(sb2), &sb1 };

	for (int i = 0; i < 3; i++)
	{
		list_pointeri[i]->afisare();
	}


}