#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ZeoFlow_SFML.h"

//Compiler Directives
using namespace std;
using namespace sf;
using namespace zeoFlow;

RenderWindow window(VideoMode(832, 574), "Fishy Waters"); //the game screen
bool editMode = false;

bool canGo(int fieldType)
{
	if(fieldType == 11 || fieldType == 12 || fieldType == 13 || fieldType == 14 || fieldType == 15 || fieldType == 16 || fieldType == 17 ||
		fieldType == 18 || fieldType == 19 || fieldType == 31 || fieldType == 32 || fieldType == 33 || fieldType == 34 || editMode)
	{
		return true;
	}
	return false;
}

void setOffsets(Vector2i &posBoat, int &startI, int &startJ, int mapSizeW, int mapSizeH, int fishyMap[40][50])
{
	bool keyUp = false, keyDown = false, keyLeft = false, keyRight = false;
	
	if(Keyboard::isKeyPressed(Keyboard::Up)) keyUp = true;
	if(Keyboard::isKeyPressed(Keyboard::Down)) keyDown = true;
	if(Keyboard::isKeyPressed(Keyboard::Left)) keyLeft = true;
	if(Keyboard::isKeyPressed(Keyboard::Right)) keyRight = true;
	
	if(!canGo(fishyMap[posBoat.y + startI][posBoat.x + startJ + 1]))
	{
		keyRight = false;
	}
	
	if(!canGo(fishyMap[posBoat.y + startI][posBoat.x + startJ - 1]))
	{
		keyLeft = false;
	}
	
	if(!canGo(fishyMap[posBoat.y + startI + 1][posBoat.x + startJ]))
	{
		keyDown = false;
	}
	
	if(!canGo(fishyMap[posBoat.y + startI - 1][posBoat.x + startJ]))
	{
		keyUp = false;
	}

	if (keyUp)
	{
		if(posBoat.y + startI > 4 && posBoat.y + startI <= mapSizeH - 5)
		{
			startI--;
		}
		else
		{
			posBoat.y--;
		}
		if(posBoat.y + startI < 0)
		{
			posBoat.y += 1;
		}
	}
	if (keyDown)
	{
		if(posBoat.y + startI >= 4 && posBoat.y + startI <= mapSizeH - 6)
		{
			startI++;
		}
		else
		{
			posBoat.y++;
		}
		if(posBoat.y + startI > mapSizeH - 1)
		{
			posBoat.y -= 1;
		}
	}
	if (keyLeft)
	{
		if(posBoat.x + startJ >= 7 && posBoat.x + startJ <= mapSizeW - 7)
		{
			startJ--;
		}
		else
		{
			posBoat.x--;
		}
		if(posBoat.x + startJ < 0)
		{
			posBoat.x += 1;
		}
	}
	if (keyRight)
	{
		if(posBoat.x + startJ >= 6 && posBoat.x + startJ <= mapSizeW - 8)
		{
			startJ++;
		}
		else
		{
			posBoat.x++;
		}
		if(posBoat.x + startJ >= mapSizeW)
		{
			posBoat.x -= 1;
		}
	}
}

bool spriteClicked(Sprite sprite, Vector2i mouseLocation)
{
	IntRect water11Btn(sprite.getPosition().x, sprite.getPosition().y,
						sprite.getGlobalBounds().width * 2, sprite.getGlobalBounds().height * 2);
	if (water11Btn.contains(mouseLocation))
	{
		return true;
	}
	return false;
}

int main()
{
	
	window.setFramerateLimit(60);

	Event event;
	int fishyMap[40][50];
	int mapSizeW = 50;
	int mapSizeH = 40;
	int i, j;
	ZeoFlow_SFML zeoFlow_SF;
	int startI = 0;
	int startJ = 23;
	Vector2i posBoat(6, 3);
	Vector2i mouseLocation(0, 0);
	Vector2i editTerrain(0, 0);
	Font font(zeoFlow_SF.loadFont("Assets/fonts/", "big_space", "otf"));
	bool leftSideClicked = false;
  
	ifstream mapRead("Assets/map/map.txt");
	for(i = 0; i < mapSizeH; i++)
	{
		for(j = 0; j < mapSizeW; j++)
		{
			mapRead>>fishyMap[i][j];
		}
	}
	mapRead.close();
	ofstream mapNew("Assets/map/map.txt");
	
	Sprite grass = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_020", "png");
	Sprite water_11 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_011", "png");
	Sprite water_12 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_012", "png");
	Sprite water_13 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_013", "png");
	Sprite water_14 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_029", "png");
	Sprite water_15 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_030", "png");
	Sprite water_16 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_031", "png");
	Sprite water_17 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_045", "png");
	Sprite water_18 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_046", "png");
	Sprite water_19 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_047", "png");
	Sprite water_31 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_014", "png");
	Sprite water_32 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_015", "png");
	Sprite water_33 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_032", "png");
	Sprite water_34 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_033", "png");
	
	Sprite ct_grass = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_020", "png");
	Sprite ct_water_15 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_030", "png");
	Sprite ed_grass = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_020", "png");
	Sprite ed_water_11 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_011", "png");
	Sprite ed_water_12 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_012", "png");
	Sprite ed_water_13 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_013", "png");
	Sprite ed_water_14 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_029", "png");
	Sprite ed_water_15 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_030", "png");
	Sprite ed_water_16 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_031", "png");
	Sprite ed_water_17 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_045", "png");
	Sprite ed_water_18 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_046", "png");
	Sprite ed_water_19 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_047", "png");
	Sprite ed_water_31 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_014", "png");
	Sprite ed_water_32 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_015", "png");
	Sprite ed_water_33 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_032", "png");
	Sprite ed_water_34 = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_033", "png");


	RectangleShape healthBarOutline;
	healthBarOutline.setSize(Vector2f(64, 64));
	healthBarOutline.setFillColor(Color(21, 21, 21, 200));
	bool terrainType = false;
	int terrainSelected = 0;

	//the loop that draws the game
    while (window.isOpen())
    {
		//the loop that checks for different inputs
        while (window.pollEvent(event))
        {
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
                window.close();
			}
			if(event.type == Event::KeyPressed)
			{
				if(Keyboard::isKeyPressed(Keyboard::E))
				{
					editMode = !editMode;
					terrainType = false;
				}
				if(terrainType && editMode)
				{
					if(Keyboard::isKeyPressed(Keyboard::W))
					{
						editTerrain.x--;
					}
					if(Keyboard::isKeyPressed(Keyboard::S))
					{
						editTerrain.x++;
					}
					if(Keyboard::isKeyPressed(Keyboard::A))
					{
						editTerrain.y--;
					}
					if(Keyboard::isKeyPressed(Keyboard::D))
					{
						editTerrain.y++;
					}
				}
			}
			if(event.type == Event::MouseMoved)
			{
				mouseLocation = Mouse::getPosition(window);
			}
			if(event.type == Event::MouseButtonPressed)
			{
				if(Mouse::isButtonPressed(Mouse::Left) && mouseLocation.x >= 0 && mouseLocation.x <= 832 && mouseLocation.y >= 0 && mouseLocation.y <= 574)
				{
					if(!terrainType && editMode)
					{
						leftSideClicked = mouseLocation.x < window.getSize().x/2;
						terrainType = true;
						editTerrain.x = mouseLocation.y/64 + startI;
						editTerrain.y = mouseLocation.x/64 + startJ;
					}
				}
				if(Mouse::isButtonPressed(Mouse::Left))
				{
					if(spriteClicked(ct_grass, mouseLocation))
					{
						terrainSelected = 0;
					}
					if(spriteClicked(ct_water_15, mouseLocation))
					{
						terrainSelected = 1;
					}
					if(terrainSelected == 0)
					{
						if(spriteClicked(ed_grass, mouseLocation))
						{
							fishyMap[editTerrain.x][editTerrain.y] = 25;
						}
					}
					else if(terrainSelected == 1)
					{
					if(spriteClicked(ed_water_11, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 11;
					}
					if(spriteClicked(ed_water_12, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 12;
					}
					if(spriteClicked(ed_water_13, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 13;
					}
					if(spriteClicked(ed_water_14, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 14;
					}
					if(spriteClicked(ed_water_15, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 15;
					}
					if(spriteClicked(ed_water_16, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 16;
					}
					if(spriteClicked(ed_water_17, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 17;
					}
					if(spriteClicked(ed_water_18, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 18;
					}
					if(spriteClicked(ed_water_19, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 19;
					}
					if(spriteClicked(ed_water_31, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 31;
					}
					if(spriteClicked(ed_water_32, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 32;
					}
					if(spriteClicked(ed_water_33, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 33;
					}
					if(spriteClicked(ed_water_34, mouseLocation))
					{
						fishyMap[editTerrain.x][editTerrain.y] = 34;
					}
					}
				}
			}
			setOffsets(posBoat, startI, startJ, mapSizeW, mapSizeH, fishyMap);
		}


		window.clear();
		for(i = startI; i < startI + 9; i++)
		{
			for(j = startJ; j < startJ + 13; j++)
			{
				if(fishyMap[i][j] == 25)
				{
					grass.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(grass);
				}
				else if(fishyMap[i][j] == 11)
				{
					water_11.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_11);
				}
				else if(fishyMap[i][j] == 12)
				{
					water_12.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_12);
				}
				else if(fishyMap[i][j] == 13)
				{
					water_13.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_13);
				}
				else if(fishyMap[i][j] == 14)
				{
					water_14.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_14);
				}
				else if(fishyMap[i][j] == 15)
				{
					water_15.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_15);
				}
				else if(fishyMap[i][j] == 16)
				{
					water_16.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_16);
				}
				else if(fishyMap[i][j] == 17)
				{
					water_17.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_17);
				}
				else if(fishyMap[i][j] == 18)
				{
					water_18.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_18);
				}
				else if(fishyMap[i][j] == 19)
				{
					water_19.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_19);
				}
				else if(fishyMap[i][j] == 31)
				{
					water_31.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_31);
				}
				else if(fishyMap[i][j] == 32)
				{
					water_32.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_32);
				}
				else if(fishyMap[i][j] == 33)
				{
					water_33.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_33);
				}
				else if(fishyMap[i][j] == 34)
				{
					water_34.setPosition((j-startJ)*64, (i-startI)*64);
					window.draw(water_34);
				}
				if(editMode)
				{
					Text txtCarHP;
					txtCarHP.setString(to_string(i) + ":" + to_string(j));
					txtCarHP.setFont(font);
					txtCarHP.setCharacterSize(15);
					txtCarHP.setOutlineColor(Color::White);
					txtCarHP.setOutlineThickness(1);
					txtCarHP.setColor(Color::Black);
					txtCarHP.setOrigin(txtCarHP.getGlobalBounds().width/2, txtCarHP.getGlobalBounds().height/2);
					txtCarHP.setPosition((j-startJ)*64 + 32, (i-startI)*64 + 28);
					window.draw(txtCarHP);
					if(terrainType)
					{
						RectangleShape mousePointer;
						mousePointer.setOrigin(32, 32);
						mousePointer.setSize(Vector2f(62, 62));
						mousePointer.setFillColor(Color(255, 255, 255, 10));
						mousePointer.setOutlineColor(Color::Red);
						mousePointer.setOutlineThickness(1);
						mousePointer.setPosition((editTerrain.y-startJ)*64 + 32, (editTerrain.x-startI)*64 + 32);
						window.draw(mousePointer);
					}
				}
			}
		}
		healthBarOutline.setPosition(posBoat.x*64, posBoat.y*64);
		window.draw(healthBarOutline);
		if(editMode && !terrainType)
		{
			RectangleShape mousePointer;
			mousePointer.setOrigin(32, 32);
			mousePointer.setSize(Vector2f(62, 62));
			mousePointer.setFillColor(Color(43, 43, 43, 150));
			mousePointer.setOutlineColor(Color::White);
			mousePointer.setOutlineThickness(1);
			mousePointer.setPosition((mouseLocation.x/64) * 64 + 32, (mouseLocation.y/64) * 64 + 32);
			window.draw(mousePointer);
		}
		else if(terrainType)
		{
			leftSideClicked = editTerrain.y < window.getSize().x/2;
			int rightSideAddition = 0;
			if(leftSideClicked) rightSideAddition = 532;
			RectangleShape terrainHolder;
			terrainHolder.setFillColor(Color(46, 46, 46, 200));
			terrainHolder.setSize(Vector2f(300, 574));
			terrainHolder.setPosition(0 + rightSideAddition, 0);
			window.draw(terrainHolder);

			ct_grass.setPosition(10 + rightSideAddition, 10);
			window.draw(ct_grass);

			ct_water_15.setPosition(84 + rightSideAddition, 10);
			window.draw(ct_water_15);

			if(terrainSelected == 0)
			{
				ed_grass.setPosition(10 + rightSideAddition, 90);
				window.draw(ed_grass);
			}
			else if(terrainSelected == 1)
			{
				ed_water_11.setPosition(10 + 70 * 0 + rightSideAddition, 90 + 70 * 0);
				window.draw(ed_water_11);
				ed_water_12.setPosition(10 + 70 * 1 + rightSideAddition, 90 + 70 * 0);
				window.draw(ed_water_12);
				ed_water_13.setPosition(10 + 70 * 2 + rightSideAddition, 90 + 70 * 0);
				window.draw(ed_water_13);
				ed_water_14.setPosition(10 + 70 * 0 + rightSideAddition, 90 + 70 * 1);
				window.draw(ed_water_14);
				ed_water_15.setPosition(10 + 70 * 1 + rightSideAddition, 90 + 70 * 1);
				window.draw(ed_water_15);
				ed_water_16.setPosition(10 + 70 * 2 + rightSideAddition, 90 + 70 * 1);
				window.draw(ed_water_16);
				ed_water_17.setPosition(10 + 70 * 0 + rightSideAddition, 90 + 70 * 2);
				window.draw(ed_water_17);
				ed_water_18.setPosition(10 + 70 * 1 + rightSideAddition, 90 + 70 * 2);
				window.draw(ed_water_18);
				ed_water_19.setPosition(10 + 70 * 2 + rightSideAddition, 90 + 70 * 2);
				window.draw(ed_water_19);
				
				ed_water_31.setPosition(10 + 70 * 0 + rightSideAddition, 90 + 70 * 3);
				window.draw(ed_water_31);
				ed_water_32.setPosition(10 + 70 * 1 + rightSideAddition, 90 + 70 * 3);
				window.draw(ed_water_32);
				ed_water_33.setPosition(10 + 70 * 0 + rightSideAddition, 90 + 70 * 4);
				window.draw(ed_water_33);
				ed_water_34.setPosition(10 + 70 * 1 + rightSideAddition, 90 + 70 * 4);
				window.draw(ed_water_34);

			}

		}

		window.display();

	}

	for(i = 0; i < mapSizeH; i++)
	{
		for(j = 0; j < mapSizeW; j++)
		{
			mapNew<<fishyMap[i][j]<<' ';
		}
		mapNew<<'\n';
	}

	return 0;
}