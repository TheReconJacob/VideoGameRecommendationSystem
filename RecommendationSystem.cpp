#include "RecommendationSystem.h"
#include <algorithm>

using namespace std;

void RecommendationSystem::addUser(User user) {
    users[user.name] = user;
}

void RecommendationSystem::addGame(Game game) {
    games[game.name] = game;
}

vector<Game> RecommendationSystem::getRecommendations(User user) {
    vector<Game> recommendations;
    unordered_map<string, int> genreFrequency;

    // Count the number of times each genre appears in the user's history
    for (const Game& game : user.history) {
        for (const string& genre : game.genres) {
            ++genreFrequency[genre];
        }
    }

    // Find games that match the user's preferences and gather genres that appear frequently in their history of previously played games
    for (const pair<string, Game>& gamePair : games) {
        const Game& game = gamePair.second;
        bool matchesPreferences = false;
        //Calculates the the sum of the amount of times each genre in a game has occured in the user's history
        int totalGenreFrequency = 0;

        for (const string& genre : game.genres) {
            if (find(user.preferences.begin(), user.preferences.end(), genre) != user.preferences.end()) {
                matchesPreferences = true;
            }
            if (genreFrequency.count(genre) > 0) {
                totalGenreFrequency += genreFrequency.at(genre);
            }
        }

        if (matchesPreferences && totalGenreFrequency > 0) {
            recommendations.push_back(game);
        }
    }

    // Sort the recommendations by their total genre frequency
    sort(recommendations.begin(), recommendations.end(), [&](const Game& gameA, const Game& gameB) {
        int gameATotalGenreFrequency = 0;
        int gameBTotalGenreFrequency = 0;

        for (const string& genre : gameA.genres) {
            if (genreFrequency.count(genre) > 0) {
                gameATotalGenreFrequency += genreFrequency.at(genre);
            }
        }
        for (const string& genre : gameB.genres) {
            if (genreFrequency.count(genre) > 0) {
                gameBTotalGenreFrequency += genreFrequency.at(genre);
            }
        }

        return gameATotalGenreFrequency > gameBTotalGenreFrequency;
    });

    return recommendations;
}
