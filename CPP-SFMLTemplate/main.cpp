#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ZeoFlow_SFML.h"
#include "MapEditor.h"
#include "FileSync.h"
#include "Map.h"

//Compiler Directives
using namespace std;
using namespace sf;
using namespace zeoFlow;

const int screenW = 864, screenH = 608;
int level;
bool modeEdit = false;
RenderWindow window(VideoMode(screenW, screenH), "Muddy Grounds"); //the game screen

bool canGo(int fieldType, int fieldType2, int objectType)
{
	if(modeEdit)
	{
		return true;
	}
	else if(objectType >= 10 && objectType < 70 && fieldType < 120 && !(fieldType2>=70 && fieldType2<=85))
	{
		return true;
	}
	else if(objectType == 9)
	{
		return true;
	}
	else if(objectType == 8)
	{
		return false;
	}
	return false;
}

int animation = 0;
void setGameViewOffset(Vector2i &characterPos, Vector2i &offset, int muddyMap[120][200], int muddyMap2[120][200], int objectsMap[120][200], int mapSizeH, int mapSizeW, int &characterFace)
{
	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
		characterFace = 1;
		if(canGo(muddyMap[characterPos.y + offset.x][characterPos.x + offset.y - 1],
			muddyMap2[characterPos.y + offset.x][characterPos.x + offset.y - 1],
			objectsMap[characterPos.y + offset.x][characterPos.x + offset.y - 1]))
		{
			animation = 1;
			if(characterPos.x + offset.y >= 14 && characterPos.x + offset.y <= mapSizeW - 14)
			{
				//offset.y--;
			}
			else
			{
				characterPos.x--;
			}
			if(characterPos.x + offset.y < 0)
			{
				characterPos.x++;
			}
		}
	}
	else if(Keyboard::isKeyPressed(Keyboard::Right))
	{
		characterFace = 2;
		if(canGo(muddyMap[characterPos.y + offset.x][characterPos.x + offset.y + 1],
			muddyMap2[characterPos.y + offset.x][characterPos.x + offset.y + 1],
			objectsMap[characterPos.y + offset.x][characterPos.x + offset.y + 1]))
		{
			//animation = 2;
			if(characterPos.x + offset.y >= 13 && characterPos.x + offset.y <= mapSizeW - 15)
			{
				offset.y++;
			}
			else
			{
				characterPos.x++;
			}
			if(characterPos.x + offset.y >= mapSizeW)
			{
				characterPos.x--;
			}
		}
	}
	else if(Keyboard::isKeyPressed(Keyboard::Up))
	{
		characterFace = 3;
		if(canGo(muddyMap[characterPos.y + offset.x - 1][characterPos.x + offset.y],
			muddyMap2[characterPos.y + offset.x - 1][characterPos.x + offset.y],
			objectsMap[characterPos.y + offset.x - 1][characterPos.x + offset.y]))
		{
			animation = 3;
			if(characterPos.y + offset.x >= 10 && characterPos.y + offset.x <= mapSizeH - 10)
			{
				//offset.x--;
			}
			else
			{
				characterPos.y--;
			}
			if(characterPos.y + offset.x < 0)
			{
				characterPos.y++;
			}
		}
	}
	else if(Keyboard::isKeyPressed(Keyboard::Down))
	{
		characterFace = 0;
		if(canGo(muddyMap[characterPos.y + offset.x + 1][characterPos.x + offset.y],
			muddyMap2[characterPos.y + offset.x + 1][characterPos.x + offset.y],
			objectsMap[characterPos.y + offset.x + 1][characterPos.x + offset.y]))
		{
			animation = 4;
			if(characterPos.y + offset.x >= 9 && characterPos.y + offset.x <= mapSizeH - 11)
			{
				//offset.x++;
			}
			else
			{
				characterPos.y++;
			}
			if(characterPos.y + offset.x >= mapSizeH)
			{
				characterPos.y--;
			}
		}
	}

}

int main()
{
	
	window.setFramerateLimit(60);

	Event event;
	ZeoFlow_SFML zeoFlow_SF;
	FileSync fileSync;
	MapEditor mapEditor;
	Map map;

	Font font(zeoFlow_SF.loadFont("Assets/fonts/", "font_5", "ttf"));
	const int tilesetSize = 32;
	const int mapSizeH = 120, mapSizeW = 200;
	int muddyMap[mapSizeH][mapSizeW], muddyMap2[mapSizeH][mapSizeW], objectsMap[mapSizeH][mapSizeW];
	int i, j;

	bool modeShowInventory = false;
	int lastTerrainUsed;
	bool modeEditShowObjects = false;
	int modeInventory = 0;
	const int INVENTORY_CATEGORY_GROUND = 0;
	const int INVENTORY_CATEGORY_GROUND2 = 1;
	const int INVENTORY_CATEGORY_OBJECTS = 2;
	bool leftSideClicked;

	Vector2i characterPos, offset;
	Vector2i mouseLocation(0, 0);
	Vector2i editLocation(0, 0);

	int bridgePerLvlOff = 5;
	int bridgeByLvl[10][4] = {
		9, 18, 1, 0,
		9, 19, 1, 0,
		9, 20, 1, 0,
		22, 10, 2, 1,
		23, 10, 2, 1
	};
  
	fileSync.loadMap(muddyMap, mapSizeH, mapSizeW);
	fileSync.loadMap2(muddyMap2, mapSizeH, mapSizeW);
	fileSync.loadObjectsMap(objectsMap, mapSizeH, mapSizeW);
	fileSync.loadStats(characterPos, offset, level);

	Texture tilesetsTexture;
	tilesetsTexture.loadFromFile("Assets/tilesets.png");
	Vector2u textureSize = tilesetsTexture.getSize();
	textureSize.x /= 8;
	textureSize.y /= 133;

	Texture tilesetsGrassTexture;
	tilesetsGrassTexture.loadFromFile("Assets/tilesets_grass.png");
	Vector2u textureGrassSize = tilesetsGrassTexture.getSize();
	textureGrassSize.x /= 8;
	textureGrassSize.y /= 66;

	Texture tilesetsWaterTexture;
	tilesetsWaterTexture.loadFromFile("Assets/tilesets_water.png");
	Vector2u textureWaterSize = tilesetsWaterTexture.getSize();
	textureWaterSize.x /= 8;
	textureWaterSize.y /= 12;

	Texture tilesetsBridgeTexture;
	tilesetsBridgeTexture.loadFromFile("Assets/tilesets_bridge.png");
	Vector2u textureBridgeSize = tilesetsBridgeTexture.getSize();
	textureBridgeSize.x /= 6;
	textureBridgeSize.y /= 3;

	Texture tilesetsCharacterTexture;
	tilesetsCharacterTexture.loadFromFile("Assets/npc/character_tilesets.png");
	Vector2u textureCharacterSize = tilesetsCharacterTexture.getSize();
	textureCharacterSize.x /= 3;
	textureCharacterSize.y /= 4;

	RectangleShape character_tilesets[6][3];
	int characterFace = 1;
	for(i = 0; i<6; i++)
	{
		for(j = 0; j<3; j++)
		{
			character_tilesets[i][j].setOrigin(0, 16);
			character_tilesets[i][j].setSize(Vector2f(tilesetSize, tilesetSize));
			character_tilesets[i][j].setTexture(&tilesetsCharacterTexture);
			character_tilesets[i][j].setTextureRect(IntRect(textureCharacterSize.x*j, textureCharacterSize.y*i, textureCharacterSize.x, textureCharacterSize.y));
		}
	}

	RectangleShape mousePointer;
	mousePointer.setOrigin(16, 16);
	mousePointer.setSize(Vector2f(32, 32));
	mousePointer.setFillColor(Color(43, 43, 43, 50));
	mousePointer.setOutlineColor(Color::White);
	mousePointer.setOutlineThickness(2);

	RectangleShape terrainPointer;
	terrainPointer.setOrigin(16, 16);
	terrainPointer.setSize(Vector2f(32, 32));
	terrainPointer.setFillColor(Color::Transparent);
	terrainPointer.setOutlineColor(Color::White);
	terrainPointer.setOutlineThickness(4);
	
	RectangleShape grass_tilesets[66][8];
	RectangleShape grass_tilesets_edit[66][8];
	for(i = 0; i<66; i++)
	{
		for(j = 0; j<8; j++)
		{
			grass_tilesets[i][j].setSize(Vector2f(tilesetSize, tilesetSize));
			grass_tilesets[i][j].setTexture(&tilesetsGrassTexture);
			grass_tilesets[i][j].setTextureRect(IntRect(textureGrassSize.x*j, textureGrassSize.y*i, textureGrassSize.x, textureGrassSize.y));
			grass_tilesets_edit[i][j].setSize(Vector2f(tilesetSize, tilesetSize));
			grass_tilesets_edit[i][j].setTexture(&tilesetsGrassTexture);
			grass_tilesets_edit[i][j].setTextureRect(IntRect(textureGrassSize.x*j, textureGrassSize.y*i, textureGrassSize.x, textureGrassSize.y));
		}
	}
	
	RectangleShape water_tilests[12][8];
	RectangleShape water_tilesets_edit[12][8];
	RectangleShape water_tilesets_transparent[12][8];
	for(i = 0; i<12; i++)
	{
		for(j = 0; j<8; j++)
		{
			water_tilests[i][j].setSize(Vector2f(tilesetSize, tilesetSize));
			water_tilests[i][j].setTexture(&tilesetsWaterTexture);
			water_tilests[i][j].setTextureRect(IntRect(textureWaterSize.x*j, textureWaterSize.y*i, textureWaterSize.x, textureWaterSize.y));
			water_tilesets_edit[i][j].setSize(Vector2f(tilesetSize, tilesetSize));
			water_tilesets_edit[i][j].setTexture(&tilesetsWaterTexture);
			water_tilesets_edit[i][j].setTextureRect(IntRect(textureWaterSize.x*j, textureWaterSize.y*i, textureWaterSize.x, textureWaterSize.y));
			water_tilesets_transparent[i][j].setSize(Vector2f(tilesetSize, tilesetSize));
			water_tilesets_transparent[i][j].setTexture(&tilesetsWaterTexture);
			water_tilesets_transparent[i][j].setFillColor(Color(0, 0, 0, 80));
			water_tilesets_transparent[i][j].setTextureRect(IntRect(textureWaterSize.x*j, textureWaterSize.y*i, textureWaterSize.x, textureWaterSize.y));
		}
	}

	RectangleShape bridge_tilesets[2][3], bridge_tilesets_edit[2][3], bridge_tilesets_transparent[2][3];
	for(j = 0; j<3; j++)
	{
		bridge_tilesets[0][j].setSize(Vector2f(tilesetSize, tilesetSize*3));
		bridge_tilesets[0][j].setTexture(&tilesetsBridgeTexture);
		bridge_tilesets[0][j].setTextureRect(IntRect(textureBridgeSize.x*j, textureBridgeSize.y*0, textureBridgeSize.x, textureBridgeSize.y*3));
	
		bridge_tilesets_edit[0][j].setSize(Vector2f(tilesetSize, tilesetSize*3));
		bridge_tilesets_edit[0][j].setTexture(&tilesetsBridgeTexture);
		bridge_tilesets_edit[0][j].setTextureRect(IntRect(textureBridgeSize.x*j, textureBridgeSize.y*0, textureBridgeSize.x, textureBridgeSize.y*3));

		bridge_tilesets_transparent[0][j].setSize(Vector2f(tilesetSize, tilesetSize*3));
		bridge_tilesets_transparent[0][j].setTexture(&tilesetsBridgeTexture);
		bridge_tilesets_transparent[0][j].setFillColor(Color(0, 0, 0, 80));
		bridge_tilesets_transparent[0][j].setTextureRect(IntRect(textureBridgeSize.x*j, textureBridgeSize.y*0, textureBridgeSize.x, textureBridgeSize.y*3));
	}
	for(j = 0; j<3; j++)
	{
		bridge_tilesets[1][j].setSize(Vector2f(tilesetSize*3, tilesetSize));
		bridge_tilesets[1][j].setTexture(&tilesetsBridgeTexture);
		bridge_tilesets[1][j].setTextureRect(IntRect(textureBridgeSize.x*3, textureBridgeSize.y*j, textureBridgeSize.x*3, textureBridgeSize.y));
	
		bridge_tilesets_edit[1][j].setSize(Vector2f(tilesetSize*3, tilesetSize));
		bridge_tilesets_edit[1][j].setTexture(&tilesetsBridgeTexture);
		bridge_tilesets_edit[1][j].setTextureRect(IntRect(textureBridgeSize.x*3, textureBridgeSize.y*j, textureBridgeSize.x*3, textureBridgeSize.y));
		
		bridge_tilesets_transparent[1][j].setSize(Vector2f(tilesetSize*3, tilesetSize));
		bridge_tilesets_transparent[1][j].setTexture(&tilesetsBridgeTexture);
		bridge_tilesets_transparent[1][j].setFillColor(Color(0, 0, 0, 80));
		bridge_tilesets_transparent[1][j].setTextureRect(IntRect(textureBridgeSize.x*3, textureBridgeSize.y*j, textureBridgeSize.x*3, textureBridgeSize.y));
	}	
	
	RectangleShape square_tilests[10];
	RectangleShape square_tilesets_edit[10];
	RectangleShape square_tilesets_transparent[10];
	
	for(j = 0; j<4; j++)
	{
		square_tilests[j].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
		square_tilests[j].setTexture(&tilesetsTexture);
		square_tilests[j].setTextureRect(IntRect(textureSize.x*(j*2), textureSize.y*1, textureSize.x * 2, textureSize.y * 2));
		
		square_tilesets_edit[j].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
		square_tilesets_edit[j].setTexture(&tilesetsTexture);
		square_tilesets_edit[j].setTextureRect(IntRect(textureSize.x*(j*2), textureSize.y*1, textureSize.x * 2, textureSize.y * 2));

		square_tilesets_transparent[j].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
		square_tilesets_transparent[j].setFillColor(Color(0, 0, 0, 80));
		square_tilesets_transparent[j].setTexture(&tilesetsTexture);
		square_tilesets_transparent[j].setTextureRect(IntRect(textureSize.x*(j*2), textureSize.y*1, textureSize.x * 2, textureSize.y * 2));
	}

	i = 28;
	j = 6;
	int no = 4;
	square_tilests[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilests[no].setTexture(&tilesetsTexture);
	square_tilests[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));
		
	square_tilesets_edit[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_edit[no].setTexture(&tilesetsTexture);
	square_tilesets_edit[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	square_tilesets_transparent[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_transparent[no].setFillColor(Color(0, 0, 0, 80));
	square_tilesets_transparent[no].setTexture(&tilesetsTexture);
	square_tilesets_transparent[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	i = 30;
	j = 6;
	no = 5;
	square_tilests[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilests[no].setTexture(&tilesetsTexture);
	square_tilests[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));
		
	square_tilesets_edit[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_edit[no].setTexture(&tilesetsTexture);
	square_tilesets_edit[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	square_tilesets_transparent[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_transparent[no].setFillColor(Color(0, 0, 0, 80));
	square_tilesets_transparent[no].setTexture(&tilesetsTexture);
	square_tilesets_transparent[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	i = 32;
	j = 6;
	no = 6;
	square_tilests[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilests[no].setTexture(&tilesetsTexture);
	square_tilests[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));
		
	square_tilesets_edit[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_edit[no].setTexture(&tilesetsTexture);
	square_tilesets_edit[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	square_tilesets_transparent[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_transparent[no].setFillColor(Color(0, 0, 0, 80));
	square_tilesets_transparent[no].setTexture(&tilesetsTexture);
	square_tilesets_transparent[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	i = 34;
	j = 6;
	no = 7;
	square_tilests[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilests[no].setTexture(&tilesetsTexture);
	square_tilests[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));
		
	square_tilesets_edit[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_edit[no].setTexture(&tilesetsTexture);
	square_tilesets_edit[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	square_tilesets_transparent[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_transparent[no].setFillColor(Color(0, 0, 0, 80));
	square_tilesets_transparent[no].setTexture(&tilesetsTexture);
	square_tilesets_transparent[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	i = 117;
	j = 3;
	no = 8;
	square_tilests[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilests[no].setTexture(&tilesetsTexture);
	square_tilests[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));
		
	square_tilesets_edit[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_edit[no].setTexture(&tilesetsTexture);
	square_tilesets_edit[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));

	square_tilesets_transparent[no].setSize(Vector2f(tilesetSize * 2, tilesetSize * 2));
	square_tilesets_transparent[no].setFillColor(Color(0, 0, 0, 80));
	square_tilesets_transparent[no].setTexture(&tilesetsTexture);
	square_tilesets_transparent[no].setTextureRect(IntRect(textureSize.x*j, textureSize.y*i, textureSize.x * 2, textureSize.y * 2));
	

	RectangleShape character;
	character.setSize(Vector2f(tilesetSize, tilesetSize));
	character.setFillColor(Color(21, 21, 21, 150));
	
	RectangleShape editModeHolder;
	editModeHolder.setFillColor(Color(46, 46, 46, 240));
	editModeHolder.setSize(Vector2f(400, 608));
	
	RectangleShape categoryGround(Vector2f(tilesetSize, tilesetSize));
	categoryGround.setTexture(&tilesetsTexture);
	categoryGround.setTextureRect(IntRect(textureSize.x*0, textureSize.y*0, textureSize.x, textureSize.y));
	
	RectangleShape categoryObject1(Vector2f(tilesetSize, tilesetSize));
	categoryObject1.setTexture(&tilesetsTexture);
	categoryObject1.setTextureRect(IntRect(textureSize.x*0, textureSize.y*5, textureSize.x, textureSize.y));
	
	RectangleShape categoryGround2(Vector2f(tilesetSize, tilesetSize));
	categoryGround2.setTexture(&tilesetsTexture);
	categoryGround2.setTextureRect(IntRect(textureSize.x*0, textureSize.y*5, textureSize.x, textureSize.y));

	Clock clock;
	View view;
	view.reset(FloatRect(0, 0, screenW, screenH));
	view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));

	//the loop that draws the game
    while (window.isOpen())
    { 
		window.setView(window.getDefaultView());
		//the loop that checks for different inputs
        while (window.pollEvent(event))
        {
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
                window.close();
			}
			if(event.type == Event::MouseMoved)
			{
				mouseLocation = Mouse::getPosition(window);
			}
			if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::E))
			{
					modeEdit = !modeEdit;
					modeShowInventory = true;
					modeEditShowObjects = false;
					modeInventory = INVENTORY_CATEGORY_GROUND;
					lastTerrainUsed = -1;
			}
			else if(mapEditor.keyPressed(lastTerrainUsed, modeShowInventory, modeEditShowObjects, modeEdit, modeInventory, event, editLocation, muddyMap, muddyMap2, objectsMap, mapSizeH, mapSizeW)) {
				//null constructor
			}
			if(event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
			{
				if(mapEditor.mousePressed(modeEdit, modeShowInventory, modeEditShowObjects, lastTerrainUsed, modeInventory, mouseLocation, editLocation, offset, tilesetSize, editModeHolder, grass_tilesets_edit, water_tilesets_edit, bridge_tilesets_edit, square_tilesets_edit))
				{

				}
			}
			if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Left) && animation && animation != 1)
			{
				offset.y--;
			}
			else if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right) && animation && animation != 2)
			{
				offset.y++;
			}
			else if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up) && animation && animation != 3)
			{
				offset.x--;
			}
			else if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down) && animation && animation != 4)
			{
				offset.x++;
			}
			setGameViewOffset(characterPos, offset, muddyMap, muddyMap2, objectsMap, mapSizeH, mapSizeW, characterFace);
			fileSync.storeStats(characterPos, offset, level);
		}

		if(animation)
		{
			if(animation == 1 && (characterPos.x + offset.y < 14 || characterPos.x + offset.y > mapSizeW - 14))
			{
				character_tilesets[characterFace][0].move(-2, 0);
				if(((int) character_tilesets[characterFace][0].getPosition().x) % tilesetSize==0)
				{
					animation = 0;
				}
			}
			else if(animation == 1 && (characterPos.x + offset.y >= 14 && characterPos.x + offset.y <= mapSizeW - 14))
			{
				character_tilesets[characterFace][0].move(-2, 0);
				if(((int) character_tilesets[characterFace][0].getPosition().x) % tilesetSize==0)
				{
					animation = 0;
					offset.y--;
				}
				else
				{
					view.reset(FloatRect(0, 0, screenW, screenH));
					int centerY = characterPos.y*tilesetSize + tilesetSize/2;
					if(offset.x == 0 || offset.x == 101) centerY = screenH/2;
					view.setCenter(Vector2f((int) character_tilesets[characterFace][0].getPosition().x + tilesetSize/2, centerY));
					window.setView(view);
				}
			}
			else if(animation == 2 && (characterPos.x + offset.y < 14 || characterPos.x + offset.y > mapSizeW - 14))
			{
				character_tilesets[characterFace][0].move(2, 0);
				if(((int) character_tilesets[characterFace][0].getPosition().x) % tilesetSize==0)
				{
					animation = 0;
				}
			}
			else if(animation == 2 && (characterPos.x + offset.y >= 13 && characterPos.x + offset.y <= mapSizeW - 14))
			{
				character_tilesets[characterFace][0].move(2, 0);
				if(((int) character_tilesets[characterFace][0].getPosition().x) % tilesetSize==0)
				{
					animation = 0;
					offset.y++;
				}
				else
				{
					view.reset(FloatRect(0, 0, screenW, screenH));
					int centerY = characterPos.y*tilesetSize + tilesetSize/2;
					if(offset.x == 0 || offset.x == 101) centerY = screenH/2;
					view.setCenter(Vector2f((int) character_tilesets[characterFace][0].getPosition().x + tilesetSize/2, centerY));
					window.setView(view);
				}
			}
			else if(animation == 3 && (characterPos.y + offset.x < 10 || characterPos.y + offset.x > mapSizeH - 10))
			{
				character_tilesets[characterFace][0].move(0, -2);
				if(((int) character_tilesets[characterFace][0].getPosition().y) % tilesetSize==0)
				{
					animation = 0;
				}
			}
			else if(animation == 3 && (characterPos.y + offset.x >= 10 && characterPos.y + offset.x <= mapSizeH - 10))
			{
				character_tilesets[characterFace][0].move(0, -2);
				if(((int) character_tilesets[characterFace][0].getPosition().y) % tilesetSize==0)
				{
					animation = 0;
					offset.x--;
				}
				else
				{
					view.reset(FloatRect(0, 0, screenW, screenH));
					int centerX = characterPos.x*tilesetSize + tilesetSize/2;
					if(offset.y == 0) centerX = screenW/2;
					view.setCenter(Vector2f(centerX, (int) character_tilesets[characterFace][0].getPosition().y +  tilesetSize/2));
					window.setView(view);
				}
			}
			else if(animation == 4 && (characterPos.y + offset.x < 9 || characterPos.y + offset.x > mapSizeH - 11))
			{
				character_tilesets[characterFace][0].move(0, 2);
				if(((int) character_tilesets[characterFace][0].getPosition().y) % tilesetSize==0)
				{
					animation = 0;
				}
			}
			else if(animation == 4 && (characterPos.y + offset.x >= 9 && characterPos.y + offset.x <= mapSizeH - 11))
			{
				character_tilesets[characterFace][0].move(0, 2);
				if(((int) character_tilesets[characterFace][0].getPosition().y) % tilesetSize==0)
				{
					animation = 0;
					offset.x++;
				}
				else
				{
					view.reset(FloatRect(0, 0, screenW, screenH));
					int centerX = characterPos.x*tilesetSize + tilesetSize/2;
					if(offset.y == 0) centerX = screenW/2;
					view.setCenter(Vector2f(centerX, (int) character_tilesets[characterFace][0].getPosition().y +  tilesetSize/2));
					window.setView(view);
				}
			}
			else
			{
				animation = 0;
			}
		}

		window.clear();
		int limitX, limitY;
		if(offset.x > 0 && offset.x < screenH)
		{
			i = offset.x - 2;
			limitX = offset.x + screenH/tilesetSize + 2;
		}
		else
		{						
			i = offset.x;
			limitX = offset.x + screenH/tilesetSize;
		}
		for(i; i < limitX; i++)
		{
			if(offset.y > 0 && offset.y < screenW)
		{
			j = offset.y - 2;
			limitY = offset.y + screenW/tilesetSize + 2;
		}
		else
		{
			j = offset.y;
			limitY = offset.y + screenW/tilesetSize;
		}
			for(j; j < limitY; j++)
			{
				int uvX, uvY;
				if(muddyMap[i][j] >= 20 && muddyMap[i][j] < 70)
				{
					map.getTerrainByType(muddyMap[i][j], uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(muddyMap[i][j] >= 70 && muddyMap[i][j] < 120)
				{
					map.getTerrainByType(muddyMap[i][j], uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(muddyMap[i][j] >= 120 && muddyMap[i][j] < 150)
				{
					map.getTerrainByType(muddyMap[i][j], uvX, uvY);
					water_tilests[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
					window.draw(water_tilests[uvX][uvY]);
				}
			}
		}
		if(modeEdit && modeShowInventory && !modeEditShowObjects)
		{
			if(lastTerrainUsed != -1)
			{
				int uvX, uvY;
				if(lastTerrainUsed >= 20 && lastTerrainUsed < 70)
				{
					map.getTerrainByType(lastTerrainUsed, uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(lastTerrainUsed >= 70 && lastTerrainUsed < 120)
				{
					map.getTerrainByType(lastTerrainUsed, uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(lastTerrainUsed >= 120 && lastTerrainUsed < 150)
				{
					map.getTerrainByType(lastTerrainUsed, uvX, uvY);
					water_tilests[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(water_tilests[uvX][uvY]);
				}
			}

			terrainPointer.setPosition((editLocation.y-offset.y)*tilesetSize + 16, (editLocation.x-offset.x)*tilesetSize + 16);
			window.draw(terrainPointer);

			mousePointer.setPosition((mouseLocation.x/tilesetSize) * tilesetSize + 16, (mouseLocation.y/tilesetSize) * tilesetSize + 16);
			window.draw(mousePointer);

		}
		if(offset.x > 0 && offset.x < screenH)
		{
			i = offset.x - 1;
			limitX = offset.x + screenH/tilesetSize + 1;
		}
		else
		{						
			i = offset.x;
			limitX = offset.x + screenH/tilesetSize;
		}
		for(i; i < limitX; i++)
		{
			if(offset.y > 0 && offset.y < screenW)
		{
			j = offset.y - 1;
			limitY = offset.y + screenW/tilesetSize + 1;
		}
		else
		{
			j = offset.y;
			limitY = offset.y + screenW/tilesetSize;
		}
			for(j; j < limitY; j++)
			{
				int uvX, uvY;
				int objectTypeN = abs(muddyMap2[i][j]);
				if(modeEdit && modeInventory < 1)
				{
					if(objectTypeN >= 70 && objectTypeN < 130)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						water_tilesets_transparent[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilesets_transparent[uvX][uvY]);
					}
				}
				else
				{
					if(objectTypeN >= 70 && objectTypeN < 130)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						water_tilests[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilests[uvX][uvY]);
					}
				}
			}
		}
		if(offset.x > 0 && offset.x < screenH)
		{
			i = offset.x - 3;
			limitX = offset.x + screenH/tilesetSize + 3;
		}
		else
		{						
			i = offset.x;
			limitX = offset.x + screenH/tilesetSize;
		}
		for(i; i < limitX; i++)
		{
			if(characterPos.y == i - offset.x)
			{
				if(animation == 1 || animation == 2)
				{
					character_tilesets[characterFace][0].setPosition(character_tilesets[characterFace][0].getPosition().x, characterPos.y*tilesetSize);
				}
				else if(animation == 3 || animation == 4)
				{
					character_tilesets[characterFace][0].setPosition(characterPos.x*tilesetSize, character_tilesets[characterFace][0].getPosition().y);
				}
				else if(animation == 0)
				{
					character_tilesets[characterFace][0].setPosition(characterPos.x*tilesetSize, characterPos.y*tilesetSize);
				}
				window.draw(character_tilesets[characterFace][0]);
			}
			if(offset.y > 0 && offset.y < screenW)
			{
				j = offset.y - 3;
				limitY = offset.y + screenW/tilesetSize + 3;
			}
			else
			{
				j = offset.y;
				limitY = offset.y + screenW/tilesetSize;
			}
			for(j; j < limitY; j++)
			{
				if(modeEdit && modeInventory < 2)
				{
					int uvX, uvY;
					int objectTypeN = abs(objectsMap[i][j]);
					if(objectTypeN > 10 && objectTypeN < 70)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						square_tilesets_transparent[uvX].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(square_tilesets_transparent[uvX]);
					}
					else if(objectTypeN >= 70 && objectTypeN < 130)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						water_tilesets_transparent[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilesets_transparent[uvX][uvY]);
					}
					else if(objectTypeN >= 150 && objectTypeN < 160)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						bridge_tilesets_transparent[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(bridge_tilesets_transparent[uvX][uvY]);
					}
				}
				else
				{
					int uvX, uvY;
					int objectTypeN = abs(objectsMap[i][j]);
					if(objectTypeN > 10 && objectTypeN < 70)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						square_tilests[uvX].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(square_tilests[uvX]);
					}
					else if(objectTypeN >= 70 && objectTypeN < 130)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						water_tilests[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilests[uvX][uvY]);
					}
					else if(objectTypeN >= 150 && objectTypeN < 160)
					{
						map.getObjectByType(objectTypeN, uvX, uvY);
						bridge_tilesets[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(bridge_tilesets[uvX][uvY]);
					}
				}
			}

		}
		for(i = 0; i<bridgePerLvlOff; i++)
		{
			if(bridgeByLvl[i][2] <= level)
			{
				if(bridgeByLvl[i][3] == 0)
				{
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1]] = 151;
					objectsMap[bridgeByLvl[i][0] + 1][bridgeByLvl[i][1]] = 9;
					objectsMap[bridgeByLvl[i][0] + 2][bridgeByLvl[i][1]] = 8;
				}
				else if(bridgeByLvl[i][3] == 1)
				{
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1]] = 154;
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1] + 1] = 9;
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1] + 2] = 8;
				}
			}
			else
			{
				if(bridgeByLvl[i][3] == 0)
				{
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1]] = 10;
					objectsMap[bridgeByLvl[i][0] + 1][bridgeByLvl[i][1]] = 10;
					objectsMap[bridgeByLvl[i][0] + 2][bridgeByLvl[i][1]] = 10;
				}
				else if(bridgeByLvl[i][3] == 1)
				{
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1]] = 10;
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1] + 1] = 10;
					objectsMap[bridgeByLvl[i][0]][bridgeByLvl[i][1] + 2] = 10;
				}
			}
		}

		if(objectsMap[characterPos.y + offset.x][characterPos.x + offset.y] == 9)
		{
				if(animation == 1 || animation == 2)
				{
					character_tilesets[characterFace][0].setPosition(character_tilesets[characterFace][0].getPosition().x, characterPos.y*tilesetSize);
				}
				else if(animation == 3 || animation == 4)
				{
					character_tilesets[characterFace][0].setPosition(characterPos.x*tilesetSize, character_tilesets[characterFace][0].getPosition().y);
				}
				else if(animation == 0)
				{
					character_tilesets[characterFace][0].setPosition(characterPos.x*tilesetSize, characterPos.y*tilesetSize);
				}
			window.draw(character_tilesets[characterFace][0]);
		}
		
		if(modeEdit && modeShowInventory && modeEditShowObjects)
		{
			if(lastTerrainUsed != -1)
			{
				int uvX, uvY;
				if(lastTerrainUsed > 10 && lastTerrainUsed < 70)
				{
					map.getObjectByType(lastTerrainUsed, uvX, uvY);
					square_tilests[uvX].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(square_tilests[uvX]);
				}
				else if(lastTerrainUsed >= 70 && lastTerrainUsed < 130)
				{
					map.getObjectByType(lastTerrainUsed, uvX, uvY);
					water_tilests[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(water_tilests[uvX][uvY]);
				}
				else if(lastTerrainUsed >= 150 && lastTerrainUsed < 160)
				{
					map.getObjectByType(lastTerrainUsed, uvX, uvY);
					bridge_tilesets[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(bridge_tilesets[uvX][uvY]);
				}
			}

			terrainPointer.setPosition((editLocation.y-offset.y)*tilesetSize + 16, (editLocation.x-offset.x)*tilesetSize + 16);
			window.draw(terrainPointer);

			mousePointer.setPosition((mouseLocation.x/tilesetSize) * tilesetSize + 16, (mouseLocation.y/tilesetSize) * tilesetSize + 16);
			window.draw(mousePointer);

		}
		if(modeEdit)
		{
			if((editLocation.y-offset.y)*tilesetSize>=0)
			{
				leftSideClicked = (editLocation.y-offset.y)*tilesetSize < window.getSize().x/2;
			}
			int rightSideAddition = 0;
			if(leftSideClicked) rightSideAddition = 464;

			editModeHolder.setPosition(0 + rightSideAddition, 0);
			window.draw(editModeHolder);

			categoryGround.setPosition(30 + rightSideAddition, 30);
			window.draw(categoryGround);

			categoryGround2.setPosition(30 + 35*1 + rightSideAddition, 30);
			window.draw(categoryGround2);

			categoryObject1.setPosition(30 + 35*2 + rightSideAddition, 30);
			window.draw(categoryObject1);

			mapEditor.setRectanlgeShapes(categoryGround, categoryGround2, categoryObject1);

			if(modeInventory == INVENTORY_CATEGORY_GROUND)
			{
				grass_tilesets_edit[12][0].setPosition(20 + 35*0 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][0]);

				grass_tilesets_edit[43][6].setPosition(20 + 35*1 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[43][6]);

				grass_tilesets_edit[12][1].setPosition(20 + 35*2 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][1]);

				grass_tilesets_edit[12][2].setPosition(20 + 35*3 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][2]);

				grass_tilesets_edit[12][3].setPosition(20 + 35*4 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][3]);

				grass_tilesets_edit[12][4].setPosition(20 + 35*5 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][4]);

				grass_tilesets_edit[13][4].setPosition(20 + 35*6 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[13][4]);

				grass_tilesets_edit[14][4].setPosition(20 + 35*7 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[14][4]);

				grass_tilesets_edit[12][5].setPosition(20 + 35*8 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][5]);

				grass_tilesets_edit[12][6].setPosition(20 + 35*9 + rightSideAddition, 80);
				window.draw(grass_tilesets_edit[12][6]);

				grass_tilesets_edit[12][7].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[12][7]);

				grass_tilesets_edit[13][5].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[13][5]);

				grass_tilesets_edit[13][6].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[13][6]);

				grass_tilesets_edit[13][7].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[13][7]);

				grass_tilesets_edit[14][5].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[14][5]);

				grass_tilesets_edit[14][6].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[14][6]);

				grass_tilesets_edit[14][7].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[14][7]);

				grass_tilesets_edit[13][0].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[13][0]);

				grass_tilesets_edit[13][1].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[13][1]);

				grass_tilesets_edit[14][0].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*1);
				window.draw(grass_tilesets_edit[14][0]);

				grass_tilesets_edit[14][1].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[14][1]);

				grass_tilesets_edit[15][4].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[15][4]);

				grass_tilesets_edit[15][5].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[15][5]);

				grass_tilesets_edit[16][4].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[16][4]);

				grass_tilesets_edit[16][5].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[16][5]);

				grass_tilesets_edit[36][0].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[36][0]);

				grass_tilesets_edit[36][1].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[36][1]);

				grass_tilesets_edit[36][2].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[36][2]);

				grass_tilesets_edit[36][3].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[36][3]);

				grass_tilesets_edit[36][4].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*2);
				window.draw(grass_tilesets_edit[36][4]);

				grass_tilesets_edit[37][4].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[37][4]);

				grass_tilesets_edit[38][4].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[38][4]);

				grass_tilesets_edit[36][5].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[36][5]);

				grass_tilesets_edit[36][6].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[36][6]);

				grass_tilesets_edit[36][7].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[36][7]);

				grass_tilesets_edit[37][5].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[37][5]);

				grass_tilesets_edit[37][6].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[37][6]);

				grass_tilesets_edit[37][7].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[37][7]);

				grass_tilesets_edit[38][5].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[38][5]);

				grass_tilesets_edit[38][6].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*3);
				window.draw(grass_tilesets_edit[38][6]);

				grass_tilesets_edit[38][7].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[38][7]);

				grass_tilesets_edit[37][0].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[37][0]);

				grass_tilesets_edit[37][1].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[37][1]);

				grass_tilesets_edit[38][0].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[38][0]);

				grass_tilesets_edit[38][1].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[38][1]);

				grass_tilesets_edit[39][4].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[39][4]);

				grass_tilesets_edit[39][5].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[39][5]);

				grass_tilesets_edit[40][4].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[40][4]);

				grass_tilesets_edit[40][5].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*4);
				window.draw(grass_tilesets_edit[40][5]);

				water_tilesets_edit[1][6].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*4);
				window.draw(water_tilesets_edit[1][6]);

			}
			else if(modeInventory == INVENTORY_CATEGORY_OBJECTS)
			{
				square_tilesets_edit[0].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*0);
				window.draw(square_tilesets_edit[0]);
				
				square_tilesets_edit[1].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*0);
				window.draw(square_tilesets_edit[1]);
				
				square_tilesets_edit[2].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*0);
				window.draw(square_tilesets_edit[2]);

				square_tilesets_edit[3].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*0);
				window.draw(square_tilesets_edit[3]);
				
				square_tilesets_edit[4].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*0);
				window.draw(square_tilesets_edit[4]);

				square_tilesets_edit[5].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*2);
				window.draw(square_tilesets_edit[5]);
				
				square_tilesets_edit[6].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*2);
				window.draw(square_tilesets_edit[6]);
				
				square_tilesets_edit[7].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*2);
				window.draw(square_tilesets_edit[7]);

				square_tilesets_edit[8].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*2);
				window.draw(square_tilesets_edit[8]);

				bridge_tilesets_edit[0][0].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*4);
				window.draw(bridge_tilesets_edit[0][0]);

				bridge_tilesets_edit[0][1].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*4);
				window.draw(bridge_tilesets_edit[0][1]);

				bridge_tilesets_edit[0][2].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*4);
				window.draw(bridge_tilesets_edit[0][2]);

				bridge_tilesets_edit[1][0].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*4);
				window.draw(bridge_tilesets_edit[1][0]);

				bridge_tilesets_edit[1][1].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*5);
				window.draw(bridge_tilesets_edit[1][1]);

				bridge_tilesets_edit[1][2].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*6);
				window.draw(bridge_tilesets_edit[1][2]);
			}
			else if(modeInventory == INVENTORY_CATEGORY_GROUND2)
			{
				water_tilesets_edit[0][1].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][1]);

				water_tilesets_edit[0][2].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][2]);

				water_tilesets_edit[0][3].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][3]);

				water_tilesets_edit[0][4].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][4]);

				water_tilesets_edit[1][4].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[1][4]);

				water_tilesets_edit[2][4].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[2][4]);

				water_tilesets_edit[0][5].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][5]);

				water_tilesets_edit[0][6].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][6]);

				water_tilesets_edit[0][7].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[0][7]);

				water_tilesets_edit[1][5].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*0);
				window.draw(water_tilesets_edit[1][5]);

				water_tilesets_edit[1][7].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[1][7]);

				water_tilesets_edit[2][5].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[2][5]);

				water_tilesets_edit[2][6].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[2][6]);

				water_tilesets_edit[2][7].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[2][7]);

				water_tilesets_edit[3][4].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[3][4]);

				water_tilesets_edit[3][5].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[3][5]);

				water_tilesets_edit[4][4].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[4][4]);

				water_tilesets_edit[4][5].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[4][5]);

				water_tilesets_edit[0][0].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[0][0]);

				water_tilesets_edit[6][1].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*1);
				window.draw(water_tilesets_edit[6][1]);

				water_tilesets_edit[6][2].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[6][2]);

				water_tilesets_edit[6][3].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[6][3]);

				water_tilesets_edit[6][4].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[6][4]);

				water_tilesets_edit[7][4].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[7][4]);

				water_tilesets_edit[8][4].setPosition(20 + 35*4 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[8][4]);

				water_tilesets_edit[6][5].setPosition(20 + 35*5 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[6][5]);

				water_tilesets_edit[6][6].setPosition(20 + 35*6 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[6][6]);

				water_tilesets_edit[6][7].setPosition(20 + 35*7 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[6][7]);

				water_tilesets_edit[7][5].setPosition(20 + 35*8 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[7][5]);

				water_tilesets_edit[7][7].setPosition(20 + 35*9 + rightSideAddition, 80 + 35*2);
				window.draw(water_tilesets_edit[7][7]);

				water_tilesets_edit[8][5].setPosition(20 + 35*0 + rightSideAddition, 80 + 35*3);
				window.draw(water_tilesets_edit[8][5]);

				water_tilesets_edit[8][6].setPosition(20 + 35*1 + rightSideAddition, 80 + 35*3);
				window.draw(water_tilesets_edit[8][6]);

				water_tilesets_edit[8][7].setPosition(20 + 35*2 + rightSideAddition, 80 + 35*3);
				window.draw(water_tilesets_edit[8][7]);

				water_tilesets_edit[6][0].setPosition(20 + 35*3 + rightSideAddition, 80 + 35*3);
				window.draw(water_tilesets_edit[6][0]);
			}
		}

		window.display();

	}

	return 0;
}