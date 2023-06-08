#include <iostream>
#include "RecommendationSystem.h"

int main() {
    RecommendationSystem system;
    std::string input;

    // Add some sample data

    Game game1;
    game1.name = "Age of Empires";
    game1.genres = { "Strategy", "Simulation" };
    system.addGame(game1);

    Game game2;
    game2.name = "World of Warcraft";
    game2.genres = { "Fantasy", "RPG" };
    system.addGame(game2);

    Game game3;
    game3.name = "Harry Potter";
    game3.genres = { "Action", "RPG" };
    system.addGame(game3);

    Game game4;
    game4.name = "Halo 2";
    game4.genres = { "Action", "FPS" };
    system.addGame(game4);

    Game game5;
    game5.name = "League of Legends";
    game5.genres = { "Fantasy", "RPG" };
    system.addGame(game5);
    
    Game game6;
    game6.name = "Halo Combat Evolved";
    game6.genres = { "Action", "FPS" };
    system.addGame(game6);

    User user1;
    user1.name = "Jacob";
    user1.preferences = { "Action", "FPS" };
    user1.history.push_back(game4);
    system.addUser(user1);

    User user2;
    user2.name = "George";
    user2.preferences = { "Action" };
    user2.history.push_back(game2);
    system.addUser(user2);

    // Implement user interface
    std::cout << "Welcome to the Video Game Recommendation System!" << std::endl;
    std::cout << "Please enter your name:" << std::endl;
    std::getline(std::cin, input);

    User user = system.getUser(input);
    std::vector<Game> recommendations = system.getRecommendations(user);

    if (recommendations.empty()) {
        system.gatherUserInfo(user);

        // Update the user's information in the system
        system.addUser(user);

        // Get new recommendations based on the updated information
        recommendations = system.getRecommendations(user);
    }

    if (!recommendations.empty()) {
        std::cout << "Here are some games we think you'll like ranked in order based on your history and preferences:" << std::endl;
        for (const Game& game : recommendations) {
            std::cout << "- " << game.name << std::endl;
        }
    }
    else {
        std::cout << "Sorry, we couldn't find any recommendations for you." << std::endl;
    }

    return 0;
}