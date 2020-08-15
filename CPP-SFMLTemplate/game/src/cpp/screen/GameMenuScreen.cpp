#include "../../header/screen/GameMenuScreen.h"
#include "../../../../library/src/header/FontManager.h"

GameMenuScreen::GameMenuScreen()
{

    gameMenuScreenBackground.setFillColor(Color(0, 150, 136));

    exitBtn.setSize(Vector2f(70, 30));
    exitBtn.setColor(Color(244, 67, 54));
    exitBtn.setHoverColor(Color(211, 47, 47));
    exitBtn.setActiveColor(Color(198, 40, 40));
    exitBtn.setText("Exit");
    exitBtn.setCharacterSize(18);

    playBtn.setSize(Vector2f(90, 40));
    playBtn.setColor(Color(156, 39, 176));
    playBtn.setHoverColor(Color(123, 31, 162));
    playBtn.setActiveColor(Color(106, 27, 154));
    playBtn.setText("Play");
    playBtn.setCharacterSize(24);

}

GameMenuScreen::~GameMenuScreen()
{

}

void GameMenuScreen::draw(RenderWindow &window)
{

    gameMenuScreenBackground.setSize(Vector2f(window.getSize().x, window.getSize().y));
    window.draw(gameMenuScreenBackground);

    exitBtn.setBtnPosition((float) window.getSize().x - 70, (float) 50);
    if (exitBtn.isClicked(window))
    {
        window.close();
    }
    window.draw(exitBtn);
    exitBtn.drawText(window);

    playBtn.setBtnPosition((float) window.getSize().x / 2, (float) 100);
    if (playBtn.isClicked(window))
    {
        this->mApp->setCurrentScreen(choose_lvl);
    }
    window.draw(playBtn);
    playBtn.drawText(window);

}

void GameMenuScreen::setApp(App *app)
{
    this->mApp = app;
    exitBtn.setApp(this->mApp);
    playBtn.setApp(this->mApp);
}
