#include "GameModel.h"
#include "Player.h"

using std::set;
using std::shared_ptr; using std::make_shared;
using sf::Sprite;

GameModel::GameModel()
{

}

// singleton accessor function
GameModel& GameModel::GetInstance()
{
	static GameModel m;
	return m;
}

void GameModel::AddSprite(shared_ptr<Sprite> sprite)
{
	Sprite_container.insert(sprite);
}

void GameModel::AddPlayer(shared_ptr<Player> player)
{
	Player_container.insert(player);
}