#include "game.h"


game::game(void)
{
    punkte = 0;
}

void game::punkteHinzufuegen(int p)
{
    punkte += p;
    std::cout << punkte << std::endl;
}

