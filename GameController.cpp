#include "GameController.h"
#include "GameModel.h"
#include "DataTypes.h"
#include "GameMap.h"
#include "Tile.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cassert>

using sf::VideoMode; using sf::RenderWindow;
using sf::Texture; using sf::Sprite; using sf::Text;
using sf::Color; using sf::Font; using sf::String;
using sf::Event; using sf::Keyboard;

using std::cout; using std::endl;
using std::for_each;
using std::ifstream; using std::getline;
using std::string;
using std::shared_ptr; using std::make_shared;

GameController::GameController(): VMode(1440, 900, 32), Window(VMode, "Battlemaze")
{
    LoadSprites();
    InitializeGame();
}

void GameController::run(shared_ptr<GameMap> World)
{
	shared_ptr<Sprite> Map = GameModel::GetInstance().FindSprite("Map");
	shared_ptr<Sprite> Footman = GameModel::GetInstance().FindSprite("Footman");
	shared_ptr<Sprite> Grunt = GameModel::GetInstance().FindSprite("Grunt");
	assert(Map); assert(Footman); assert(Grunt);

    int currXPos = 0, currYPos = 0, xMove = 0, yMove = 0;
    int nextXPos = -1, nextYPos = -1;
    float xGuiMove = 0.0f, yGuiMove = 0.0f;


    shared_ptr<Player> footman = GameModel::GetInstance().FindPlayer("footman");
    shared_ptr<Player> grunt = GameModel::GetInstance().FindPlayer("grunt");
    assert(footman); assert(grunt);

    World->AddPlayer(footman);
    World->SetTileOccupant(0, 0, footman);
    World->AddPlayer(grunt);
    World->SetTileOccupant(9, 5, grunt);

    Font font;
    font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
    Text Title("Battle Maze", font, 32);
    Title.setColor(Color(0, 255, 0));
    Title.move(float(VMode.width)/2 - float(65.0), 20);

    while (Window.isOpen()){
        Event Event;
        while (Window.pollEvent(Event)){
            switch (Event.type){
                case Event::Closed:
                    Window.close();
                    break;
                case Event::GainedFocus:
                case Event::LostFocus:
                    break;
                case Event::KeyReleased:
                    xMove = yMove = 0;
                    xGuiMove = yGuiMove = 0.0f;
                    switch (Event.key.code){
                        case Keyboard::Escape:
                            Window.close();
                            break;
                        case Keyboard::Up:
                            yMove -= 1;
                            yGuiMove = -41.0f;
                            break;
                        case Keyboard::Down:
                            yMove += 1;
                            yGuiMove = 41.0f;
                            break;
                        case Keyboard::Right:
                            xMove += 1;
                            xGuiMove = 42.25f;
                            break;
                        case Keyboard::Left:
                            xMove -= 1;
                            xGuiMove = -42.25f;
                            break;
                        default:
                            break;
                    }
                    nextXPos = currXPos + xMove;
                    nextYPos = currYPos + yMove;
                    if (World->IsValidSpot(nextXPos, nextYPos)){
                        if (World->IsTileOccupied(nextXPos, nextYPos) && ((nextXPos) != currXPos || (nextYPos) != currYPos)){
                            shared_ptr<Player> Attacker = World->GetPlayer(currXPos, currYPos);
                            shared_ptr<Player> Victim = World->GetPlayer(nextXPos, nextYPos);
                            if (!Attacker->HasTarget()) {
                                Attacker->AcquireTarget(Victim);
                            }
                            if (!Victim->HasTarget()) {
                                Victim->AcquireTarget(Attacker);
                            }
                            Attacker->AttackTarget();
                            Victim->AttackTarget();
                        }
                        else{
                            cout << "Moved to tile: (" << nextXPos << ", " << nextYPos << ")" << endl;
                            World->SetTileOccupant(currXPos, currYPos, nullptr);
                            footman->Move(xMove, yMove);
                            World->SetTileOccupant(nextXPos, nextYPos, footman);
                            currXPos += xMove;
                            currYPos += yMove;
                            Footman->move(xGuiMove, yGuiMove);
                        }
                    }else{
                        cout << "Cannot move to tile" << endl;
                    }    
                    break;
                default:
                    break;
            }
        }
        Window.clear(Color(0, 55, 255));
        Window.draw(Title);
        GameModel::GetInstance().UpdateSprites(Window);
        Window.display();
    }
}

void GameController::LoadSprites()
{
    if (!Map_pic.loadFromFile("Sprites/map.png")) throw Error("Could not load Map");
    if (!Footman_pic.loadFromFile("Sprites/footman.png")) throw Error("Could not load Footman");
    if (!Grunt_pic.loadFromFile("Sprites/grunt.png")) throw Error("Could not load Grunt");

    // assign sprite and map configurations
    shared_ptr<Sprite> Map(new Sprite(Map_pic));
    shared_ptr<Sprite> Footman(new Sprite(Footman_pic));
    shared_ptr<Sprite> Grunt(new Sprite(Grunt_pic));

    GameModel::GetInstance().AddSprite("Map", Map);
    GameModel::GetInstance().AddSprite("Footman", Footman);
    GameModel::GetInstance().AddSprite("Grunt", Grunt);

    Map->setPosition(float(VMode.width)/4, float(VMode.height)/4);
    Map->setScale(float(VMode.width)/float(Map->getTexture()->getSize().x)/2, 
                float(VMode.height)/float(Map->getTexture()->getSize().y)/2);
    Footman->setPosition(362.5f, 225.0f);
    Grunt->setPosition(362.5f + (9.0f * 42.25f), 225.0f + (5.0 * 41.0f));
}

void GameController::InitializeGame()
{
    Window.setFramerateLimit(60);

    shared_ptr<Player> footman(new Player(0, 0, 180, 12, "Footman"));
    shared_ptr<Player> grunt(new Player(9, 5, 240, 10, "Grunt"));

    GameModel::GetInstance().AddPlayer("footman", footman);
    GameModel::GetInstance().AddPlayer("grunt", grunt);
}
