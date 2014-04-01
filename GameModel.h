#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// #include "DataTypes.h"
#include <memory>
#include <set>
#include <map>
#include <string>
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
		void AddSprite(const std::string&, std::shared_ptr<sf::Sprite>);
		void UpdateSprites(sf::RenderWindow&);
		std::shared_ptr<sf::Sprite> FindSprite(const std::string&);

		// Player functions
		void AddPlayer(const std::string&, std::shared_ptr<Player>);
		std::shared_ptr<Player> FindPlayer(const std::string&);

	private:
		GameModel(); // This class is a singleton

		// containers typedefs
		typedef std::map<std::string, std::shared_ptr<sf::Sprite>> Sprite_cont_t;
		typedef std::set<std::shared_ptr<sf::Sprite>> Sprite_cont_set_t;
		typedef std::map<std::string, std::shared_ptr<Player>> Player_cont_t;

		// container definitions
		Sprite_cont_t Sprite_container;
		Sprite_cont_set_t sprites;
		Player_cont_t Player_container;
};

#endif
