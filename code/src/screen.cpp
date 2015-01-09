#include <iostream>
#include <SFML/Graphics.hpp>

#include "screen.h"

using namespace std;


extern benachrichtigung debugMsg;


void hintergrundLaden(string levelName, sf::Sprite* s, sf::Texture* h)
{
    // Dateiname zusammenstellen
    string dateiName = "levels/" + levelName + "/" + levelName + ".png";

    // Datei versuchen zu laden
    if(!h->loadFromFile(dateiName))
    {
        std::cerr << "Fehler beim Laden des Hintergrunds\n";
    }

    // Die Textur dem Sprite zuweisen!
    s->setTexture(*h);

}



