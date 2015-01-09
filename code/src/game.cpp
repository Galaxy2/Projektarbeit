#include "game.h"
#include "level.h"

extern level *aktuellesLevel;

bool game::checkSieg(void)
{
    // Sieg überprüfen? (Alle Punkte geholt?)
    if(punkte >= aktuellesLevel->minPunkte)
        return true;

    return false;
}

game::game(void)
{
    // Am Anfang des Spiels -> Punkte auf 0 setzen
    punkte = 0;
}

void game::punkteHinzufuegen(int p)
{
    // Punkte zum laufenden Spiel hinzufügen
    punkte += p;
    std::cout << punkte << std::endl;
}

