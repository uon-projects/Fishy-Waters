#pragma once

#include "Utils.h"
#include <SFML/Graphics.hpp>
#include "../../../library/src/header/LoadImage.h"
#include "player/MainCharacter.h"
#include "game/GameMap.h"

using namespace sf;

class App
{

#define WindowX 800
#define WindowY 500

public:
    App()
    {
        mLoadImage = new LoadImage();
        currentScreen = splash;
        lvlUnlocked = 1;
        mCharacter = mLoadImage->loadSpriteFromTexture("c00a_01idle_00", png);
        mMainCharacter = new MainCharacter;
        mGameMap = new GameMap;
        mNewGameLvl = false;
    }

    ~App()
    {

    }

public:
    screen getCurrentScreen()
    {
        return currentScreen;
    }

    void setCurrentScreen(screen screenChose)
    {
        currentScreen = screenChose;
        if (screenChose == game)
        {
            mNewGameLvl = true;
            mMainCharacter->reset(mLvlSelected);
        }
    }

    int getCharacterLives()
    {
        return lives;
    }

    void decreaseLives()
    {
        if (lives > 0)
        {
            lives--;
        }
    }

    void increaseLives()
    {
        lives++;
    }

    void resetLives()
    {
        lives = 3;
    }

    int getLevelsUnlocked()
    {
        return lvlUnlocked;
    }

    void increaseLevelsUnlocked()
    {
        if (lvlUnlocked < 4)
        {
            lvlUnlocked++;
        }
    }

    bool isNewGame()
    {
        bool isNewGame = mNewGameLvl;
        if (mNewGameLvl)
        {
            mNewGameLvl = false;
        }
        return isNewGame;
    }

    int getGameOffsetY()
    {
        return mMainCharacter->getGameOffsetY();
    }

    void setLvl(int mLvl)
    {
        this->mLvlSelected = mLvl;
    }

    int getLvlSelected()
    {
        return mLvlSelected;
    }

    Event getEvent()
    {
        return event;
    }

    void setEvent(Event eventN)
    {
        event = eventN;
    }

    Sprite getCharacterSprite()
    {
        return mCharacter;
    }

    Sprite getBullet1Sprite()
    {
        return mLoadImage->loadSpriteFromTexture("bullet1", png);
    }

    Sprite getBullet2Sprite()
    {
        return mLoadImage->loadSpriteFromTexture("bullet2", png);
    }

    MainCharacter *getMainCharacter()
    {
        return mMainCharacter;
    }

    GameMap *getGameMap()
    {
        return mGameMap;
    }

    LoadImage *getImageLoader()
    {
        return mLoadImage;
    }

private:
    screen currentScreen;
    Event event;
    int lvlUnlocked;
    Sprite mCharacter;
    MainCharacter *mMainCharacter;
    GameMap *mGameMap;
    LoadImage *mLoadImage;
    int mLvlSelected;
    int mCharacterLives;
    bool mNewGameLvl;
    int lives;

};