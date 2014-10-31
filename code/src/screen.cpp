#include <iostream>
#include <SFML/Graphics.hpp>

void hintergrundLaden(sf::Sprite& s, sf::Texture& h){

    if(!h.loadFromFile("levels/test/test.png")){
        std::cerr << "Fehler Hintergrund";
    }

    s.setTexture(h);
    s.setScale(0.7, 0.7);
}



