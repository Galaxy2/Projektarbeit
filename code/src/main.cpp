#include <iostream>
#include <SFML/Window.hpp>

int main(void)
{
    sf::Window fenster(sf::VideoMode(1024, 768), "Robber", sf::Style::Fullscreen);

    // Solange das Fenster geöffnet ist
    while(fenster.isOpen())
    {
        sf::Event event;
        fenster.pollEvent(event);

        if(event.type == sf::Event::Closed){
            fenster.close();
        }
    }

    // Input Loop
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        fenster.close();
    }


    return 0;
}
