#include "FileSync.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

//Compiler Directives
using namespace std;
using namespace sf;

FileSync::FileSync(void)
{
	//initialise
}

void FileSync::loadMap(int muddyMap[120][200], int mapSizeH, int mapSizeW)
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

void FileSync::storeMap(int muddyMap[120][200], int mapSizeH, int mapSizeW)
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

void FileSync::loadMap2(int muddyMap2[120][200], int mapSizeH, int mapSizeW)
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

void FileSync::storeMap2(int muddyMap2[120][200], int mapSizeH, int mapSizeW)
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

void FileSync::loadObjectsMap(int objectsMap[120][200], int mapSizeH, int mapSizeW)
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

void FileSync::storeObjectsMap(int objectsMap[120][200], int mapSizeH, int mapSizeW)
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

void FileSync::loadStats(Vector2i &characterPos, Vector2i &offset, int &level)
{
	ifstream statsRead("Assets/stats.txt");
	statsRead>>characterPos.x;
	statsRead>>characterPos.y;
	statsRead>>offset.x;
	statsRead>>offset.y;
	statsRead>>level;
	statsRead.close();
}

void FileSync::storeStats(Vector2i &characterPos, Vector2i offset, int &level)
{
	ofstream statsNew("Assets/stats.txt");
	statsNew<<characterPos.x<<' ';
	statsNew<<characterPos.y<<' ';
	statsNew<<offset.x<<' ';
	statsNew<<offset.y<<' ';
	statsNew<<level<<' ';
	statsNew.close();
}

FileSync::~FileSync(void)
{
	//destroy
}
