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
}


void gegenspieler::addWaypoint(sf::Vector2f *v)
{
    waypoints.push_back(v);
}


void gegenspieler::bewegen(void)
{
    if(waypointNr < waypoints.size()-1)
    {
        cerr << waypointNr << endl;

        float deltaX = waypoints[waypointNr+1]->x - waypoints[waypointNr]->x;
        float deltaY = waypoints[waypointNr+1]->y - waypoints[waypointNr]->y;

        sprite.move(deltaX/speed, deltaY/speed);

        cerr << sprite.getPosition().x << " =?= " << waypoints[waypointNr+1]->x << endl;
        cerr << sprite.getPosition().y << " =?= " <<  waypoints[waypointNr+1]->y << endl << "---------" << endl;
        if(sprite.getPosition().x == waypoints[waypointNr+1]->x && sprite.getPosition().y == waypoints[waypointNr+1]->y)
        {
            waypointNr++;
            cerr << "Neuer Waypoint erreicht: " << waypointNr << endl;
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
