#include <iostream>
#include "main.h"

extern sf::Music musik;

void hintergrundMusik(void)
{
    if (!musik.openFromFile("resources/sound/gameover.ogg"))
    {
        std::cerr << "Fehler beim öffnen der hintergrundMusik";
    }

    musik.play();
}
