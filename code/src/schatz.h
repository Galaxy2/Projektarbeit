#ifndef __SCHATZ_H__
#define __SCHATZ_H__

#include "animation.h"

class schatz
{
public:
    animation *s;
    bool eingesammelt;

    schatz(void);
    ~schatz(void);
};

#endif // __SCHATZ_H__
