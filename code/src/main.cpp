#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"
#include "screen.h"

using namespace std;

int main(void)
{
    // Update Überprüfung
    stringstream updateVerfuegbarText;
    updateVerfuegbarText << "Robber " << ROBBER_VERSION;

    if(newVersionAvailable()){
        cout << endl << "! Es steht eine Aktualisierung des Spiels zum Herunterladen bereit !" << endl << endl;
        updateVerfuegbarText << " (Update verfuegbar!)";
    } else {
        cout << endl << "Das Spiel läuft in der aktuellsten Version!" << endl << endl;
    }

    // Version im Spiel anzeigen!
    sf::Font standardSchriftart;
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");


    sf::Text versionsText(updateVerfuegbarText.str(), standardSchriftart, 20);
    versionsText.setPosition(25, 25);

    // Fenster
    sf::RenderWindow fenster(sf::VideoMode::getDesktopMode(), "Robber", sf::Style::None);

    // Hintergrundbild
    sf::Texture Hintergrund;
    sf::Sprite Hintergrundsprite;
    hintergrundLaden(Hintergrundsprite, Hintergrund);


    // Solange das Fenster geöffnet ist
    while(fenster.isOpen())
    {
        sf::Event event;
        while(fenster.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                fenster.close();
            }


            // Input Loop
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                fenster.close();
            }

            fenster.draw(Hintergrundsprite);
            fenster.draw(versionsText);
            //fenster.setActive();
            fenster.display();

        }

    }

    return 0;
}
