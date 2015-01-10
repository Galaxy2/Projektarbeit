#include "schatz.h"

schatz::schatz(void)
{
    // Schatz einsammeln!
    eingesammelt = false;
}


schatz::~schatz(void)
{
    // Speicher freigeben!
    delete s;
}
