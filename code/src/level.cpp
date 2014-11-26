#include <iostream>
#include <fstream>

#include "level.h"
#include "screen.h"
#include "notification.h"


extern benachrichtigung debugMsg;


/** \brief Lädt das Level in den Speicher (Mauern, Animationen, ...)
 *
 * \param pfad string Pfad zur Leveldatei (levels/test/test.lvl)
 * \param renderList list<sf::Drawable *>& Die Renderliste
 * \param animationList list<animation *>& Die Animationsliste
 * \return void
 *
 */
void level::loadFromFile(string pfad, list<sf::Drawable *>& renderList, list<animation *>& animationList)
{
    fstream levelDatei(pfad.c_str(), fstream::in);


    // Spieler Spawn Position lesen!
    levelDatei >> spielerPosition.x >> spielerPosition.y;

    unsigned int N;

    // Anzahl Pfeile einlesen
    levelDatei >> N;
    unsigned int x, y, r;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x >> y >> r;

        pfeile.push_back(new animation("resources/pfeil", 8, true, true, true, 0.05, x, y));
        pfeile[i]->zeigeSchritt(0);
        pfeile[i]->sprite.setOrigin(100, 50);
        pfeile[i]->sprite.setRotation(r);

        renderList.push_back(&pfeile[i]->sprite);
        animationList.push_back(pfeile[i]);
    }

    levelDatei >> N;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x >> y >> r;

        tueren.push_back(new animation("resources/tuere", 5, false, false, true, 0.1, x, y));
        tueren[i]->zeigeSchritt(0);
        tueren[i]->sprite.setRotation(r);

        renderList.push_back(&tueren[i]->sprite);
        animationList.push_back(tueren[i]);
    }


    // Anzahl Mauern einlesen
    levelDatei >> N;

    unsigned int x1, y1, x2, y2;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x1 >> y1 >> x2 >> y2;
        sf::Vector2f koordinatenOben(x1, y1);
        sf::Vector2f koordinatenUnten(x2, y2);

        mauern.push_back(sf::FloatRect(koordinatenOben.x, koordinatenOben.y, koordinatenUnten.x-koordinatenOben.x, koordinatenUnten.y-koordinatenOben.y));
    }

    if(levelDatei.fail())
        cerr << "Fehler beim Laden der Leveldatei" << endl;

    levelDatei.close();
}


/** \brief Kollisionsdetektion
 *
 * \param spielerPosition sf::FloatRect& Ein Rechteck mit den Koordinaten des Spielers
 * \return bool
 *
 */
bool level::checkCollision(sf::FloatRect& spielerPosition)
{
    if(!collisionsActivated)
        return false;


    for(sf::FloatRect mauer : mauern)
    {
        if(mauer.intersects(spielerPosition))
        {
            return true;
        }
    }

    return false;
}


 /** \brief Lädt das ganze Level auf den Bildschirm zum Spielen
 * Das heisst alle Animationen, Mauern, etc. werden mitgeladen
 *
 * \param hintergrundTextur sf::Texture*& Zeiger zur Hintergrundtextur
 * \param hintergrund sf::Sprite*& Zeiger zum Hintergrundsprite
 * \param renderList list<sf::Drawable *>& Die Renderliste
 * \param animationList list<animation *>& Die Animationsliste
 * \return void
 *
 */
void level::loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList)
{
    if(hintergrundTextur != 0x0 && hintergrund != 0x0)
    {
        delete hintergrundTextur;
        delete hintergrund;
    }

    hintergrundTextur = new sf::Texture;
    hintergrund = new sf::Sprite;


    // Aktuelles Level leeren
    for(auto p : pfeile)
    {
        delete p;
    }

    pfeile.clear();
    mauern.clear();
    renderList.clear();
    animationList.clear();

    collisionsActivated = true;

    string levelDateiName = "levels/" + name + "/" + name + ".lvl";
    this->loadFromFile(levelDateiName, renderList, animationList);

    // Hintergrundbild laden
    hintergrundLaden(name, hintergrund, hintergrundTextur);
    renderList.push_front(hintergrund);
}

