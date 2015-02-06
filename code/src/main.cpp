#include <iostream>
#include <sstream>
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <vector>
#include <list>
#include <unordered_map>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "main.h"


using namespace std;

sf::Font standardSchriftart;
benachrichtigung debugMsg("Debug Mode", 25, 80, 20);
benachrichtigung debugMsg2("Debug Mode", 25, 110, 20);

sf::RenderWindow* globalFenster;

//Musik
sf::Music musik; //sound.cpp // Zeile 117

// Levelliste erstellen
unordered_map<string, level*> levelListe;
level *aktuellesLevel;

// Zeit und Spiel
sf::Clock Uhr;
game spiel;


int main(void)
{
    // Update Überprüfung
    stringstream updateVerfuegbarText;
    updateVerfuegbarText << "Robber " << ROBBER_VERSION;

    if(newVersionAvailable())
    {
        // Neue Version verfügbar!
        cout << endl << "! Es steht eine Aktualisierung des Spiels zum Herunterladen bereit !" << endl << endl;
        updateVerfuegbarText << " (Update verfuegbar: " << LATEST_VERSION << " )";
    }
    else
    {
        // Keine neue Version verfügbar
        cout << endl << "Das Spiel läuft in der aktuellsten Version!" << endl << endl;
    }


    // Fenster- und Grafikeinstellungen
    sf::VideoMode aufloesung = sf::VideoMode::getDesktopMode();


    // Musik loopen!
    musik.setLoop(true);

// Fenster erstellen
#ifndef LINUX
    // Nur Windows

    sf::RenderWindow fenster(aufloesung, "Robber", sf::Style::None);

#else
    // Nur Linux

    sf::RenderWindow  fenster(aufloesung, "Robber", sf::Style::Fullscreen);

#endif

    // Fensterreferenz erstellen!
    globalFenster = &fenster;

    // Maximal 50 FPS
    fenster.setFramerateLimit(50);

    // vsync!
    fenster.setVerticalSyncEnabled(true);


    // SFML View erstellen!
    sf::View ansicht(sf::FloatRect(0,0, aufloesung.width, aufloesung.height));


    // Anzeigebereich festlegen
    ansicht.setViewport(sf::FloatRect(0,0, 1, 1));
    fenster.setView(ansicht);

    // AnimationList vorbereiten
    list<animation *> animationList;

    // Renderlist vorbereiten
    list<sf::Drawable *> renderList;

    // Hintergrundbild
    sf::Texture* hintergrundTextur = 0x0;
    sf::Sprite* hintergrund = 0x0;

    // Globale Schriftart laden!
    standardSchriftart.loadFromFile("resources/DejaVuSans.ttf");

    // Hauptmenü laden!
    aktuellesLevel = levelLaden("hauptmenu");
    aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

    // Version im Spiel anzeigen!
    benachrichtigung version(updateVerfuegbarText.str(), 25, 25, 20);
    renderList.push_back((sf::Drawable *)&version.text);

    // DebugMsg anzeigen!
    renderList.push_back((sf::Drawable *)&debugMsg.text);

    // DebugMsg2 anzeigen!
    renderList.push_back((sf::Drawable *)&debugMsg2.text);



    // Benachrichtigung für Zeit erstellen
    benachrichtigung zeit("Zeit", 25, 150, 20);

    // Zeit nur anzeigen, wenn man nicht im Hauptmenü und nicht "Game Over" ist
    if(aktuellesLevel->name != "hauptmenu" && aktuellesLevel->name != "gameOver")
    {
        renderList.push_back((sf::Drawable *)&zeit.text);
    }


    // Benachrichtigung für Punkte erstellen
    benachrichtigung anzahlPunkte("0 Punkte", 25, 125, 20);
    if(aktuellesLevel->name != "hauptmenu" && aktuellesLevel->name != "gameOver")
    {
        renderList.push_back((sf::Drawable *)&anzahlPunkte.text);
    }


    // Entwicklernachricht anzeigen
    debugMsg.updateText("Game running in Debug Mode!");


    // Benachrichtigung für Lärm erstellen
    benachrichtigung schall("Lärm", 25, 175, 20);
    if(aktuellesLevel->name != "hauptmenu" && aktuellesLevel->name != "gameOver")
    {
        renderList.push_back((sf::Drawable *)&schall.text);
    }


    // Konsole erstellen!
    console::eingabeFeld.setFont(standardSchriftart);
    console::eingabeFeld.setColor(sf::Color::Red);
    console::eingabeFeld.setCharacterSize(20);

    // Konsole anzeigen lassen!
    renderList.push_back((sf::Drawable *)&console::eingabeFeld);


    // Spielertextur laden!
    sf::Texture spielerTexture;
    sf::Sprite spieler;
    spielerTexture.loadFromFile("resources/spieler.png");

    // Spielertextur zuordnen
    spieler.setTexture(spielerTexture);

    // Textur auf 1/4 Fläche verkleinern
    spieler.setScale(0.5, 0.5);

    // Mitt des Spielers für sämtliche Rotationen (Rotation, Translation)
    spieler.setOrigin(sf::Vector2f(50, 50));

    // Spieler auf Startposition setzen
    spieler.setPosition(aktuellesLevel->spielerPosition);

    // Spieler immer anzeigen!
    renderList.push_back(&spieler);

    // Dunkles Fenster um den Spieler (für dunkle Levels)
    sf::Texture dunkelTextur;
    sf::Sprite dunkel;
    dunkelTextur.loadFromFile("resources/Dunkel.png");

    // Dunkeltextur zuordnen
    dunkel.setTexture(dunkelTextur);

    // Zentrum der Dunkelheit ist auf dem Spieler
    dunkel.setOrigin(960*2, 540*2);

    // Dunkelheit mitverschieben
    dunkel.setPosition(spieler.getPosition());


    // Schallpegel: Am Anfang = 0
    float schallPegel = 0;

    // Standardposition (ist nicht wichtig)
    sf::Vector2i schallPosition(25, 25);
    int sX =  fenster.mapPixelToCoords(schallPosition).x;
    int sY =  fenster.mapPixelToCoords(schallPosition).y;

    // Animation für Schallmesser erstellen
    animation schallAnimation("resources/schall", 11, false, false, true, 1, sX, sY);

    // Mitte des Bildes ist Zentrum
    schallAnimation.sprite.setOrigin(75,75);

    // Animation wird hizugefügt: Muss nicht wiederholt werden.
    animationList.push_back(&schallAnimation);

    // Zoombegrenzung
    int zoomLevel = 0;

    // Input delay
    sf::Clock verzoegerung;

    // Musik
    string vorherigesLevel = "hauptmenu";
    hintergrundMusik("hauptmenu");

    // rand initialisieren (Zufallsseed aus der Zeit lesen)
    srand(time(0x0));

    //Sound für Schritte
    sf::Sound schritt;
    sf::SoundBuffer schrittbuffer;
    schrittbuffer.loadFromFile("resources/sound/Schritte.wav");
    schritt.setBuffer(schrittbuffer);

    // Für die Schritte benötigt man eine Info ob sich der Spieler gerade bewegt oder nicht
    bool Wert = false;

    // Solange das Fenster geöffnet ist:
    while(fenster.isOpen())
    {
        // Hat sich das Level geändert?
        if(aktuellesLevel->name != vorherigesLevel)
        {
            // Je nach Level entsprechende Musik abspielen
            if(aktuellesLevel->name == "hauptmenu")
            {
                hintergrundMusik("hauptmenu");
            }

            else if(aktuellesLevel->name == "gameOver")
            {
                hintergrundMusik("gameover");
            }

            else
            {
                // Wenn weder Menü noch Gameover -> main Musik
                hintergrundMusik("main");
            }

            // Zum Überprüfen nächstes Mal
            vorherigesLevel = aktuellesLevel->name;
        }


        // Eingabeüberprüfung!
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // Bei Escape Hauptmenü laden
            // Gespeicherte Levels zurücksetzen
            for(auto l: levelListe)
            {
                cout << "Level '" << l.first << "' aus Speicher entfernt\n";
                delete l.second;
            }
            cout << "Alle " << levelListe.size() << " Level entfernt\n";
            levelListe.clear();


            // Punkte zurücksetzen
            spiel.punkte = 0;
            aktuellesLevel = levelLaden("hauptmenu");
            aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);


            // Spieler in die hauptmenu Level positionieren
            spieler.setPosition(520, 375);

            // Den Spieler wieder anzeigen
            renderList.push_back(&spieler);
            renderList.push_back((sf::Drawable *)&version.text);
            renderList.push_back((sf::Drawable *)&debugMsg.text);
            renderList.push_back((sf::Drawable *)&debugMsg2.text);
            renderList.push_back((sf::Drawable *)&console::eingabeFeld);
        }

        // Kollisionsdetektion
        sf::FloatRect spielerEcken = spieler.getGlobalBounds();

        // Zoom erneut auf 1 setzen
        float zoom = 1.0f;

        // Input loop

        // Nur wenn Konsole nicht aktiviert!
        if(!console::activated)
        {
            if(aktuellesLevel->name != "gameOver")
            {
                //rennen: doppelt so schnell, dafür aber laut
                int s;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    s = 10;
                    schritt.setPitch(2);
                }
                else
                {
                    s = 5;
                    schritt.setPitch(1);
                }

                // Nur in eine Richtung auf einmal!
                // Nach vorne
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    // Zuerst Kollision überprüfen!
                    spielerEcken.top -= s;

                    if(s == 10 && aktuellesLevel->dunkel)
                        schallPegel += 0.05;// schallpegel wird höher beim rennen

                    if(aktuellesLevel->checkCollision(spielerEcken))
                    {
                        // Nicht bewegen!
                        spielerEcken.top += s;
                        Wert = false;
                    }
                    else
                    {
                        // Bewegen!
                        spieler.setRotation(0);
                        spieler.move(0, -s);
                    }

                }

                else
                    // Nach links
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        spielerEcken.left-=s;

                        if(s == 10 && aktuellesLevel->dunkel)
                        schallPegel += 0.05;// schallpegel wird höher beim rennen

                        if(aktuellesLevel->checkCollision(spielerEcken))
                        {
                            spielerEcken.left +=s;
                            Wert = false;
                        }
                        else
                        {
                            spieler.setRotation(270);
                            spieler.move(-s, 0);
                        }
                    }
                    // Nach hinten
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        {
                            // Zuerst Kollision überprüfen!
                            spielerEcken.top += s;

                            if(s == 10 && aktuellesLevel->dunkel)
                            schallPegel += 0.05;// schallpegel wird höher beim rennen

                            if(aktuellesLevel->checkCollision(spielerEcken))
                            {
                                // Nicht bewegen!
                                spielerEcken.top -= s;
                                Wert = false;
                            }
                            else
                            {
                                // Bewegen!
                                spieler.setRotation(180);
                                spieler.move(0, s);
                            }

                        }

                        else
                            // Nach rechts
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                            {
                                spielerEcken.width +=s;

                                if(s == 10 && aktuellesLevel->dunkel)
                                schallPegel += 0.05;// schallpegel wird höher beim rennen

                                if(aktuellesLevel->checkCollision(spielerEcken))
                                {
                                    spielerEcken.width -=s;
                                    Wert = false;
                                }
                                else
                                {
                                    spieler.setRotation(90);
                                    spieler.move(s, 0);
                                }

                            }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true) &&
                   Wert == false)
                {
                    schritt.play();
                    schritt.setLoop(true);
                    Wert = true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) == false &&
                   sf::Keyboard::isKeyPressed(sf::Keyboard::S) == false &&
                   sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false &&
                   sf::Keyboard::isKeyPressed(sf::Keyboard::W) == false)
                {
                    Wert = false;
                    schritt.setLoop(false);
                }



                // Kollision überprüfen
                if(aktuellesLevel->checkCollision(spielerEcken))
                {
                    spieler.move(5, 5);
                }


                // Reinzoomen (Begrenzung beachten)
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
                {
                    if(zoomLevel > -10)
                    {
                        zoom -= 0.05;
                        zoomLevel--;
                        ansicht.zoom(zoom);
                    }
                }


                // Rauszoomen (Begrenzung beachten)
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
                {
                    if(zoomLevel < 10)
                    {
                        zoom += 0.05;
                        zoomLevel++;
                        ansicht.zoom(zoom);
                    }
                }



                // Dunkles Overlay wandert mit dem Spieler mit
                dunkel.setPosition(spieler.getPosition());
            }



            // "Spiel beenden"-Feld möglich machen
            if(aktuellesLevel->name == "hauptmenu")
            {
                sf::FloatRect spielEnde;
                spielEnde = sf::FloatRect(50, 400, 370, 60);

                // Beim Überschneiden -> Fenster schliessen, Schleife wird verlassen, Spiel beendet
                if(spielEnde.intersects(spielerEcken))
                {
                    fenster.close();
                }
            }



            // Auf Pfeile achten: -> Wenn ja, wohin Teleportieren?
            int pfeilNummer = aktuellesLevel->checkCollisionPfeile(spielerEcken);

            // Wenn mit Pfeil geschnitten
            if(pfeilNummer != -1)
            {
                if(aktuellesLevel->pfeile[pfeilNummer]->farbe != 0 || (aktuellesLevel->pfeile[pfeilNummer]->farbe == 0 && spiel.gewonnen == true))
                {
                    // Lese x/y Koordinaten heraus, bevor sie verworfen werden!
                    float spielerX = aktuellesLevel->pfeile[pfeilNummer]->nX;
                    float spielerY = aktuellesLevel->pfeile[pfeilNummer]->nY;

                    // Neues Level laden
                    aktuellesLevel = levelLaden(aktuellesLevel->pfeile[pfeilNummer]->nLevel); // neuer Level wird durch den jeweiligen Pfeil bestummen

                    // Neues Level anzeigen
                    aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                    // Spieler an die dem i-ten Pfeil zugehörigen Position im neuen Level positionieren
                    spieler.setPosition(spielerX, spielerY);

                    // Wenn das Level dunkel ist
                    if(aktuellesLevel->dunkel)
                    {
                        if(aktuellesLevel->Wert == 1)
                            dunkelTextur.loadFromFile("resources/DunkelDecke.png");
                        else
                            dunkelTextur.loadFromFile("resources/Dunkel.png");
                        renderList.push_back(&dunkel);
                        renderList.push_back(&schallAnimation.sprite);
                        schallPegel = 0; // zurücksetzen
                    }

                    // Spieler und Benachrichtigungen wieder anzeigen
                    renderList.push_back(&spieler);
                    renderList.push_back((sf::Drawable *)&zeit.text);
                    renderList.push_back((sf::Drawable *)&anzahlPunkte.text);
                    renderList.push_back((sf::Drawable *)&version.text);
                    renderList.push_back((sf::Drawable *)&debugMsg.text);
                    renderList.push_back((sf::Drawable *)&debugMsg2.text);
                    renderList.push_back((sf::Drawable *)&console::eingabeFeld);

                    // Zeit für das Level zurücksetzen
                    Uhr.restart();

                }
            }

            // Schätze einsammeln
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && verzoegerung.getElapsedTime().asSeconds() > 0.2)
            {
                int schaetzeNummer = aktuellesLevel->checkCollisionSchaetze(spielerEcken);
                if(schaetzeNummer != -1 && aktuellesLevel->schaetze[schaetzeNummer]->s->istBeendet() && !aktuellesLevel->schaetze[schaetzeNummer]->eingesammelt)
                {
                    renderList.remove(&aktuellesLevel->schaetze[schaetzeNummer]->s->sprite);
                    aktuellesLevel->schaetze[schaetzeNummer]->eingesammelt = true;
                    spiel.punkteHinzufuegen(10);
                }

                // Türe in der Nähe finden!
                int tuereNummer = aktuellesLevel->checkCollisionTuere(spielerEcken);

                // Türe nur öffnen wenn die, die in der Nähe ist, nicht gerade am Öffnen ist
                if(tuereNummer != -1 && aktuellesLevel->tueren[tuereNummer]->t->istBeendet())
                {
                    // Wenn tuere aufgeht ist es laut
                    schallPegel += 1;

                    float Ux = aktuellesLevel->tueren[tuereNummer]->posX;
                    float Uy = aktuellesLevel->tueren[tuereNummer]->posY;


                    // Neue Mauernkoordinaten berechnen!

                    // Fall 1: Rotation der Türe: 0°
                    if(aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation() == 0)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                        }
                    }
                    else if((aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation())-360 == -90)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-186, 14, 193));
                        }
                    }

                    else if(aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation()-360 == -180)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-186, Uy-7, 193, 14));
                        }
                    }

                    else if(aktuellesLevel->tueren[tuereNummer]->t->sprite.getRotation()-360 == -270)
                    {
                        if(aktuellesLevel->tueren[tuereNummer]->offen)//tuere geschlossen -> tuere offen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                        }
                        else //tuere offen -> türe geschlossen
                        {
                            aktuellesLevel->mauern.remove(sf::FloatRect(Ux-7, Uy-7, 193, 14));
                            aktuellesLevel->mauern.push_back(sf::FloatRect(Ux-7, Uy-7, 14, 193));
                        }
                    }

                    // Animation abspielen

                    aktuellesLevel->tueren[tuereNummer]->t->setRichtung(aktuellesLevel->tueren[tuereNummer]->offen);
                    aktuellesLevel->tueren[tuereNummer]->t->start();
                    aktuellesLevel->tueren[tuereNummer]->offen = !aktuellesLevel->tueren[tuereNummer]->offen;
                }

                // Zeit für Eingabeverzögerung zurücksetzen
                verzoegerung.restart();
            }
        }

        // Wenn die Konsole nocht nicht aktiviert ist -> Aktivieren wenn RShift gedrückt
        if(!console::activated && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            if(!console::activated)
            {
                showConsole();
            }

        }


        // Wenn die Konsole aber aktiviert ist
        if(console::activated && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            string befehl = console::eingabeText.str();

            // Debug: Befehl in der Kommandozeile ausgeben
            cout << "Ausfuehren: '" << befehl << "'" << endl;

            // Befehle auslesen
            if(befehl == "9990")
            {
                // 9990 cheat
                debugMsg2.updateText("----- LOL -----");
            }
            else if(befehl == "toggleWalls")
            {
                // Wände umschalten
                aktuellesLevel->collisionsActivated = (!aktuellesLevel->collisionsActivated);
            }
            else if(befehl.find("loadLevel ") == 0)
            {
                // Levelname auslesen
                aktuellesLevel->name = befehl.substr(befehl.find("loadLevel ") + 10);

                // Neues Level laden
                aktuellesLevel = levelLaden(aktuellesLevel->name);

                // Debugnachricht anzeigen
                cerr << "Lade: '" << aktuellesLevel->name << "'" << endl;

                // Level anzeigen
                aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

                // Neue Spielerposition setzen!
                spieler.setPosition(aktuellesLevel->spielerPosition);


                // Wenn es dunkel ist -> Overlay anzeigen
                if(aktuellesLevel->dunkel)
                {
                    renderList.push_back(&dunkel);
                    renderList.push_back(&schallAnimation.sprite);
                }

                // Spieler und Labels wieder anzeigen!
                renderList.push_back(&spieler);
                renderList.push_back((sf::Drawable *)&zeit.text);
                renderList.push_back((sf::Drawable *)&anzahlPunkte.text);
                renderList.push_back((sf::Drawable *)&version.text);
                renderList.push_back((sf::Drawable *)&debugMsg.text);
                renderList.push_back((sf::Drawable *)&debugMsg2.text);
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);

                // Uhr für Levelzeit neustarten
                Uhr.restart();
                schallPegel = 0;
            }
            else if(befehl == "dunkel")
            {
                renderList.remove(&dunkel);
            }
            else if(befehl == "exit")
            {
                fenster.close();
            }

            // Wenn "Enter" gedrückt und Befehl eingelesen -> Konsole zurücksetzen und verstecken
            hideConsole();
        }



        // Event Poll! (Fenster schliessen, etc.)
        sf::Event event;
        while(fenster.pollEvent(event))
        {
            // Schliessen per "Kreuzchen" (x)
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

        // Weil es keinen animationsschritt über 10 gibt -> Zurücksetzen
        if(schallPegel > 10)
            schallPegel = 10;

        // Mit static_cast<int>: float -> int
        schallAnimation.zeigeSchritt(static_cast<int>(schallPegel));

        // Ansicht anpassen! (Neu zentrieren)
        ansicht.setCenter(spieler.getPosition());
        fenster.setView(ansicht);

        // "Fixe" Benachrichtigungen neu setzen
        sf::Vector2i versionPosition(25, 25);
        sf::Vector2i debugPosition(25, 50);
        sf::Vector2i debug2Position(25, 75);
        sf::Vector2i consolePosition(25, 100);
        sf::Vector2i zeitPosition(25, 125);
        sf::Vector2i anzahlPunktePosition(25, 150);

        // Koordinatentransformation: Bildschirm -> Fenster
        version.text.setPosition(fenster.mapPixelToCoords(versionPosition));
        debugMsg.text.setPosition(fenster.mapPixelToCoords(debugPosition));
        debugMsg2.text.setPosition(fenster.mapPixelToCoords(debug2Position));
        console::eingabeFeld.setPosition(fenster.mapPixelToCoords(consolePosition));
        zeit.text.setPosition(fenster.mapPixelToCoords(zeitPosition));
        anzahlPunkte.text.setPosition(fenster.mapPixelToCoords(anzahlPunktePosition));

        // Position des Schallmessers auf dem Bildschirm
        sf::Vector2i schallPosition(100, 600);

        // Koordinatentransformation: Bildschirm -> Fenster
        float sX =  fenster.mapPixelToCoords(schallPosition).x;
        float sY =  fenster.mapPixelToCoords(schallPosition).y;

        // Schallmesser setzen
        schallAnimation.sprite.setPosition(sX, sY);


        // Animation Loop
        // = Alle Animationen ausführen, sodass das nächste Bild geladen wird
        for(animation* a : animationList)
        {
            a->animationAusfuehren();
        }


        // SFML: Fenster leeren!
        fenster.clear();

        for(auto object : renderList)
        {
            // Jedes Objekt anzeigen
            fenster.draw(*object);
        }

        // Fensterinhalt anzeigen
        fenster.display();


        // Debugstring aktualisieren
        stringstream debugMsgText;
        debugMsgText << "Spielerposition: " << spieler.getPosition().x << ", " << spieler.getPosition().y;

        debugMsg.updateText(debugMsgText.str());


        // Gegenspieler bewegen
        for(gegenspieler* g : aktuellesLevel->gegenspielers)
        {
            g->bewegen();
        }

        // Punkte aktualisieren
        stringstream anzahlPunkteAnzeige;
        anzahlPunkteAnzeige << "Punkte: " << spiel.punkte;
        anzahlPunkte.updateText(anzahlPunkteAnzeige.str());

        //Wenn der Pegel im roten Bereich ist, ist nicht sofort gameOver sondern erst nach einer Zufallszeit
        int Zufall = rand() % 200;
        if(schallPegel >= 7 && Zufall == 199)
        {
            // Punkte zurücksetzen
            spiel.punkte = 0;

            cerr << "GAME OVER: GRUND 2" << endl;

            // Neues Level laden und anzeigen
            aktuellesLevel = levelLaden("gameOver"); // Wegen dem geht man GameOver ohne dass etwas passiert ist
            aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);

            // Hintergrund neu positionieren
            hintergrund->setOrigin(0, 0);

            // Spieler in Mitte setzen
            spieler.setPosition(960, 540);

            // Schall zurücksetzen
            schallPegel = 0;

            // Konsole wieder anzeigen, nachdem renderListe geleert wurde
            renderList.push_back((sf::Drawable *)&console::eingabeFeld);
        }

        if(schallPegel > 0)
        {
            //Pegel nimmt mit der Zeit wieder ab
            schallPegel -= 0.005;
        }


        // Zeit aktualisieren
        int verbleibendeZeit;
        if(aktuellesLevel->Zeit.asSeconds() >= 0.5) // t
        {
            verbleibendeZeit = aktuellesLevel->Zeit.asSeconds() - Uhr.getElapsedTime().asSeconds();

            if(aktuellesLevel->checkCollisionLaser(spielerEcken) == true ??!??! verbleibendeZeit < 0)
            {
                spiel.punkte = 0;
                schallPegel = 0;
                cerr << "GAME OVER: GRUND 1" << endl;
                aktuellesLevel = levelLaden("gameOver");
                aktuellesLevel->loadToScreen(hintergrundTextur, hintergrund, renderList, animationList);
                hintergrund->setOrigin(0, 0);
                spieler.setPosition(960, 540);

                //ansicht.setCenter(fenster.mapPixelToCoords(sf::Vector2i(960, 540)));
                renderList.push_back((sf::Drawable *)&console::eingabeFeld);
            }

            stringstream zeitAnzeige;
            zeitAnzeige << "Zeit: " << verbleibendeZeit << " s";
            zeit.updateText(zeitAnzeige.str());
        }
        else
        {
            renderList.remove((sf::Drawable *)&zeit.text);

        }

        if(spiel.checkSieg() && spiel.gewonnen == false)
        {
            // Animationen nur einmal starten!
            spiel.gewonnen = true;
            anzahlPunkte.text.setColor(sf::Color::Green);

            //Pfeile sollen sich jetzt aktivieren!
            for(int i = 0; i<aktuellesLevel->pfeile.size(); i++)
            {
                if(aktuellesLevel->pfeile[i]->farbe == 0)
                    aktuellesLevel->pfeile[i]->p->start();
            }
        }
    }


    // Nach der Gameloop


    // Levels wieder freigeben!
    for(auto l: levelListe)
    {
        delete l.second;
    }


    // Meamleak Fix!
    if(hintergrundTextur != 0x0 && hintergrund != 0x0)
    {
        delete hintergrundTextur;
        delete hintergrund;
    }

    return 0;
}
