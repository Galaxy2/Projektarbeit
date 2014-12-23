#include <iostream>
#include <sstream>
#include <vector>
#include <list>
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

    // Level laden!
    level demoLevel;

    // Schriftart laden!
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");

    // Level hier anpassen
    demoLevel.name = "hauptmenu"; // Todo: Konstruktor erstellen!
    demoLevel.loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

    // Version im Spiel anzeigen!
    benachrichtigung version(updateVerfuegbarText.str(), 25, 25, 20);
    renderList.push_back((sf::Drawable *)&version.text);

    // DebugMsg anzeigen!
    renderList.push_back((sf::Drawable *)&debugMsg.text);

    // DebugMsg2 anzeigen!
    renderList.push_back((sf::Drawable *)&debugMsg2.text);


    sf::Texture spielerTexture;
    sf::Sprite spieler;
    spielerTexture.loadFromFile("resources/spieler.png");
    spieler.setTexture(spielerTexture);
    spieler.setScale(0.5, 0.5);
    spieler.setOrigin(sf::Vector2f(50, 50));
    spieler.setPosition(demoLevel.spielerPosition);

    // Spieler immer anzeigen!
    renderList.push_back(&spieler);


    debugMsg.updateText("Game running in Debug Mode!");

    // Konsole!
    console::eingabeFeld.setFont(standardSchriftart);
    console::eingabeFeld.setColor(sf::Color::Red);
    console::eingabeFeld.setCharacterSize(20);

    renderList.push_back((sf::Drawable *)&console::eingabeFeld);

    // Zoombegrenzung
    int zoomLevel = 0;

    // Musik
    string vorherigesLevel = "hauptmenu";
    hintergrundMusik("hauptmenu");

    // Solange das Fenster geöffnet ist
    while(fenster.isOpen())
    {
          // Levelcheck
        if(demoLevel.name != vorherigesLevel)
        {
            if(demoLevel.name == "hauptmenu")
            {
                hintergrundMusik("hauptmenu");
            }

            else if(demoLevel.name == "gameover")
            {
                hintergrundMusik("gameover");
            }

            else
            {
                hintergrundMusik("main");
            }

            vorherigesLevel = demoLevel.name;
        }


        // Eingabeüberprüfung!
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            demoLevel.name = "hauptmenu";
            demoLevel.loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Spieler an die dem i-ten Pfeil zugehörigen Position im neuen Level positionieren
                spieler.setPosition(200, 400);

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

            // Nur in eine Richtung auf einmal!
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                // Zuerst Kollision überprüfen!
                spielerEcken.top -= 10;
                if(demoLevel.checkCollision(spielerEcken))
                {
                    // Nicht bewegen!
                    spielerEcken.top += 10;
                }
                else
                {
                    // Bewegen!
                    spieler.setRotation(0);
                    spieler.move(0, -10);
                }

            }

            else

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    spielerEcken.left-=10;
                    if(demoLevel.checkCollision(spielerEcken))
                    {
                        spielerEcken.left +=10;
                    }
                    else
                    {
                        spieler.setRotation(270);
                        spieler.move(-10, 0);
                    }
                }

            else

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    // Zuerst Kollision überprüfen!
                    spielerEcken.top += 10;
                    if(demoLevel.checkCollision(spielerEcken))
                    {
                        // Nicht bewegen!
                        spielerEcken.top -= 10;
                    }
                    else
                    {
                        // Bewegen!
                        spieler.setRotation(180);
                        spieler.move(0, 10);
                    }

                }

            else

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    spielerEcken.width +=10;
                    if(demoLevel.checkCollision(spielerEcken))
                    {
                        spielerEcken.width -=10;
                    }
                    else
                    {
                        spieler.setRotation(90);
                        spieler.move(10, 0);
                    }

                }


            if(demoLevel.name == "hauptmenu")
            {
                sf::FloatRect spielEnde;
                spielEnde = sf::FloatRect(50, 400, 420, 460);

                if(spielEnde.intersects(spielerEcken))
                    {
                       fenster.close();
                    }
            }

            if(demoLevel.checkCollisionPfeile(spielerEcken) != -1)
            {
                int pfeilNummer = demoLevel.checkCollisionPfeile(spielerEcken);
                demoLevel.name = demoLevel.deckeName; //setze  neuen Namen

                // Lese x/y Koordinaten heraus, bevor sie verworfen werden!
                float spielerX = demoLevel.pfeile[pfeilNummer]->nX;
                float spielerY = demoLevel.pfeile[pfeilNummer]->nY;

                demoLevel.loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Spieler an die dem i-ten Pfeil zugehörigen Position im neuen Level positionieren
                spieler.setPosition(spielerX, spielerY);

                // Den Spieler wieder anzeigen
                renderList.push_back(&spieler);
                renderList.push_back((sf::Drawable *)&version.text);
                renderList.push_back((sf::Drawable *)&debugMsg.text);
                renderList.push_back((sf::Drawable *)&debugMsg2.text);
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);
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


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                int schaetzeNummer = demoLevel.checkCollisionSchaetze(spielerEcken);
                if(schaetzeNummer != -1 && demoLevel.schaetze[schaetzeNummer]->s->istBeendet())
                {
                    renderList.remove(&demoLevel.schaetze[schaetzeNummer]->s->sprite);
                }

                int tuereNummer = demoLevel.checkCollisionTuere(spielerEcken);
                if(tuereNummer != -1 && demoLevel.tueren[tuereNummer]->t->istBeendet())
                {
                    float Ux = demoLevel.tueren[tuereNummer]->posX;
                    float Uy = demoLevel.tueren[tuereNummer]->posY;
                    cout << demoLevel.tueren[tuereNummer]->t->sprite.getRotation() << endl;

                    // Fall 1: Rotation der Türe: 0°
                    if(demoLevel.tueren[tuereNummer]->t->sprite.getRotation() == 0)
                    {
                        if(demoLevel.tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                        }
                    }
                    else if((demoLevel.tueren[tuereNummer]->t->sprite.getRotation())-360 == -90)
                    {
                        if(demoLevel.tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                        }
                    }

                    else if(demoLevel.tueren[tuereNummer]->t->sprite.getRotation()-360 == -180)
                    {
                        if(demoLevel.tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                        }
                    }

                    else if(demoLevel.tueren[tuereNummer]->t->sprite.getRotation()-360 == -270)
                    {
                        if(demoLevel.tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            demoLevel.mauern.remove(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                            demoLevel.mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                        }
                    }

                    // Animation abspielen
                    demoLevel.tueren[tuereNummer]->t->setRichtung(demoLevel.tueren[tuereNummer]->offen);
                    demoLevel.tueren[tuereNummer]->t->start();
                    demoLevel.tueren[tuereNummer]->offen = !demoLevel.tueren[tuereNummer]->offen;
                }

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
                demoLevel.collisionsActivated = (!demoLevel.collisionsActivated);
            }
            else if(befehl.find("loadLevel ") == 0)
            {
                demoLevel.name = befehl.substr(befehl.find("loadLevel ") + 10);
                cerr << "Lade: '" << demoLevel.name << "'" << endl;
                demoLevel.loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Neue Spielerposition setzen!
                spieler.setPosition(demoLevel.spielerPosition);

                // Den Spieler wieder anzeigen
                renderList.push_back(&spieler);
                renderList.push_back((sf::Drawable *)&version.text);
                renderList.push_back((sf::Drawable *)&debugMsg.text);
                renderList.push_back((sf::Drawable *)&debugMsg2.text);
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);
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

        // Ansicht anpassen!
        ansicht.setCenter(spieler.getPosition());
        fenster.setView(ansicht);

        // Fixe Elemente neu setzen
        sf::Vector2i versionPosition(25, 25);
        sf::Vector2i debugPosition(25, 50);
        sf::Vector2i debug2Position(25, 75);
        sf::Vector2i consolePosition(25, 100);

        version.text.setPosition(fenster.mapPixelToCoords(versionPosition));
        debugMsg.text.setPosition(fenster.mapPixelToCoords(debugPosition));
        debugMsg2.text.setPosition(fenster.mapPixelToCoords(debug2Position));
        console::eingabeFeld.setPosition(fenster.mapPixelToCoords(consolePosition));

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

    }

    // Meamleak Fix!
    if(hintergrundTextur != 0x0 && hintergrund != 0x0)
    {
        delete hintergrundTextur;
        delete hintergrund;
    }

    return 0;
}
