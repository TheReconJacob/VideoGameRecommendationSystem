#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include <unordered_map>
#include "User.h"
#include "Game.h"

class RecommendationSystem {
public:
    void addUser(User user);
    void addGame(Game game);
    std::vector<Game> getRecommendations(User user);

private:
    std::unordered_map<std::string, User> users;
    std::unordered_map<std::string, Game> games;
};

#endif