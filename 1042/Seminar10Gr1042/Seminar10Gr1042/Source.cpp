#include<iostream>
using namespace std;

class Student {
protected:
	char* nume;
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
};

class StudentBursier : private Student {
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

	friend ostream& operator<<(ostream& out, StudentBursier& s)
	{
		out << (Student)s;
		out << "Bursa: " << s.bursa << endl;

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



}