#ifndef DAI_MAKAI_MURA_NPCHARACTER_H
#define DAI_MAKAI_MURA_NPCHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../game/GameMap.h"
#include "../../../../library/src/header/LoadImage.h"

using namespace std;
using namespace sf;

class NPCharacter
{

private:
    GameMap *mGameMap;
    Texture mMainCharacterTexture;
    Sprite mMainCharacterSprite;
    Vector2u mTextureMainCharacterSize;
    bool isRightFace;
    float mMainCharacterGravity; //The Average Value At Earth's Surface (Standard Gravity) is, by definition, 9.80665 m/s^2 (9.80f).
    float mMainCharacterMass;
    float mMainCharacterVelocity;
    Vector2f mMainCharacterPosition;
    int mMovingRange;
    int mCurrentMoved;
    int mGameOffsetY;
	LoadImage *mLoadImage;
    float mMainCharacterVelocityMove;
    float mNPCScale;

public:
    NPCharacter(GameMap *mGameMap, bool isRightFace, float startX, float startY, int range, LoadImage *mLoadImage)
    {
        this->mGameMap = mGameMap;
        this->isRightFace = isRightFace;
        this->mMovingRange = range;
        this->mMainCharacterPosition.x = startX;
        this->mMainCharacterPosition.y = startY;
        this->mGameOffsetY = 500;
        this->mLoadImage = mLoadImage;

        mMainCharacterMass = 200.0f;
        mMainCharacterVelocity = 650.0f;
        mMainCharacterGravity = 8.0f;

        mCurrentMoved = 0;

        mMainCharacterTexture.loadFromFile("game/src/res/drawable/e003a_01idle_00.png");
        mTextureMainCharacterSize = mMainCharacterTexture.getSize();
        mTextureMainCharacterSize.x /= 1;
        mTextureMainCharacterSize.y /= 1;
        mMainCharacterVelocity = 20.0f;

        mNPCScale = 0.4f;
        mMainCharacterSprite.setTexture(mMainCharacterTexture);
        mMainCharacterSprite.setTextureRect(
                IntRect(mTextureMainCharacterSize.x * 0, mTextureMainCharacterSize.y * 0, mTextureMainCharacterSize.x,
                        mTextureMainCharacterSize.y));
        mMainCharacterSprite.setScale(Vector2f(mNPCScale, mNPCScale));
        mMainCharacterSprite.setOrigin(mTextureMainCharacterSize.x / 2, -110);
        mMainCharacterSprite.setPosition(mMainCharacterPosition);
    }

    ~NPCharacter()
    {

    }

    void update(float mSpeed, int mGameOffsetY = 500)
    {
        this->mGameOffsetY = mGameOffsetY;

        Vector2f mSpriteLocStart;
        mSpriteLocStart.x = mMainCharacterSprite.getGlobalBounds().left;
        mSpriteLocStart.y = mMainCharacterPosition.y;
        Vector2f mSpriteLocSize;
        mSpriteLocSize.x = mMainCharacterSprite.getGlobalBounds().width;
        mSpriteLocSize.y = mMainCharacterSprite.getGlobalBounds().height;
        int mGroundLevel = mGameMap->getNearestGroundLvl(mSpriteLocStart, mSpriteLocSize, mGameOffsetY);
        mMainCharacterVelocity -= mMainCharacterMass * mMainCharacterGravity * mSpeed;
        mMainCharacterPosition.y -= mMainCharacterVelocity * mSpeed / 1.2;

        isRightFace ? (mMainCharacterSprite.setScale(Vector2f(-mNPCScale, mNPCScale))) : (mMainCharacterSprite.setScale(
                Vector2f(mNPCScale, mNPCScale)));
        isRightFace ? (mMainCharacterPosition.x += 1) : (mMainCharacterPosition.x -= 1);

        mCurrentMoved += 1;
        if (mCurrentMoved >= mMovingRange)
        {
            mCurrentMoved = 0;
            isRightFace = !isRightFace;
        }
        if (mMainCharacterPosition.y >= mGroundLevel)
        {
            mMainCharacterPosition.y = (float) mGroundLevel;
        }
    }

    Sprite getSprite()
    {
        mMainCharacterPosition.y += mGameOffsetY;
        mMainCharacterPosition.y -= mMainCharacterSprite.getGlobalBounds().height;
        mMainCharacterSprite.setPosition(mMainCharacterPosition);
        mMainCharacterPosition.y -= mGameOffsetY;
        mMainCharacterPosition.y += mMainCharacterSprite.getGlobalBounds().height;
        return mMainCharacterSprite;
    }

};

#endif //DAI_MAKAI_MURA_NPCHARACTER_H
