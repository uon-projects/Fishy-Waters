#include "../../header/screen/HowToPlayScreen.h"

HowToPlayScreen::HowToPlayScreen()
{

    lvlChooseScreenBackground.setFillColor(Color(0, 150, 136));

    exitBtn.setSize(Vector2f(90, 30));
    exitBtn.setColor(Color(244, 67, 54));
    exitBtn.setHoverColor(Color(211, 47, 47));
    exitBtn.setActiveColor(Color(198, 40, 40));
    exitBtn.setText("Go Back");
    exitBtn.setCharacterSize(18);

}

HowToPlayScreen::~HowToPlayScreen()
{

}


void HowToPlayScreen::draw(RenderWindow &window)
{

    lvlChooseScreenBackground.setSize(Vector2f(window.getSize().x, window.getSize().y));
    window.draw(lvlChooseScreenBackground);

    exitBtn.setBtnPosition((float) 90, (float) 50);
    if (exitBtn.isClicked(window))
    {
        this->mApp->setCurrentScreen(menu);
    }
    window.draw(exitBtn);
    exitBtn.drawText(window);

}

void HowToPlayScreen::setApp(App *app)
{
    this->mApp = app;
    exitBtn.setApp(this->mApp);
}