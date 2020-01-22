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
		cout<<posBoat.y<<' '<<startI<<' '<<posBoat.y + startI<<'\n';
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
		cout<<posBoat.y<<' '<<startI<<' '<<posBoat.y + startI<<'\n';
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
		cout<<posBoat.x<<' '<<startJ<<' '<<posBoat.x + startJ<<'\n';
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
		cout<<posBoat.x<<' '<<startJ<<' '<<posBoat.x + startJ<<'\n';
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
	Font font(zeoFlow_SF.loadFont("Assets/fonts/", "big_space", "otf"));
  
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
				Text txtCarHP;
				txtCarHP.setString(to_string(i) + ":" + to_string(j));
				txtCarHP.setFont(font);
				txtCarHP.setCharacterSize(15);
				txtCarHP.setOutlineColor(Color::White);
				txtCarHP.setOutlineThickness(1);
				txtCarHP.setColor(Color::Black);
				txtCarHP.setOrigin(txtCarHP.getGlobalBounds().width/2, txtCarHP.getGlobalBounds().height/2);
				txtCarHP.setPosition((j-startJ)*64 + 32, (i-startI)*64 + 32);
				window.draw(txtCarHP);
				if(j == 50 || j == 51)
				{
					cout<<startI<<' '<<startJ<<'\n';
				}
			}
		}
		healthBarOutline.setPosition(posBoat.x*64, posBoat.y*64);
		window.draw(healthBarOutline);

		window.display();

	}

	return 0;
}