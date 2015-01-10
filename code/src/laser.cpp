#include "laser.h"

laser::laser(void)
{
    // Laserkonstruktor
    l->zeigeSchritt(0);
    l->sprite.setOrigin(0, 0);
}


laser::~laser(void)
{
    // Speicher freigeben
    delete l;
}
