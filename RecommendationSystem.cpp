#include "RecommendationSystem.h"
#include <algorithm>

// I made an exception to use the std namespace here due to the amount of times std is used, as it makes the code easier to read
using namespace std;

void RecommendationSystem::addUser(User user) {
    // Add the user to the system
    users[user.name] = user;
}

void RecommendationSystem::addGame(Game game) {
    // Add the game to the system
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
        //Calculates the sum of the amount of times each genre in a game has occurred in the user's history
        int totalGenreFrequency = 0;

        for (const string& genre : game.genres) {
            if (find(user.preferences.begin(), user.preferences.end(), genre) != user.preferences.end()) {
                matchesPreferences = true;
            }
            if (genreFrequency.count(genre) > 0) {
                totalGenreFrequency += genreFrequency.at(genre);
            }
        }

        // Check if the game has already been played by the user
        bool alreadyPlayed = false;
        for (const Game& playedGame : user.history) {
            if (playedGame.name == game.name) {
                alreadyPlayed = true;
                break;
            }
        }

        if (!alreadyPlayed && ((matchesPreferences || totalGenreFrequency > 0) && !user.history.empty())) {
            recommendations.push_back(game);
        }
        else if (!alreadyPlayed && matchesPreferences && user.history.empty()) {
            recommendations.push_back(game);
        }
    }

    // Sort the recommendations by their total genre frequency using Enhanced Bubble Sort
    if (recommendations.empty()) {
        return recommendations;
    }
    bool swapped;
    for (int i = 0; i < recommendations.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < recommendations.size() - i - 1; j++) {
            int gameATotalGenreFrequency = 0;
            int gameBTotalGenreFrequency = 0;

            for (const string& genre : recommendations[j].genres) {
                if (genreFrequency.count(genre) > 0) {
                    gameATotalGenreFrequency += genreFrequency.at(genre);
                }
            }
            for (const string& genre : recommendations[j + 1].genres) {
                if (genreFrequency.count(genre) > 0) {
                    gameBTotalGenreFrequency += genreFrequency.at(genre);
                }
            }

            if (gameATotalGenreFrequency < gameBTotalGenreFrequency) {
                swap(recommendations[j], recommendations[j + 1]);
                swapped = true;
            }
        }
        // If no elements were swapped in the inner loop, the list is already sorted
        if (!swapped) {
            break;
        }
    }

    return recommendations;
}

User RecommendationSystem::getUser(string name) {
    // Check if the user exists in the system
    if (users.count(name) > 0) {
        // If the user exists, return their information
        return users.at(name);
    }
    else {
        // If the user does not exist, create a new user with the given name and return it
        User user;
        user.name = name;
        return user;
    }
}