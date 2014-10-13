#include <iostream>

#include "klassen.h"

using namespace std;


// Folgender Code könnte auch ausgelagert werden, ist dann
// nicht mehr so leicht zu kompilieren.
void raumschiff::printLeben(void)
{
	cout << "Aktuelles Leben: " << leben << endl;
}

void raumschiff::crash(void)
{
	leben = leben - 10;
}

raumschiff::raumschiff(int pos_x, int pos_y, int leb)
{
	x = pos_x;
	y = pos_y;
	leben = leb;
}

raumschiff::raumschiff(void)
{
	x = 0;
	y = 0;
	leben = 100;
}


raumschiff::~raumschiff()
{
	cout << "Raumschiff wurde zerstört: Game over!\n";
}



// Hauptprogramm

int main(int argc, char *argv[])
{
	raumschiff iss(200, 100, 76);
	
	raumschiff enterprise;
	
	
	iss.printLeben();
	iss.crash();
	iss.crash();
	iss.printLeben();

	enterprise.printLeben();

}
