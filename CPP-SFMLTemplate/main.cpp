#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ZeoFlow_SFML.h"

//Compiler Directives
using namespace std;
using namespace sf;
using namespace zeoFlow;

RenderWindow window(VideoMode(832, 574), "Fishy Waters"); //the game screen

void setOffsets(Vector2f &posBoat, int &startI, int &startJ, int mapSizeW, int mapSizeH)
{
	bool keyUp = false, keyDown = false, keyLeft = false, keyRight = false;
	
	if(Keyboard::isKeyPressed(Keyboard::Up)) keyUp = true;
	if(Keyboard::isKeyPressed(Keyboard::Down)) keyDown = true;
	if(Keyboard::isKeyPressed(Keyboard::Left)) keyLeft = true;
	if(Keyboard::isKeyPressed(Keyboard::Right)) keyRight = true;
	
	if (keyUp)
	{
		if(posBoat.y + startI > 4 && posBoat.y + startI <= mapSizeH - 3)
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
		cout<<posBoat.y<<' '<<startI<<' '<<posBoat.y + startI<<'\n';
	}
	if (keyDown)
	{
		if(posBoat.y + startI >= 4 && posBoat.y + startI <= mapSizeH - 4)
		{
			startI++;
		}
		else
		{
			posBoat.y++;
		}
		if(posBoat.y + startI > mapSizeH)
		{
			posBoat.y -= 1;
		}
		cout<<posBoat.y<<' '<<startI<<' '<<posBoat.y + startI<<'\n';
	}
	if (keyLeft)
	{
		if(posBoat.x + startJ >= 7 && posBoat.x + startJ <= mapSizeW - 5)
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
		if(posBoat.x + startJ >= 6 && posBoat.x + startJ <= mapSizeW - 6)
		{
			startJ++;
		}
		else
		{
			posBoat.x++;
		}
		if(posBoat.x + startJ >= mapSizeW + 2)
		{
			posBoat.x -= 1;
		}
	}
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
	int startJ = 0;
  
	ifstream mapRead("Assets/map/map.txt");
	for(i = 0; i < mapSizeH; i++)
	{
		for(j = 0; j < mapSizeW; j++)
		{
			mapRead>>fishyMap[i][j];
		}
	}
	
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
	RectangleShape healthBarOutline;
	healthBarOutline.setSize(Vector2f(64, 64));
	healthBarOutline.setFillColor(Color(21, 21, 21, 200));
	Vector2f posBoat(0, 0);

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
			setOffsets(posBoat, startI, startJ, mapSizeW, mapSizeH);
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
			}
		}
		healthBarOutline.setPosition(posBoat.x*64, posBoat.y*64);
		window.draw(healthBarOutline);

		Text txtCarHP;
		Font font;
		txtCarHP.setString("test");
		txtCarHP.setFont(font);
		txtCarHP.setCharacterSize(15);
		txtCarHP.setOutlineColor(Color::White);
		txtCarHP.setOutlineThickness(1);
		txtCarHP.setColor(Color::Black);
		txtCarHP.setPosition(100, 100);
		window.draw(txtCarHP);

		window.display();

	}

	return 0;
}