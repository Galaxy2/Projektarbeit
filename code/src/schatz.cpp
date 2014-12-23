#include "schatz.h"

schatz::schatz(void)
{
    eingesammelt = false;
}


schatz::~schatz(void)
{
    delete s;
}
