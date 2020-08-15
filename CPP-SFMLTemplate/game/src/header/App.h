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
            mMainCharacter->reset();
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

    Event getEvent()
    {
        return event;
    }

    void setEvent(Event eventN)
    {
        event = eventN;
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
    MainCharacter *mMainCharacter;
    GameMap *mGameMap;
    LoadImage *mLoadImage;
    bool mNewGameLvl;
    int lives;

};