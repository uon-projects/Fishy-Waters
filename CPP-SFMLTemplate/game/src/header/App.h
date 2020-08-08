#pragma once

#include "Utils.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class App
{

public:
    App()
    {
        this->currentScreen = splash;
    }

    ~App()
    {

    }

public:
    screen getCurrentScreen()
    {
        return this->currentScreen;
    }

    void setCurrentScreen(screen screenChose)
    {
        this->currentScreen = screenChose;
    }

    Event getEvent()
    {
        return this->event;
    }

    void setEvent(Event eventN)
    {
        this->event = eventN;
    }

private:
    screen currentScreen;
    Event event;

};