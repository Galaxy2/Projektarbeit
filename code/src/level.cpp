#include <iostream>
#include <fstream>

??=include "level.h"
??=include "screen.h"
%:include "notification.h"


extern benachrichtigung debugMsg;


void level::loadFromFile(void)
{
    // Dateiname zusammensetzen
    string levelDateiName = "levels/" + name + "/" + name + ".lvl";

    // Datei öffnen (Fail -> Exception)
    fstream levelDatei(levelDateiName.c_str(), fstream::in);

    // Einlesen ob dunkel (= 1) oder hell (= 0)
    int dunkelInt;
    levelDatei >> dunkelInt;

    // direkt als bool einlesen funktioniet nicht?!
    if(dunkelInt == 0)
        dunkel = false;
    else
        dunkel = true;

    // Anzahl Mindestpunkte einlesen
    levelDatei >> minPunkte;

    // Spieler Spawn Position lesen!
    levelDatei >> spielerPosition.x >> spielerPosition.y;

    //Wert zum Angeben ob draussen( =1) oder drinnen( !=1) oder Hauptmenu( =2)
    levelDatei >> Wert;

    //Wert um anzugeben welche Punktezahl erreicht werden muss
    levelDatei >> Punkt;

    // Anzahl
    unsigned int N;

    // Anzahl Pfeile einlesen
    levelDatei >> N;
    unsigned int x, y, nX, nY, farbe;
    int r;
    string nLevel;
    for(unsigned int i=0; i<N; i++)
    {
        // Pfeilposition, Rotation, Teleportpunkt, Farbe einlesen
        levelDatei >> x >> y >> r >> nX >> nY >> farbe >> nLevel;

        pfeile.push_back(new pfeil);
        // 1 sagt, dass der Pfiel rot ist und somit tiefer ins haus hineinführt
        if(farbe == 1)
        {
            // Neue Animation für roten Pfeil erstellen
            pfeile[i]->p = (new animation("resources/pfeilRot", 8, true, true, true, 0.05, x, y)); //rote pfeile werden geladen
        }
        if(farbe == 2)
        {
            // Hauptmenüpfeil -> Andere Animation laden
            pfeile[i]->p = (new animation("resources/spielStarten", 1, true, false, false, 0.05, x, y)); // SpielStarten
        }
        if(farbe == 0)
        {
            // Neue Animation für grünen Pfeil erstellen
            pfeile[i]->p = (new animation("resources/pfeil", 8, true, false, true, 0.05, x, y));
        }

        // \todo In Konstruktor auslagern
        pfeile[i]->p->zeigeSchritt(0);
        pfeile[i]->p->sprite.setOrigin(100, 50);
        pfeile[i]->p->sprite.setRotation(r);
        pfeile[i]->p->Id = i;
        pfeile[i]->farbe = farbe;
        pfeile[i]->nLevel = nLevel;
        pfeile[i]->nX = nX;  //x-koordinate des Spielers im neuen Level
        pfeile[i]->nY = nY;  //y-koordinate des Spielers im neuen Level
    }


    // Anzahl Türen einlesen
    levelDatei >> N;
    for(unsigned int i=0; i<N; i++)
    {
        // Tür Position einlesen
        levelDatei >> x >> y >> r;

        // Neue Türe erstellen
        tueren.push_back(new tuere);

        // \todo Outsource in den Konstruktor
        // Neue Animation für die Türe erstellen
        tueren[i]->t = new animation("resources/tuere", 5, false, false, true, 0.05, x, y);
        tueren[i]->offen = true;
        tueren[i]->t->zeigeSchritt(0);
        tueren[i]->t->sprite.setOrigin(14, 186);
        tueren[i]->t->sprite.setRotation(r);
        tueren[i]->t->Id = i;
        tueren[i]->posX = x;
        tueren[i]->posY = y;
        tueren[i]->t->setOnAnimationEnde(&setzeMauer);

        // Mauern je nach Rotation einfügen
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
    ??<
        levelDatei >> x >> y >> r;

        schaetze.push_back(new schatz);
        schaetze??(i??)->s = new animation("resources/schatz", 1, false, false, true, 0.05, x, y, 2);

        // \todo Outsource
        schaetze??(i??)->s->zeigeSchritt(0);
        schaetze??(i??)->s->sprite.setOrigin(0,0);
        schaetze??(i??)->s->sprite.setRotation(r);
        schaetze??(i??)->s->Id = i;
    ??>


    // Anzahl Mauern einlesen
    levelDatei >> N;

    unsigned int x1, y1, x2, y2;
    for(unsigned int i=0; i<N; i++)
    {
        // 2 Punkte pro Mauer einlesen
        levelDatei >> x1 >> y1 >> x2 >> y2;

        sf::Vector2f koordinatenOben(x1, y1);
        sf::Vector2f koordinatenUnten(x2, y2);

        mauern.push_back(sf::FloatRect(koordinatenOben.x, koordinatenOben.y, koordinatenUnten.x-koordinatenOben.x, koordinatenUnten.y-koordinatenOben.y));
    }

    // Laser einlesen
    levelDatei >> N;
    for(unsigned int i=0; i<N; i++)
    {
        // Position und Rotation einlesen
        levelDatei >> x >> y >> r;

        lasers.push_back(new laser);

        // \todo Outsource
        lasers[i]->l = new animation("resources/laser", 14, true, true, true, 0.1, x, y);
        lasers[i]->l->zeigeSchritt(0);
        lasers[i]->l->sprite.setOrigin(0, 0);
        lasers[i]->l->sprite.setRotation(r);

    }


    // Verfügbare Zeit einlesen
    int t;
    levelDatei >> t;
    Zeit = sf::seconds(t);

    // Bei einem Lesefehler
    if(levelDatei.fail())
    {
        cerr << "Fehler beim Laden der Leveldatei: '" << levelDateiName << "'" << endl;
    }


    // Datei schliessen
    levelDatei.close();
}


int level::checkCollisionPfeile(sf::FloatRect& spielerPosition)
{
    // Kollision von Pfeilen überprüfen

    int k = 0;
    for(pfeil* P : pfeile)
    {
        if(P->p->sprite.getGlobalBounds().intersects(spielerPosition))
        {
            // Welcher Pfeil?
            return k;
        }

        k++;
    }

    // Keine Kollision
    return -1;
}


bool level::checkCollisionLaser(sf::FloatRect& spielerPosition)
{
    // Kollision von Lasern überprüfen

    for(laser* L : lasers)
    {
        if(L->l->sprite.getGlobalBounds().intersects(spielerPosition))
        {
            if(L->l->schritt > 5)
            {
                // Kollision entdeckt!
                return true;
            }
        }
    }

    // Keine Kollision
    return false;
}


int level::checkCollisionTuere(sf::FloatRect& spielerPosition)
{
    // Türen in der Nähe finden

    int k = 0;
    for(tuere* T : tueren)
    {
        // Pufferbereich um die Türe erstellen
        sf::FloatRect puffer;
        puffer = T->t->sprite.getGlobalBounds();

        puffer.height += 20;
        puffer.width += 20;
        puffer.left -= 10;
        puffer.top -= 10;

        if(puffer.intersects(spielerPosition))
        {
            // Welche Türe in der Nähe?
            return k;
        }

        k++;
    }

    // Keine Türe in der Nähe
    return -1;
}


bool level::checkCollision(sf::FloatRect& spielerPosition)
{
    // Kollision mit Mauern überprüfen

    // toggleWalls-Cheat!
    if(!collisionsActivated)
        return false;


    for(sf::FloatRect mauer : mauern)
    {
        if(mauer.intersects(spielerPosition))
        {
            // Kollision entdeckt!
            return true;
        }
    }

    // Keine Kollision
    return false;
}


int level::checkCollisionSchaetze(sf::FloatRect& spielerPosition)
{
    // Schätze in der Nähe finden

    int i = 0;
    for(schatz* S : schaetze)
    {
        if(S->s->sprite.getGlobalBounds().intersects(spielerPosition))
        {
            // Welcher Schatz?
            return i;
        }

        i++;
    }

    // Kein Schatz in der Nähe
    return -1;
}


void level::loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList)
{
    // Level in den Arbeitsspeicher laden!

    // Eventuelle alte Hintergrundbilder freigeben!
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

    // Hintergrundbild laden...
    hintergrundLaden(name, hintergrund, hintergrundTextur);

    // ...und anzeigen
    renderList.push_front(hintergrund);
}



level::level(void)
{
    // Leerer Konstruktor als Überladung -> macht nichts
    return;
}


level::level(string n)
{
    // Konstruktor mit Levelnamen -> Setzt Levelnamen
    name = n;
}



level::~level(void)
{
    // Destruktor um Speicher freizugeben

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
    // Leere Callbackfunktion
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

        // Kollisionen sind standardmässig aktiviert
        // \todo Outsource
        l->collisionsActivated = true;

        levelListe[n] = l;
        cerr << "Neues Level erstellen: " << n << "   Neue Anzahl: " << levelListe.size() << endl;

        return l;
    }
    else
    {
        // gefunden: -> altes zurückgeben
        cerr << "Level bereits erstellt: " << n << endl;
        return levelListe[n];
    }
}
