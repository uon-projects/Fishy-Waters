#include <SFML/Graphics.hpp>
#include "../../../../library/src/header/MaterialButton.h"
#include "../../../../library/src/header/FontManager.h"
#include "../App.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class HowToPlayScreen
{

public:
    RectangleShape lvlChooseScreenBackground;
    App *mApp;

public:
    HowToPlayScreen()
    {

        font = FontManager().loadFont();

        lvlChooseScreenBackground.setFillColor(Color(0, 150, 136));

        exitBtn.setSize(Vector2f(90, 30));
        exitBtn.setColor(Color(244, 67, 54));
        exitBtn.setHoverColor(Color(211, 47, 47));
        exitBtn.setActiveColor(Color(198, 40, 40));
        exitBtn.setText("Go Back");
        exitBtn.setCharacterSize(18);

        ifstream howTo(".\\game\\src\\res\\file\\howTo.txt");
        string content((istreambuf_iterator<char>(howTo)), (istreambuf_iterator<char>()));
        contentHowToPlay.setFont(font);
        contentHowToPlay.setString(content);
        contentHowToPlay.setFillColor(Color::White);
        contentHowToPlay.setCharacterSize(16);
        contentHowToPlay.setPosition((float) 50, (float) 80);
    }

    ~HowToPlayScreen()
    {

    }

public:
    void draw(RenderWindow &window)
    {

        lvlChooseScreenBackground.setSize(Vector2f((float) window.getSize().x, (float) window.getSize().y));
        window.draw(lvlChooseScreenBackground);

        exitBtn.setBtnPosition((float) 90, (float) 50);
        if (exitBtn.isClicked(window))
        {
            this->mApp->setCurrentScreen(menu);
        }
        window.draw(exitBtn);
        exitBtn.drawText(window);

        window.draw(contentHowToPlay);

    }

    void setApp(App *app)
    {
        this->mApp = app;
        exitBtn.setApp(this->mApp);
    }

private:
    MaterialButton exitBtn;
    Text contentHowToPlay;
    Font font;

};
