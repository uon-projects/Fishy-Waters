#include <SFML/Graphics.hpp>
#include "../../header/screen/SplashScreen.h"
#include "../../../../library/src/header/FontManager.h"

using namespace sf;

void SplashScreen::SplashScreen()
{

    splashScreenBg.setFillColor(Color(21, 21, 21));
    mSplashLogo = mLoader.loadSpriteFromTexture("zeoflow_logo", png);

    font = LoadFont::loadFont();
    text.setFont(font);
    text.setFillColor(Color(88, 52, 235));
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setString("Dai Makai Mura");
    text.setCharacterSize(40);

}

void SplashScreen::~SplashScreen()
{

}

void SplashScreen::draw(RenderWindow &window)
{

    splashScreenBg.setSize(Vector2f(window.getSize().x, window.getSize().y));
    window.draw(splashScreenBg);

    mSplashLogo.setScale(0.12, 0.12);
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
