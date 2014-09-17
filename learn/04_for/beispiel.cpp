#include <iostream>

using namespace std;

int main(void)
{
	/* Hier ein auskommentiertes Beispiel für eine Unendlichschleife:
		for(; ;)
		{
			cout << "Yeyy" << endl;
		}
	*/


	int x;
	for(x=1; x<=10; x++)
	{
		cout << x << " ist eine natürliche Zahl :)" << endl;
	}

	
	// Alternativ kann die Variabeldefinition auch in den Kopf der for-Schleife geschrieben werden:
	for(int y=5; y<100; y++)
	{
		cout << y << endl;
	}


	return 0;
}