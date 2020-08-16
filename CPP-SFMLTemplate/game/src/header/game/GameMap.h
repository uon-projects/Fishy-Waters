#ifndef DAI_MAKAI_MURA_GAMEMAP_H
#define DAI_MAKAI_MURA_GAMEMAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "./ItemModel.h"

using namespace std;
using namespace sf;

class GameMap
{

private:
    vector<ItemModel *> mItems;
    vector<ItemModel *> mCharacterStartPos;
    vector<ItemModel *> mNPCStartPos;

public:
    GameMap()
    {
        initialize();
    }

    ~GameMap()
    {

    }

    void initialize()
    {
        initializeStartPos();
        initializeNPCs();
        initializeLvl1();
        initializeLvl2();
        initializeLvl3();
        initializeLvl4();
    }

    void addStartPos(int mLvl, int mStartPosX, int mStartPosY)
    {
        ItemModel *mItemModel;

        mStartPosY *= -1;
        mItemModel = new ItemModel(
                mLvl,
                Vector2i(mStartPosX, mStartPosY)
        );
        mCharacterStartPos.push_back(mItemModel);
    }

    void addNPCStartPos(int mLvl, int mStartPosX, int mStartPosY, int mArea, bool mFaceRight)
    {
        ItemModel *mItemModel;

        mStartPosY *= -1;
        mItemModel = new ItemModel(
                mLvl,
                Vector2i(mStartPosX, mStartPosY),
                mArea,
                mFaceRight
        );
        mNPCStartPos.push_back(mItemModel);
    }

    vector<ItemModel *> getNPCByLvl()
    {
        vector < ItemModel * > npcList;
        for (ItemModel *mNPC : mNPCStartPos)
        {
            if (mNPC->getLvl() == 0)
            {
                npcList.push_back(mNPC);
            }
        }

        return npcList;
    }

    Vector2f getCharacterStartPos()
    {
        Vector2f mStartPosOfLvl = Vector2f(0.0f, 0.0f);
        return mStartPosOfLvl;
    }

    void addItem(int mLvl, int mStartPosX, int mStartPosY, int mSizeW, int mSizeH, int mType)
    {
        ItemModel *mItemModel;

        mStartPosY *= -1;
        mItemModel = new ItemModel(
                mLvl,
                Vector2i(mStartPosX, mStartPosY - mSizeH),
                Vector2i(mSizeW, mSizeH),
                mType
        );
        mItems.push_back(mItemModel);
    }

    vector<ItemModel *> getItemsByLvl()
    {
        vector < ItemModel * > lvlItems;
        for (ItemModel *mItem : mItems)
        {
            if (mItem->getLvl() == 0 && (mItem->getType() == 0))
            {
                lvlItems.push_back(mItem);
            }
        }

        return lvlItems;
    }

    vector<ItemModel *> getEndPortalByLvl()
    {
        vector < ItemModel * > endPortals;

        for (ItemModel *mItem : mItems)
        {
            if (mItem->getLvl() == 0 && mItem->getType() == 1)
            {
                endPortals.push_back(mItem);
            }
        }

        return endPortals;
    }

    int getNearestGroundLvl(Vector2f mSpriteLocStart, Vector2f mSpriteLocSize, int mGameOffsetY = 0)
    {
        int mNearestGroundLvl = 0;
        int characterPosY = mSpriteLocStart.y;
        int characterPosSX = mSpriteLocStart.x + 64;
        int characterPosEX = mSpriteLocStart.x + mSpriteLocSize.x - 64;

        vector < ItemModel * > mLvlItems = getItemsByLvl();
        for (ItemModel *mItem : mLvlItems)
        {
            int itemPosSX = mItem->getStartPos().x - 30;
            int itemPosEX = mItem->getSize().x + mItem->getStartPos().x + 30;
            int itemPosY = mItem->getStartPos().y;
            if (itemPosY >= characterPosY)
            {
                if (characterPosSX >= itemPosSX && characterPosEX <= itemPosEX)
                {
                    if (mNearestGroundLvl == 0)
                    {
                        mNearestGroundLvl = itemPosY;
                    } else if (mNearestGroundLvl >= characterPosY)
                    {
                        mNearestGroundLvl = itemPosY;
                    }
                }
            }
        }
        return mNearestGroundLvl;
    }

    int getNearestGroundLvlCharacter(Vector2f mSpriteLocStart, Vector2f mSpriteLocSize, int mGameOffsetY = 0)
    {

        int mNearestGroundLvl = 0;
        int characterPosY = mSpriteLocStart.y;
        int characterPosSX = mSpriteLocStart.x + 64;
        int characterPosEX = mSpriteLocStart.x + mSpriteLocSize.x - 64;

        vector < ItemModel * > mLvlItems = getItemsByLvl();
        for (ItemModel *mItem : mLvlItems)
        {
            int itemPosSX = mItem->getStartPos().x - 30;
            int itemPosEX = mItem->getSize().x + mItem->getStartPos().x + 30;
            int itemPosY = mItem->getStartPos().y;
            if (itemPosY >= characterPosY)
            {
                if (characterPosSX >= itemPosSX && characterPosEX <= itemPosEX)
                {
                    if (mNearestGroundLvl == 0)
                    {
                        mNearestGroundLvl = itemPosY;
                    } else if (mNearestGroundLvl >= characterPosY)
                    {
                        mNearestGroundLvl = itemPosY;
                    }
                }
            }
        }
        return mNearestGroundLvl;
    }

    void initializeStartPos()
    {
        addStartPos(1, 100, 50);
        addStartPos(2, 600, 50);
        addStartPos(3, 225, 80);
    }

    void initializeNPCs()
    {
        //lvl 1
        addNPCStartPos(1, 400, 50, 200, true);
        addNPCStartPos(1, 620, 500, 240, false);
        addNPCStartPos(1, 430, 500, 140, false);

        //lvl 2
        addNPCStartPos(2, 70, 50, 300, true);
        addNPCStartPos(2, 675, 320, 100, false);

        //lvl 3
        addNPCStartPos(3, 600, 190, 100, true);
        addNPCStartPos(3, 300, 360, 120, false);
        addNPCStartPos(3, 70, 480, 120, true);
        addNPCStartPos(3, 70, 640, 300, true);
        addNPCStartPos(3, 370, 640, 300, false);
        addNPCStartPos(3, 240, 800, 60, false);
        addNPCStartPos(3, 260, 800, 60, true);
    }

    void initializeLvl1()
    {

        //blocks
        addItem(1, 0, 0, 800, 50, 0);
        addItem(1, 250, 150, 100, 20, 0);
        addItem(1, 375, 250, 100, 20, 0);
        addItem(1, 250, 350, 100, 20, 0);
        addItem(1, 375, 450, 425, 20, 0);

        //portals
        addItem(1, 790, 470, 10, 120, 1);

    }

    void initializeLvl2()
    {

        //blocks
        addItem(2, 0, 0, 800, 50, 0);
        addItem(2, 250, 150, 100, 20, 0);
        addItem(2, 375, 300, 425, 20, 0);
        addItem(2, 375, 450, 75, 20, 0);
        addItem(2, 525, 450, 275, 20, 0);
        addItem(2, 100, 550, 250, 20, 0);
        addItem(2, 300, 700, 400, 20, 0);
        addItem(2, 450, 800, 100, 20, 0);

        //portals
        addItem(2, 475, 1050, 50, 20, 1);

    }

    void initializeLvl3()
    {

        //blocks
        addItem(3, 50, 60, 500, 20, 0);
        addItem(3, 600, 170, 100, 20, 0);
        addItem(3, 450, 280, 100, 20, 0);
        addItem(3, 600, 390, 100, 20, 0);
        addItem(3, 450, 500, 100, 20, 0);
        addItem(3, 600, 610, 100, 20, 0);
        addItem(3, 450, 720, 100, 20, 0);
        addItem(3, 150, 340, 200, 20, 0);
        addItem(3, 50, 460, 175, 20, 0);
        addItem(3, 0, 620, 400, 20, 0);
        addItem(3, 200, 780, 125, 20, 0);
        addItem(3, 400, 900, 80, 20, 0);
        addItem(3, 300, 1020, 120, 20, 0);
        addItem(3, 50, 1100, 150, 20, 0);

        //portals
        addItem(3, 50, 1120, 20, 100, 1);

    }

    void generateNewPlatform(
            int &mSide,
            int &mStartPos,
            int &mSizeWidth,
            int &mProgressPos,
            int &mMultiplierFactor,
            int &mMultiplier,
            int &rageY
    )
    {


        if (mSide == -1)
        {
            mSide = rand() % 64 / 16;
        }
        switch (mSide)
        {
            case 0:
                mStartPos = 50 + rand() % 170 + 15;
                mSizeWidth = (rand() % 15 * rand() % 15) + 100;
                break;
            case 1:
                mStartPos = 200 + rand() % 170 + 15;
                mSizeWidth = (rand() % 14 * rand() % 14) + 120;
                break;
            case 2:
                mStartPos = 400 + rand() % 170 + 15;
                mSizeWidth = (rand() % 14 * rand() % 14) + 120;
                break;
            case 3:
                mStartPos = 550 + rand() % 170 + 15;
                mSizeWidth = (rand() % 15 * rand() % 15) + 100;
                break;
            default:
                break;
        }

        mProgressPos = rageY;
        mMultiplierFactor = rand() % 3 + 1;
        if (mMultiplierFactor > 2)
        {
            mMultiplier = mMultiplierFactor * (rand() % 20 + 30);
        } else if (mMultiplierFactor > 1)
        {
            mMultiplier = mMultiplierFactor * (rand() % 30 + 70);
        } else
        {
            mMultiplier = mMultiplierFactor * (rand() % 20 + 110);
        }

    }

    void generateExtraNewPlatform(
            int &mSide,
            int &mStartPos,
            int &mSizeWidth,
            int &mProgressPos,
            int &rageY
    )
    {

        int mEndPos = mStartPos + mSizeWidth;
        if (mStartPos >= 700)
        {
            mSide = 6;
        } else if (mEndPos <= 100)
        {
            mSide = 1;
        } else if (mStartPos > 100 && mEndPos < 250)
        {
            mSide = 2;
        } else if (mStartPos >= 250 && mEndPos <= 400)
        {
            mSide = 3;
        } else if (mStartPos > 550 && mEndPos < 700)
        {
            mSide = 4;
        } else if (mStartPos >= 400 && mEndPos <= 550)
        {
            mSide = 5;
        } else if (mStartPos >= 0 && mEndPos < 250)
        {
            mSide = 7;
        } else if (mStartPos > 550 && mEndPos <= 800)
        {
            mSide = 8;
        } else if (mStartPos >= 100 && mEndPos <= 300)
        {
            mSide = 9;
        } else if (mStartPos >= 500 && mEndPos <= 700)
        {
            mSide = 10;
        } else if (mStartPos >= 300)
        {
            mSide = 2;
        } else if (mEndPos <= 500)
        {
            mSide = 4;
        } else
        {
            mSide = 11;
        }
        switch (mSide)
        {
            case 1:
                mStartPos = 150 + rand() % 200;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 2:
                mStartPos = 300 + rand() % 200;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 3:
                mStartPos = 460 + rand() % 100;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 4:
                mStartPos = 500 - rand() % 200;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 5:
                mStartPos = 340 - rand() % 100;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 6:
                mStartPos = 550 - rand() % 200;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 7:
                mStartPos = 400 + rand() % 100;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 8:
                mStartPos = 400 - rand() % 100;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 9:
                mStartPos = 300 + rand() % 200;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 10:
                mStartPos = 500 - rand() % 200;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            case 11:
                mStartPos = 100 + rand() % 600;
                mSizeWidth = (rand() % 15 * rand() % 15) + 120;
                break;
            default:
                break;
        }
        rageY += (rand() % 7 * rand() % 7 + 100);
        mProgressPos = rageY;
        rageY -= rand() % 10 * rand() % 10;
    }

    void initializeLvl4()
    {
        size_t i;
        srand(time(NULL));

        //blocks
        int rageY = 200;
        int posX = 0;
        int posY = 0;
        int mRecommendedSide = -1;
        for (i = 0; i < 4; i++)
        {
            int mStartPos1;
            int mSizeWidth1;
            int mStartPos2;
            int mSizeWidth2;
            int mProgressPos1;
            int mProgressPos2;
            int mMultiplierFactor;
            int mMultiplier;
            int mSide1;
            int mSide2;
            int mPrevPosY;
            int mSpawnNPC;

            mSide1 = mRecommendedSide;
            mRecommendedSide = -1;
            generateNewPlatform(
                    mSide1,
                    mStartPos1,
                    mSizeWidth1,
                    mProgressPos1,
                    mMultiplierFactor,
                    mMultiplier,
                    rageY
            );
            addItem(4, mStartPos1, mProgressPos1, mSizeWidth1, 20, 0);
            mSpawnNPC = rand() % 10;
            if (mSpawnNPC < 4 && mProgressPos1 > 500)
            {
                addNPCStartPos(4, mStartPos1 + 10, mProgressPos1 + 20, mSizeWidth1 - 20, true);
            }

            if (posX == 0 && posY == 0)
            {
                posX = mStartPos1 + 20;
                posY = mProgressPos1 + 20;
                addStartPos(4, posX, posY);
            }

            mSide2 = mSide1;
            generateExtraNewPlatform(
                    mSide2,
                    mStartPos2,
                    mSizeWidth2,
                    mProgressPos2,
                    rageY
            );
            addItem(4, mStartPos2, mProgressPos2, mSizeWidth2, 20, 0);
            mSpawnNPC = rand() % 10;
            if (mSpawnNPC < 4 && mProgressPos2 > 500)
            {
                addNPCStartPos(4, mStartPos2 + 10, mProgressPos2 + 20, mSizeWidth2 - 20, true);
            }

            mPrevPosY = rageY;
            rageY -= 40;
            rageY += rand() % 200;
            if ((abs)(rageY - mPrevPosY) <= 40)
            {
                if (mStartPos2 >= 400 || mStartPos2 + mSizeWidth2 > 700)
                {
                    mRecommendedSide = 0;
                } else if (mStartPos1 < 100 || mStartPos1 + mSizeWidth1 <= 400)
                {
                    mRecommendedSide = 3;
                } else
                {
                    mRecommendedSide = rand() % 2 + 1;
                }
            }

            if (i == 3)
            {
                if (mProgressPos1 > mProgressPos2)
                {
                    //portal
                    addItem(4, mStartPos1, mProgressPos1 + 170, mSizeWidth1, 10, 1);
                } else
                {
                    //portal
                    addItem(4, mStartPos2, mProgressPos2 + 170, mSizeWidth2, 10, 1);
                }
            }
        }

    }

};

#endif //DAI_MAKAI_MURA_GAMEMAP_H
