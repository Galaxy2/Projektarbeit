#include <iostream>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"

using namespace std;

sf::Font standardSchriftart;
benachrichtigung debugMsg("Debug Mode", 25, 80, 20);
benachrichtigung debugMsg2("Debug Mode", 25, 110, 20);

sf::RenderWindow* globalFenster;



sf::Vector2f koordinaten(int x, int y )
{
    sf::Vector2i pos(x, y);
    return globalFenster->mapPixelToCoords(pos);
}





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



    // Fenster und Grafik

    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();



#ifndef LINUX
    sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::None);
#else
    sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::Fullscreen);
#endif

    globalFenster = &fenster;
    fenster.setFramerateLimit(50);

    sf::Vector2u fensterGroesse = fenster.getSize();
    float factor =  1920.0f / fensterGroesse.x;

    sf::View ansicht(sf::FloatRect(0,0, aufloesung.width, aufloesung.height));
    //ansicht.zoom(1.5);

    ansicht.setViewport(sf::FloatRect(0,0, 1, 1));
    fenster.setView(ansicht);


    // AnimationList vorbereiten
    list<animation *> animationList;

    // Renderlist vorbereiten
    list<sf::Drawable *> renderList;


    // Level laden!
    level demoLevel;

    // Level hier anpassen
    string levelName = "test";

    string levelDateiName = "levels/" + levelName + "/" + levelName + ".lvl";
    demoLevel.loadFromFile(levelDateiName);


    // Hintergrundbild laden
    sf::Texture hintergrundTextur;
    sf::Sprite hintergrund;
    hintergrundLaden(levelName, hintergrund, hintergrundTextur);
    renderList.push_front(&hintergrund);


    // Schriftart laden!
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");

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
    spieler.setPosition(310, 10);
    spieler.setOrigin(sf::Vector2f(50, 50));

    // Spieler immer anzeigen!
    renderList.push_back(&spieler);


    debugMsg.updateText("Game running in Debug Mode!");

    // Konsole!
    console::eingabeFeld.setFont(standardSchriftart);
    console::eingabeFeld.setColor(sf::Color::Red);
    console::eingabeFeld.setCharacterSize(20);

    renderList.push_back((sf::Drawable *)&console::eingabeFeld);

    // Test: Pfeilanimation
    animation pfeil("resources/pfeil", 8, 0.05, 525, 20);
    pfeil.sprite.setScale(0.5, 0.5);
    pfeil.sprite.setRotation(90);
    renderList.push_back(&pfeil.sprite);
    animationList.push_back(&pfeil);


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

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
                {
                    zoom -= 0.05;
                    ansicht.zoom(zoom);
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
                {
                    zoom += 0.05;
                    ansicht.zoom(zoom);
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
            else
            if(befehl == "toggleWalls")
            {
                demoLevel.collisionsActivated = (!demoLevel.collisionsActivated);
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

        sf::Sprite tuereGeschlossen();
       // renderList.push_back(&tuereGeschlossen)

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

    return 0;
}
