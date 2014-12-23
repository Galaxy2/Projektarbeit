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
void level::loadFromFile(void)
{
    string levelDateiName = "levels/" + name + "/" + name + ".lvl";
    fstream levelDatei(levelDateiName.c_str(), fstream::in);

    // abähngige Datei
    levelDatei >> deckeName;

    // Spieler Spawn Position lesen!
    levelDatei >> spielerPosition.x >> spielerPosition.y;

    int Wert; //Wert zum Angeben ob draussen( =1) oder drinnen( !=1) oder Hauptmenu( =2)
    levelDatei >> Wert;

    unsigned int N;

    // Anzahl Pfeile einlesen
    levelDatei >> N;
    unsigned int x, y, nX, nY;
    int r;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x >> y >> r >> nX >> nY;

        pfeile.push_back(new pfeil);
        if(Wert == 1) // überprüfen ob man im Haus ist oder nicht (1 = aussen)
        {
            pfeile[i]->p = (new animation("resources/pfeilRot", 8, true, true, true, 0.05, x, y)); //rote pfeile werden geladen
        }
        if(Wert == 2)
        {
            pfeile[i]->p = (new animation("resources/spielStarten", 1, true, false, false, 0.05, x, y)); // SpielStarten
        }
        else
        {
            pfeile[i]->p = (new animation("resources/pfeil", 8, true, true, true, 0.05, x, y));
        }
        pfeile[i]->p->zeigeSchritt(0);
        pfeile[i]->p->sprite.setOrigin(100, 50);
        pfeile[i]->p->sprite.setRotation(r);
        pfeile[i]->p->Id = i;
        pfeile[i]->nX = nX;  //x-koordinate des Spielers im neuen Level
        pfeile[i]->nY = nY;  //y-koordinate des Spielers im neuen Level

    }


    // Anzahl Türen einlesen
    levelDatei >> N;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x >> y >> r;

        tueren.push_back(new tuere);
        tueren[i]->t = new animation("resources/tuere", 5, false, false, true, 0.05, x, y);
        tueren[i]->offen = true;
        tueren[i]->t->zeigeSchritt(0);
        tueren[i]->t->sprite.setOrigin(14, 186);
        tueren[i]->t->sprite.setRotation(r);
        tueren[i]->t->Id = i;
        tueren[i]->posX = x;
        tueren[i]->posY = y;
        tueren[i]->t->setOnAnimationEnde(&setzeMauer);

        if(r == 0)
            mauern.push_back(sf::FloatRect(x-7, y-7, 193, 14));
        else if(r == -90)
            mauern.push_back(sf::FloatRect(x-7, y-186, 14, 193));
        else if(r == -180)
            mauern.push_back(sf::FloatRect(x-186, y-7, 193, 14));
        else if(r == -270)
            mauern.push_back(sf::FloatRect(x-7, y-7, 14, 193));
    }


    // Anzahl Schätze einlesen
    levelDatei >> N;
    for (unsigned int i=0; i<N; i++)
    {
        levelDatei >> x >> y >> r;

        schaetze.push_back(new schatz);
        schaetze[i]->s = new animation("resources/schatz", 1, false, false, true, 0.05, x, y);
        schaetze[i]->s->zeigeSchritt(0);
        schaetze[i]->s->sprite.setOrigin(0,0);
        schaetze[i]->s->sprite.setRotation(r);
        schaetze[i]->s->Id = i;
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

    levelDatei >> N;
    for(unsigned int i=0; i<N; i++)
    {
        levelDatei >> x >> y >> r;

        lasers.push_back(new laser);
        lasers[i]->l = new animation("resources/laser", 3, true, true, true, 0.05, x, y);
        lasers[i]->l->zeigeSchritt(0);
        lasers[i]->l->sprite.setOrigin(0, 0);
        lasers[i]->l->sprite.setRotation(r);


    }

    if(levelDatei.fail())
    {
        cerr << "Fehler beim Laden der Leveldatei" << endl;
        cerr << levelDateiName << endl;
    }


    levelDatei.close();
}



int level::checkCollisionPfeile(sf::FloatRect& spielerPosition)
{
    int k = 0;
    for(pfeil* P : pfeile)
    {
        if(P->p->sprite.getGlobalBounds().intersects(spielerPosition))
        {
            return k;
        }

        k++;
    }
    return -1;
}

bool level::checkCollisionLaser(sf::FloatRect& spielerPosition)
{
    for(laser* L : lasers)
    {
        if(L->l->sprite.getGlobalBounds().intersects(spielerPosition))
        {
            return true;
        }
        return false;
    }
}

int level::checkCollisionTuere(sf::FloatRect& spielerPosition)
{
    int k = 0;
    for(tuere* T : tueren)
    {
        sf::FloatRect puffer;
        puffer = T->t->sprite.getGlobalBounds();
        puffer.height += 20;
        puffer.width += 20;
        puffer.left -= 10;
        puffer.top -= 10;
        if(puffer.intersects(spielerPosition))
        {
            return k;
        }

        k++;
    }

    return -1;
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

//checkSchaetze

int level::checkCollisionSchaetze(sf::FloatRect& spielerPosition)
{
    int i = 0;
    for(schatz* S : schaetze)
    {
        if(S->s->sprite.getGlobalBounds().intersects(spielerPosition))
        {
            return i;
        }

    i++;
    }

    return -1;
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
    renderList.clear();
    animationList.clear();


    // Alle Pfeile anzeigen
    for(int i=0; i<pfeile.size(); i++)
    {
        renderList.push_back(&pfeile[i]->p->sprite);
        animationList.push_back(pfeile[i]->p);
    }

    // Alle Türen anzeigen
    for(int i=0; i<tueren.size(); i++)
    {
        renderList.push_back(&tueren[i]->t->sprite);
        animationList.push_back(tueren[i]->t);
    }

    // Alle Schätze anzeigen
    for(int i=0; i<schaetze.size(); i++)
    {
        if(!schaetze[i]->eingesammelt)
        {
            renderList.push_back(&schaetze[i]->s->sprite);
            animationList.push_back(schaetze[i]->s);
        }
    }

    // Alle Laser anzeigen
    for(int i=0; i<lasers.size(); i++)
    {
        renderList.push_back(&lasers[i]->l->sprite);
        animationList.push_back(lasers[i]->l);
    }

    //cout << hintergrund << endl;

    // Hintergrundbild laden
    hintergrundLaden(name, hintergrund, hintergrundTextur);

    renderList.push_front(hintergrund);
}


// Leerer Konstruktor als Überladung
level::level(void)
{

}


level::level(string n)
{
    name = n;
}

level::~level(void)
{
    for(auto x : tueren)
    {
        delete x;
    }

    for(auto x : pfeile)
    {
        delete x;
    }

    for(auto x : schaetze)
    {
        delete x;
    }

}



void setzeMauer(int Id)
{
    cout << "Animationsende" << endl;
    return;
}


level *levelLaden(string n)
{
    // Level neu laden oder bereits gefunden?
    unordered_map<string, level*>::const_iterator suche = levelListe.find(n);

    if(suche == levelListe.end())
    {



        // Nicht gefunden -> Neu laden
        level *l = new level(n);
        l->name = n;
        l->loadFromFile();
        l->collisionsActivated = true;

        levelListe[n] = l;
        cerr << "Neues Level erstellen: " << n << "   Neue Anzahl: " << levelListe.size() << endl;


        return l;
    }
    else
    {
        cerr << "Level bereits erstellt: " << n << endl;

        // gefunden: -> altes zurückgeben
        return levelListe[n];
    }
}
