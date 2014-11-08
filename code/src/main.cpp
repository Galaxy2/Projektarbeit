#include <iostream>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"

using namespace std;

sf::Font standardSchriftart;
benachrichtigung debugMsg("Debug Mode", 25, 80, 20);


sf::RenderWindow* globalFenster;

sf::Vector2f koordinaten(int x, int y){
    sf::Vector2i pos(x, y);
    return globalFenster->mapPixelToCoords(pos);
}



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



    // Fenster und Grafik

    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();



    #ifndef LINUX
        sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::None);
    #else
        sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::Fullscreen);
    #endif

    globalFenster = &fenster;


    sf::Vector2u fensterGroesse = fenster.getSize();
    float factor =  1920.0f / fensterGroesse.x;

    sf::View ansicht(sf::FloatRect(0,0, aufloesung.width, aufloesung.height));
    ansicht.zoom(factor);

    ansicht.setViewport(sf::FloatRect(0,0, 1, 1));
    fenster.setView(ansicht);



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
    renderList.push_back((sf::Drawable *)&debugMsg.text);

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


    debugMsg.test();
    debugMsg.updateText("Debug Mode!");



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

        // Input loop
        // Nur in eine Richtung auf einmal!
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


        // Ende der Eingabeüberprüfung
        // Event Poll!

        sf::Event event;
        while(fenster.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                fenster.close();
            }

        }



        // Mauer Debug
        sf::RectangleShape demoMauer;
        renderList.push_back(&demoMauer);

        demoMauer.setPosition(demoLevel.mauern.front().left, demoLevel.mauern.front().top);

        sf::Vector2f groesse(demoLevel.mauern.front().width, demoLevel.mauern.front().height);
        demoMauer.setSize(groesse);
        demoMauer.setFillColor(sf::Color::Green);


        // Ansicht anpassen!
        fenster.setView(ansicht);

        // Render loop
        fenster.clear();

        for(auto object : renderList){
            fenster.draw(*object);
        }

        fenster.display();

    }

    return 0;
}
