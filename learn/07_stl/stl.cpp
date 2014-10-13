#include <iostream>
#include <vector>

using namespace std;


/* Übergeben wird nur eine Referenz auf den Vektor!
 * Das heisst alles was in den Vektor geschrieben wird
 * ist automatisch im Vektor der main()-Funktion,
 * obwohl die Namen hier eingelesen werden.
 */
void namenEinlesen(vector<string>& namenListe)
{
	cout << "Vornamen eingeben, 999 um abzubrechen" << endl;
	while(true)
	{
		string name;
		cin >> name;
		
		if(name == "999")
			break;
		
		namenListe.push_back(name);
	}
}



void statistiken(vector<string>& anwesende, vector<string>& abwesende)
{
	int anzahlAnwesende = anwesende.size();
	int anzahlAbwesende = abwesende.size();
	int total = anzahlAnwesende + anzahlAbwesende;
	
	cout << endl << endl
		 << "===============================" << endl
		 << "          Statistiken          " << endl
		 << "===============================" << endl << endl
	
		<< "Anzahl Anwesende: " << anzahlAnwesende << " (" << 100*anzahlAnwesende/total << "%)" << endl
		<< "Anzahl Abwesende: " << anzahlAbwesende << " (" << 100*anzahlAbwesende/total << "%)" << endl
		<< "-------------------------------" << endl
		<< "Total:            " << total << " (100%)" << endl << endl;
		
}



int main(int argc, char *argv[]){
	cout << "Protokollschreiber gestartet!" << endl;
	
	// Anwesende einlesen
	cout << "Welche Personen sind anwesend?" << endl;
	vector<string> anwesende;
	namenEinlesen(anwesende);
	
	// Abwesende einlesen
	cout << "Welche Personen sind abwesend?" << endl;
	vector<string> abwesende;
	namenEinlesen(abwesende); 
	
	
	// Nun die Statistiken ausgeben
	statistiken(anwesende, abwesende);
	
	
	// Beenden
	cout << "Vielen Dank für die Benutzung des Programmes!" << endl;
	
	return 0;
}
