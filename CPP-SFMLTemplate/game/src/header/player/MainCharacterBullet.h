#ifndef DAI_MAKAI_MURA_MAIN_CHARACTER_BULLET_H
#define DAI_MAKAI_MURA_MAIN_CHARACTER_BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../App.h"

using namespace std;
using namespace sf;

class MainCharacterBullet
{

private:
    Sprite mBulletSprite;
    Vector2f mBulletPosition;
    float mEnemyBulletSpeed;
    int mClassType;
    int mLifes;
    int mInitialPosY;
    bool isRightFace;
    float mScaleSprite;

public:
    MainCharacterBullet()
    {

    }

    ~MainCharacterBullet()
    {

    }

    void init(Vector2f mPosition, int mType, bool isRightFaceN, int mLifesN, float mEnemyBulletSpeedN,
              float mScaleSpriteN)
    {
        mClassType = mType;
        isRightFace = isRightFaceN;
        mLifes = mLifesN;
        mEnemyBulletSpeed = mEnemyBulletSpeedN;
        mScaleSprite = mScaleSpriteN;

        mInitialPosY = mPosition.y;
        mBulletPosition = mPosition;
        mBulletSprite.setPosition(mBulletPosition);
        isRightFace ? (mBulletSprite.setScale(Vector2f(mScaleSprite, mScaleSprite))) : (mBulletSprite.setScale(
                Vector2f(-mScaleSprite, mScaleSprite)));
        mBulletSprite.setRotation(0);
    }

    void update()
    {
        mBulletPosition.x = mBulletPosition.x + (mEnemyBulletSpeed * (isRightFace ? 1 : -1));
        mBulletSprite.setPosition(mBulletPosition);
    }

    Sprite getSprite(int mGameOffsetY)
    {
        mBulletPosition.y = mGameOffsetY + mInitialPosY;
        mBulletSprite.setPosition(mBulletPosition);
        return mBulletSprite;
    }

    bool decreaseLife()
    {
        mLifes--;
        return mLifes == 0;
    }

};

#endif //DAI_MAKAI_MURA_MAIN_CHARACTER_BULLET_H