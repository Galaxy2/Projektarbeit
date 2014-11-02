#include <iostream>
#include <SFML/Graphics.hpp>

void hintergrundLaden(sf::Sprite& s, sf::Texture& h){

    if(!h.loadFromFile("levels/test/test.png")){
        std::cerr << "Fehler Hintergrund";
    }

    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();

    // Berechne Skalierungsfaktor
    float factor = aufloesung.width/1920.0f;
    std:: cout << factor;
    if (factor > 1){
            factor = 1;
    }

    s.setTexture(h);
    s.setScale(factor, factor);
}



