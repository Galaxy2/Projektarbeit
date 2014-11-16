#include <iostream>
#include <SFML/Graphics.hpp>

#include "screen.h"
using namespace screen;
using namespace std;

namespace screen
{
    float factor;
}


extern benachrichtigung debugMsg;


void hintergrundLaden(string levelName, sf::Sprite* s, sf::Texture* h)
{
    string dateiName = "levels/" + levelName + "/" + levelName + ".png";

    if(!h->loadFromFile(dateiName))
    {
        std::cerr << "Fehler beim Laden des Hintergrunds\n";
    }

    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();

    // Berechne Skalierungsfaktor
    /*factor = aufloesung.width/1920.0f;
    std::cout << "Factor: " << factor << std::endl;
    if (factor > 1)
    {
        factor = 1; */

    float factor = aufloesung.width/1920.0f;


<<<<<<< HEAD
    s.setTexture(h);
//    s.setScale(factor, factor);
=======
    s->setTexture(*h);
    s->setScale(factor, factor);
>>>>>>> 18449c2b7473032a46ad70974beab9be746ef7b1
}



