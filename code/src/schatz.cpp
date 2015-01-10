#include "schatz.h"

schatz::schatz(void)
{
    // Schatzkonstruktor
    eingesammelt = false;
    s->zeigeSchritt(0);
    s->sprite.setOrigin(0,0);
}


schatz::~schatz(void)
{
    // Speicher freigeben!
    delete s;
}
