#include "game.h"
#include "level.h"

extern level *aktuellesLevel;

bool game::checkSieg(void)
{
    if(punkte >= aktuellesLevel->minPunkte)
        return true;

    return false;
}

game::game(void)
{
    punkte = 0;
}

void game::punkteHinzufuegen(int p)
{
    punkte += p;
    std::cout << punkte << std::endl;
}

