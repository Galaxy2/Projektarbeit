#include "notification.h"

benachrichtigung::benachrichtigung(std::string text, int xpos=50, int ypos=50, int charSize=20){
    this->text.setString(text);
    this->text.setFont(standardSchriftart);
    this->text.setPosition(xpos, ypos);
    this->text.setCharacterSize(charSize);
}