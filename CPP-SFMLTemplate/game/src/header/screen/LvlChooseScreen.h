#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/MaterialButton.h"
#include "../../../../library/src/header/LevelButton.h"
#include "../App.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

using namespace sf;

class LvlChooseScreen
{

public:
    RectangleShape lvlChooseScreenBackground;
    App *mApp;

public:
    LvlChooseScreen()
    {

        lvlChooseScreenBackground.setFillColor(Color(0, 150, 136));

        exitBtn.setBtnPosition((float) 90, (float) 50);
        exitBtn.setSize(Vector2f(90, 30));
        exitBtn.setColor(Color(244, 67, 54));
        exitBtn.setHoverColor(Color(211, 47, 47));
        exitBtn.setActiveColor(Color(198, 40, 40));
        exitBtn.setText("Go Back");
        exitBtn.setCharacterSize(18);

        lvlBtn1.setSize(Vector2f(120, 50));
        lvlBtn1.setText("Level 1");
        lvlBtn1.setLevel(1);
        lvlBtn1.setCharacterSize(24);

        lvlBtn2.setSize(Vector2f(120, 50));
        lvlBtn2.setText("Level 2");
        lvlBtn2.setLevel(2);
        lvlBtn2.setCharacterSize(24);

        lvlBtn3.setSize(Vector2f(120, 50));
        lvlBtn3.setText("Level 3");
        lvlBtn3.setLevel(3);
        lvlBtn3.setCharacterSize(24);

        lvlBtn4.setSize(Vector2f(120, 50));
        lvlBtn4.setText("Level 4");
        lvlBtn4.setLevel(4);
        lvlBtn4.setCharacterSize(24);

    }

    ~LvlChooseScreen()
    {

    }

public:
    void draw(RenderWindow &window)
    {
        float windowWidthHalf = (float) window.getSize().x / 2;
        lvlBtn1.setBtnPosition((float) windowWidthHalf - 300, (float) 250);
        lvlBtn2.setBtnPosition((float) windowWidthHalf - 100, (float) 250);
        lvlBtn3.setBtnPosition((float) windowWidthHalf + 100, (float) 250);
        lvlBtn4.setBtnPosition((float) windowWidthHalf + 300, (float) 250);

        lvlChooseScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
        window.draw(lvlChooseScreenBackground);

        if (exitBtn.isClicked(window))
        {
            mApp->setCurrentScreen(menu);
        }
        window.draw(exitBtn);
        exitBtn.drawText(window);

        lvlBtn1 = getLevelBtnColor(lvlBtn1);
        if (lvlBtn1.isClicked(window) && lvlBtn1.getBtnLevel() <= mApp->getLevelsUnlocked())
        {
            mApp->resetLives();
            mApp->setLvl(1);
            mApp->setCurrentScreen(game);
        }
        window.draw(lvlBtn1);
        lvlBtn1.drawText(window);

        lvlBtn2 = getLevelBtnColor(lvlBtn2);
        if (lvlBtn2.isClicked(window) && lvlBtn2.getBtnLevel() <= mApp->getLevelsUnlocked())
        {
            mApp->resetLives();
            mApp->setLvl(2);
            mApp->setCurrentScreen(game);
        }
        window.draw(lvlBtn2);
        lvlBtn2.drawText(window);

        lvlBtn3 = getLevelBtnColor(lvlBtn3);
        if (lvlBtn3.isClicked(window) && lvlBtn3.getBtnLevel() <= mApp->getLevelsUnlocked())
        {
            mApp->resetLives();
            mApp->setLvl(3);
            mApp->setCurrentScreen(game);
        }
        window.draw(lvlBtn3);
        lvlBtn3.drawText(window);

        lvlBtn4 = getLevelBtnColor(lvlBtn4);
        if (lvlBtn4.isClicked(window) && lvlBtn4.getBtnLevel() <= mApp->getLevelsUnlocked())
        {
            mApp->resetLives();
            mApp->setLvl(4);
            mApp->setCurrentScreen(game);
        }
        window.draw(lvlBtn4);
        lvlBtn4.drawText(window);

    }

    LevelButton getLevelBtnColor(LevelButton lvlBtn)
    {
        if (lvlBtn.getBtnLevel() <= mApp->getLevelsUnlocked())
        {
            lvlBtn.setColor(Color(5, 240, 83));
            lvlBtn.setHoverColor(Color(4, 194, 67));
            lvlBtn.setActiveColor(Color(4, 194, 67));
        } else
        {
            lvlBtn.setColor(Color(244, 67, 54));
            lvlBtn.setHoverColor(Color(211, 47, 47));
            lvlBtn.setActiveColor(Color(198, 40, 40));
        }

        return lvlBtn;
    }

    void setApp(App *app)
    {
        mApp = app;
        exitBtn.setApp(mApp);
        lvlBtn1.setApp(mApp);
        lvlBtn2.setApp(mApp);
        lvlBtn3.setApp(mApp);
        lvlBtn4.setApp(mApp);
    }

private:
    MaterialButton exitBtn;
    LevelButton lvlBtn1;
    LevelButton lvlBtn2;
    LevelButton lvlBtn3;
    LevelButton lvlBtn4;

};
