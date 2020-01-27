#pragma once
class Map
{
public:
	Map(void);
	~Map(void);
	int getObjectType(int type, int x, int y);
	void getObjectByType(int type, int &x, int &y);
	int getTerrainType(int type, int x, int y);
	void getTerrainByType(int type, int &x, int &y);
};

