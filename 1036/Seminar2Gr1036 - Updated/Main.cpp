#include<iostream>
using namespace std;
struct Telefon
{
	int id;
	char producator[50];
	char* denumire;
	int numar_preturi;
	float* preturi;
	int dimensiuni[3];
};

void initializare(Telefon* t)
{
	cout << "Id: ";
	cin >> (*t).id; // echiv cu t->id

	cout << "Producator: ";
	cin >> t->producator;

	char aux[50];
	cout << "Denumire: ";
	cin.ignore();
	cin.getline(aux, 50);
	t->denumire = new char[strlen(aux)+1];
	strcpy(t->denumire, aux);

	cout << "Numar preturi: ";
	cin >> t->numar_preturi;

	t->preturi = new float[t->numar_preturi];
	for (int i = 0; i < t->numar_preturi; i++) {
		cout << "Pret[" << i << "]: ";
		cin >> t->preturi[i];
	}

	cout << "Inaltime: ";
	cin >> t->dimensiuni[0];
	cout << "Latime: ";
	cin >> t->dimensiuni[1];
	cout << "Grosime: ";
	cin >> t->dimensiuni[2];
}

void afisare(Telefon t){
	cout << "Id: " << t.id<<endl;
	cout << "Producator: " << t.producator<<endl;
	cout << "Denumire: " << t.denumire<<endl;
	for (int i = 0; i < t.numar_preturi; i++){
		cout << "Pret[" << i << "] = " << t.preturi[i]<<endl;
	}
	cout << "Dimensiuni: " << t.dimensiuni[0] << "," << t.dimensiuni[1] << "," << t.dimensiuni[2] << endl;
}

void actualizeaza(Telefon& t, char* denumireNoua)
{
	if (t.denumire != NULL){
		delete[] t.denumire;
	}
	t.denumire = new char[strlen(denumireNoua) + 1];
	strcpy(t.denumire, denumireNoua);
}

void main()
{
	Telefon t;
	initializare(&t);
	afisare(t);

	Telefon * pt;
	pt = &t;
	afisare(*pt);

	char denumire[50];
	cout << "Dati noua denumire: ";
	cin >> denumire;

	actualizeaza(t, denumire);
	afisare(t);

}