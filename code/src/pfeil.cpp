#include "pfeil.h"

pfeil::pfeil(void)
{
    // Pfeilkonstruktor
    p->zeigeSchritt(0);
    p->sprite.setOrigin(100, 50);
}


pfeil::~pfeil(void)
{
    // Speicher freigeben!
    delete p;
}


