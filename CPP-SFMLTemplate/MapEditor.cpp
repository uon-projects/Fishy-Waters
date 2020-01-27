#include "MapEditor.h"
#include "FileSync.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"

//Compiler Directives
using namespace std;
using namespace sf;

FileSync fileSync;
Map mapInfo;
RectangleShape categoryGround, categoryGround2, categoryObject1;
const int INVENTORY_CATEGORY_GROUND = 0;
const int INVENTORY_CATEGORY_GROUND2 = 1;
const int INVENTORY_CATEGORY_OBJECTS = 2;

MapEditor::MapEditor(void)
{
	//initialise
}

void MapEditor::setRectanlgeShapes(RectangleShape nCategoryGround, RectangleShape nCategoryGround2, RectangleShape nCategoryObject1)
{
	categoryGround = nCategoryGround;
	categoryGround2 = nCategoryGround2;
	categoryObject1 = nCategoryObject1;
}

bool MapEditor::rectClicked(RectangleShape sprite, Vector2i mouseLocation)
{
	IntRect water11Btn(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	if (water11Btn.contains(mouseLocation))
	{
		return true;
	}
	return false;
}

bool MapEditor::keyPressed(int &lastTerrainUsed, bool modeShowInventory, bool modeEditShowObjects, bool modeEdit, int modeInventory, Event event, Vector2i &editLocation, int muddyMap[120][200], int muddyMap2[120][200], int objectsMap[120][200], int mapSizeH, int mapSizeW)
{
	bool pressed = false;
	if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Q))
    {
        pressed = true;
        if(!modeEditShowObjects)
        {
            lastTerrainUsed = muddyMap[editLocation.x][editLocation.y];
        }
    }
	else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Delete))
    {
        pressed = true;
        if(modeInventory == INVENTORY_CATEGORY_GROUND)
        {
            if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
            {
                muddyMap[editLocation.x][editLocation.y] = 20;
                fileSync.storeMap(muddyMap, mapSizeH, mapSizeW);
            }
        }
        else if(modeInventory == INVENTORY_CATEGORY_GROUND2)
        {
            if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
            {
                muddyMap2[editLocation.x][editLocation.y] = 0;
                fileSync.storeMap2(muddyMap2, mapSizeH, mapSizeW);
            }
        }
        else
        {
            if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
            {
                objectsMap[editLocation.x][editLocation.y] = 10;
                fileSync.storeObjectsMap(objectsMap, mapSizeH, mapSizeW);
                fileSync.loadObjectsMap(objectsMap, mapSizeH, mapSizeW);
            }
        }
    }
	else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Return))
    {
        pressed = true;
        if(modeInventory == INVENTORY_CATEGORY_GROUND)
        {
            muddyMap[editLocation.x][editLocation.y] = lastTerrainUsed;
            fileSync.storeMap(muddyMap, mapSizeH, mapSizeW);
        }
        else if(modeInventory == INVENTORY_CATEGORY_GROUND2)
        {
            muddyMap2[editLocation.x][editLocation.y] = lastTerrainUsed;
            fileSync.storeMap2(muddyMap2, mapSizeH, mapSizeW);
        }
        else if(modeInventory == INVENTORY_CATEGORY_OBJECTS)
        {
			cout<<"here";
            if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
            {
                objectsMap[editLocation.x][editLocation.y] = lastTerrainUsed;
                fileSync.storeObjectsMap(objectsMap, mapSizeH, mapSizeW);
                fileSync.loadObjectsMap(objectsMap, mapSizeH, mapSizeW);
            }
        }
    }
	else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::A))
    {
        pressed = true;
        editLocation.y--;
    }
	else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::D))
    {
        pressed = true;
        editLocation.y++;
    }
	else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::W))
    {
        pressed = true;
        editLocation.x--;
    }
	else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S))
    {
        pressed = true;
        editLocation.x++;
    }
	return pressed;
}

bool MapEditor::mousePressed(bool modeEdit, bool &modeShowInventory, bool &modeEditShowObjects, int &lastTerrainUsed, int &modeInventory, Vector2i &mouseLocation, Vector2i &editLocation, Vector2i &offset, int tilesetSize, RectangleShape editModeHolder, RectangleShape grass_tilesets_edit[66][8], RectangleShape water_tilesets_edit[12][8], RectangleShape bridge_tilesets_edit[2][3], RectangleShape square_tilesets_edit[10])
{
	bool mousePressed = false;
	
	if(modeEdit && modeShowInventory && rectClicked(categoryGround, mouseLocation))
    {
        modeInventory = 0;
        modeEditShowObjects = false;
        lastTerrainUsed = -1;
    } else if(modeEdit && modeShowInventory && rectClicked(categoryGround2, mouseLocation))
    {
        modeInventory = 1;
        modeEditShowObjects = true;
        lastTerrainUsed = -1;
    } else if(modeEdit && modeShowInventory && rectClicked(categoryObject1, mouseLocation))
    {
        modeInventory = 2;
        modeEditShowObjects = true;
        lastTerrainUsed = -1;
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[43][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 43, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[15][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 15, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[15][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 15, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[16][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 16, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[16][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 16, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 2);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][3], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 3);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 13, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 14, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 12, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 13, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 13, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 13, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 14, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 14, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 14, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 13, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 13, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 14, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(1, 14, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 37, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 37, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 38, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[39][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 39, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[39][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 39, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[40][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 40, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[40][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 40, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 38, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 2);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][3], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 3);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 37, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 38, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 36, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 37, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 37, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 37, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 38, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 38, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(2, 38, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getTerrainType(3, 1, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 0, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 1, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 2, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[3], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 3, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 4, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 5, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 6, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 7, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[8], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(1, 8, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[0][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(3, 0, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[0][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(3, 0, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[0][2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(3, 0, 2);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[1][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(3, 1, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[1][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(3, 1, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[1][2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(3, 1, 2);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 2);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][3], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 3);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 1, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 2, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 1, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 1, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 1, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 2, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 2, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 2, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 0, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][1], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 1);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][2], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 2);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][3], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 3);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 7, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 8, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 7, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 7, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 7, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 8, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][6], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 8, 6);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][7], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 8, 7);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][0], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 6, 0);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[3][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 3, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[3][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 3, 5);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[4][4], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 4, 4);
    } else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[4][5], mouseLocation))
    {
        lastTerrainUsed = mapInfo.getObjectType(2, 4, 5);
    } else if(modeEdit && modeShowInventory && editModeHolder.getGlobalBounds().left <= mouseLocation.x && editModeHolder.getGlobalBounds().left + editModeHolder.getGlobalBounds().width >= mouseLocation.x)
    {
        //prevent mistaken clicks on terrain under edit holder
    }
	else if(mouseLocation.x >= 0 && mouseLocation.x <= 832 && mouseLocation.y >= 0 && mouseLocation.y <= 574)
    {
        if(modeEdit)
        {
            editLocation.x = mouseLocation.y/tilesetSize + offset.x;
            editLocation.y = mouseLocation.x/tilesetSize + offset.y;
            modeShowInventory = true;
        }
        //cout<<mouseLocation.y/tilesetSize + offset.x<<' '<<mouseLocation.x/tilesetSize + offset.y<<'\n';
    }
	return mousePressed;
}

MapEditor::~MapEditor(void)
{
	//destroy
}
