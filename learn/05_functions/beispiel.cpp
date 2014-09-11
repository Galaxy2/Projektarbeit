#include <iostream>

using namespace std;


int summe(int a, int b)
{
	return a+b;
}


int quadrat(int x)
{
	return x*x;
}


void programm_info_ausgeben(void)
{
	cout << "Das ist ein Beispielprogramm :)" << endl;
}


int main(void)
{
	cout << "Die Summe von 15 und 17: " << summe(15, 17) << endl;

	cout << "Die ersten 10 Quadratzahlen: ";

	for(int a=1; a<=10; a++)
	{
		cout << quadrat(a) << " ";
	}	
	
	cout << endl;


	programm_info_ausgeben();

	return 0;
}