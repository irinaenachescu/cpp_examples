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
	cin >> (*t).id;

	cout << "Producator: ";
	cin >> t->producator;

	cout << "Denumire: ";
	char aux[50];
	cin.ignore();
	cin.getline(aux, 50);
	t->denumire = new char[strlen(aux) + 1];
	strcpy(t->denumire, aux);

	cout << "Numar preturi: ";
	cin >> t->numar_preturi;

	t->preturi = new float[t->numar_preturi];
	for (int i = 0; i < t->numar_preturi; i++){
		cout << "Pret[" << i << "]= ";
		cin >> t->preturi[i];
	}

	cout << "Latime: "; 
	cin >> t->dimensiuni[0];

	cout << "Lungime: ";
	cin >> t->dimensiuni[1];

	cout << "Grosime: ";
	cin >> t->dimensiuni[2];
}

void afisare(Telefon t)
{
	cout << "Id: " << t.id << endl;
	cout << "Producator: " << t.producator << endl;
	cout << "Denumire: " << t.denumire << endl;
	cout << "Preturi: ";
	for (int i = 0; i < t.numar_preturi; i++){
		cout << t.preturi[i] << " ";
	}
	cout << endl;
	cout << "Dimensiuni: " << t.dimensiuni[0] << "," << t.dimensiuni[1] << ","
		<< t.dimensiuni[2] << endl;
}

void main()
{
	Telefon t;
	initializare(&t);
	afisare(t);


}