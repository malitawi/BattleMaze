#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// #include "DataTypes.h"
#include <memory>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>

class Player;

class GameModel 
{
	public:
		// disable copy/move, construction, or assignment
		GameModel(const GameModel&) = delete;
		GameModel(GameModel&&) = delete;
		GameModel& operator =(const GameModel&) = delete;
		GameModel& operator =(GameModel&&) = delete;

		// singleton accessor function
		static GameModel& GetInstance();

		// Sprite functions
		void AddSprite(std::shared_ptr<sf::Sprite>);

		// Player functions
		void AddPlayer(std::shared_ptr<Player>);

	private:
		GameModel(); // This class is a singleton

		// containers typedefs
		typedef std::set<std::shared_ptr<sf::Sprite>> Sprite_cont_t;
		typedef std::set<std::shared_ptr<Player>> Player_cont_t;

		// container definitions
		Sprite_cont_t Sprite_container;
		Player_cont_t Player_container;
};

#endif
