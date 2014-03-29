#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>

class GameMap;

class GameController {
public:
	GameController();

	void run(std::shared_ptr<GameMap>);

private:
	// helper functions for interacting with the users
	sf::VideoMode VMode;
	sf::RenderWindow Window;
	sf::Texture Map_pic, Footman_pic, Grunt_pic;

	void LoadSprites();
};

#endif
