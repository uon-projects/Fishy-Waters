#include "../header/MaterialButton.h"
#include "../header/FontManager.h"

MaterialButton::~MaterialButton()
{

}

MaterialButton::MaterialButton(const Vector2f &size)
{
    mySize = size;
    color = Color::Black;
    hoverColor = Color::Black;
    activeColor = Color::Black;

    font = LoadFont::loadFont();
    text.setFont(font);
    text.setFillColor(Color(0, 0, 0, 100));
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setFillColor(sf::Color::Black);

    update();
}

void MaterialButton::setSize(const Vector2f &size)
{
    mySize = size;
    setOrigin(mySize.x / 2, mySize.y / 2);
    update();
}

size_t MaterialButton::getPointCount() const
{
    return 4;
}

Vector2f MaterialButton::getPoint(size_t index) const
{
    switch (index)
    {
        default:
        case 0:
            return Vector2f(0, 0);
        case 1:
            return Vector2f(mySize.x, 0);
        case 2:
            return Vector2f(mySize.x, mySize.y);
        case 3:
            return Vector2f(0, mySize.y);
    }
}

void MaterialButton::setColor(Color newColor)
{
    color = newColor;
}

void MaterialButton::setHoverColor(Color newHoverColor)
{
    hoverColor = newHoverColor;
}

void MaterialButton::setActiveColor(Color newActiveColor)
{
    activeColor = newActiveColor;
}

bool MaterialButton::isClicked(RenderWindow &window)
{
    btnBounders = IntRect(getPosition().x - getGlobalBounds().width / 2,
                          getPosition().y - getGlobalBounds().height / 2,
                          getGlobalBounds().width,
                          getGlobalBounds().height);
    if (btnBounders.contains(Mouse::getPosition(window)))
    {
        this->text.setCharacterSize(characterSize - 2);
        this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);

        Event event = this->mApp->getEvent(); // NOLINT(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        bool clicked = (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left);
        if (clicked)
        {
            setFillColor(activeColor);
        } else
        {
            setFillColor(hoverColor);
        }
        return clicked;
    } else
    {
        this->text.setCharacterSize(characterSize);
        this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);
        setFillColor(color);
        return false;
    }

}

void MaterialButton::setText(std::string text)
{
    this->content = text;
    this->text.setString(content);
    this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);
}

void MaterialButton::setCharacterSize(int size)
{
    this->characterSize = size;
    this->text.setCharacterSize(characterSize);
    this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 1.3f);
}

void MaterialButton::setBtnPosition(float x, float y)
{
    this->setPosition(x, y);
    this->text.setPosition(x, y);
}

void MaterialButton::drawText(RenderWindow &window)
{
    window.draw(text);
}

void MaterialButton::setApp(App *app)
{
    this->mApp = app;
}
