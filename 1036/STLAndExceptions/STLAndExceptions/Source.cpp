#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<set>
#include<map>
#include<list>
using namespace std;
class NumarNegativException:public exception{

};

void main()
{
	/*
	try
	{
		//validarea unei valori citite de la tastatura
		cout << "Dati varsta: ";
		int varsta;
		cin >> varsta;
		if (varsta < 0){
			throw new NumarNegativException();
		}
		else if (varsta > 100)
		{
			throw varsta;
			//throw "Varsta prea mare";
		}
		cout << "Varsta introdusa: " << varsta << endl;
	}
	catch (NumarNegativException* ex)
	{
		cout << "Varsta nu poate fi negativa." << endl;
	}
	catch (int nr)
	{
		cout << "Varsta a depasit 100 de ani: " << nr << endl;
	}
	catch (char* mesaj)
	{
		cout << "Eroare: " << mesaj << endl;
	}
	catch (...)
	{
		cout << "Eroare generica." << endl;
	}
	*/

	/*
	
	//string - pentru a inlocui lucrul cu char*
	string nume = "Enachescu";
	cout << nume << endl;
	nume = nume + " Irina";
	cout << nume << endl;
	nume = "Popescu";
	cout << nume << endl;
	string nume2 = nume.substr(0, 3);
	cout << nume2 << endl;
	cout << nume.length();
	*/

	
	//STL - Standard Template Library - Biblioteca c++ de clase si functii generice

	//1. containere
	//2. iteratori

	//1.1 vector : #include<vector>
	cout << "-----------Vector-------------" << endl;
	vector<int> numere;
	numere.push_back(15);
	numere.push_back(16);
	numere.push_back(23);
	cout << "Valoarea de la indexul 2: " << numere[2] << endl;
	numere.pop_back();
	for (int i = 0; i < numere.size(); i++)
	{
		cout << numere[i] << endl;
	}
	cout << "------------------------------" << endl;

	//2.1 interator pentru un vector
	cout << "-----------Iterator pentru Vector-------------" << endl;
	vector<int>::iterator it;
	for (it = numere.begin(); it != numere.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "------------------------------" << endl;

	//1.2 deque - coada cu doua capete, parcurgere in ambele directii : #include<deque>
	cout << "-----------Deque-------------" << endl;
	deque<float> numere2;
	numere2.push_back(19);
	numere2.push_front(99);
	numere2.push_front(12);
	for (int i = 0; i < numere2.size(); i++)
	{
		cout << numere2[i] << endl;
	}
	numere2.pop_front();
	cout << "------------------------------" << endl;
	
	//2.2 interator pentru deque
	cout << "-----------Iterator pentru Deque-------------" << endl;
	deque<float>::iterator it2;
	for (it2 = numere2.begin(); it2 != numere2.end(); it2++)
	{
		cout << *it2 << endl;
	}
	cout << "------------------------------" << endl;

	

	//1.3 set - valori unice, sortate : #include<set>
	cout << "-----------Set-------------" << endl;
	set<string> numeSet;
	numeSet.insert("Irina");
	numeSet.insert("Mihai");
	numeSet.insert("Florin");
	numeSet.insert("Irina");
	cout << "------------------------------" << endl;

	//2.3 interator pentru set
	cout << "-----------Iterator pentru Set-------------" << endl;
	set<string>::iterator it3;
	for (it3 = numeSet.begin(); it3 != numeSet.end(); it3++)
	{
		cout << *it3 << endl;
	}

	it3 = numeSet.find("Florin");
	if (it3 != numeSet.end())
	{
		cout << "Exista." << endl;
	}
	else
	{
		cout << "Nu exista." << endl;
	}
	cout << "------------------------------" << endl;

	//1.4 map - perechi (cheie,valoare); cheile au valori unice : #include<map>
	cout << "-----------Map-------------" << endl;
	map<int, string> studenti;
	studenti[100] = "Irina";
	studenti[200] = "Gigi";
	studenti.insert(make_pair(300, "Andrei"));
	string numeStudent = studenti[200];
	if (!numeStudent.empty()){
		cout << "Valoarea pentru cheia 200 este: " << numeStudent << endl;
	}
	cout << "------------------------------" << endl;

	//2.4 interator pentru map
	cout << "-----------Iterator invers pentru Map-------------" << endl;
	map<int, string>::reverse_iterator it4;
	for (it4 = studenti.rbegin(); it4 != studenti.rend(); it4++)
	{
		cout << "Cheia " << it4->first << " are valoarea " << it4->second << endl;
	}
	cout << "------------------------------" << endl;

	//list
	cout << "-----------List-------------" << endl;
	list<int> lista;
	lista.push_front(-3);
	lista.push_back(3);
	lista.push_back(6);
	lista.push_front(1);
	lista.sort();
	list<int>::iterator it5;
	for (it5 = lista.begin(); it5 != lista.end(); it5++)
	{
		cout << *it5 << endl;
	}
	lista.reverse();
	cout << "Dupa apelare reverse: " << endl;
	for (it5 = lista.begin(); it5 != lista.end(); it5++)
	{
		cout << *it5 << endl;
	}
	cout << "------------------------------" << endl;
}