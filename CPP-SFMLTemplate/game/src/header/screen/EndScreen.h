#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/MaterialButton.h"
#include "../App.h"

using namespace sf;

class EndScreen
{

public:
    RectangleShape gameMenuScreenBackground;
    App *mApp;

public:
    EndScreen()
    {

        gameMenuScreenBackground.setFillColor(Color(0, 150, 136));

        mBackToMenu.setSize(Vector2f(170, 40));
        mBackToMenu.setColor(Color(244, 67, 54));
        mBackToMenu.setHoverColor(Color(211, 47, 47));
        mBackToMenu.setActiveColor(Color(198, 40, 40));
        mBackToMenu.setText("Return to Menu");
        mBackToMenu.setCharacterSize(20);

        mNavigateToLvlSelector.setSize(Vector2f(160, 40));
        mNavigateToLvlSelector.setColor(Color(156, 39, 176));
        mNavigateToLvlSelector.setHoverColor(Color(123, 31, 162));
        mNavigateToLvlSelector.setActiveColor(Color(106, 27, 154));
        mNavigateToLvlSelector.setText("Level Selector");
        mNavigateToLvlSelector.setCharacterSize(20);

        mNextLvl.setSize(Vector2f(130, 40));
        mNextLvl.setColor(Color(156, 39, 176));
        mNextLvl.setHoverColor(Color(123, 31, 162));
        mNextLvl.setActiveColor(Color(106, 27, 154));
        mNextLvl.setText("Next Level");
        mNextLvl.setCharacterSize(20);

    }

    ~EndScreen()
    {

    }

public:
    void draw(RenderWindow &window)
    {

        bool showNextLvl = true;

        gameMenuScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));

        mNavigateToLvlSelector.setBtnPosition((float) window.getSize().x / 2, (float) 100);
        if (showNextLvl)
        {
            mNextLvl.setBtnPosition((float) window.getSize().x / 2, (float) 150);
            mBackToMenu.setBtnPosition((float) window.getSize().x / 2, (float) 200);
        } else
        {
            mBackToMenu.setBtnPosition((float) window.getSize().x / 2, (float) 150);
        }

        if (mNavigateToLvlSelector.isClicked(window))
        {
            this->mApp->setCurrentScreen(choose_lvl);
        }
        if (mBackToMenu.isClicked(window))
        {
            mApp->setCurrentScreen(menu);
        }

        window.draw(gameMenuScreenBackground);

        window.draw(mBackToMenu);
        mBackToMenu.drawText(window);
        window.draw(mNavigateToLvlSelector);
        mNavigateToLvlSelector.drawText(window);

        if (showNextLvl)
        {
            if (mNextLvl.isClicked(window))
            {
                this->mApp->setCurrentScreen(game);
            }
            window.draw(mNextLvl);
            mNextLvl.drawText(window);
        }

    }

    void setApp(App *app)
    {
        this->mApp = app;
        mBackToMenu.setApp(this->mApp);
        mNavigateToLvlSelector.setApp(this->mApp);
        mNextLvl.setApp(this->mApp);
    }

private:
    MaterialButton mBackToMenu;
    MaterialButton mNavigateToLvlSelector;
    MaterialButton mNextLvl;
    Font font;

};
