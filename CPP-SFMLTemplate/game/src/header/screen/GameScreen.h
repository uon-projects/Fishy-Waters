#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "../player/MainCharacterBullet.h"
#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/MaterialButton.h"
#include "../App.h"
#include "../npc/NPCharacter.h"
#include "../player/MainCharacter.h"
#include "../game/GameMap.h"

using namespace std;
using namespace sf;

class GameScreen
{

private:
    RectangleShape gameMenuScreenBackground;
    App *mApp;
    MainCharacter *mMainCharacter;
    GameMap *mGameMap;
    vector<MainCharacterBullet *> mMainCharacterBullets;
    vector<NPCharacter *> mNPCharacters;
    int mColorEndPortal;
    bool mColorAscending;
    int mBackgroundR, mBackgroundG, mBackgroundB;
    int **mWaterMap;

public:
    GameScreen()
    {

        mColorEndPortal = 77;
        mColorAscending = true;

        mBackgroundR = 32;
        mBackgroundG = 165;
        mBackgroundB = 227;

    }

    ~GameScreen()
    {

    }

public:

    void draw(RenderWindow &window)
    {

        int i, j;
        Vector2i mGameOffsetMoving;
        Vector2f mWindowSize;
        Vector2f mGameOffset;
        Vector2i mLoc;
        Vector2i mGridAreaSurface;
        Vector2f mCharacterPosGrid;
        RectangleShape item;

        gameMenuScreenBackground.setFillColor(Color(mBackgroundR, mBackgroundG, mBackgroundB));
        gameMenuScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
        window.draw(gameMenuScreenBackground);

        mWindowSize.x = (float) window.getSize().x;
        mWindowSize.y = (float) window.getSize().y;
        mGridAreaSurface.x = mWindowSize.x / 40 + 2;
        mGridAreaSurface.y = mWindowSize.y / 40 + 2;
        mGameOffset = mMainCharacter->getGameOffset(window);
        mGameOffsetMoving = mMainCharacter->getGameOffsetMoving();

        mCharacterPosGrid.x = mMainCharacter->getCharacterPosition().x / 40;
        mCharacterPosGrid.y = mMainCharacter->getCharacterPosition().y / 40;
        Vector2i mStartGridArea;
        mStartGridArea.x = mCharacterPosGrid.x - mGridAreaSurface.x / 2;
        mStartGridArea.y = mCharacterPosGrid.y - mGridAreaSurface.y / 2;
        if (mStartGridArea.x < 0)
        {
            mStartGridArea.x = 40 + mStartGridArea.x;
        }
        if (mStartGridArea.y < 0)
        {
            mStartGridArea.y = 40 + mStartGridArea.y;
        }
        mStartGridArea.x = mStartGridArea.x % 40;
        mStartGridArea.y = mStartGridArea.y % 40;
        if (mGameOffsetMoving.x > 0)
        {
            mStartGridArea.x--;
        }
        if (mStartGridArea.x < 0)
        {
            mStartGridArea.x = 40 + mStartGridArea.x;
        }
        if (mGameOffsetMoving.y > 0)
        {
            mStartGridArea.y--;
        }
        if (mStartGridArea.y < 0)
        {
            mStartGridArea.y = 40 + mStartGridArea.y % 40;
        }
        Vector2i mEndArea;
        mEndArea.x = mStartGridArea.x + mGridAreaSurface.x;
        mEndArea.y = mStartGridArea.y + mGridAreaSurface.y;

        cout << mStartGridArea.x << ' ' << mCharacterPosGrid.x << '\n';

        mLoc.x = -1;
        for (i = mStartGridArea.x; i <= mEndArea.x; i++)
        {
            mLoc.y = -1;
            for (j = mStartGridArea.y; j <= mEndArea.y; j++)
            {
                int mTileType = mWaterMap[j % 40][i % 40];
                if (mTileType == 0)
                {
                    item.setFillColor(Color(3, 90, 252));
                } else if (mTileType == 1)
                {
                    item.setFillColor(Color(252, 240, 3));
                }
                item.setPosition(
                        Vector2f(
                                (float) mLoc.x * 40 - mGameOffsetMoving.x,
                                (float) mLoc.y * 40 - mGameOffsetMoving.y
                        )
                );
                item.setSize(Vector2f(40.0f, 40.0f));
                window.draw(item);
                mLoc.y++;
            }
            mLoc.x++;
        }

    }

    void initNPCs()
    {
        vector < ItemModel * > mNPCs = mGameMap->getNPCByLvl();
        NPCharacter *mNPCharacter;
        for (ItemModel *mNPC : mNPCs)
        {
            mNPCharacter = new NPCharacter(
                    mApp->getGameMap(),
                    mNPC->isFacingRight(),
                    mNPC->getStartPos().x,
                    mNPC->getStartPos().y,
                    mNPC->getArea(),
                    mApp->getImageLoader()
            );
            mNPCharacters.push_back(mNPCharacter);
        }
    }

    void setApp(App *app)
    {
        this->mApp = app;
        mMainCharacter = mApp->getMainCharacter();
        mGameMap = mApp->getGameMap();
        mMainCharacter->setGameMap(mApp->getGameMap());
        mWaterMap = mGameMap->getGameMap();
    }

    void inputListener(Event event)
    {
        if (event.key.code == Keyboard::X)
        {
            system("pause");
        }
        if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
        {
            mMainCharacter->moveLeft();
        } else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
        {
            mMainCharacter->moveRight();
        } else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
        {
            mMainCharacter->moveNorth();
        } else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
        {
            mMainCharacter->moveSouth();
        }
    }

    void update(float speed)
    {

        mMainCharacter->update(speed);

    }

    void initNewLvl()
    {
        mMainCharacterBullets.clear();
        mNPCharacters.clear();
        mMainCharacter->reset();

        mColorEndPortal = 77;
        mColorAscending = true;

        initNPCs();
    }

};
