#include <iostream>
#include "main.h"

extern sf::Music musik;

void hintergrundMusik(void)
{
    if (!musik.openFromFile("resources/sound/Gameover.ogg"))
    {
        std::cerr << "Fehler beim �ffnen der hintergrundMusik";
    }

    musik.play();
}
