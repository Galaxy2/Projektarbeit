#include <iostream>
#include <SFML/Window.hpp>

int main(void)
{
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
