#include <iostream>

using namespace std;

int main(void)
{
	/* Hier ein auskommentiertes Beispiel für eine Unendlichschleife:
		while(true)
		{
			cout << "Yeyy" << endl;
		}
	*/


	int x=1;
	while(x <= 10)
	{
		cout << x << " ist eine natürliche Zahl :)" << endl;
		
		// x++ bewirkt dasselbe wie x = x + 1
		x++;
	}

	return 0;
}