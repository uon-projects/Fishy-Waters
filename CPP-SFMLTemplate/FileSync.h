#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;

class FileSync
{

public:
	FileSync(void);
	~FileSync(void);
	void FileSync::loadMap(int muddyMap[120][200], int mapSizeH, int mapSizeW);
	void FileSync::storeMap(int muddyMap[120][200], int mapSizeH, int mapSizeW);
	void FileSync::loadMap2(int muddyMap2[120][200], int mapSizeH, int mapSizeW);
	void FileSync::storeMap2(int muddyMap2[120][200], int mapSizeH, int mapSizeW);
	void FileSync::loadObjectsMap(int objectsMap[120][200], int mapSizeH, int mapSizeW);
	void FileSync::storeObjectsMap(int objectsMap[120][200], int mapSizeH, int mapSizeW);
	void FileSync::loadStats(Vector2i &characterPos, Vector2i &offset, int &level);
	void FileSync::storeStats(Vector2i &characterPos, Vector2i offset, int &level);

};

