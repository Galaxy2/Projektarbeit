#include <iostream>
#include "main.h"

extern sf::Music musik;

void hintergrundMusik(void)
{
    if (!musik.openFromFile("resources/sound/gameover.ogg"))
    {
        std::cerr << "Fehler beim �ffnen der hintergrundMusik";
    }

    musik.play();
}
