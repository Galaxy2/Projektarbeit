#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>

#include "updates.h"


bool newVersionAvailable(void)
{
    sf::Http versionHttp("Galaxy2.github.io");
    sf::Http::Request versionRequest;
    versionRequest.setUri("Projektarbeit/version");

    sf::Http::Response versionResponse = versionHttp.sendRequest(versionRequest, sf::seconds(1));

    if(versionResponse.getStatus() == sf::Http::Response::ConnectionFailed || versionResponse.getBody() == ""){
        std::cout << "Verbindungsfehler beim Überprüfen auf Aktualisierungen!";
        return false;
    }

    std::cout << "Lokale Version:     " << ROBBER_VERSION << std::endl;
    std::cout << "Aktuellste Version: " << versionResponse.getBody() << std::endl;

    return (ROBBER_VERSION != versionResponse.getBody());
}
