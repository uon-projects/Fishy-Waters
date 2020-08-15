#ifndef DAI_MAKAI_MURA_ITEMMODEL_H
#define DAI_MAKAI_MURA_ITEMMODEL_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class ItemModel
{

private:
    int mLvl;
    int mType;
    int mArea;
    Vector2i mStartPos;
    Vector2i mSize;
    bool mFaceRight;

public:
    ItemModel(int mLvl, Vector2i mStartPos)
    {
        this->mLvl = mLvl;
        this->mStartPos = mStartPos;
    }

    ItemModel(int mLvl, Vector2i mStartPos, int mArea, bool mFaceRight)
    {
        this->mLvl = mLvl;
        this->mStartPos = mStartPos;
        this->mArea = mArea;
        this->mFaceRight = mFaceRight;
    }

    ItemModel(int mLvl, Vector2i mStartPos, Vector2i mSize, int mType)
    {
        this->mLvl = mLvl;
        this->mStartPos = mStartPos;
        this->mSize = mSize;
        this->mType = mType;
    }

    ~ItemModel()
    {

    }

    int getLvl()
    {
        return mLvl;
    }

    int getType()
    {
        return mType;
    }

    int getArea()
    {
        return mArea;
    }

    bool isFacingRight()
    {
        return mFaceRight;
    }

    Vector2i getStartPos()
    {
        return mStartPos;
    }

    Vector2i getSize()
    {
        return mSize;
    }

};

#endif //DAI_MAKAI_MURA_ITEMMODEL_H
