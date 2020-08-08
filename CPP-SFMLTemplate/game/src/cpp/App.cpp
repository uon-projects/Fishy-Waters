#include "../header/App.h"

App::App()
{
    this->currentScreen = splash;
}

App::~App()
{

}

screen App::getCurrentScreen()
{
    return this->currentScreen;
}

void App::setCurrentScreen(screen screenChose)
{
    this->currentScreen = screenChose;
}

Event App::getEvent()
{
    return this->event;
}

void App::setEvent(Event eventN)
{
    this->event = eventN;
}
