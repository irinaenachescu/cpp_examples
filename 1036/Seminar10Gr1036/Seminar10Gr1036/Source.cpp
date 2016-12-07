#include<iostream>
using namespace std;
class Student
{
protected:
	char* nume;
	bool integralist;
	unsigned int numar_note;
	float* note;
public:
	Student()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->integralist = true;
		this->numar_note = 0;
		this->note = NULL;
	}

	Student(char* v_nume, bool v_integralist, unsigned int v_numar_note, float* v_note)
	{
		this->nume = new char[strlen(v_nume) + 1];
		strcpy(this->nume, v_nume);
		this->integralist = v_integralist;
		this->numar_note = v_numar_note;
		this->note = new float[this->numar_note];
		for (int i = 0; i < this->numar_note; i++)
		{
			this->note[i] = v_note[i];
		}
	}

	~Student()
	{
		delete[] this->nume;
		delete[] this->note;
	}

	Student(const Student& sursa)
	{
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;
		this->numar_note = sursa.numar_note;
		this->note = new float[sursa.numar_note];
		for (int i = 0; i < sursa.numar_note; i++)
		{
			this->note[i] = sursa.note[i];
		}
	}

	Student& operator=(const Student& sursa)
	{
		delete[] this->nume;
		delete[] this->note;
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;
		this->numar_note = sursa.numar_note;
		this->note = new float[sursa.numar_note];
		for (int i = 0; i < sursa.numar_note; i++)
		{
			this->note[i] = sursa.note[i];
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, Student stud)
	{
		out << "Nume: " << stud.nume << endl;
		out << "Integralist: " << ((stud.integralist == true) ? "Da" : "Nu") << endl;
		out << "Numar note: " << stud.numar_note << endl;
		for (int i = 0; i < stud.numar_note; i++)
		{
			out << "Nota " << i + 1 << " este: " << stud.note[i] << endl;
		}

		return out;
	}
};

class StudentBursier :private Student {
private:
	double bursa;
public:
	StudentBursier():Student(){
		this->bursa = 0;
	}

	StudentBursier(char* v_nume, bool v_integralist,
		unsigned int v_numar_note, float* v_note, double v_bursa) :Student(v_nume,v_integralist,
		v_numar_note,v_note)
	{
		this->bursa = v_bursa;
	}

	~StudentBursier()
	{
		cout << "In destructor - StudentBursier..." << endl;
	}

	StudentBursier(const StudentBursier& sursa)
		:Student(sursa.nume, sursa.integralist,sursa.numar_note,sursa.note)
	{
		this->bursa = sursa.bursa;
	}

	friend ostream& operator<<(ostream& out, StudentBursier stud)
	{
		out << (Student)stud;
		out << "Bursa: " << stud.bursa << endl;

		return out;
	}

};


void main()
{
	Student s1;
	cout << s1;

	float note[3] = { 10, 9.6, 8.9 };
	Student s2("Enachescu Irina", false, 3, note);
	cout << s2;

	StudentBursier sb1;
	cout << sb1;
	StudentBursier sb2("Enachescu Mihaela", true, 3, note,500.5);
	cout << sb2;
}