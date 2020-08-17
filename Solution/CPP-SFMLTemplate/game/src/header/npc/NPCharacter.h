#ifndef DAI_MAKAI_MURA_NPCHARACTER_H
#define DAI_MAKAI_MURA_NPCHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../game/GameMap.h"

using namespace std;
using namespace sf;

class NPCharacter
{

private:
    Vector2f mNPCharacterPosition;
    int mMovesCount;
    int mNPCharacterOnMove;
    bool isFacingEast;
    bool isFacingNorth;
    GameMap *mGameMap;
    int mMovementPF;
    int mFacingNow;

public:
    NPCharacter(Vector2i mStartPos)
    {

        mNPCharacterPosition.x = mStartPos.x;
        mNPCharacterPosition.y = mStartPos.y;

        mMovesCount = 0;
        mNPCharacterOnMove = 0;

        isFacingEast = false;
        isFacingNorth = false;
        mFacingNow = 0;

    }

    ~NPCharacter()
    {

    }

    void setGameMap(GameMap *mGameMap)
    {
        this->mGameMap = mGameMap;
    }

    void reset()
    {

        mNPCharacterPosition = mGameMap->getCharacterStartPos();

        mMovesCount = 0;
        mNPCharacterOnMove = 0;
        mFacingNow = 2;

    }

    Vector2f getSpriteLocation(RenderWindow &window)
    {
        Vector2f mSpriteLocation;
        if (mFacingNow == 0)
        {
            mSpriteLocation.x = (float) window.getSize().x / 2 - 20;
            mSpriteLocation.y = (float) window.getSize().y / 2 - 20;
        } else if (mFacingNow == 1)
        {
            mSpriteLocation.x = (float) window.getSize().x / 2 + 20;
            mSpriteLocation.y = (float) window.getSize().y / 2 - 20;
        } else if (mFacingNow == 2)
        {
            mSpriteLocation.x = (float) window.getSize().x / 2 + 20;
            mSpriteLocation.y = (float) window.getSize().y / 2 + 20;
        } else if (mFacingNow == 3)
        {
            mSpriteLocation.x = (float) window.getSize().x / 2 - 20;
            mSpriteLocation.y = (float) window.getSize().y / 2 + 20;
        }
        return mSpriteLocation;
    }

    int getBoatRotation()
    {
        return mFacingNow * 90;
    }

    Vector2f getCharacterPosition()
    {
        return mNPCharacterPosition;
    }

    Vector2i getGameOffsetMoving()
    {
        Vector2i mGameOffset;
        mGameOffset.x = (int) mNPCharacterPosition.x % 40;
        mGameOffset.y = (int) mNPCharacterPosition.y % 40;
        return mGameOffset;
    }

    void update()
    {
        mMovementPF = 1;
        if (mNPCharacterOnMove != 0)
        {
            if (mNPCharacterOnMove == 1)
            {
                mNPCharacterPosition.x -= mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mNPCharacterOnMove = 0;
                }
            } else if (mNPCharacterOnMove == 2)
            {
                mNPCharacterPosition.y -= mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mNPCharacterOnMove = 0;
                }
            } else if (mNPCharacterOnMove == 3)
            {
                mNPCharacterPosition.x += mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mNPCharacterOnMove = 0;
                }
            } else if (mNPCharacterOnMove == 4)
            {
                mNPCharacterPosition.y += mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mNPCharacterOnMove = 0;
                }
            }
        }
    }

    void moveWest()
    {
        if (mNPCharacterOnMove == 0)
        {
            mNPCharacterOnMove = 1;
            mMovesCount = 0;
            isFacingEast = false;
            mFacingNow = 1;
        }
    }

    void moveEast()
    {
        if (mNPCharacterOnMove == 0)
        {
            mNPCharacterOnMove = 3;
            mMovesCount = 0;
            isFacingEast = true;
            mFacingNow = 3;
        }
    }

    void moveNorth()
    {
        if (mNPCharacterOnMove == 0)
        {
            mNPCharacterOnMove = 2;
            mMovesCount = 0;
            isFacingNorth = true;
            mFacingNow = 2;
        }
    }

    void moveSouth()
    {
        if (mNPCharacterOnMove == 0)
        {
            mNPCharacterOnMove = 4;
            mMovesCount = 0;
            isFacingNorth = false;
            mFacingNow = 0;
        }
    }

    bool isInArea(Vector2i mAreaX, Vector2i mAreaY)
    {
        return false;
    }

};

#endif //DAI_MAKAI_MURA_NPCHARACTER_H

