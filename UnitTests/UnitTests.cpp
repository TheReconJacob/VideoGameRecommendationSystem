#include "pch.h"
#include "CppUnitTest.h"
#include "../RecommendationSystem.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VideoGameRecommendationSystemUnitTests
{
	TEST_CLASS(VideoGameRecommendationSystemUnitTests)
	{
	private:
		RecommendationSystem system;

	public:
		TEST_METHOD_INITIALIZE(setUp)
		{
			system = RecommendationSystem();
		}

		TEST_METHOD(testAddUser)
		{
			User user;
			user.name = "Jacob";
			system.addUser(user);

			User retrievedUser = system.getUser("Jacob");

			//Checking the retrieved user's name matches the name we defined
			Assert::AreEqual(retrievedUser.name, user.name);
		}

		TEST_METHOD(testAddGame)
		{
			Game game;
			game.name = "Age of Empires";
			game.genres = { "Strategy", "Simulation" };
			system.addGame(game);

			std::vector<std::string> genres = { "Strategy", "Simulation" };
			std::vector<Game> retrievedGames = system.getGamesByGenres(genres);
			
			//Checking that there is one game added to the system that matches the genres we defined 
			Assert::AreEqual(retrievedGames.size(), (size_t)1);
			Assert::AreEqual(retrievedGames[0].name, game.name);
		}

		TEST_METHOD(testGetRecommendations)
		{
			Game matchedGame;
			matchedGame.name = "Halo 2";
			matchedGame.genres = { "Action", "FPS" };
			system.addGame(matchedGame);

			Game unmatchedGame;
			unmatchedGame.name = "League of Legends";
			unmatchedGame.genres = { "Fantasy", "RPG" };
			system.addGame(unmatchedGame);

			Game previouslyPlayedGame;
			previouslyPlayedGame.name = "Halo Combat Evolved";
			previouslyPlayedGame.genres = { "Action", "FPS" };
			system.addGame(previouslyPlayedGame);

			User user;
			user.name = "George";
			user.preferences.push_back("Action");
			user.history.push_back(previouslyPlayedGame);
			system.addUser(user);

			std::vector<Game> recommendations = system.getRecommendations(user);
			
			//There is only one game returned, since two games match the Action genre that's in the user's preferences,
			//but one gets removed since it's a game they've played before, so there should only be one.
			Assert::AreEqual(recommendations.size(), (size_t)1);
			Assert::AreEqual(recommendations[0].name, matchedGame.name);
		}

		TEST_METHOD(testGetGamesByGenres)
		{
			Game game1;
			game1.name = "Harry Potter";
			game1.genres.push_back("Action");
			system.addGame(game1);

			Game game2;
			game2.name = "World of Warcraft";
			game2.genres.push_back("RPG");
			system.addGame(game2);

			std::vector<Game> retrievedGames = system.getGamesByGenres(game1.genres);

			//Retrieved games are only Action games, which there is only one
			Assert::AreEqual(retrievedGames.size(), (size_t)1);
			Assert::AreEqual(retrievedGames[0].name, game1.name);

			retrievedGames = system.getGamesByGenres(game2.genres);

			//Retrieved games are only RPG games, which there is only one
			Assert::AreEqual(retrievedGames.size(), (size_t)1);
			Assert::AreEqual(retrievedGames[0].name, game2.name);

			std::vector<std::string> genres = { "Action", "RPG" };
			retrievedGames = system.getGamesByGenres(genres);

			//Retrieved games both Action and RPG, which there is one each which means two total
			Assert::AreEqual(retrievedGames.size(), (size_t)2);
		}

		TEST_METHOD(testGetUser)
		{
			RecommendationSystem system;
			User user;
			user.name = "Jacob";
			system.addUser(user);

			User retrievedUser = system.getUser("Jacob");
			Assert::AreEqual(retrievedUser.name, user.name);

			retrievedUser = system.getUser("NoUser");

			//Function returns string with the given name if user doesn't exist
			Assert::AreEqual(retrievedUser.name, std::string("NoUser"));
		}
	};
}