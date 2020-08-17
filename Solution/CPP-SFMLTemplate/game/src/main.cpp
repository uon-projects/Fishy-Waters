#include <SFML/Graphics.hpp>
#include "header/Utils.h"
#include "header/screen/SplashScreen.h"
#include "header/screen/GameMenuScreen.h"
#include "header/screen/LvlChooseScreen.h"
#include "header/screen/HowToPlayScreen.h"
#include "header/screen/GameScreen.h"
#include "header/screen/EndScreen.h"

using namespace std;
using namespace sf;

App *mApp;
SplashScreen mSplashScreen;
GameMenuScreen mGameMenu;
LvlChooseScreen mLvlChooseScreen;
HowToPlayScreen mHowToPlayScreen;
GameScreen mGameScreen;
EndScreen mEndScreen;
Vector2i theGameWindow_currentDimensions(WindowX, WindowY);
Vector2i theGameWindow_perspectiveDimensions(WindowX, WindowY);
RenderWindow theGameWindow(
        VideoMode(theGameWindow_currentDimensions.x, theGameWindow_currentDimensions.y),
        "Fishy Waters");
Clock inGameClock;

void init();

void inputListener();

void update(float seconds);

void draw();

int main()
{

    Clock clockTime;
    Time speed;

    init();

    while (theGameWindow.isOpen())
    {

        inputListener();

        speed = clockTime.restart();
        update(speed.asSeconds());

        theGameWindow.clear();

        draw();

        theGameWindow.display();
    }

    return 0;
}

void init()
{

    inGameClock.restart();

    mApp = new App;
    mGameMenu.setApp(mApp);
    mLvlChooseScreen.setApp(mApp);
    mHowToPlayScreen.setApp(mApp);
    mGameScreen.setApp(mApp);
    mEndScreen.setApp(mApp);

    theGameWindow.setFramerateLimit(60);
    srand((int) time(0));

}

void inputListener()
{

    Event event;

    while (theGameWindow.pollEvent(event))
    {
        mApp->setEvent(event);
        if (event.key.code == Keyboard::Escape || event.type == Event::Closed)
        {
            theGameWindow.close();
        } else if (event.type == sf::Event::KeyPressed && mApp->getCurrentScreen() == game)
        {
            mGameScreen.inputListener(event);
        }
    }

}

void update(float seconds)
{

    if (mApp->getCurrentScreen() == game)
    {
        if (mApp->isNewGame())
        {
            mGameScreen.initNewLvl();
        }
        mGameScreen.update();
    }

}

void draw()
{

    screen currentScreen = mApp->getCurrentScreen();
    if (currentScreen == splash)
    {
        float sec = inGameClock.getElapsedTime().asSeconds();
        mSplashScreen.draw(theGameWindow);
        if (sec >= 2.0)
        {
            inGameClock.restart();
            mApp->setCurrentScreen(menu);
        }
    } else if (currentScreen == menu)
    {
        mGameMenu.draw(theGameWindow);
    } else if (currentScreen == choose_lvl)
    {
        mLvlChooseScreen.draw(theGameWindow);
    } else if (currentScreen == how_to_play)
    {
        mHowToPlayScreen.draw(theGameWindow);
    } else if (currentScreen == game)
    {
        mGameScreen.draw(theGameWindow);
    } else if (currentScreen == end_screen)
    {
        mEndScreen.draw(theGameWindow);
    }

}