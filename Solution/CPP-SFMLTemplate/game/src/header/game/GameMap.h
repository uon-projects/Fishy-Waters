#ifndef DAI_MAKAI_MURA_GAMEMAP_H
#define DAI_MAKAI_MURA_GAMEMAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "./ItemModel.h"

using namespace std;
using namespace sf;

class GameMap
{

private:
    int mMapLines;
    int mMapColumns;
    int mTileSize;

public:
    GameMap()
    {
        initialize();
    }

    ~GameMap()
    {

    }

    int getMapLines()
    {
        return mMapLines;
    }

    int getMapColumns()
    {
        return mMapColumns;
    }

    int getTileSize()
    {
        return mTileSize;
    }

    void initialize()
    {
        mMapLines = 40;
        mMapColumns = 40;
        mTileSize = 40;
    }

    Vector2f getCharacterStartPos()
    {
        Vector2f mStartPosOfLvl = Vector2f(10 * 40.0f, 4 * 40.0f);
        return mStartPosOfLvl;
    }

    int **getGameMap()
    {

        int **fishyWorld;
        int height = getMapLines();
        int width = getMapColumns();
        ifstream fishyMap("game/src/res/file/water.map");
        int h, w;

        fishyWorld = new int *[height];
        srand((unsigned) time(NULL));

        for (h = 0; h < height; h++)
        {
            fishyWorld[h] = new int[width];
            for (w = 0; w < width; w++)
            {
                fishyMap >> fishyWorld[h][w];
            }
        }

        return fishyWorld;

    }

};

#endif //DAI_MAKAI_MURA_GAMEMAP_H
