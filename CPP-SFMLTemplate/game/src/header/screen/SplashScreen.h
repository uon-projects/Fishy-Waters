#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/LoadImage.h"
#include "../../../../library/src/header/FontManager.h"

using namespace sf;

class SplashScreen
{

public:
    SplashScreen()
    {

        splashScreenBg.setFillColor(Color(21, 21, 21));
        mSplashLogo = mLoader.loadSpriteFromTexture("zeoflow_logo", png);

        font = FontManager().loadFont();

        text.setFont(font);
        text.setFillColor(Color(88, 52, 235));
        text.setOutlineColor(sf::Color::White);
        text.setOutlineThickness(1);
        text.setString("Dai Makai Mura");
        text.setCharacterSize(40);

    }

    ~SplashScreen()
    {

    }

private:
    RectangleShape splashScreenBg;
    Sprite mSplashLogo;
    LoadImage mLoader;
    Font font;
    Text text;


public:
    void draw(sf::RenderWindow &window)
    {
        splashScreenBg.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
        window.draw(splashScreenBg);

        mSplashLogo.setScale(0.12f, 0.12f);
        float windowHeightHalf = (float) window.getSize().y / 2;
        float windowWidthHalf = (float) window.getSize().x / 2;
        float spriteHeightHalf = mSplashLogo.getGlobalBounds().height / 2;
        float spriteWidthHalf = mSplashLogo.getGlobalBounds().width / 2;
        mSplashLogo.setPosition(windowWidthHalf - spriteWidthHalf, windowHeightHalf - spriteHeightHalf - 30);
        window.draw(mSplashLogo);

        float textHeightHalf = text.getGlobalBounds().height / 2;
        float textWidthHalf = text.getGlobalBounds().width / 2;
        text.setPosition(windowWidthHalf - textWidthHalf, windowHeightHalf - textHeightHalf + 40);
        window.draw(text);

    }

};
