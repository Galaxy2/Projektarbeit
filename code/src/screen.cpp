#include <iostream>
#include <SFML/Graphics.hpp>

#include "screen.h"
using namespace screen;

namespace screen
{
float factor;
}


extern benachrichtigung debugMsg;


void hintergrundLaden(sf::Sprite& s, sf::Texture& h)
{

    if(!h.loadFromFile("levels/test1/test1.png"))
    {
        std::cerr << "Fehler Hintergrund";
    }

    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();

    // Berechne Skalierungsfaktor
    /*factor = aufloesung.width/1920.0f;
    std::cout << "Factor: " << factor << std::endl;
    if (factor > 1)
    {
        factor = 1; */

float factor = aufloesung.width/1920.0f;


    s.setTexture(h);
    s.setScale(factor, factor);
}



