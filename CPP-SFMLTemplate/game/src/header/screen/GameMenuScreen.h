#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/MaterialButton.h"
#include "../App.h"

using namespace sf;

class GameMenuScreen
{

public:
    RectangleShape gameMenuScreenBackground;
    App *mApp;

public:
    GameMenuScreen()
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

        howToPlayBtn.setSize(Vector2f(170, 40));
        howToPlayBtn.setColor(Color(156, 39, 176));
        howToPlayBtn.setHoverColor(Color(123, 31, 162));
        howToPlayBtn.setActiveColor(Color(106, 27, 154));
        howToPlayBtn.setText("How To Play");
        howToPlayBtn.setCharacterSize(24);

    }

    ~GameMenuScreen()
    {

    }

public:
    void draw(RenderWindow &window)
    {

        gameMenuScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
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

        howToPlayBtn.setBtnPosition((float) window.getSize().x / 2, (float) 150);
        if (howToPlayBtn.isClicked(window))
        {
            this->mApp->setCurrentScreen(how_to_play);
        }
        window.draw(howToPlayBtn);
        howToPlayBtn.drawText(window);

    }

    void setApp(App *app)
    {
        this->mApp = app;
        exitBtn.setApp(this->mApp);
        playBtn.setApp(this->mApp);
        howToPlayBtn.setApp(this->mApp);
    }

private:
    MaterialButton exitBtn;
    MaterialButton playBtn;
    MaterialButton howToPlayBtn;
    Font font;

};
