#include<iostream>
using namespace std;
//prototip
void interschimba(int x, int y);

void interschimba2(int* x, int* y);

void main(){
	/*std::cout << "Dimensiunea unui int " << sizeof(int) << endl;
	cout << "Dimensiunea unui double:" << sizeof(double) << endl;*/

	int a = 100, b = 200;
	int temp;
	temp = a;
	a = b;
	b = temp;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	interschimba(a, b);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	interschimba2(&a, &b);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

}

void interschimba(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

void interschimba2(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}