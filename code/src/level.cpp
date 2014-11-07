#include <iostream>
#include <fstream>

#include "level.h"
#include "screen.h"
#include "notification.h"


extern benachrichtigung debugMsg;


void level::loadFromFile(string pfad)
{
    fstream levelDatei(pfad.c_str(), fstream::in);

    // Anzahl Mauern einlesen
    unsigned int N;
    levelDatei >> N;

    unsigned int x1, y1, x2, y2;
    for(unsigned int i=0; i<N; i++){
        levelDatei >> x1 >> y1 >> x2 >> y2;

        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

        // Skalierungsfix
        x1 *= screen::factor;
        y1 *= screen::factor;
        x2 *= screen::factor;
        y2 *= screen::factor;

        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

        mauern.push_back(sf::FloatRect(x1, y2, x2-x1, y2-y1));
    }

    if(levelDatei.fail())
        cerr << "Fehler beim Laden der Leveldatei" << endl;

    levelDatei.close();
}


bool level::checkCollision(sf::FloatRect& spielerPosition)
{
    for(sf::FloatRect mauer : mauern){
        if(spielerPosition.intersects(mauer))
            // Diese Zeile verhindert eine Bewegung des Spielers
            //debugMsg.updateText("Intersect!");

            return true;
    }

    return false;
}
