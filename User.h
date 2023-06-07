#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Game.h"

class User {
public:
    std::string name;
    std::vector<std::string> preferences;
    std::vector<Game> history;
};

#endif