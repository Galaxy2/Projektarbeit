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

        sf::Vector2f koordinatenOben = koordinaten(x1, y1);
        sf::Vector2f koordinatenUnten = koordinaten(x2, y2);

        mauern.push_back(sf::FloatRect(koordinatenOben.x, koordinatenUnten.y, koordinatenUnten.x-koordinatenOben.x, koordinatenUnten.y-koordinatenOben.y));
    }

    if(levelDatei.fail())
        cerr << "Fehler beim Laden der Leveldatei" << endl;

    levelDatei.close();
}


bool level::checkCollision(sf::FloatRect& spielerPosition)
{
    for(sf::FloatRect mauer : mauern){
        if(mauer.intersects(spielerPosition)){
            // Diese Zeile verhindert eine Bewegung des Spielers
            //debugMsg.updateText("Intersect!");
            return true;
        }
    }

    return false;
}
