#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <memory>
#include "DataTypes.h"
#include "GameMap.h"
#include "Tile.h"
#include "Player.h"

using sf::VideoMode; using sf::RenderWindow;
using sf::Texture; using sf::Sprite; using sf::Text;
using sf::Color; using sf::Font; using sf::String;
using sf::Event; using sf::Keyboard;

using std::cout; using std::endl;
using std::ifstream; using std::getline;
using std::string;
using std::shared_ptr; using std::make_shared;

shared_ptr<GameMap> LoadGameBoard(string);

int main(int argc, char* argv[])
{
    // initialize map and game board
    shared_ptr<GameMap> World = LoadGameBoard("gameboard1.txt");
	VideoMode VMode(1440, 900, 32);
    RenderWindow Window(VMode, "Battlemaze");
	Texture Map_pic, Footman_pic, Grunt_pic;

    // load sprites
	if (!Map_pic.loadFromFile("Sprites/map.png")) return 1;
    if (!Footman_pic.loadFromFile("Sprites/footman.png")) return 1;
    if (!Grunt_pic.loadFromFile("Sprites/grunt.png")) return 1;

    // assign sprite and map configurations
	Sprite Map(Map_pic), Footman(Footman_pic), Grunt(Grunt_pic);
	Map.setPosition(float(VMode.width)/4, float(VMode.height)/4);
	Map.setScale(float(VMode.width)/float(Map.getTexture()->getSize().x)/2, 
                float(VMode.height)/float(Map.getTexture()->getSize().y)/2);
    Footman.setPosition(362.5f, 225.0f);
    Grunt.setPosition(362.5f + (9.0f * 42.25f), 225.0f + (5.0 * 41.0f));

    int currXPos = 0, currYPos = 0, xMove = 0, yMove = 0;
    int nextXPos = -1, nextYPos = -1;
    float xGuiMove = 0.0f, yGuiMove = 0.0f;

    shared_ptr<Player> footman(new Player(currXPos, currYPos, 180, 12, "Footman"));
    shared_ptr<Player> grunt(new Player(9, 5, 240, 10, "Grunt"));

    World->AddPlayer(footman);
    World->SetTileOccupant(0, 0, footman);
    World->AddPlayer(grunt);
    World->SetTileOccupant(9, 5, grunt);

    Text Text("Battle Maze", Font());
    Text.setColor(Color(0, 255, 0));
    Text.move(float(VMode.width)/2 - float(65.0), 0);
    Text.setCharacterSize(32U);

    Window.setFramerateLimit(60);

    while (Window.isOpen()){
        Event Event;
        while (Window.pollEvent(Event)){
            switch (Event.type){
				case Event::Closed:
					// cout << "Window Closed" << endl;
					Window.close();
					break;
				case Event::GainedFocus:
					// cout << "GUI Window gained foucs" << endl;
					break;
				case Event::LostFocus:
					// cout << "GUI Window lost focus" << endl;
					break;
				case Event::KeyReleased:
                    xMove = yMove = 0;
                    xGuiMove = yGuiMove = 0.0f;
					switch (Event.key.code){
                        case Keyboard::Escape:
                            Window.close();
                            break;
						case Keyboard::Up:
							//cout << "The up arrow was pressed" << endl;
                            yMove -= 1;
                            yGuiMove = -41.0f;
  							break;
						case Keyboard::Down:
							//cout << "The down arrow was pressed" << endl;
                            yMove += 1;
                            yGuiMove = 41.0f;
							break;
						case Keyboard::Right:
							//cout << "The right arrow was pressed" << endl;
                            xMove += 1;
                            xGuiMove = 42.25f;
							break;
						case Keyboard::Left:
							//cout << "The left arrow was pressed" << endl;
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
                            // World->AttackPlayer(Victim, Attacker);
                            // World->AttackPlayer(Attacker, Victim);
                        }
                        else{
                            cout << "Moved to tile: (" << nextXPos << ", " << nextYPos << ")" << endl;
                            World->SetTileOccupant(currXPos, currYPos, nullptr);
                            footman->Move(xMove, yMove);
                            World->SetTileOccupant(nextXPos, nextYPos, footman);
                            currXPos += xMove;
                            currYPos += yMove;
                            Footman.move(xGuiMove, yGuiMove);
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
		Window.draw(Map);
        Window.draw(Footman);
        Window.draw(Grunt);
        Window.draw(Text);
        Window.display();
    }
    return 0;
}

shared_ptr<GameMap> LoadGameBoard(string filename)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()){
        cout << "Error, could not open file" << endl;
        return nullptr;
    }
    int width, height;
    string clr, tile_label;
    TileType tile_type;
    Walkable walk;
    infile >> width >> height;
    getline(infile, clr);
    shared_ptr<GameMap> World(new GameMap(width, height));

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            infile >> tile_label;
            walk = WALKABLE;
            if (tile_label == "G"){
                tile_type = GRASS;
            }else if (tile_label == "D"){
                tile_type = DIRT;
            }else if (tile_label == "S"){
                tile_type = STONE;
            }else if (tile_label == "T"){
                tile_type = TREE;
                walk = NOT_WALKABLE;
            }
            World->SetTile(j, i, tile_type, walk);
        }
        getline(infile, clr);
    }
    infile.close();
    return World;
}
