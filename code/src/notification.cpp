#include "notification.h"

benachrichtigung::benachrichtigung(std::string text){
    this->text.setString(text);
    this->text.setFont(standardSchriftart);
}
