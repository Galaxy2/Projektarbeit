#include "tuere.h"

tuere::tuere(void)
{
    // Türe öffnen
    offen = false;
}

tuere::~tuere(void)
{
    // Speicher freigeben!
    delete t;
}
