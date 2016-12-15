#include<iostream>
#include<fstream>
using namespace std;
class Student
{
public:
	char* nume;
protected:
	
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

	virtual void afisare()
	{
		cout << (*this);
	}
};

//class StudentBursier :private Student
class StudentBursier :public Student {
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

	//operatorul=
	StudentBursier& operator=(const StudentBursier& sursa)
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
		this->bursa = sursa.bursa;

		return *this;
	}

	friend ostream& operator<<(ostream& out, StudentBursier stud)
	{
		out << (Student)stud;
		out << "Bursa: " << stud.bursa << endl;

		return out;
	}

	
	bool operator< (StudentBursier sb)
	{
		return this->bursa < sb.bursa;
	}

	//overriding / suprascriere
	void afisare()
	{
		cout << (*this);
	}

};

class Grupa
{
public:
	int numar_studenti;
	Student* studenti;
	char denumire[10];

	Grupa()
	{
		this->numar_studenti = 0;
		this->studenti = NULL;
		strcpy(this->denumire, "Grupa 000");
	}

	Grupa(int v_numar_studenti, Student* v_studenti, char* v_denumire)
	{
		this->numar_studenti = v_numar_studenti;
		this->studenti = new Student[v_numar_studenti];
		for (int i = 0; i < v_numar_studenti; i++)
		{
			this->studenti[i] = v_studenti[i];
		}
		strcpy(this->denumire, v_denumire);
	}

	//Operatorul << care scrie intr-un fisier
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

	float note[3] = { 10, 9.6, 8.9 };
	Student s2("Enachescu Irina", false, 3, note);
	cout << s2;

	StudentBursier sb1;
	cout << sb1;
	StudentBursier sb2("Enachescu Mihaela", true, 3, note,500.5);
	cout << sb2;

	//test constructor de copiere din StudentBursier
	StudentBursier sb3 = sb2;
	cout << sb3;

	//test operator= din StudentBursier
	StudentBursier sb4;
	sb4 = sb1;
	cout << sb4;

	//operatorul < intre studenti bursieri
	if (sb3 < sb4)
	{
		cout << sb3.nume << " are bursa mai mica decat " << sb4.nume << endl;
	}
	else
	{
		cout << sb4.nume << " are bursa mai mica decat " << sb3.nume << endl;
	}

	Student lista[3] = { s2, sb2, sb4 };

	Grupa grupa1036(3, lista, "Grupa 1036");

	ofstream fisier;
	fisier.open("Catalog.txt", ofstream::out);
	fisier << grupa1036;
	fisier.close();

	cout << "Studentii din grupa 1036" << endl;
	for (int i = 0; i < grupa1036.numar_studenti; i++)
	{
		cout << grupa1036.studenti[i] << endl;
	}


	Student* lista_pointeri[3] = { new Student(s2), new StudentBursier(sb2), new StudentBursier(sb4) };

	cout << "Studentii din grupa 1036 - Pointeri" << endl;
	for (int i = 0; i < 3; i++)
	{
		lista_pointeri[i]->afisare();
	}
}