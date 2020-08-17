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
        Vector2i mStartGridArea;
        Vector2i mCharacterPosOnGrid;
        RectangleShape item;

        gameMenuScreenBackground.setFillColor(Color(mBackgroundR, mBackgroundG, mBackgroundB));
        gameMenuScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
        window.draw(gameMenuScreenBackground);

        mWindowSize.x = (float) window.getSize().x;
        mWindowSize.y = (float) window.getSize().y;
        mGridAreaSurface.x = mWindowSize.x / 40 + 2;
        mGridAreaSurface.y = mWindowSize.y / 40 + 3;
        mGameOffset = mMainCharacter->getGameOffset(window);
        mGameOffsetMoving = mMainCharacter->getGameOffsetMoving();

        mCharacterPosGrid.x = mMainCharacter->getCharacterPosition().x / 40;
        mCharacterPosGrid.y = mMainCharacter->getCharacterPosition().y / 40;
        if (mCharacterPosGrid.x > 0)
        {
            mCharacterPosGrid.x = 40 - mCharacterPosGrid.x * -1;
        }
        mCharacterPosGrid.x = (int) mCharacterPosGrid.x % 40;
        if (mCharacterPosGrid.y > 0)
        {
            mCharacterPosGrid.y = 40 - mCharacterPosGrid.y * -1;
        }
        mCharacterPosGrid.y = (int) mCharacterPosGrid.y % 40;

        mCharacterPosOnGrid.x = mCharacterPosGrid.x;
        mCharacterPosOnGrid.y = mCharacterPosGrid.y;
        if (mCharacterPosOnGrid.x < 0)
        {
            mCharacterPosOnGrid.x = 40 + mCharacterPosGrid.x;
        }
        if (mCharacterPosOnGrid.y < 0)
        {
            mCharacterPosOnGrid.y = 40 + mCharacterPosGrid.y;
        }

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

        if (mCharacterPosGrid.x >= 0 && mGameOffsetMoving.x > 0)
        {
            mStartGridArea.x++;
        }
        if (mCharacterPosGrid.y >= 0 && mGameOffsetMoving.y > 0)
        {
            mStartGridArea.y++;
        }

        Vector2i mEndArea;
        mEndArea.x = mStartGridArea.x + mGridAreaSurface.x;
        mEndArea.y = mStartGridArea.y + mGridAreaSurface.y;

        mLoc.x = -1;
        for (i = mStartGridArea.x; i <= mEndArea.x; i++)
        {
            mLoc.y = -1;
            for (j = mStartGridArea.y; j <= mEndArea.y; j++)
            {

                int mTileType = mWaterMap[j % 40][i % 40];
                int mTileN, mTileE, mTileS, mTileW;

                if (mTileType == 0)
                {
                    item.setFillColor(Color(3, 90, 252));
                } else if (mTileType == 1)
                {
                    Vector2i mItemPos(i, j);
                    mTileS = mWaterMap[(mItemPos.y + 1) % 40][(mItemPos.x) % 40];
                    mTileE = mWaterMap[(mItemPos.y) % 40][(mItemPos.x + 1) % 40];
                    if (mItemPos.y - 1 < 0)
                    {
                        mTileN = mWaterMap[(40 - mItemPos.y - 1) % 40][(mItemPos.x) % 40];
                    } else
                    {
                        mTileN = mWaterMap[(mItemPos.y - 1) % 40][(mItemPos.x) % 40];
                    }
                    if (mItemPos.x - 1 < 0)
                    {
                        mTileW = mWaterMap[(mItemPos.y) % 40][(40 - mItemPos.x - 1) % 40];
                    } else
                    {
                        mTileW = mWaterMap[(mItemPos.y) % 40][(mItemPos.x - 1) % 40];
                    }

                    if (mTileN == 0 || mTileE == 0 || mTileS == 0 || mTileW == 0)
                    {
                        item.setFillColor(Color(252, 240, 3, 230));
                    } else
                    {
                        item.setFillColor(Color(252, 240, 3));
                    }
                }
                item.setPosition(
                        Vector2f(
                                (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                        )
                );
                item.setSize(Vector2f(40.0f, 40.0f));
                window.draw(item);
                mLoc.y++;
            }
            mLoc.x++;
        }

        window.draw(mMainCharacter->getSprite(window));

        for (i = -1; i < mWindowSize.x / 40 + 2; i++)
        {
            for (j = -1; j < mWindowSize.y / 40 + 3; j++)
            {
                item.setOutlineColor(Color::Black);
                item.setOutlineThickness(1);
                item.setFillColor(Color(3, 252, 32, 0));
                item.setPosition(
                        Vector2f(
                                i * 40 - 20,
                                j * 40 - 10
                        )
                );
                item.setSize(Vector2f(40.0f, 40.0f));
//                window.draw(item);
            }
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
