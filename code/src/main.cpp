#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"

using namespace std;

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

    // Version im Spiel anzeigen!
    sf::Font standardSchriftart;
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");


    sf::Text versionsText(updateVerfuegbarText.str(), standardSchriftart, 20);
    versionsText.setPosition(25, 25);

    // Fenster
    #ifndef LINUX
        sf::RenderWindow fenster(sf::VideoMode::getDesktopMode(), "Robber", sf::Style::None);
    #else
        sf::RenderWindow fenster(sf::VideoMode::getDesktopMode(), "Robber", sf::Style::Fullscreen);
    #endif

    // Hintergrundbild
    sf::Texture hintergrundTextur;
    sf::Sprite hintergrund;
    hintergrundLaden(hintergrund, hintergrundTextur);

    sf::Texture spielerTexture;
    sf::Sprite spieler;
    spielerTexture.loadFromFile("resources/spieler.png");
    spieler.setTexture(spielerTexture);
    spieler.setScale(0.5, 0.5);
    spieler.setPosition(700, 1000);

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


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                fenster.close();
            }


            // Input loop
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
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
                    spieler.move(0, -5);
                }

            }

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
                    spieler.move(0, 5);
                }

            }



            // Render loop
            fenster.draw(hintergrund);
            fenster.draw(versionsText);
            fenster.draw(spieler);
            fenster.display();


        }

    }

    return 0;
}
