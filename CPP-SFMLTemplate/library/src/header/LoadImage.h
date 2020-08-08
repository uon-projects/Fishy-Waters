#include <SFML/Graphics.hpp>
#include <list>
#include <string>

using namespace sf;

enum image_ext
{
    png,
    jpg,
    jpeg
};

class LoadImage
{

    std::list <sf::Texture> zfTextures;

public:
    Sprite loadSpriteFromTexture(std::string assetName, image_ext extension)
    {
        std::string image_extension;
        if (extension == png)
        {
            image_extension = ".png";
        } else if (extension == jpg)
        {
            image_extension = ".jpg";
        } else if (extension == jpeg)
        {
            image_extension = ".jpeg";
        } else
        {
            image_extension = ".png";
        }
        sf::Texture zfTexture;
        if (!zfTexture.loadFromFile("game/src/res/drawable/" + assetName + image_extension))
        {
            system("pause");
        }
        zfTexture.setSmooth(true);
        zfTextures.push_front(zfTexture);
        sf::Sprite zfSprite(zfTextures.front());
        return zfSprite;
    }

};
