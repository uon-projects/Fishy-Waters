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

        lvlBtn1.setSize(Vector2f(200, 50));
        lvlBtn1.setText("Start New Game");
        lvlBtn1.setCharacterSize(24);

    }

    ~LvlChooseScreen()
    {

    }

public:
    void draw(RenderWindow &window)
    {
        float windowWidthHalf = (float) window.getSize().x / 2;
        lvlBtn1.setBtnPosition((float) windowWidthHalf, (float) 250);

        lvlChooseScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
        window.draw(lvlChooseScreenBackground);

        if (exitBtn.isClicked(window))
        {
            mApp->setCurrentScreen(menu);
        }
        window.draw(exitBtn);
        exitBtn.drawText(window);

        lvlBtn1 = getLevelBtnColor(lvlBtn1);
        if (lvlBtn1.isClicked(window))
        {
            mApp->setCurrentScreen(game);
        }
        window.draw(lvlBtn1);
        lvlBtn1.drawText(window);

    }

    LevelButton getLevelBtnColor(LevelButton lvlBtn)
    {
        lvlBtn.setColor(Color(5, 240, 83));
        lvlBtn.setHoverColor(Color(4, 194, 67));
        lvlBtn.setActiveColor(Color(4, 194, 67));
        return lvlBtn;
    }

    void setApp(App *app)
    {
        mApp = app;
        exitBtn.setApp(mApp);
        lvlBtn1.setApp(mApp);
    }

private:
    MaterialButton exitBtn;
    LevelButton lvlBtn1;

};
