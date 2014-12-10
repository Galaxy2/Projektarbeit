#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class animation
{
public:
    int anzahlSchritte;
    int schritt;

    string name;
    std::vector<sf::Texture*> texturen;

    // Animationsparameter
    bool endlos;
    bool richtung;
    bool aktiv;

    float deltaT;
    sf::Clock t;
    sf::Sprite sprite;
    int Id;

    // Event callback pointers
    void (*animationEnde)(int);

    // Globale Funktionen
    void animationAusfuehren(void);
    void start(void);
    void stop(void);
    void setRichtung(bool vorwaerts);
    void zeigeSchritt(int k);
    bool istBeendet(void);
    void setOnAnimationEnde(void (*callback)(int));

    animation(string n, int N, bool endlos, bool start, bool vorwaerts, float dT, int x, int y);
    ~animation(void);
};


#endif // __ANIMATION_H__
