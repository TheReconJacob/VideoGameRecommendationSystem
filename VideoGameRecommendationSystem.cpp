#include <iostream>
#include "RecommendationSystem.h"

int main() {
    RecommendationSystem system;
    std::string input;

    // Add some sample data
    User user1;
    user1.name = "Jacob";
    user1.preferences = { "Action", "FPS" };
    system.addUser(user1);

    User user2;
    user2.name = "George";
    user2.preferences = { "Action" };
    system.addUser(user2);

    Game game1;
    game1.name = "Halo Combat Evolved";
    game1.genres = { "Action", "FPS" };
    system.addGame(game1);

    Game game2;
    game2.name = "Age of Empires";
    game2.genres = { "Strategy", "Simulation" };
    system.addGame(game2);

    Game game3;
    game3.name = "World of Warcraft";
    game3.genres = { "Action", "RPG" };
    system.addGame(game3);

    // Implement user interface
    std::cout << "Welcome to the Video Game Recommendation System!" << std::endl;
    std::cout << "Please enter your name: ";
    std::getline(std::cin, input);

    User user = system.getUser(input);
    std::vector<Game> recommendations = system.getRecommendations(user);

    if (!recommendations.empty()) {
        std::cout << "Here are some games we think you'll like:" << std::endl;
        for (const Game& game : recommendations) {
            std::cout << "- " << game.name << std::endl;
        }
    }
    else {
        std::cout << "Sorry, we couldn't find any recommendations for you." << std::endl;
    }

    return 0;
}