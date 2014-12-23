#include <iostream>
#include "main.h"

extern sf::Music musik;

void hintergrundMusik(void)
{
    if (!musik.openFromFile("resources/sound/Gameover.ogg"))
    {
        std::cerr << "Fehler beim öffnen der hintergrundMusik";
    }

    musik.play();
}
