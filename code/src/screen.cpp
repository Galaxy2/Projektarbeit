#include <iostream>
#include <SFML/Graphics.hpp>

#include "screen.h"

using namespace std;


extern benachrichtigung debugMsg;


void hintergrundLaden(string levelName, sf::Sprite* s, sf::Texture* h)
{
    string dateiName = "levels/" + levelName + "/" + levelName + ".png";

    if(!h->loadFromFile(dateiName))
    {
        std::cerr << "Fehler beim Laden des Hintergrunds\n";
    }

    s->setTexture(*h);

}



