#include <iostream>
#include <SFML/Window.hpp>

#include "main.h"

using namespace std;

int main(void)
{
    // Update Überprüfung
    if(newVersionAvailable()){
        cout << endl << "! Es steht eine Aktualisierung des Spiels zum Herunterladen bereit !" << endl << endl;
    } else {
        cout << endl << "Das Spiel läuft in der aktuellsten Version!" << endl << endl;
    }


    // Fenster
    sf::Window fenster(sf::VideoMode::getDesktopMode(), "Robber", sf::Style::Fullscreen);

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

            fenster.setActive();
            fenster.display();

        }

    }

    return 0;
}
