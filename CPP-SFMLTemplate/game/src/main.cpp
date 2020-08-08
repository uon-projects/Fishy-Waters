#include <SFML/Graphics.hpp>
#include "header/screen/SplashScreen.h"
#include "header/screen/GameMenuScreen.h"
#include "header/screen/LvlChooseScreen.h"

using namespace std;
using namespace sf;

#define WindowX 800
#define WindowY 500

App *mApp;
SplashScreen mSplashScreen;
GameMenuScreen mGameMenu;
LvlChooseScreen mLvlChooseScreen;
Vector2i theGameWindow_currentDimensions(WindowX, WindowY);
Vector2i theGameWindow_perspectiveDimensions(WindowX, WindowY);
RenderWindow theGameWindow(
        VideoMode(theGameWindow_currentDimensions.x, theGameWindow_currentDimensions.y),
        "Dai Makai-Mura");
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

    theGameWindow.setFramerateLimit(60);

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
        }
    }

}

void update(float seconds)
{

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
    } else if (currentScreen == game)
    {

    }

}