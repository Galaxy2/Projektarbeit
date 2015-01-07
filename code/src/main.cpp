#include <iostream>
#include <sstream>
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <vector>
#include <list>
#include <unordered_map>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"


using namespace std;

sf::Font standardSchriftart;
benachrichtigung debugMsg("Debug Mode", 25, 80, 20);
benachrichtigung debugMsg2("Debug Mode", 25, 110, 20);

sf::RenderWindow* globalFenster;

//Musik
sf::Music musik; //sound.cpp // Zeile 117

// Levelliste erstellen
unordered_map<string, level*> levelListe;
level *aktuellesLevel;

// Zeit und Spiel
sf::Clock Uhr;
game spiel;


int main(void)
{
    // Update Überprüfung
    stringstream updateVerfuegbarText;
    updateVerfuegbarText << "Robber " << ROBBER_VERSION;

    if(newVersionAvailable())
    {
        cout << endl << "! Es steht eine Aktualisierung des Spiels zum Herunterladen bereit !" << endl << endl;
        updateVerfuegbarText << " (Update verfuegbar: " << LATEST_VERSION << " )";
    }
    else
    {
        cout << endl << "Das Spiel läuft in der aktuellsten Version!" << endl << endl;
    }

    // Fenster- und Grafikeinstellungen
    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();

    // Musik loopen!
    musik.setLoop(true);

#ifndef LINUX
    sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::None);
#else
    sf::RenderWindow  fenster(aufloesung, "Robber", sf::Style::Fullscreen);
#endif

    globalFenster = &fenster;
    fenster.setFramerateLimit(50);
    fenster.setVerticalSyncEnabled(true);

    // Das Spiel starten!

    sf::View ansicht(sf::FloatRect(0,0, aufloesung.width, aufloesung.height));

    ansicht.setViewport(sf::FloatRect(0,0, 1, 1));
    fenster.setView(ansicht);

    // AnimationList vorbereiten
    list<animation *> animationList;

    // Renderlist vorbereiten
    list<sf::Drawable *> renderList;

    // Hintergrundbild
    sf::Texture* hintergrundTextur = 0x0;
    sf::Sprite* hintergrund = 0x0;

    // Schriftart laden!
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");

    // Level hier anpassen
    aktuellesLevel = levelLaden("hauptmenu");
    aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

    // Version im Spiel anzeigen!
    benachrichtigung version(updateVerfuegbarText.str(), 25, 25, 20);
    renderList.push_back((sf::Drawable *)&version.text);

    // DebugMsg anzeigen!
    renderList.push_back((sf::Drawable *)&debugMsg.text);

    // DebugMsg2 anzeigen!
    renderList.push_back((sf::Drawable *)&debugMsg2.text);


    benachrichtigung zeit("Zeit", 25, 150, 20);
    if(aktuellesLevel->name != "hauptmenu" && aktuellesLevel->name != "gameOver")
    {
        renderList.push_back((sf::Drawable *)&zeit.text);
    }

    //Punkte
    benachrichtigung anzahlPunkte("0 Punkte", 25, 125, 20);
    if(aktuellesLevel->name != "hauptmenu" && aktuellesLevel->name != "gameOver")
    {
        renderList.push_back((sf::Drawable *)&anzahlPunkte.text);
    }

    debugMsg.updateText("Game running in Debug Mode!");

    benachrichtigung schall("Lärm", 25, 175, 20);
    if(aktuellesLevel->name != "hauptmenu" && aktuellesLevel->name != "gameOver")
    {
        renderList.push_back((sf::Drawable *)&schall.text);
    }

    // Konsole!
    console::eingabeFeld.setFont(standardSchriftart);
    console::eingabeFeld.setColor(sf::Color::Red);
    console::eingabeFeld.setCharacterSize(20);

    renderList.push_back((sf::Drawable *)&console::eingabeFeld);


    sf::Texture spielerTexture;
    sf::Sprite spieler;
    spielerTexture.loadFromFile("resources/spieler.png");
    spieler.setTexture(spielerTexture);
    spieler.setScale(0.5, 0.5);
    spieler.setOrigin(sf::Vector2f(50, 50));
    //cerr << aktuellesLevel->spielerPosition.x << "|" << aktuellesLevel->spielerPosition.y << endl;
    spieler.setPosition(aktuellesLevel->spielerPosition);

    // Spieler immer anzeigen!
    renderList.push_back(&spieler);

    //dunkles Fenster um den Spieler
    sf::Texture dunkelTextur;
    sf::Sprite dunkel;
    dunkelTextur.loadFromFile("resources/Dunkel.png");
    dunkel.setTexture(dunkelTextur);
    dunkel.setOrigin(960, 540);//Zentrum der Dunkelheit ist auf dem Spieler
    dunkel.setPosition(spieler.getPosition());

    // Schallpegel! Zuerst 0
    float schallPegel = 0;

    sf::Vector2i schallPosition(25, 25); // standardposition (ist nicht wichtig)
    int sX =  fenster.mapPixelToCoords(schallPosition).x;
    int sY =  fenster.mapPixelToCoords(schallPosition).y;
    animation schallAnimation("resources/schall", 11, false, false, true, 1, sX, sY);//erschaffe Animation
    schallAnimation.sprite.setOrigin(75,75);// Mitte des Bildes ist Zentrum
    //animation wird hizugefügt. Muss nicht wiederholt werden.
    animationList.push_back(&schallAnimation);

    // Zoombegrenzung
    int zoomLevel = 0;

    // Input delay
    sf::Clock verzoegerung;

    // Musik
    string vorherigesLevel = "hauptmenu";
    hintergrundMusik("hauptmenu");

    // rand initialisieren
    srand(time(0x0));

    // Solange das Fenster geöffnet ist
    while(fenster.isOpen())
    {
        // Levelcheck
        if(aktuellesLevel->name != vorherigesLevel)
        {
            if(aktuellesLevel->name == "hauptmenu")
            {
                hintergrundMusik("hauptmenu");
            }

            else if(aktuellesLevel->name == "gameOver")
            {
                hintergrundMusik("gameover");
            }

            else
            {
                hintergrundMusik("main");
            }

            vorherigesLevel = aktuellesLevel->name;
        }

        // Eingabeüberprüfung!
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // \todo Nächstes Level Laden
            spiel.punkte = 0;
            aktuellesLevel = levelLaden("hauptmenu");
            aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

            // Spieler in die hauptmenu Level positionieren
            spieler.setPosition(200, 300);

            // Den Spieler wieder anzeigen
            renderList.push_back(&spieler);
            renderList.push_back((sf::Drawable *)&version.text);
            renderList.push_back((sf::Drawable *)&debugMsg.text);
            renderList.push_back((sf::Drawable *)&debugMsg2.text);
            renderList.push_back((sf::Drawable *)&console::eingabeFeld);
        }

        // Kollisionsdetektion
        sf::FloatRect spielerEcken = spieler.getGlobalBounds();

        // Zoom erneut auf 1 setzen
        float zoom = 1.0f;

        // Input loop

        // Nur wenn Konsole nicht aktiviert!
        if(!console::activated)
        {
            if(aktuellesLevel->name != "gameOver")
            {
                //rennen: doppelt so schnell, dafür aber laut
                int s;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    s = 10;
                }
                else
                {
                    s = 5;
                }

                // Nur in eine Richtung auf einmal!
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    // Zuerst Kollision überprüfen!
                    spielerEcken.top -= s;

                    if(s == 10 && aktuellesLevel->dunkel)
                        schallPegel += 0.05;// schallpegel wird höher beim rennen

                    if(aktuellesLevel->checkCollision(spielerEcken))
                    {
                        // Nicht bewegen!
                        spielerEcken.top += s;
                    }
                    else
                    {
                        // Bewegen!
                        spieler.setRotation(0);
                        spieler.move(0, -s);
                    }

                }

                else

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        spielerEcken.left-=s;

                        if(s == 10 && aktuellesLevel->dunkel)
                        schallPegel += 0.05;// schallpegel wird höher beim rennen

                        if(aktuellesLevel->checkCollision(spielerEcken))
                        {
                            spielerEcken.left +=s;
                        }
                        else
                        {
                            spieler.setRotation(270);
                            spieler.move(-s, 0);
                        }
                    }

                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        {
                            // Zuerst Kollision überprüfen!
                            spielerEcken.top += s;

                            if(s == 10 && aktuellesLevel->dunkel)
                            schallPegel += 0.05;// schallpegel wird höher beim rennen

                            if(aktuellesLevel->checkCollision(spielerEcken))
                            {
                                // Nicht bewegen!
                                spielerEcken.top -= s;
                            }
                            else
                            {
                                // Bewegen!
                                spieler.setRotation(180);
                                spieler.move(0, s);
                            }

                        }

                        else

                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                            {
                                spielerEcken.width +=s;

                                if(s == 10 && aktuellesLevel->dunkel)
                                schallPegel += 0.05;// schallpegel wird höher beim rennen

                                if(aktuellesLevel->checkCollision(spielerEcken))
                                {
                                    spielerEcken.width -=s;
                                }
                                else
                                {
                                    spieler.setRotation(90);
                                    spieler.move(s, 0);
                                }

                            }

                if(aktuellesLevel->checkCollision(spielerEcken))
                {
                    spieler.move(5, 5);
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
                {
                    if(zoomLevel > -10)
                    {
                        zoom -= 0.05;
                        zoomLevel--;
                        ansicht.zoom(zoom);
                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
                {
                    if(zoomLevel < 10)
                    {
                        zoom += 0.05;
                        zoomLevel++;
                        ansicht.zoom(zoom);
                    }
                }
                dunkel.setPosition(spieler.getPosition());
            }




            if(aktuellesLevel->name == "hauptmenu")
            {
                sf::FloatRect spielEnde;
                spielEnde = sf::FloatRect(50, 400, 370, 60);

                if(spielEnde.intersects(spielerEcken))
                {
                    fenster.close();
                }
            }

            if(aktuellesLevel->checkCollisionPfeile(spielerEcken) != -1)
            {
                int pfeilNummer = aktuellesLevel->checkCollisionPfeile(spielerEcken);

                // Lese x/y Koordinaten heraus, bevor sie verworfen werden!
                float spielerX = aktuellesLevel->pfeile[pfeilNummer]->nX;
                float spielerY = aktuellesLevel->pfeile[pfeilNummer]->nY;

                cerr << "Teleport von: " << aktuellesLevel->name << " zu " << aktuellesLevel->deckeName << endl;

                aktuellesLevel = levelLaden(aktuellesLevel->deckeName); //setze neuen Namen
                aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Spieler an die dem i-ten Pfeil zugehörigen Position im neuen Level positionieren
                spieler.setPosition(spielerX, spielerY);

                if(aktuellesLevel->dunkel)
                {
                    renderList.push_back(&dunkel);
                    renderList.push_back(&schallAnimation.sprite);
                    schallPegel = 0; // zurücksetzen
                }

                renderList.push_back(&spieler);
                renderList.push_back((sf::Drawable *)&zeit.text);
                renderList.push_back((sf::Drawable *)&anzahlPunkte.text);
                renderList.push_back((sf::Drawable *)&version.text);
                renderList.push_back((sf::Drawable *)&debugMsg.text);
                renderList.push_back((sf::Drawable *)&debugMsg2.text);
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);
                Uhr.restart();

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && verzoegerung.getElapsedTime().asSeconds() > 0.2)
            {
                int schaetzeNummer = aktuellesLevel->checkCollisionSchaetze(spielerEcken);
                if(schaetzeNummer != -1 && aktuellesLevel->schaetze[schaetzeNummer]->s->istBeendet() && !aktuellesLevel->schaetze[schaetzeNummer]->eingesammelt)
                {
                    renderList.remove(&aktuellesLevel->schaetze[schaetzeNummer]->s->sprite);
                    aktuellesLevel->schaetze[schaetzeNummer]->eingesammelt = true;
                    spiel.punkteHinzufuegen(10);
                }

                int tuereNummer = aktuellesLevel->checkCollisionTuere(spielerEcken);
                if(tuereNummer != -1 && aktuellesLevel->tueren[tuereNummer]->t->istBeendet())
                {
                    schallPegel += 1; //Wenn tuere aufgeht ist es laut

                    float Ux = aktuellesLevel->tueren[tuereNummer]->posX;
                    float Uy = aktuellesLevel->tueren[tuereNummer]->posY;
                    cout << aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation() << endl;

                    // Fall 1: Rotation der Türe: 0°
                    if(aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation() == 0)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                        }
                    }
                    else if((aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation())-360 == -90)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                        }
                    }

                    else if(aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation()-360 == -180)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                        }
                    }

                    else if(aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation()-360 == -270)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                        }
                    }

                    // Animation abspielen
                    aktuellesLevel->tueren[tuereNummer]->t->setRichtung(aktuellesLevel->tueren[tuereNummer]->offen);
                    aktuellesLevel->tueren[tuereNummer]->t->start();
                    aktuellesLevel->tueren[tuereNummer]->offen = !aktuellesLevel->tueren[tuereNummer]->offen;
                }

                verzoegerung.restart();
            }
        }

        if(!console::activated && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            if(!console::activated)
            {
                showConsole();
            }

        }


        if(console::activated && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            string befehl = console::eingabeText.str();

            cout << "Ausfuehren: '" << befehl << "'" << endl;

            if(befehl == "9990")
            {
                debugMsg2.updateText("----- LOL -----");
            }
            else if(befehl == "toggleWalls")
            {
                aktuellesLevel->collisionsActivated = (!aktuellesLevel->collisionsActivated);
            }
            else if(befehl.find("loadLevel ") == 0)
            {
                aktuellesLevel->name = befehl.substr(befehl.find("loadLevel ") + 10);
                aktuellesLevel = levelLaden(aktuellesLevel->name);

                cerr << "Lade: '" << aktuellesLevel->name << "'" << endl;
                aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Neue Spielerposition setzen!
                spieler.setPosition(aktuellesLevel->spielerPosition);

                // Den Spieler wieder anzeigen
                if(aktuellesLevel->dunkel)
                {
                    renderList.push_back(&dunkel);
                    renderList.push_back(&schallAnimation.sprite);
                    schallPegel = 0; // zurücksetzen
                }

                renderList.push_back(&spieler);
                renderList.push_back((sf::Drawable *)&zeit.text);
                renderList.push_back((sf::Drawable *)&anzahlPunkte.text);
                renderList.push_back((sf::Drawable *)&version.text);
                renderList.push_back((sf::Drawable *)&debugMsg.text);
                renderList.push_back((sf::Drawable *)&debugMsg2.text);
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);
                Uhr.restart();
                schallPegel = 0;
            }

            hideConsole();
        }


        // Ende der Eingabeüberprüfung
        // Event Poll!

        sf::Event event;
        while(fenster.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                fenster.close();
            }

            else

                if(console::activated && event.type == sf::Event::TextEntered)
                {
                    // Wenn Konsole aktiviert, Eingabe lesen!
                    updateConsole(static_cast<char>(event.text.unicode));
                }
        }

        //weil es keinen animationsschritt über 10 gibt
        if(schallPegel > 10)
            schallPegel = 10;

        //Rationale Zahlen -> Ganze Zahlen
        int schallSchritt;
        schallSchritt = schallPegel;
        schallAnimation.zeigeSchritt(schallSchritt);

        // Ansicht anpassen!
        ansicht.setCenter(spieler.getPosition());
        fenster.setView(ansicht);

        // Fixe Elemente neu setzen
        sf::Vector2i versionPosition(25, 25);
        sf::Vector2i debugPosition(25, 50);
        sf::Vector2i debug2Position(25, 75);
        sf::Vector2i consolePosition(25, 100);
        sf::Vector2i zeitPosition(25, 125);
        sf::Vector2i anzahlPunktePosition(25, 150);

        version.text.setPosition(fenster.mapPixelToCoords(versionPosition));
        debugMsg.text.setPosition(fenster.mapPixelToCoords(debugPosition));
        debugMsg2.text.setPosition(fenster.mapPixelToCoords(debug2Position));
        console::eingabeFeld.setPosition(fenster.mapPixelToCoords(consolePosition));
        zeit.text.setPosition(fenster.mapPixelToCoords(zeitPosition));
        anzahlPunkte.text.setPosition(fenster.mapPixelToCoords(anzahlPunktePosition));

        //position des Schallmeters auf dem Bildschirm
        sf::Vector2i schallPosition(100, 600);
        float sX =  fenster.mapPixelToCoords(schallPosition).x;
        float sY =  fenster.mapPixelToCoords(schallPosition).y;
        schallAnimation.sprite.setPosition(sX, sY);

        // Animation Loop
        for(animation* a : animationList)
        {
            a->animationAusfuehren();
        }


        // Render loop
        fenster.clear();

        for(auto object : renderList)
        {
            fenster.draw(*object);
        }

        fenster.display();


        // Debugstring aktualisieren
        stringstream debugMsgText;
        debugMsgText << "Spielerposition: " << spieler.getPosition().x << ", " << spieler.getPosition().y;

        debugMsg.updateText(debugMsgText.str());


        // Punkte aktualisieren
        stringstream anzahlPunkteAnzeige;
        anzahlPunkteAnzeige << "Punkte: " << spiel.punkte;
        anzahlPunkte.updateText(anzahlPunkteAnzeige.str());

        //Wenn der Pegel im roten Bereich ist, ist nicht sofort gameOver sondern erst nach einer Zufallszeit
        int Zufall = rand() % 200;
        if(schallPegel >= 7 && Zufall == 199)
        {
            spiel.punkte = 0;
            cerr << "GAME OVER: GRUND 2" << endl;
            aktuellesLevel = levelLaden("gameOver"); // Wegen dem geht man GameOver ohne dass etwas passiert ist
            aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);
            hintergrund->setOrigin(0, 0);
            spieler.setPosition(960, 540);
            schallPegel = 0;

            renderList.push_back((sf::Drawable *)&console::eingabeFeld);
        }

        if(schallPegel > 0)
        {
            //Pegel nimmt mit der Zeit wieder ab
            schallPegel -= 0.005;
        }


        // Zeit aktualisieren
        int verbleibendeZeit;
        if(aktuellesLevel->Zeit.asSeconds() > -1) // t
        {
            verbleibendeZeit = aktuellesLevel->Zeit.asSeconds() - Uhr.getElapsedTime().asSeconds();

            if(aktuellesLevel->checkCollisionLaser(spielerEcken) == true ??!??! verbleibendeZeit == 0)
            {
                spiel.punkte = 0;
                schallPegel = 0;
                cerr << "GAME OVER: GRUND 1" << endl;
                aktuellesLevel = levelLaden("gameOver");
                aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);
                hintergrund->setOrigin(0, 0);
                spieler.setPosition(960, 540);

                //ansicht.setCenter(fenster.mapPixelToCoords(sf::Vector2i(960, 540)));
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);
            }

            stringstream zeitAnzeige;
            zeitAnzeige << "Zeit: " << verbleibendeZeit << " s";
            zeit.updateText(zeitAnzeige.str());
        }
        else
        {
            renderList.remove((sf::Drawable *)&zeit.text);

        }

        if(spiel.checkSieg())
        {
            spiel.punkte = 0;
            aktuellesLevel = levelLaden("hauptmenu");
            aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

            // Spieler in die hauptmenu Level positionieren
            spieler.setPosition(200, 300);

            // Den Spieler wieder anzeigen
            renderList.push_back(&spieler);
            renderList.push_back((sf::Drawable *)&version.text);
            renderList.push_back((sf::Drawable *)&debugMsg.text);
            renderList.push_back((sf::Drawable *)&debugMsg2.text);
            renderList.push_back((sf::Drawable *)&console::eingabeFeld);
        }
    }


    // Nach der Gameloop


    // Levels wieder freigeben!
    for(auto l: levelListe)
    {
        delete l.second;
    }


    // Meamleak Fix!
    if(hintergrundTextur != 0x0 && hintergrund != 0x0)
    {
        delete hintergrundTextur;
        delete hintergrund;
    }

    return 0;
}
