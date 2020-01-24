#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ZeoFlow_SFML.h"

//Compiler Directives
using namespace std;
using namespace sf;
using namespace zeoFlow;

const int screenW = 864, screenH = 608;
RenderWindow window(VideoMode(screenW, screenH), "Muddy Grounds"); //the game screen

bool canGo(int fieldType, int fieldType2, int objectType)
{
	if(objectType >= 10 && objectType < 70 && fieldType < 120 && !(fieldType2>=70 && fieldType2<=85))
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

void setGameViewOffset(Vector2i &characterPos, Vector2i &offset, int muddyMap[120][200], int muddyMap2[120][200], int objectsMap[120][200], int mapSizeH, int mapSizeW)
{

	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
		if(canGo(muddyMap[characterPos.y + offset.x][characterPos.x + offset.y - 1],
			muddyMap2[characterPos.y + offset.x][characterPos.x + offset.y - 1],
			objectsMap[characterPos.y + offset.x][characterPos.x + offset.y - 1]))
		{
			if(characterPos.x + offset.y >= 14 && characterPos.x + offset.y <= mapSizeW - 14)
			{
				offset.y--;
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
	if(Keyboard::isKeyPressed(Keyboard::Right))
	{
		if(canGo(muddyMap[characterPos.y + offset.x][characterPos.x + offset.y + 1],
			muddyMap2[characterPos.y + offset.x][characterPos.x + offset.y + 1],
			objectsMap[characterPos.y + offset.x][characterPos.x + offset.y + 1]))
		{
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
	if(Keyboard::isKeyPressed(Keyboard::Up))
	{
		if(canGo(muddyMap[characterPos.y + offset.x - 1][characterPos.x + offset.y],
			muddyMap2[characterPos.y + offset.x - 1][characterPos.x + offset.y],
			objectsMap[characterPos.y + offset.x - 1][characterPos.x + offset.y]))
		{
			if(characterPos.y + offset.x >= 10 && characterPos.y + offset.x <= mapSizeH - 10)
			{
				offset.x--;
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
	if(Keyboard::isKeyPressed(Keyboard::Down))
	{
		if(canGo(muddyMap[characterPos.y + offset.x + 1][characterPos.x + offset.y],
			muddyMap2[characterPos.y + offset.x + 1][characterPos.x + offset.y],
			objectsMap[characterPos.y + offset.x + 1][characterPos.x + offset.y]))
		{
			if(characterPos.y + offset.x >= 9 && characterPos.y + offset.x <= mapSizeH - 11)
			{
				offset.x++;
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

bool rectClicked(RectangleShape sprite, Vector2i mouseLocation)
{
	IntRect water11Btn(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	if (water11Btn.contains(mouseLocation))
	{
		return true;
	}
	return false;
}

int getObjectType(int type, int x, int y)
{
	//type 1 - 2x2
	//type 2 - 1x1
	//type 3 - bridge
	if(type == 1 && x == 0) {
		return 11;
	} else if(type == 1 && x == 1) {
		return 12;
	} else if(type == 1 && x == 2) {
		return 13;
	} else if(type == 1 && x == 3) {
		return 14;
	} else if(type == 1 && x == 4) {
		return 15;
	} else if(type == 1 && x == 5) {
		return 16;
	} else if(type == 1 && x == 6) {
		return 17;
	} else if(type == 1 && x == 7) {
		return 18;
	} else if(type == 1 && x == 8) {
		return 19;
	} else if(type == 2 && x == 0 && y == 1) {
		return 70;
	} else if(type == 2 && x == 0 && y == 2) {
		return 71;
	} else if(type == 2 && x == 0 && y == 3) {
		return 72;
	} else if(type == 2 && x == 0 && y == 4) {
		return 73;
	} else if(type == 2 && x == 1 && y == 4) {
		return 74;
	} else if(type == 2 && x == 2 && y == 4) {
		return 75;
	} else if(type == 2 && x == 0 && y == 5) {
		return 76;
	} else if(type == 2 && x == 0 && y == 6) {
		return 77;
	} else if(type == 2 && x == 0 && y == 7) {
		return 78;
	} else if(type == 2 && x == 1 && y == 5) {
		return 79;
	} else if(type == 2 && x == 1 && y == 6) {
		return 80;
	} else if(type == 2 && x == 1 && y == 7) {
		return 81;
	} else if(type == 2 && x == 2 && y == 5) {
		return 82;
	} else if(type == 2 && x == 2 && y == 6) {
		return 83;
	} else if(type == 2 && x == 2 && y == 7) {
		return 84;
	} else if(type == 2 && x == 0 && y == 0) {
		return 85;
	} else if(type == 2 && x == 6 && y == 1) {
		return 86;
	} else if(type == 2 && x == 6 && y == 2) {
		return 87;
	} else if(type == 2 && x == 6 && y == 3) {
		return 88;
	} else if(type == 2 && x == 6 && y == 4) {
		return 89;
	} else if(type == 2 && x == 7 && y == 4) {
		return 90;
	} else if(type == 2 && x == 8 && y == 4) {
		return 91;
	} else if(type == 2 && x == 6 && y == 5) {
		return 92;
	} else if(type == 2 && x == 6 && y == 6) {
		return 93;
	} else if(type == 2 && x == 6 && y == 7) {
		return 94;
	} else if(type == 2 && x == 7 && y == 5) {
		return 95;
	} else if(type == 2 && x == 7 && y == 6) {
		return 96;
	} else if(type == 2 && x == 7 && y == 7) {
		return 97;
	} else if(type == 2 && x == 8 && y == 5) {
		return 98;
	} else if(type == 2 && x == 8 && y == 6) {
		return 99;
	} else if(type == 2 && x == 8 && y == 7) {
		return 100;
	} else if(type == 2 && x == 6 && y == 0) {
		return 101;
	} else if(type == 2 && x == 3 && y == 4) {
		return 102;
	} else if(type == 2 && x == 3 && y == 5) {
		return 103;
	} else if(type == 2 && x == 4 && y == 4) {
		return 104;
	} else if(type == 2 && x == 4 && y == 5) {
		return 105;
	} else if(type == 3 && x == 0 && y == 0) {
		return 150;
	} else if(type == 3 && x == 0 && y == 1) {
		return 151;
	} else if(type == 3 && x == 0 && y == 2) {
		return 152;
	} else if(type == 3 && x == 1 && y == 0) {
		return 153;
	} else if(type == 3 && x == 1 && y == 1) {
		return 154;
	} else if(type == 3 && x == 1 && y == 2) {
		return 155;
	}
}

void getObjectByType(int type, int &x, int &y)
{
	if(type == 11) {
		x = 0;
	} else if(type == 12) {
		x = 1;
	} else if(type == 13) {
		x = 2;
	} else if(type == 14) {
		x = 3;
	} else if(type == 15) {
		x = 4;
	} else if(type == 16) {
		x = 5;
	} else if(type == 17) {
		x = 6;
	} else if(type == 18) {
		x = 7;
	} else if(type == 19) {
		x = 8;
	} else if(type == 70) {
		x = 0;
		y = 1;
	} else if(type == 71) {
		x = 0;
		y = 2;
	} else if(type == 72) {
		x = 0;
		y = 3;
	} else if(type == 73) {
		x = 0;
		y = 4;
	} else if(type == 74) {
		x = 1;
		y = 4;
	} else if(type == 75) {
		x = 2;
		y = 4;
	} else if(type == 76) {
		x = 0;
		y = 5;
	} else if(type == 77) {
		x = 0;
		y = 6;
	} else if(type == 78) {
		x = 0;
		y = 7;
	} else if(type == 79) {
		x = 1;
		y = 5;
	} else if(type == 80) {
		x = 1;
		y = 6;
	} else if(type == 81) {
		x = 1;
		y = 7;
	} else if(type == 82) {
		x = 2;
		y = 5;
	} else if(type == 83) {
		x = 2;
		y = 6;
	} else if(type == 84) {
		x = 2;
		y = 7;
	} else if(type == 85) {
		x = 0;
		y = 0;
	} else if(type == 86) {
		x = 6;
		y = 1;
	} else if(type == 87) {
		x = 6;
		y = 2;
	} else if(type == 88) {
		x = 6;
		y = 3;
	} else if(type == 89) {
		x = 6;
		y = 4;
	} else if(type == 90) {
		x = 7;
		y = 4;
	} else if(type == 91) {
		x = 8;
		y = 4;
	} else if(type == 92) {
		x = 6;
		y = 5;
	} else if(type == 93) {
		x = 6;
		y = 6;
	} else if(type == 94) {
		x = 6;
		y = 7;
	} else if(type == 95) {
		x = 7;
		y = 5;
	} else if(type == 96) {
		x = 7;
		y = 6;
	} else if(type == 97) {
		x = 7;
		y = 7;
	} else if(type == 98) {
		x = 8;
		y = 5;
	} else if(type == 99) {
		x = 8;
		y = 6;
	} else if(type == 100) {
		x = 8;
		y = 7;
	} else if(type == 101) {
		x = 6;
		y = 0;
	} else if(type == 102) {
		x = 3;
		y = 4;
	} else if(type == 103) {
		x = 3;
		y = 5;
	} else if(type == 104) {
		x = 4;
		y = 4;
	} else if(type == 105) {
		x = 4;
		y = 5;
	} else if(type == 150) {
		x = 0;
		y = 0;
	} else if(type == 151) {
		x = 0;
		y = 1;
	} else if(type == 152) {
		x = 0;
		y = 2;
	} else if(type == 153) {
		x = 1;
		y = 0;
	} else if(type == 154) {
		x = 1;
		y = 1;
	} else if(type == 155) {
		x = 1;
		y = 2;
	}
}

int getTerrainType(int type, int x, int y)
{
	//type 1 - grass
	//type 2 - mud
	//type 3 - water
	if(type == 1 && x == 43 && y == 6) {
		return 20;
	} else if(type == 1 && x == 12 && y == 1) {
		return 30;
	} else if(type == 1 && x == 12 && y == 2) {
		return 31;
	} else if(type == 1 && x == 12 && y == 3) {
		return 32;
	} else if(type == 1 && x == 12 && y == 4) {
		return 33;
	} else if(type == 1 && x == 13 && y == 4) {
		return 34;
	} else if(type == 1 && x == 14 && y == 4) {
		return 35;
	} else if(type == 1 && x == 12 && y == 5) {
		return 36;
	} else if(type == 1 && x == 12 && y == 6) {
		return 37;
	} else if(type == 1 && x == 12 && y == 7) {
		return 38;
	} else if(type == 1 && x == 13 && y == 5) {
		return 39;
	} else if(type == 1 && x == 13 && y == 6) {
		return 40;
	} else if(type == 1 && x == 13 && y == 7) {
		return 41;
	} else if(type == 1 && x == 14 && y == 5) {
		return 42;
	} else if(type == 1 && x == 14 && y == 6) {
		return 43;
	} else if(type == 1 && x == 14 && y == 7) {
		return 44;
	} else if(type == 1 && x == 13 && y == 0) {
		return 45;
	} else if(type == 1 && x == 13 && y == 1) {
		return 46;
	} else if(type == 1 && x == 14 && y == 0) {
		return 47;
	} else if(type == 1 && x == 14 && y == 1) {
		return 48;
	} else if(type == 1 && x == 12 && y == 0) {
		return 49;
	} else if(type == 1 && x == 15 && y == 4) {
		return 50;
	} else if(type == 1 && x == 15 && y == 5) {
		return 51;
	} else if(type == 1 && x == 16 && y == 4) {
		return 52;
	} else if(type == 1 && x == 16 && y == 5) {
		return 53;
	} else if(type == 2 && x == 36 && y == 1) {
		return 70;
	} else if(type == 2 && x == 36 && y == 2) {
		return 71;
	} else if(type == 2 && x == 36 && y == 3) {
		return 72;
	} else if(type == 2 && x == 36 && y == 4) {
		return 73;
	} else if(type == 2 && x == 37 && y == 4) {
		return 74;
	} else if(type == 2 && x == 38 && y == 4) {
		return 75;
	} else if(type == 2 && x == 36 && y == 5) {
		return 76;
	} else if(type == 2 && x == 36 && y == 6) {
		return 77;
	} else if(type == 2 && x == 36 && y == 7) {
		return 78;
	} else if(type == 2 && x == 37 && y == 5) {
		return 79;
	} else if(type == 2 && x == 37 && y == 6) {
		return 80;
	} else if(type == 2 && x == 37 && y == 7) {
		return 81;
	} else if(type == 2 && x == 38 && y == 5) {
		return 82;
	} else if(type == 2 && x == 38 && y == 6) {
		return 83;
	} else if(type == 2 && x == 38 && y == 7) {
		return 84;
	} else if(type == 2 && x == 36 && y == 0) {
		return 85;
	} else if(type == 2 && x == 37 && y == 0) {
		return 86;
	} else if(type == 2 && x == 37 && y == 1) {
		return 87;
	} else if(type == 2 && x == 38 && y == 0) {
		return 88;
	} else if(type == 2 && x == 38 && y == 1) {
		return 89;
	} else if(type == 2 && x == 39 && y == 4) {
		return 90;
	} else if(type == 2 && x == 39 && y == 5) {
		return 91;
	} else if(type == 2 && x == 40 && y == 4) {
		return 92;
	} else if(type == 2 && x == 40 && y == 5) {
		return 93;
	} else if(type == 3 && x == 1 && y == 6) {
		return 120;
	}
}

void getTerrainByType(int type, int &x, int &y)
{
	if(type == 20) {
		x = 43;
		y = 6;
	} else if(type == 30) {
		x = 12;
		y = 1;
	} else if(type == 31) {
		x = 12;
		y = 2;
	} else if(type == 32) {
		x = 12;
		y = 3;
	} else if(type == 33) {
		x = 12;
		y = 4;
	} else if(type == 34) {
		x = 13;
		y = 4;
	} else if(type == 35) {
		x = 14;
		y = 4;
	} else if(type == 36) {
		x = 12;
		y = 5;
	} else if(type == 37) {
		x = 12;
		y = 6;
	} else if(type == 38) {
		x = 12;
		y = 7;
	} else if(type == 39) {
		x = 13;
		y = 5;
	} else if(type == 40) {
		x = 13;
		y = 6;
	} else if(type == 41) {
		x = 13;
		y = 7;
	} else if(type == 42) {
		x = 14;
		y = 5;
	} else if(type == 43) {
		x = 14;
		y = 6;
	} else if(type == 44) {
		x = 14;
		y = 7;
	} else if(type == 45) {
		x = 13;
		y = 0;
	} else if(type == 46) {
		x = 13;
		y = 1;
	} else if(type == 47) {
		x = 14;
		y = 0;
	} else if(type == 48) {
		x = 14;
		y = 1;
	} else if(type == 49) {
		x = 12;
		y = 0;
	} else if(type == 50) {
		x = 15;
		y = 4;
	} else if(type == 51) {
		x = 15;
		y = 5;
	} else if(type == 52) {
		x = 16;
		y = 4;
	} else if(type == 53) {
		x = 16;
		y = 5;
	} else if(type == 70) {
		x = 36;
		y = 1;
	} else if(type == 71) {
		x = 36;
		y = 2;
	} else if(type == 72) {
		x = 36;
		y = 3;
	} else if(type == 73) {
		x = 36;
		y = 4;
	} else if(type == 74) {
		x = 37;
		y = 4;
	} else if(type == 75) {
		x = 38;
		y = 4;
	} else if(type == 76) {
		x = 36;
		y = 5;
	} else if(type == 77) {
		x = 36;
		y = 6;
	} else if(type == 78) {
		x = 36;
		y = 7;
	} else if(type == 79) {
		x = 37;
		y = 5;
	} else if(type == 80) {
		x = 37;
		y = 6;
	} else if(type == 81) {
		x = 37;
		y = 7;
	} else if(type == 82) {
		x = 38;
		y = 5;
	} else if(type == 83) {
		x = 38;
		y = 6;
	} else if(type == 84) {
		x = 38;
		y = 7;
	} else if(type == 85) {
		x = 36;
		y = 0;
	} else if(type == 86) {
		x = 37;
		y = 0;
	} else if(type == 87) {
		x = 37;
		y = 1;
	} else if(type == 88) {
		x = 38;
		y = 0;
	} else if(type == 89) {
		x = 38;
		y = 1;
	} else if(type == 90) {
		x = 39;
		y = 4;
	} else if(type == 91) {
		x = 39;
		y = 5;
	} else if(type == 92) {
		x = 40;
		y = 4;
	} else if(type == 93) {
		x = 40;
		y = 5;
	} else if(type == 120) {
		x = 1;
		y = 6;
	}
}

void loadMap(int muddyMap[120][200], int mapSizeH, int mapSizeW)
{
	ifstream mapRead("Assets/map/map.txt");
	for(int i = 0; i < mapSizeH; i++)
	{
		for(int j = 0; j < mapSizeW; j++)
		{
			mapRead>>muddyMap[i][j];
		}
	}
	mapRead.close();
}

void storeMap(int muddyMap[120][200], int mapSizeH, int mapSizeW)
{		
	ofstream mapNew("Assets/map/map.txt");
	for(int i = 0; i < mapSizeH; i++)
	{
		for(int j = 0; j < mapSizeW; j++)
		{
			mapNew<<muddyMap[i][j]<<' ';
		}
		mapNew<<'\n';
	}
	mapNew.close();
}

void loadMap2(int muddyMap2[120][200], int mapSizeH, int mapSizeW)
{
	ifstream map2Read("Assets/map/map2.txt");
	for(int i = 0; i < mapSizeH; i++)
	{
		for(int j = 0; j < mapSizeW; j++)
		{
			map2Read>>muddyMap2[i][j];
		}
	}
	map2Read.close();
}

void storeMap2(int muddyMap2[120][200], int mapSizeH, int mapSizeW)
{		
	ofstream map2New("Assets/map/map2.txt");
	for(int i = 0; i < mapSizeH; i++)
	{
		for(int j = 0; j < mapSizeW; j++)
		{
			map2New<<muddyMap2[i][j]<<' ';
		}
		map2New<<'\n';
	}
	map2New.close();
}

void loadObjectsMap(int objectsMap[120][200], int mapSizeH, int mapSizeW)
{
	int i, j;
	for(i = 0; i < mapSizeH; i++)
	{
		for(j = 0; j < mapSizeW; j++)
		{
			objectsMap[i][j] = 0;
		}
	}
	ifstream objectsRead("Assets/map/objects.txt");
	int objectTypeNew;
	for(i = 0; i < mapSizeH; i++)
	{
		for(j = 0; j < mapSizeW; j++)
		{
			objectsRead>>objectTypeNew;
			if(objectTypeNew > 10 && objectTypeNew <70)
			{
				objectsMap[i + 1][j] = -1;
				objectsMap[i + 1][j + 1] = -1;
				if(objectsMap[i][j] == -1)
				{
					objectsMap[i][j] = objectTypeNew * -1;
				}
				else
				{
					objectsMap[i][j] = objectTypeNew;
				}
				if(objectsMap[i][j + 1] >= 0) objectsMap[i][j + 1] = 10;
			}
			else if(objectTypeNew >= 150 && objectTypeNew <= 152)
			{
				objectsMap[i][j] = objectTypeNew;
				objectsMap[i + 1][j] = 9;
				objectsMap[i + 2][j] = 8;
			}
			else if(objectTypeNew >= 153 && objectTypeNew <= 155)
			{
				objectsMap[i][j] = objectTypeNew;
				objectsMap[i][j + 1] = 9;
				objectsMap[i][j + 2] = 8;
			}
			else
			{
				if(objectsMap[i][j] >= 0 && objectsMap[i][j] != 9 && objectsMap[i][j] != 8) objectsMap[i][j] = objectTypeNew;
			}
		}
	}
	objectsRead.close();
}

void storeObjectsMap(int objectsMap[120][200], int mapSizeH, int mapSizeW)
{
	ofstream objectsNew("Assets/map/objects.txt");
	for(int i = 0; i < mapSizeH; i++)
	{
		for(int j = 0; j < mapSizeW; j++)
		{
			if(objectsMap[i][j] == -1 || objectsMap[i][j] == 8 || objectsMap[i][j] == 9) {
				objectsNew<<10<<' ';
			} else if(objectsMap[i][j]<0) {
				objectsNew<<-1*objectsMap[i][j]<<' ';
			} else {
				objectsNew<<objectsMap[i][j]<<' ';
			}
		}
		objectsNew<<'\n';
	}
	objectsNew.close();
}

int main()
{
	
	window.setFramerateLimit(60);

	Event event;
	ZeoFlow_SFML zeoFlow_SF;
	Font font(zeoFlow_SF.loadFont("Assets/fonts/", "font_5", "ttf"));
	const int tilesetSize = 32;
	const int mapSizeH = 120, mapSizeW = 200;
	int muddyMap[mapSizeH][mapSizeW], muddyMap2[mapSizeH][mapSizeW], objectsMap[mapSizeH][mapSizeW];
	int i, j;

	bool modeEdit = false;
	bool modeShowInventory = false;
	int lastTerrainUsed;
	bool modeEditShowObjects = false;
	int modeInventory = 0;
	const int INVENTORY_CATEGORY_GROUND = 0;
	const int INVENTORY_CATEGORY_GROUND2 = 1;
	const int INVENTORY_CATEGORY_OBJECTS = 2;
	bool leftSideClicked;

	Vector2i characterPos(0, 9);
	Vector2i offset(0, 0);
	Vector2i mouseLocation(0, 0);
	Vector2i editLocation(0, 0);
  
	loadMap(muddyMap, mapSizeH, mapSizeW);
	loadMap2(muddyMap2, mapSizeH, mapSizeW);
	loadObjectsMap(objectsMap, mapSizeH, mapSizeW);

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
			if(event.type == Event::MouseMoved)
			{
				mouseLocation = Mouse::getPosition(window);
			}
			if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::E))
			{
					modeEdit = !modeEdit;
					modeShowInventory = true;
					modeEditShowObjects = false;
					lastTerrainUsed = -1;
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Q))
			{
				if(!modeEditShowObjects)
				{
					lastTerrainUsed = muddyMap[editLocation.x][editLocation.y];
				}
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Delete))
			{
				if(modeInventory == INVENTORY_CATEGORY_GROUND)
				{
					if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
					{
						muddyMap[editLocation.x][editLocation.y] = 20;
						storeMap(muddyMap, mapSizeH, mapSizeW);
					}
				}
				else if(modeInventory == INVENTORY_CATEGORY_GROUND2)
				{
					if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
					{
						muddyMap2[editLocation.x][editLocation.y] = 0;
						storeMap2(muddyMap2, mapSizeH, mapSizeW);
					}
				}
				else
				{
					if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
					{
						objectsMap[editLocation.x][editLocation.y] = 10;
						storeObjectsMap(objectsMap, mapSizeH, mapSizeW);
						loadObjectsMap(objectsMap, mapSizeH, mapSizeW);			
					}
				}
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Return))
			{
				if(modeInventory == INVENTORY_CATEGORY_GROUND)
				{
					muddyMap[editLocation.x][editLocation.y] = lastTerrainUsed;
					storeMap(muddyMap, mapSizeH, mapSizeW);
				}
				else if(modeInventory == INVENTORY_CATEGORY_GROUND2)
				{
					muddyMap2[editLocation.x][editLocation.y] = lastTerrainUsed;
					storeMap2(muddyMap2, mapSizeH, mapSizeW);
				}
				else
				{
					if(editLocation.x >= 0 && editLocation.x <= mapSizeW - 1 && editLocation.y >= 0 && editLocation.y <= mapSizeH - 1)
					{
						objectsMap[editLocation.x][editLocation.y] = lastTerrainUsed;
						storeObjectsMap(objectsMap, mapSizeH, mapSizeW);
						loadObjectsMap(objectsMap, mapSizeH, mapSizeW);
					}
				}
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::A))
			{
				editLocation.y--;
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::D))
			{
				editLocation.y++;
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::W))
			{
				editLocation.x--;
			}
			else if((lastTerrainUsed != -1 || modeShowInventory) && modeEdit && event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S))
			{
				editLocation.x++;
			}
			if(event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
			{
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
					lastTerrainUsed = getTerrainType(1, 43, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[15][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 15, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[15][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 15, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[16][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 16, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[16][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 16, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][0], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][1], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][2], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 2);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][3], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 3);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 13, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 14, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[12][7], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 12, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 13, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 13, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][7], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 13, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 14, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 14, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][7], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 14, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][0], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 13, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[13][1], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 13, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][0], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 14, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[14][1], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(1, 14, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][0], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][0], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 37, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][1], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 37, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][0], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 38, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[39][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 39, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[39][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 39, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[40][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 40, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[40][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 40, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][1], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 38, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][1], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][2], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 2);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][3], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 3);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 37, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][4], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 38, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[36][7], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 36, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 37, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 37, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[37][7], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 37, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][5], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 38, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 38, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(grass_tilesets_edit[38][7], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(2, 38, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][6], mouseLocation))
				{
					lastTerrainUsed = getTerrainType(3, 1, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[0], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 0, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[1], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 1, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[2], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 2, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[3], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 3, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 4, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 5, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 6, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 7, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(square_tilesets_edit[8], mouseLocation))
				{
					lastTerrainUsed = getObjectType(1, 8, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[0][0], mouseLocation))
				{
					lastTerrainUsed = getObjectType(3, 0, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[0][1], mouseLocation))
				{
					lastTerrainUsed = getObjectType(3, 0, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[0][2], mouseLocation))
				{
					lastTerrainUsed = getObjectType(3, 0, 2);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[1][0], mouseLocation))
				{
					lastTerrainUsed = getObjectType(3, 1, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[1][1], mouseLocation))
				{
					lastTerrainUsed = getObjectType(3, 1, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_OBJECTS && modeEdit && modeShowInventory && rectClicked(bridge_tilesets_edit[1][2], mouseLocation))
				{
					lastTerrainUsed = getObjectType(3, 1, 2);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][1], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][2], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 2);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][3], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 3);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 1, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 2, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 1, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 1, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[1][7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 1, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 2, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 2, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[2][7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 2, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[0][0], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 0, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][1], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 1);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][2], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 2);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][3], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 3);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 7, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 8, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 7, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 7, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[7][7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 7, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 8, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][6], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 8, 6);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[8][7], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 8, 7);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[6][0], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 6, 0);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[3][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 3, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[3][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 3, 5);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[4][4], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 4, 4);
				} else if(modeInventory == INVENTORY_CATEGORY_GROUND2 && modeEdit && modeShowInventory && rectClicked(water_tilesets_edit[4][5], mouseLocation))
				{
					lastTerrainUsed = getObjectType(2, 4, 5);
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
				}
			}
			setGameViewOffset(characterPos, offset, muddyMap, muddyMap2, objectsMap, mapSizeH, mapSizeW);
		}

		window.clear(Color::Red);
		for(i = offset.x; i < offset.x + screenH/tilesetSize; i++)
		{
			for(j = offset.y; j < offset.y + screenW/tilesetSize; j++)
			{
				int uvX, uvY;
				if(muddyMap[i][j] >= 20 && muddyMap[i][j] < 70)
				{
					getTerrainByType(muddyMap[i][j], uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(muddyMap[i][j] >= 70 && muddyMap[i][j] < 120)
				{
					getTerrainByType(muddyMap[i][j], uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(muddyMap[i][j] >= 120 && muddyMap[i][j] < 150)
				{
					getTerrainByType(muddyMap[i][j], uvX, uvY);
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
					getTerrainByType(lastTerrainUsed, uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(lastTerrainUsed >= 70 && lastTerrainUsed < 120)
				{
					getTerrainByType(lastTerrainUsed, uvX, uvY);
					grass_tilesets[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(grass_tilesets[uvX][uvY]);
				}
				else if(lastTerrainUsed >= 120 && lastTerrainUsed < 150)
				{
					getTerrainByType(lastTerrainUsed, uvX, uvY);
					water_tilests[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(water_tilests[uvX][uvY]);
				}
			}

			terrainPointer.setPosition((editLocation.y-offset.y)*tilesetSize + 16, (editLocation.x-offset.x)*tilesetSize + 16);
			window.draw(terrainPointer);

			mousePointer.setPosition((mouseLocation.x/tilesetSize) * tilesetSize + 16, (mouseLocation.y/tilesetSize) * tilesetSize + 16);
			window.draw(mousePointer);

		}
		for(i = offset.x; i < offset.x + screenH/tilesetSize; i++)
		{
			for(j = offset.y; j < offset.y + screenW/tilesetSize; j++)
			{
				int uvX, uvY;
				int objectTypeN = abs(muddyMap2[i][j]);
				if(modeEdit && modeInventory < 1)
				{
					if(objectTypeN >= 70 && objectTypeN < 130)
					{
						getObjectByType(objectTypeN, uvX, uvY);
						water_tilesets_transparent[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilesets_transparent[uvX][uvY]);
					}
				}
				else
				{
					if(objectTypeN >= 70 && objectTypeN < 130)
					{
						getObjectByType(objectTypeN, uvX, uvY);
						water_tilests[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilests[uvX][uvY]);
					}
				}
			}
		}
		int limitX, limitY;
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
		if(objectsMap[characterPos.y + offset.x][characterPos.x + offset.y] != 9)
		{
			character.setPosition(characterPos.x*tilesetSize, characterPos.y*tilesetSize);
			window.draw(character);
		}
		for(i; i < limitX; i++)
		{
			for(j = offset.y - 1; j < offset.y + screenW/tilesetSize; j++)
			{
				if(modeEdit && modeInventory < 2)
				{
					int uvX, uvY;
					int objectTypeN = abs(objectsMap[i][j]);
					if(objectTypeN > 10 && objectTypeN < 70)
					{
						getObjectByType(objectTypeN, uvX, uvY);
						square_tilesets_transparent[uvX].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(square_tilesets_transparent[uvX]);
					}
					else if(objectTypeN >= 70 && objectTypeN < 130)
					{
						getObjectByType(objectTypeN, uvX, uvY);
						water_tilesets_transparent[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilesets_transparent[uvX][uvY]);
					}
					else if(objectTypeN >= 150 && objectTypeN < 160)
					{
						getObjectByType(objectTypeN, uvX, uvY);
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
						getObjectByType(objectTypeN, uvX, uvY);
						square_tilests[uvX].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(square_tilests[uvX]);
					}
					else if(objectTypeN >= 70 && objectTypeN < 130)
					{
						getObjectByType(objectTypeN, uvX, uvY);
						water_tilests[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(water_tilests[uvX][uvY]);
					}
					else if(objectTypeN >= 150 && objectTypeN < 160)
					{
						getObjectByType(objectTypeN, uvX, uvY);
						bridge_tilesets[uvX][uvY].setPosition((j-offset.y)*tilesetSize, (i-offset.x)*tilesetSize);
						window.draw(bridge_tilesets[uvX][uvY]);
					}
				}
			}

		}
		if(objectsMap[characterPos.y + offset.x][characterPos.x + offset.y] == 9)
		{
			character.setPosition(characterPos.x*tilesetSize, characterPos.y*tilesetSize);
			window.draw(character);
		}
		
		if(modeEdit && modeShowInventory && modeEditShowObjects)
		{
			if(lastTerrainUsed != -1)
			{
				int uvX, uvY;
				if(lastTerrainUsed > 10 && lastTerrainUsed < 70)
				{
					getObjectByType(lastTerrainUsed, uvX, uvY);
					square_tilests[uvX].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(square_tilests[uvX]);
				}
				else if(lastTerrainUsed >= 70 && lastTerrainUsed < 130)
				{
					getObjectByType(lastTerrainUsed, uvX, uvY);
					water_tilests[uvX][uvY].setPosition((editLocation.y-offset.y)*tilesetSize, (editLocation.x-offset.x)*tilesetSize);
					window.draw(water_tilests[uvX][uvY]);
				}
				else if(lastTerrainUsed >= 150 && lastTerrainUsed < 160)
				{
					getObjectByType(lastTerrainUsed, uvX, uvY);
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
			//cout<<lastTerrainUsed<<'\n';
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