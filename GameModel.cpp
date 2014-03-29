#include "GameModel.h"
#include "Player.h"
#include <algorithm>
#include <iostream>
using std::string;
using std::set; using std::map; using std::pair;
using std::shared_ptr; using std::make_shared;
using std::for_each;
using sf::Sprite; using sf::RenderWindow;

GameModel::GameModel()
{

}

// singleton accessor function
GameModel& GameModel::GetInstance()
{
	static GameModel m;
	return m;
}

void GameModel::AddSprite(const string& name, shared_ptr<Sprite> sprite)
{
	Sprite_container.insert(pair<string, shared_ptr<Sprite>>(name, sprite));
	sprites.insert(sprite);
}

void GameModel::UpdateSprites(RenderWindow& Window)
{
	for_each(sprites.begin(), sprites.end(), 
	[&Window](shared_ptr<Sprite> sprite) {
		Window.draw(*sprite); 
	});
}

shared_ptr<Sprite> GameModel::FindSprite(const string& name)
{
	auto iter = Sprite_container.find(name);
	if (iter == Sprite_container.end()){
		throw Error("Sprite not found!");
	}
	return iter->second;
}

void GameModel::AddPlayer(shared_ptr<Player> player)
{
	Player_container.insert(player);
}