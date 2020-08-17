#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/MaterialButton.h"
#include "../../../../library/src/header/FontManager.h"
#include "../App.h"
#include "../npc/NPCharacter.h"
#include "../player/MainCharacter.h"
#include "../game/GameMap.h"
#include "../npc/LocationModel.h"

using namespace std;
using namespace sf;

class GameScreen
{

private:
    RectangleShape gameMenuScreenBackground;
    App *mApp;
    Font mFont;
    MainCharacter *mMainCharacter;
    vector<NPCharacter *> mFishList;
    GameMap *mGameMap;
    int mBackgroundR, mBackgroundG, mBackgroundB;
    int **mWaterMap;
    bool mNearFish;
    bool mMiniGameKeySelected;
    int mMiniGameKey;
    int mMiniGameTimer;
    int mMiniGameKeys;
    Vector2i mMiniGameFish;

public:
    GameScreen()
    {

        mBackgroundR = 32;
        mBackgroundG = 165;
        mBackgroundB = 227;
        srand((unsigned) time(NULL));
        mNearFish = false;
        mFont = FontManager().loadFont();

    }

    ~GameScreen()
    {

    }

public:

    void mMoveCharacter()
    {
        mMiniGameKeys = 0;
        mMiniGameKeySelected = false;
        mNearFish = false;
        mWaterMap[mMiniGameFish.x][mMiniGameFish.y] = 0;
    }

    void drawStone(RenderWindow &window, Vector2f mPosition)
    {
        RectangleShape mStoneSprite;

        mStoneSprite.setOrigin(Vector2f(-5.0f, -10.0f));
        mStoneSprite.setFillColor(Color(74, 74, 74));
        mStoneSprite.setPosition(mPosition);
        mStoneSprite.setSize(Vector2f(30.0f, 20.0f));
        window.draw(mStoneSprite);

        mStoneSprite.setOrigin(Vector2f(-10.0f, -15.0f));
        mStoneSprite.setFillColor(Color(255, 255, 255, 30));
        mStoneSprite.setPosition(mPosition);
        mStoneSprite.setSize(Vector2f(20.0f, 10.0f));
        window.draw(mStoneSprite);

        mStoneSprite.setOrigin(Vector2f(-14.0f, -17.0f));
        mStoneSprite.setFillColor(Color(255, 255, 255, 40));
        mStoneSprite.setPosition(mPosition);
        mStoneSprite.setSize(Vector2f(12.0f, 6.0f));
        window.draw(mStoneSprite);
    }

    void drawHarbor(RenderWindow &window, Vector2f mPosition)
    {
        RectangleShape mHarborSprite;

        mHarborSprite.setOrigin(Vector2f(0.0f, -15.0f));
        mHarborSprite.setFillColor(Color(245, 195, 15));
        mHarborSprite.setPosition(mPosition);
        mHarborSprite.setSize(Vector2f(50.0f, 25.0f));
        window.draw(mHarborSprite);
    }

    void drawBoat(RenderWindow &window)
    {
        RectangleShape mBoatSprite;
        Vector2f mPosition = mMainCharacter->getSpriteLocation(window);
        mBoatSprite.setRotation(mMainCharacter->getBoatRotation());

        mBoatSprite.setOrigin(Vector2f(-10.0f, -5.0f));
        mBoatSprite.setFillColor(Color(212, 174, 11));
        mBoatSprite.setPosition(mPosition);
        mBoatSprite.setSize(Vector2f(20.0f, 30.0f));
        window.draw(mBoatSprite);

        mBoatSprite.setOrigin(Vector2f(-24.0f, -6.0f));
        mBoatSprite.setFillColor(Color(247, 209, 42));
        mBoatSprite.setPosition(mPosition);
        mBoatSprite.setSize(Vector2f(6.0f, 28.0f));
        window.draw(mBoatSprite);

        mBoatSprite.setOrigin(Vector2f(-17.0f, -6.0f));
        mBoatSprite.setFillColor(Color(247, 209, 42));
        mBoatSprite.setPosition(mPosition);
        mBoatSprite.setSize(Vector2f(6.0f, 28.0f));
        window.draw(mBoatSprite);

        mBoatSprite.setOrigin(Vector2f(-10.0f, -6.0f));
        mBoatSprite.setFillColor(Color(247, 209, 42));
        mBoatSprite.setPosition(mPosition);
        mBoatSprite.setSize(Vector2f(6.0f, 28.0f));
        window.draw(mBoatSprite);

        mBoatSprite.setOrigin(Vector2f(-14.0f, -12.0f));
        mBoatSprite.setFillColor(Color(247, 86, 42));
        mBoatSprite.setPosition(mPosition);
        mBoatSprite.setSize(Vector2f(12.0f, 6.0f));
        window.draw(mBoatSprite);
    }

    int getNumberSquares(Vector2i mAreaLines, Vector2i mAreaColumns, int type)
    {
        int i, j;
        int mSize = 0;
        int mMapLines = mGameMap->getMapLines();
        int mMapColumns = mGameMap->getMapColumns();
        for (i = mAreaLines.x; i <= mAreaLines.y; i++)
        {
            for (j = mAreaColumns.x; j <= mAreaColumns.y; j++)
            {
                int mTileType = mWaterMap[j % mMapLines][i % mMapColumns];
                if (mTileType == type)
                {
                    mSize++;
                }
            }
        }
        return mSize;
    }

    void spawnFish(Vector2i mAreaLines, Vector2i mAreaColumns)
    {
        int i, j;
        int mMapLines = mGameMap->getMapLines();
        int mMapColumns = mGameMap->getMapColumns();
        if (getNumberSquares(mAreaLines, mAreaColumns, 4) < getNumberSquares(mAreaLines, mAreaColumns, 0) / 20)
        {
            vector < LocationModel * > mAvailableLocations;
            LocationModel *mLocationModel;
            for (i = mAreaLines.x; i <= mAreaLines.y; i++)
            {
                for (j = mAreaColumns.x; j <= mAreaColumns.y; j++)
                {

                    int mTileType = mWaterMap[j % mMapLines][i % mMapColumns];
                    if (mTileType == 0)
                    {
                        mLocationModel = new LocationModel(Vector2i(j % mMapLines, i % mMapColumns));
                        mAvailableLocations.push_back(mLocationModel);
                    }
                }
            }
            if (mAvailableLocations.size() != 0)
            {
                Vector2i mBoatPos = mAvailableLocations[rand() % mAvailableLocations.size()]->getPosition();
                mWaterMap[mBoatPos.x][mBoatPos.y] = 4;
            }
        }
    }

    bool mMiniGameInteracted;

    void showFishMiniGame(RenderWindow &window)
    {
        RectangleShape mMiniGameSprite;
        Vector2f mWindowSize;
        Text mText;

        mWindowSize.x = (float) window.getSize().x;
        mWindowSize.y = (float) window.getSize().y;

        mMiniGameSprite.setOutlineColor(Color(0, 0, 0));
        mMiniGameSprite.setOutlineThickness(3);
        mMiniGameSprite.setFillColor(Color(74, 74, 74, 240));
        mMiniGameSprite.setPosition(Vector2f(mWindowSize.x / 2, mWindowSize.y / 2));
        mMiniGameSprite.setSize(Vector2f(90.0f, 56.0f));
        mMiniGameSprite.setOrigin(Vector2f(45.0f, 28.0f));
        window.draw(mMiniGameSprite);

        if (!mMiniGameKeySelected)
        {
            if (!mMiniGameInteracted)
            {
                mMoveCharacter();
            }
            mMiniGameKey = rand() % 4;
            mMiniGameKeySelected = true;
            mMiniGameInteracted = false;
            mMiniGameTimer = rand() % 20 + 40;
            if (mMiniGameKeys == 0)
            {
                mMiniGameKeys = 5;
            }
            mMiniGameKeys--;
        }
        mMiniGameTimer--;
        if (mMiniGameTimer <= 0)
        {
            mMiniGameKeySelected = false;
            if (mMiniGameKeys == 0)
            {
                mApp->addCoins(rand() % 4 + 3);
                mMoveCharacter();
            }
        }

        mText.setFont(mFont);
        mText.setFillColor(Color(0, 0, 0, 100));
        mText.setCharacterSize(22);
        mText.setFillColor(Color::Black);
        if (mMiniGameKey == 0)
        {
            mText.setString("Left");
        } else if (mMiniGameKey == 1)
        {
            mText.setString("Up");
        } else if (mMiniGameKey == 2)
        {
            mText.setString("Right");
        } else if (mMiniGameKey == 3)
        {
            mText.setString("Down");
        }
        mText.setPosition(Vector2f(mWindowSize.x / 2, mWindowSize.y / 2));
        mText.setOrigin(mText.getLocalBounds().width / 2, mText.getLocalBounds().height / 1.3f);
        window.draw(mText);
    }

    void drawCoins(RenderWindow &window)
    {
        RectangleShape mMiniGameSprite;
        Vector2f mWindowSize;
        Text mText;

        mWindowSize.x = (float) window.getSize().x;
        mWindowSize.y = (float) window.getSize().y;

        mMiniGameSprite.setOutlineColor(Color(255, 255, 255, 200));
        mMiniGameSprite.setOutlineThickness(2);
        mMiniGameSprite.setFillColor(Color(255, 255, 255, 100));
        mMiniGameSprite.setSize(Vector2f(100.0f, 36.0f));
        mMiniGameSprite.setPosition(Vector2f(mWindowSize.x - mMiniGameSprite.getLocalBounds().width - 8, 10));
        window.draw(mMiniGameSprite);

        mText.setFont(mFont);
        mText.setFillColor(Color(0, 0, 0, 200));
        mText.setCharacterSize(20);
        mText.setString("Coins: " + to_string(mApp->getCoins()));
        mText.setPosition(Vector2f(mWindowSize.x - mMiniGameSprite.getLocalBounds().width + 2, 14));
        window.draw(mText);
    }

    void draw(RenderWindow &window)
    {
        int i, j;
        int mMapLines = mGameMap->getMapLines();
        int mMapColumns = mGameMap->getMapColumns();
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
        mGridAreaSurface.x = mWindowSize.x / mMapColumns + 2;
        mGridAreaSurface.y = mWindowSize.y / mMapLines + 3;
        mGameOffset = mMainCharacter->getGameOffset(window);
        mGameOffsetMoving = mMainCharacter->getGameOffsetMoving();

        mCharacterPosGrid.x = mMainCharacter->getCharacterPosition().x / mMapColumns;
        mCharacterPosGrid.y = mMainCharacter->getCharacterPosition().y / mMapLines;
        if (mCharacterPosGrid.x > 0)
        {
            mCharacterPosGrid.x = mMapColumns - mCharacterPosGrid.x * -1;
        }
        mCharacterPosGrid.x = (int) mCharacterPosGrid.x % mMapColumns;
        if (mCharacterPosGrid.y > 0)
        {
            mCharacterPosGrid.y = mMapLines - mCharacterPosGrid.y * -1;
        }
        mCharacterPosGrid.y = (int) mCharacterPosGrid.y % mMapLines;

        mCharacterPosOnGrid.x = mCharacterPosGrid.x;
        mCharacterPosOnGrid.y = mCharacterPosGrid.y;
        if (mCharacterPosOnGrid.x < 0)
        {
            mCharacterPosOnGrid.x = mMapColumns + mCharacterPosGrid.x;
        }
        if (mCharacterPosOnGrid.y < 0)
        {
            mCharacterPosOnGrid.y = mMapLines + mCharacterPosGrid.y;
        }

        mStartGridArea.x = mCharacterPosGrid.x - mGridAreaSurface.x / 2;
        mStartGridArea.y = mCharacterPosGrid.y - mGridAreaSurface.y / 2;
        if (mStartGridArea.x < 0)
        {
            mStartGridArea.x = mMapColumns + mStartGridArea.x;
        }
        if (mStartGridArea.y < 0)
        {
            mStartGridArea.y = mMapLines + mStartGridArea.y;
        }
        mStartGridArea.x = mStartGridArea.x % mMapColumns;
        mStartGridArea.y = mStartGridArea.y % mMapLines;
        if (mGameOffsetMoving.x > 0)
        {
            mStartGridArea.x--;
        }
        if (mStartGridArea.x < 0)
        {
            mStartGridArea.x = mMapColumns + mStartGridArea.x;
        }
        if (mGameOffsetMoving.y > 0)
        {
            mStartGridArea.y--;
        }
        if (mStartGridArea.y < 0)
        {
            mStartGridArea.y = mMapLines + mStartGridArea.y % mMapLines;
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
        spawnFish(
                Vector2i(
                        mStartGridArea.x,
                        mEndArea.x
                ),
                Vector2i(
                        mStartGridArea.y,
                        mEndArea.y
                )
        );

        for (i = mStartGridArea.x; i <= mEndArea.x; i++)
        {
            mLoc.y = -1;
            for (j = mStartGridArea.y; j <= mEndArea.y; j++)
            {

                int mTileType = mWaterMap[j % mMapLines][i % mMapColumns];
                int mTileN, mTileE, mTileS, mTileW;
                int mTileNE, mTileNW, mTileSE, mTileSW;
                int mPosN, mPosE, mPosS, mPosW;

                if (mTileType == 0)
                {
                    item.setOrigin(Vector2f(0.0f, 0.0f));
                    item.setFillColor(Color(3, 90, 252));
                    item.setPosition(
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                    item.setSize(Vector2f(40.0f, 40.0f));
                    window.draw(item);
                } else if (mTileType == 2)
                {
                    item.setOrigin(Vector2f(0.0f, 0.0f));
                    item.setFillColor(Color(3, 90, 252));
                    item.setPosition(
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                    item.setSize(Vector2f(40.0f, 40.0f));
                    window.draw(item);

                    drawStone(
                            window,
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                } else if (mTileType == 4)
                {
                    item.setOrigin(Vector2f(0.0f, 0.0f));
                    item.setFillColor(Color(3, 90, 252));
                    item.setPosition(
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                    item.setSize(Vector2f(40.0f, 40.0f));
                    window.draw(item);

                    drawStone(
                            window,
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                } else if (mTileType == 3)
                {
                    item.setOrigin(Vector2f(0.0f, 0.0f));
                    item.setFillColor(Color(152, 219, 18));
                    item.setPosition(
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                    item.setSize(Vector2f(40.0f, 40.0f));
                    window.draw(item);

                    drawHarbor(
                            window,
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                } else if (mTileType == 1)
                {
                    Vector2i mItemPos(i % mMapLines, j % mMapColumns);
                    mPosS = (mItemPos.y + 1) % mMapLines;
                    mPosE = (mItemPos.x + 1) % mMapColumns;
                    mPosN = mItemPos.y - 1 < 0 ?
                            (mMapLines - mItemPos.y - 1) % mMapLines :
                            (mItemPos.y - 1) % mMapLines;
                    mPosW = mItemPos.x - 1 < 0 ?
                            (mMapColumns - mItemPos.x - 1) % mMapColumns :
                            (mItemPos.x - 1) % mMapColumns;

                    mTileN = mWaterMap[mPosN][mItemPos.x];
                    mTileS = mWaterMap[mPosS][mItemPos.x];
                    mTileE = mWaterMap[mItemPos.y][mPosE];
                    mTileW = mWaterMap[mItemPos.y][mPosW];
                    mTileNE = mWaterMap[mPosN][mPosE];
                    mTileNW = mWaterMap[mPosN][mPosW];
                    mTileSE = mWaterMap[mPosS][mPosE];
                    mTileSW = mWaterMap[mPosS][mPosW];

                    item.setOrigin(Vector2f(0.0f, 0.0f));
                    if (mTileN != 1 || mTileE != 1 || mTileS != 1 || mTileW != 1)
                    {
                        item.setFillColor(Color(152, 219, 18));
                    } else if (mTileNE != 1 || mTileNW != 1 || mTileSE != 1 || mTileSW != 1)
                    {
                        item.setFillColor(Color(152, 219, 18));
                    } else
                    {
                        item.setFillColor(Color(124, 181, 9));
                    }
                    item.setPosition(
                            Vector2f(
                                    (float) mLoc.x * 40 - mGameOffsetMoving.x - 20,
                                    (float) mLoc.y * 40 - mGameOffsetMoving.y - 10
                            )
                    );
                    item.setSize(Vector2f(40.0f, 40.0f));
                    window.draw(item);
                }
                mLoc.y++;
            }
            mLoc.x++;
        }

        drawBoat(window);

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

        if (mNearFish)
        {
            showFishMiniGame(window);
        }
        if (mIsNearHarbor)
        {
            //show harbor shopscreen
        } else
        {
            drawCoins(window);
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

    int getTileType(int nextX, int nextY)
    {
        int mMapLines = mGameMap->getMapLines();
        int mMapColumns = mGameMap->getMapColumns();
        Vector2f mCharacterPosGrid;
        mCharacterPosGrid.x = mMainCharacter->getCharacterPosition().x / mMapColumns + nextX;
        mCharacterPosGrid.y = mMainCharacter->getCharacterPosition().y / mMapLines + nextY;
        if (mCharacterPosGrid.x > 0)
        {
            mCharacterPosGrid.x = mMapColumns - mCharacterPosGrid.x * -1;
        }
        mCharacterPosGrid.x = (int) mCharacterPosGrid.x % mMapColumns;
        if (mCharacterPosGrid.y > 0)
        {
            mCharacterPosGrid.y = mMapLines - mCharacterPosGrid.y * -1;
        }
        mCharacterPosGrid.y = (int) mCharacterPosGrid.y % mMapLines;
        if (mCharacterPosGrid.x < 0)
        {
            mCharacterPosGrid.x = mMapColumns + mCharacterPosGrid.x;
        }
        if (mCharacterPosGrid.y < 0)
        {
            mCharacterPosGrid.y = mMapLines + mCharacterPosGrid.y;
        }

        int mTileType = mWaterMap[(int) mCharacterPosGrid.y % mMapLines][(int) mCharacterPosGrid.x % mMapColumns];
        return mTileType;
    }

    void storeFishPos(int nextX, int nextY)
    {
        int mMapLines = mGameMap->getMapLines();
        int mMapColumns = mGameMap->getMapColumns();
        Vector2f mCharacterPosGrid;
        mCharacterPosGrid.x = mMainCharacter->getCharacterPosition().x / mMapColumns + nextX;
        mCharacterPosGrid.y = mMainCharacter->getCharacterPosition().y / mMapLines + nextY;
        if (mCharacterPosGrid.x > 0)
        {
            mCharacterPosGrid.x = mMapColumns - mCharacterPosGrid.x * -1;
        }
        mCharacterPosGrid.x = (int) mCharacterPosGrid.x % mMapColumns;
        if (mCharacterPosGrid.y > 0)
        {
            mCharacterPosGrid.y = mMapLines - mCharacterPosGrid.y * -1;
        }
        mCharacterPosGrid.y = (int) mCharacterPosGrid.y % mMapLines;
        if (mCharacterPosGrid.x < 0)
        {
            mCharacterPosGrid.x = mMapColumns + mCharacterPosGrid.x;
        }
        if (mCharacterPosGrid.y < 0)
        {
            mCharacterPosGrid.y = mMapLines + mCharacterPosGrid.y;
        }

        mMiniGameFish.x = (int) mCharacterPosGrid.y % mMapLines;
        mMiniGameFish.y = (int) mCharacterPosGrid.x % mMapColumns;
    }

    bool canMove(int nextX, int nextY)
    {
        return 0 == getTileType(nextX, nextY);
    }

    bool canMoveNorth()
    {
        return canMove(0, -1);
    }

    bool canMoveEast()
    {
        return canMove(1, 0);
    }

    bool canMoveSouth()
    {
        return canMove(0, 1);
    }

    bool canMoveWest()
    {
        return canMove(-1, 0);
    }

    void inputListener(Event event)
    {

        if (event.key.code == Keyboard::X)
        {
            system("pause");
        }
        if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
        {
            if (mNearFish)
            {
                if (mMiniGameKey == 0)
                {
                    mMiniGameInteracted = true;
                    mMiniGameTimer = 0;
                } else
                {
                    mMiniGameTimer = 0;
                    mMoveCharacter();
                }
            } else if (canMoveWest())
            {
                mMainCharacter->moveWest();
            }
        } else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
        {
            if (mNearFish)
            {
                if (mMiniGameKey == 2)
                {
                    mMiniGameInteracted = true;
                    mMiniGameTimer = 0;
                } else
                {
                    mMiniGameTimer = 0;
                    mMoveCharacter();
                }
            } else if (canMoveEast())
            {
                mMainCharacter->moveEast();
            }
        } else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
        {
            if (mNearFish)
            {
                if (mMiniGameKey == 1)
                {
                    mMiniGameInteracted = true;
                    mMiniGameTimer = 0;
                } else
                {
                    mMiniGameTimer = 0;
                    mMoveCharacter();
                }
            } else if (canMoveNorth())
            {
                mMainCharacter->moveNorth();
            }
        } else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
        {
            if (mNearFish)
            {
                if (mMiniGameKey == 3)
                {
                    mMiniGameInteracted = true;
                    mMiniGameTimer = 0;
                } else
                {
                    mMiniGameTimer = 0;
                    mMoveCharacter();
                }
            } else if (canMoveSouth())
            {
                mMainCharacter->moveSouth();
            }
        }
    }

    bool mIsNearHarbor;

    void update()
    {

        if (mMainCharacter->isCharacterMoving())
        {
            mIsNearHarbor = getTileType(0, -1) == 3;
            if (getTileType(0, -1) == 4)
            {
                mMiniGameInteracted = true;
                mNearFish = true;
                storeFishPos(0, -1);
            } else if (getTileType(0, 1) == 4)
            {
                mMiniGameInteracted = true;
                mNearFish = true;
                storeFishPos(0, 1);
            } else if (getTileType(-1, 0) == 4)
            {
                mMiniGameInteracted = true;
                mNearFish = true;
                storeFishPos(-1, 0);
            } else if (getTileType(1, 0) == 4)
            {
                mMiniGameInteracted = true;
                mNearFish = true;
                storeFishPos(1, 0);
            } else
            {
                mNearFish = false;
            }
        }
        mMainCharacter->update();

    }

    void initNewLvl()
    {

        mMiniGameKeySelected = false;
        mIsNearHarbor = false;
        mFishList.clear();
        mMainCharacter->reset();
        mMiniGameKeys = 0;

    }

};
