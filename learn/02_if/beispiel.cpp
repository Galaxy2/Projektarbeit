#include <iostream>

using namespace std;

int main(void)
{
	int x;

	cout << "Bitte eine Zahl eingeben: ";	
	cin >> x;
	
	if(x > 16)
	{
		cout << "Die Zahl ist gr�sser als 16 ;)" << endl;
	}
	else
	{
		cout << "Die Zahl ist kleiner als 16, oder gr�sser als 2^31 :)" << endl;
	}

	return 0;
}