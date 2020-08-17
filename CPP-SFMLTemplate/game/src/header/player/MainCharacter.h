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
    Sprite mMainCharacterSprite;
    Texture mMainCharacterTexture;
    float mCharacterScale;
    Vector2f mMainCharacterPosition;
    int mJumpCount;
    int mMovesCount;
    Vector2u mTextureMainCharacterSize;
    float mMainCharacterMass;
    float mMainCharacterVelocity;
    float mMainCharacterVelocityMove;
    float mMainCharacterGravity; //The Average Value At Earth's Surface (Standard Gravity) is, by definition, 9.80665 m/s^2 (9.80f).
    bool mMainCharacterJump;
    int mMainCharacterOnMove;
    bool isFacingEast;
    bool isFacingNorth;
    GameMap *mGameMap;
    int mGameOffsetY;
    LoadImage *mLoadImage;

public:
    MainCharacter()
    {
        mLoadImage = new LoadImage();

        mJumpCount = 0;
        mMovesCount = 0;
        mMainCharacterGravity = 8.0f;
        mMainCharacterVelocity = 0.0f;

        mMainCharacterMass = 200.0f;
        mMainCharacterJump = false;
        mMainCharacterOnMove = 0;

        isFacingEast = true;
        isFacingNorth = true;

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
        mGameOffsetY = getGameOffsetY();

        mJumpCount = 0;
        mMovesCount = 0;
        mMainCharacterGravity = 8.0f;

        mMainCharacterMass = 200.0f;
        mMainCharacterJump = false;
        mMainCharacterOnMove = 0;

        mMainCharacterTexture.loadFromFile("game/src/res/drawable/heart.png");
        mTextureMainCharacterSize = mMainCharacterTexture.getSize();
        mTextureMainCharacterSize.x /= 1;
        mTextureMainCharacterSize.y /= 1;
        mMainCharacterSprite.setTexture(mMainCharacterTexture);
        mMainCharacterSprite.setTextureRect(
                IntRect(mTextureMainCharacterSize.x * 0, mTextureMainCharacterSize.y * 0, mTextureMainCharacterSize.x,
                        mTextureMainCharacterSize.y));
        mCharacterScale = 1.5f;
        mMainCharacterSprite.setScale(Vector2f(mCharacterScale, mCharacterScale));
        mMainCharacterSprite.setOrigin(Vector2f(mTextureMainCharacterSize.x / 2, mTextureMainCharacterSize.y / 2));

    }

    int getGameOffsetY()
    {
        if (mMainCharacterPosition.y > -220)
        {
            mGameOffsetY = 500;
        } else
        {
            mGameOffsetY = 500 - mMainCharacterPosition.y - 220;
        }
        return mGameOffsetY;
    }

    Sprite getSprite(RenderWindow &window)
    {
        mMainCharacterSprite.setPosition(Vector2f((float) window.getSize().x / 2, (float) window.getSize().y / 2));
        return mMainCharacterSprite;
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

    int getGameHeight()
    {
        int gameHeight = 0;
        if (mMainCharacterPosition.y > -170)
        {
            mGameOffsetY = 500;
        } else
        {
            mGameOffsetY = 500 - mMainCharacterPosition.y - 170;
        }
        return mMainCharacterPosition.y;
    }

    int mMovementPF;

    void update(float mSpeed)
    {
        mMovementPF = 2;
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

    void moveLeft()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 1;
            mMovesCount = 0;
        }
    }

    void moveRight()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 3;
            mMovesCount = 0;
        }
    }

    void moveNorth()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 2;
            mMovesCount = 0;
        }
    }

    void moveSouth()
    {
        if (mMainCharacterOnMove == 0)
        {
            mMainCharacterOnMove = 4;
            mMovesCount = 0;
        }
    }

};

#endif //DAI_MAKAI_MURA_MAIN_CHARACTER_H
