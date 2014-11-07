#include <iostream>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"

using namespace std;

sf::Font standardSchriftart;
// benachrichtigung debugMsg("", 25, 60, 20);

int main(void)
{
    // Update Überprüfung
    stringstream updateVerfuegbarText;
    updateVerfuegbarText << "Robber " << ROBBER_VERSION;

    if(newVersionAvailable()){
        cout << endl << "! Es steht eine Aktualisierung des Spiels zum Herunterladen bereit !" << endl << endl;
        updateVerfuegbarText << " (Update verfuegbar: " << LATEST_VERSION << " )";
    } else {
        cout << endl << "Das Spiel läuft in der aktuellsten Version!" << endl << endl;
    }

    // Fenster
    #ifndef LINUX
        sf::RenderWindow fenster(sf::VideoMode::getDesktopMode(), "Robber", sf::Style::None);
    #else
        sf::RenderWindow fenster(sf::VideoMode::getDesktopMode(), "Robber", sf::Style::Fullscreen);
    #endif

    // Renderlist vorbereiten
    list<sf::Drawable *> renderList;

    // Hintergrundbild
    sf::Texture hintergrundTextur;
    sf::Sprite hintergrund;
    hintergrundLaden(hintergrund, hintergrundTextur);
    renderList.push_front(&hintergrund);


    // Schriftart laden!
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");

    // Version im Spiel anzeigen!
    benachrichtigung version(updateVerfuegbarText.str(), 25, 25, 20);
    renderList.push_back((sf::Drawable *)&version.text);

    // DebugMsg anzeigen!
    //renderList.push_back((sf::Drawable *)&debugMsg.text);

    sf::Texture spielerTexture;
    sf::Sprite spieler;
    spielerTexture.loadFromFile("resources/spieler.png");
    spieler.setTexture(spielerTexture);
    spieler.setScale(0.5, 0.5);
    spieler.setPosition(300, 500);
    spieler.setOrigin(sf::Vector2f(50, 50));

    // Spieler immer anzeigen!
    renderList.push_back(&spieler);

    // Level laden!
    level demoLevel;


    demoLevel.loadFromFile("levels/test/test.lvl");

    sf::FloatRect spielerEcken = spieler.getGlobalBounds();

    // Solange das Fenster geöffnet ist
    while(fenster.isOpen())
    {
        sf::Event event;
        while(fenster.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                fenster.close();
            }

        }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                fenster.close();
            }


            // Input loop
            // Nur in eine Richtung auf einmal!
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                cout << "W" << endl;

                // Zuerst Kollision überprüfen!
                spielerEcken.top -= 5;
                if(demoLevel.checkCollision(spielerEcken))
                {
                    // Nicht bewegen!
                    spielerEcken.top += 5;
                }
                else
                {
                    // Bewegen!
                    spieler.setRotation(0);
                    spieler.move(0, -5);
                }

            }

            else

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                spielerEcken.width -=5;
                if(demoLevel.checkCollision(spielerEcken))
                {
                    spielerEcken.width +=5;
                }
                else
                {
                    spieler.setRotation(270);
                    spieler.move(-5, 0);
                }
            }

            else

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                // Zuerst Kollision überprüfen!
                spielerEcken.top += 5;
                if(demoLevel.checkCollision(spielerEcken))
                {
                    // Nicht bewegen!
                    spielerEcken.top -= 5;
                }
                else
                {
                    // Bewegen!
                    spieler.setRotation(180);
                    spieler.move(0, 5);
                }

            }

            else

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                spielerEcken.width +=5;
                if(demoLevel.checkCollision(spielerEcken))
                {
                    spielerEcken.width -=5;
                }
                else
                {
                    spieler.setRotation(90);
                    spieler.move(5, 0);
                }
            }


            // Mauer Debug
            sf::RectangleShape demoMauer;
            renderList.push_back(&demoMauer);

            demoMauer.setPosition(demoLevel.mauern.front().left, demoLevel.mauern.front().top);

            sf::Vector2f groesse(demoLevel.mauern.front().width, demoLevel.mauern.front().height);
            demoMauer.setSize(groesse);
            demoMauer.setFillColor(sf::Color::Green);


            // Render loop
            fenster.clear();

            for(auto object : renderList){
                fenster.draw(*object);
            }

            fenster.display();

    }

    return 0;
}
