#include "tuere.h"

tuere::tuere(void)
{
    // Türen Konstruktor
    offen = true;
    t->zeigeSchritt(0);
    t->sprite.setOrigin(14, 186);
}


tuere::~tuere(void)
{
    // Speicher freigeben!
    delete t;
}
