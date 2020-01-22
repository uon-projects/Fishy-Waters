#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ZeoFlow_SFML.h"

//Compiler Directives
using namespace std;
using namespace sf;
using namespace zeoFlow;

RenderWindow window(VideoMode(832, 574), "Fishy Waters"); //the game screen

int main()
{
	
	Event event;
	int fishyMap[50][40];
	int mapSizeW = 50;
	int mapSizeH = 40;
	ifstream mapRead("Assets/map/map.txt");
	int i, j;
	ZeoFlow_SFML zeoFlow_SF;

	for(i = 0; i < mapSizeW; i++)
	{
		for(j = 0; j < mapSizeH; j++)
		{
			mapRead>>fishyMap[i][j];
		}
	}

	for(i = 0; i < mapSizeW; i++)
	{
		for(j = 0; j < mapSizeH; j++)
		{
			cout<<fishyMap[i][j]<<' ';
		}
		cout<<endl;
	}
	
	Sprite grass = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_020", "png");
	Sprite water = zeoFlow_SF.loadSpriteFromTexture("Assets/tilesets/", "tileset_030", "png");

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
		}

		window.clear();

		int startI = 0;
		int startJ = 0;
		for(i = startI; i < startI + 13; i++)
		{
			for(j = startJ; j < startJ + 9; j++)
			{
				if(fishyMap[i][j] == 25)
				{
					//grass
					grass.setPosition((i-startI)*64, (j-startJ)*64);
					window.draw(grass);
				}
				else if(fishyMap[i][j] == 15)
				{
					//water
					water.setPosition((i-startI)*64, (j-startJ)*64);
					window.draw(water);
				}
			}
		}

		window.display();

	}

	return 0;
}