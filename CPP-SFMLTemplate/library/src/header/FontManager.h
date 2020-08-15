#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class FontManager
{

public:
    FontManager()
    {

    }

    ~FontManager()
    {

    }

public:
    Font loadFont()
    {
        Font font;
        if (!font.loadFromFile("game/src/res/font/font1.otf"))
        {
            system("pause");
        }
        return font;

    }

};
