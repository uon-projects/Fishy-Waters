#ifndef DAI_MAKAI_MURA_MAIN_CHARACTER_H
#define DAI_MAKAI_MURA_MAIN_CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../game/GameMap.h"
#include "../../../../library/src/header/LoadImage.h"

using namespace std;
using namespace sf;

class MainCharacter
{

private:
    Vector2f mMainCharacterPosition;
    int mMovesCount;
    int mMainCharacterOnMove;
    bool isFacingEast;
    bool isFacingNorth;
    GameMap *mGameMap;
    int mMovementPF;
    int mFacingNow;
    LoadImage *mLoadImage;

public:
    MainCharacter()
    {
        mLoadImage = new LoadImage();

        mMovesCount = 0;
        mMainCharacterOnMove = 0;

        isFacingEast = false;
        isFacingNorth = false;
        mFacingNow = 0;

    }

    ~MainCharacter()
    {

    }

    void setGameMap(GameMap *mGameMap)
    {
        this->mGameMap = mGameMap;
    }

    void reset()
    {

        mMainCharacterPosition = mGameMap->getCharacterStartPos();

        mMovesCount = 0;
        mMainCharacterOnMove = 0;
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
        return mMainCharacterPosition;
    }

    Vector2f getGameOffset(RenderWindow &window)
    {
        Vector2f mGameOffset;
        mGameOffset.x = mMainCharacterPosition.x - window.getSize().x / 2;
        mGameOffset.y = mMainCharacterPosition.y - window.getSize().y / 2;
        return mGameOffset;
    }

    Vector2i getGameOffsetMoving()
    {
        Vector2i mGameOffset;
        mGameOffset.x = (int) mMainCharacterPosition.x % 40;
        mGameOffset.y = (int) mMainCharacterPosition.y % 40;
        return mGameOffset;
    }

    void update()
    {
        mMovementPF = 1;
        if (mMainCharacterOnMove != 0)
        {
            if (mMainCharacterOnMove == 1)
            {
                mMainCharacterPosition.x -= mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mMainCharacterOnMove = 0;
                }
            } else if (mMainCharacterOnMove == 2)
            {
                mMainCharacterPosition.y -= mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mMainCharacterOnMove = 0;
                }
            } else if (mMainCharacterOnMove == 3)
            {
                mMainCharacterPosition.x += mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mMainCharacterOnMove = 0;
                }
            } else if (mMainCharacterOnMove == 4)
            {
                mMainCharacterPosition.y += mMovementPF;
                mMovesCount++;
                if (mMovesCount == 40 / mMovementPF)
                {
                    mMainCharacterOnMove = 0;
                }
            }
        }
    }

    void moveWest()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 1;
            mMovesCount = 0;
            isFacingEast = false;
            mFacingNow = 1;
        }
    }

    void moveEast()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 3;
            mMovesCount = 0;
            isFacingEast = true;
            mFacingNow = 3;
        }
    }

    void moveNorth()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 2;
            mMovesCount = 0;
            isFacingNorth = true;
            mFacingNow = 2;
        }
    }

    void moveSouth()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 4;
            mMovesCount = 0;
            isFacingNorth = false;
            mFacingNow = 0;
        }
    }

};

#endif //DAI_MAKAI_MURA_MAIN_CHARACTER_H
