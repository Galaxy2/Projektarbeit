#include <iostream>
#include "gegenspieler.h"

gegenspieler::gegenspieler(float s)
{
    textur.loadFromFile("resources/gegenspieler.png");
    sprite.setTexture(textur);
    sprite.setScale(0.5, 0.5);
    sprite.setOrigin(50, 50);
    waypointNr = 0;
    speed = s;
    vorwaerts = true;
}


void gegenspieler::addWaypoint(sf::Vector2f *v)
{
    waypoints.push_back(v);
}


void gegenspieler::bewegen(void)
{
    if(waypointNr < waypoints.size()-1 && vorwaerts)
    {
        float deltaX = waypoints[waypointNr+1]->x - waypoints[waypointNr]->x;
        float deltaY = waypoints[waypointNr+1]->y - waypoints[waypointNr]->y;

        sprite.move(deltaX/speed, deltaY/speed);

        if(sprite.getPosition().x == waypoints[waypointNr+1]->x && sprite.getPosition().y == waypoints[waypointNr+1]->y)
        {
            waypointNr++;

            if(waypointNr == waypoints.size()-1)
            {
                vorwaerts = false;
            }
        }
    }
    else if(waypointNr > 0 && !vorwaerts)
    {
        float deltaX = waypoints[waypointNr-1]->x - waypoints[waypointNr]->x;
        float deltaY = waypoints[waypointNr-1]->y - waypoints[waypointNr]->y;

        sprite.move(deltaX/speed, deltaY/speed);

        if(sprite.getPosition().x == waypoints[waypointNr-1]->x && sprite.getPosition().y == waypoints[waypointNr-1]->y)
        {
            waypointNr--;

            if(waypointNr == 0)
            {
                vorwaerts = true;
            }
        }
    }
}


gegenspieler::~gegenspieler(void)
{
    // Waypoint-Vektoren löschen
    for(auto x : waypoints)
    {
        delete x;
    }
}

int gegenspieler::schrittAbstand(sf::FloatRect spielerPostion)
{
    float dx, dy, Abstand;
    dx = spielerPostion.top-sprite.getGlobalBounds().top;
    dy = spielerPostion.left - sprite.getGlobalBounds().left;
    Abstand = sqrt(dx*dx + dy*dy);
    cout << Abstand << endl;
    return Abstand;
}
