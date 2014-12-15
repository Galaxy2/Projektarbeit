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
    sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::Fullscreen);
#endif

    globalFenster = &fenster;
    fenster.setFramerateLimit(50);
    fenster.setVerticalSyncEnabled(true);

    hauptmenu:

    // Menü view
    sf::View menu(sf::FloatRect(0,0, aufloesung.width, aufloesung.height));

    menu.setViewport(sf::FloatRect(0,0, 1, 1));
    fenster.setView(menu);

    // Schriftart laden!
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");


    // Menüelemente
    sf::Texture robberLogoTexture;
    robberLogoTexture.loadFromFile("resources/robber.png");
    sf::Sprite robberLogo(robberLogoTexture);

    sf::Texture spielStartenTexture;
    spielStartenTexture.loadFromFile("resources/spielStarten.png");
    sf::Sprite spielStarten(spielStartenTexture);
    spielStarten.setPosition(50, 350);

    sf::Texture spielBeendenTexture;
    spielBeendenTexture.loadFromFile("resources/spielBeenden.png");
    sf::Sprite spielBeenden(spielBeendenTexture);
    spielBeenden.setPosition(50, 475);

    sf::Texture sfmlTexture;
    sfmlTexture.loadFromFile("resources/sfml.png");
    sf::Sprite sfml(sfmlTexture);
    sfml.setScale(0.5, 0.5);
    sfml.setPosition((aufloesung.width)*0.5, (aufloesung.height)*0.5);

    sf::Text statusBar("", standardSchriftart);
    statusBar.setPosition(10, aufloesung.height-50);
    statusBar.setCharacterSize(16);
    statusBar.setColor(sf::Color(100, 100, 100));
    sf::Clock statusBarClock;

    sf::Text info(updateVerfuegbarText.str(), standardSchriftart);
    info.setPosition(10, aufloesung.height-25);
    info.setCharacterSize(16);
    info.setColor(sf::Color(100, 100, 100));

    // Menüschleife
    bool startGame = false;
    while(!startGame)
    {
        // Beenden?
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            fenster.close();
            return 0;
        }

        // Klicks verarbeiten!
        sf::Event klick;
        while(fenster.pollEvent(klick))
        {
            if(klick.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mausPosition(klick.mouseMove.x, klick.mouseMove.y);

                if(spielStarten.getGlobalBounds().contains(mausPosition))
                {
                    statusBar.setString("Das Spiel starten!");
                    statusBarClock.restart();
                }
                else if(spielBeenden.getGlobalBounds().contains(mausPosition))
                {
                    statusBar.setString("Das Spiel beenden! :-(");
                    statusBarClock.restart();
                }
                else if(sfml.getGlobalBounds().contains(mausPosition))
                {
                    statusBar.setString("Dieses Spiel wurde in C++ mit der \"Simple and Fast Multimedia Library\" erstellt!");
                    statusBarClock.restart();
                }
            }

            if(klick.type == sf::Event::MouseButtonReleased && klick.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mausPosition(klick.mouseButton.x, klick.mouseButton.y);

                if(spielStarten.getGlobalBounds().contains(mausPosition))
                {
                    startGame = true;
                }
                else if(spielBeenden.getGlobalBounds().contains(mausPosition))
                {
                    fenster.close();
                    return 0;
                }
            }

        int zoomMenu = 0;
        float zoom = 1.0f;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
                {
                    if(zoomMenu > -10)
                    {
                        zoom -= 0.05;
                        zoomMenu--;
                        menu.zoom(zoom);
                        }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
                {
                    if(zoomMenu < 10)
                    {
                        zoom += 0.05;
                        zoomMenu++;
                        menu.zoom(zoom);
                    }
                }
        }

        // StatusBar nach 2 Sekunden wieder leeren! :)
        if(statusBarClock.getElapsedTime().asSeconds() > 2)
            statusBar.setString("");


        // Fenster neu zeichnen
        fenster.clear();

        fenster.draw(robberLogo);
        fenster.draw(spielStarten);
        fenster.draw(spielBeenden);
        fenster.draw(sfml);
        fenster.draw(info);
        fenster.draw(statusBar);
        fenster.display();
    }




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

    // Level hier anpassen
    demoLevel.name = "testDecke"; // Todo: Konstruktor erstellen!
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

    // Solange das Fenster geöffnet ist
    while(fenster.isOpen())
    {
        // Eingabeüberprüfung!
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            fenster.close();
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


            if(demoLevel.checkCollisionPfeile(spielerEcken) != -1)
            {
                int pfeilNummer = demoLevel.checkCollisionPfeile(spielerEcken);
                demoLevel.name = demoLevel.deckeName; //setze  neuen Namen
                demoLevel.loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Spieler an die dem i-ten Pfeil zugehörigen Position im neuen Level positionieren
                spieler.setPosition(demoLevel.pfeile[pfeilNummer]->nX, demoLevel.pfeile[pfeilNummer]->nY);

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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
                goto hauptmenu;

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
                    // Geschlossen -> Offen
  /* ges -> off */  if(demoLevel.tueren[tuereNummer]->offen)
  /* ges -> off */  {
                        cout << "Türe geschlossen -> offen\n";
                        cout << "x: " << demoLevel.tueren[tuereNummer]->posX << "  y: " << demoLevel.tueren[tuereNummer]->posY;


                        // Fall 1: Rotation der Türe: 0°
                        if(demoLevel.tueren[tuereNummer]->t->sprite.getRotation() == 0)
                        {
                            // Der Punkt U ist das Rotationszentrum der Türe
                            float Ux = demoLevel.tueren[tuereNummer]->posX;
  /* ges -> off */          float Uy = demoLevel.tueren[tuereNummer]->posY;

                            // Der 1. Türenpunkt nach der Rotation (T1')
                            float T1x = Ux - 14;
                            float T1y = Uy - 200;

                            demoLevel.mauern.remove(sf::FloatRect(demoLevel.tueren[tuereNummer]->posX, demoLevel.tueren[tuereNummer]->posY+179-200, 200, 14));
                            demoLevel.mauern.push_back(sf::FloatRect(T1x, T1y, 14, 200));
                        }

  /* ges -> off */  }

                    else

                    {
                        // Der Punkt U ist das Rotationszentrum der Türe
                        float Ux = demoLevel.tueren[tuereNummer]->posX;
  /* off -> ges */      float Uy = demoLevel.tueren[tuereNummer]->posY;

                        // Der 1. Türenpunkt nach der Rotation (T1')
                        float T1x = Ux - 14;
                        float T1y = Uy - 200;

  /* off -> ges */      cout << "Türe offen -> geschlossen\n";
                        demoLevel.mauern.remove(sf::FloatRect(T1x, T1y, 14, 200));
  /* off -> ges */      demoLevel.mauern.push_back(sf::FloatRect(Ux, Uy+179-200, 200, 14));
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
