#include <iostream>
#include <fstream>

#include "level.h"
#include "screen.h"
#include "notification.h"

sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();
float factor = aufloesung.width/1920.0f;

extern benachrichtigung debugMsg;


void level::loadFromFile(string pfad)
{
    fstream levelDatei(pfad.c_str(), fstream::in);

    // Anzahl Mauern einlesen
    unsigned int N;
    levelDatei >> N;

    unsigned int x1, y1, x2, y2;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x1 >> y1 >> x2 >> y2;
        x1 *= factor;
        y1 *= factor;
        x2 *= factor;
        y2 *= factor;
        sf::Vector2f koordinatenOben(x1, y1);
        sf::Vector2f koordinatenUnten(x2, y2);

        mauern.push_back(sf::FloatRect(koordinatenOben.x, koordinatenOben.y, koordinatenUnten.x-koordinatenOben.x, koordinatenUnten.y-koordinatenOben.y));
    }

    if(levelDatei.fail())
        cerr << "Fehler beim Laden der Leveldatei" << endl;

    levelDatei.close();
}


bool level::checkCollision(sf::FloatRect& spielerPosition)
{
    if(!collisionsActivated)
        return false;


    for(sf::FloatRect mauer : mauern)
    {
        if(mauer.intersects(spielerPosition))
        {
            return true;
        }
    }

    return false;
}


void level::loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList)
{
    if(hintergrundTextur != 0x0 && hintergrund != 0x0)
    {
        delete hintergrundTextur;
        delete hintergrund;
    }

    hintergrundTextur = new sf::Texture;
    hintergrund = new sf::Sprite;


    // Aktuelles Level leeren
    mauern.clear();
    collisionsActivated = true;

    string levelDateiName = "levels/" + name + "/" + name + ".lvl";
    this->loadFromFile(levelDateiName);

    // Hintergrundbild laden
    hintergrundLaden(name, hintergrund, hintergrundTextur);
    renderList.push_front(hintergrund);
}
