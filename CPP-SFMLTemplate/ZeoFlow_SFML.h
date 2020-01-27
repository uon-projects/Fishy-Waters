/*
 * File:   MD2.h
 * Author: Teodor Grigor (original version)
 *
 * Class for loading the assets and format the background
 * For SFML2.

 (c) 2019 - ZeoFlow, Ltd
 
 This software is provided 'as-is', without any express or
 implied warranty. In no event will the authors be held
 liable for any damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute
 it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented;
 you must not claim that you wrote the original software.
 If you use this software in a product, an acknowledgment
 in the product documentation would be appreciated but
 is not required.
 
 2. Altered source versions must be plainly marked as such,
 and must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any
 source distribution.
 
 *
 * Created on 30 January 2009, 11:02
 */

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

using namespace sf;

namespace zeoFlow
{
	class ZeoFlow_SFML
	{
		std::list<sf::Texture> zfTextures;

	public:
		sf::Sprite loadSpriteFromTexture(std::string, std::string, std::string);

	public:
		sf::Font loadFont(std::string, std::string, std::string);

	public:
		bool rectClicked(RectangleShape sprite, Vector2i mouseLocation);

	};

	sf::Sprite ZeoFlow_SFML::loadSpriteFromTexture(std::string assetPath, std::string assetName, std::string assetExtension)
	{
		sf::Texture zfTexture;
		if (!zfTexture.loadFromFile(assetPath + assetName + "." + assetExtension)) {
				system("pause");
		}
		zfTextures.push_front(zfTexture);
		sf::Sprite zfSprite(zfTextures.front());
		return zfSprite;
	}

	sf::Font ZeoFlow_SFML::loadFont(std::string assetPath, std::string assetName, std::string assetExtension)
	{
		sf::Font font;
		if (!font.loadFromFile(assetPath + assetName + "." + assetExtension)) {
				system("pause");
		}
		return font;
	}

	bool ZeoFlow_SFML::rectClicked(RectangleShape sprite, Vector2i mouseLocation)
	{
		IntRect water11Btn(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		if (water11Btn.contains(mouseLocation))
		{
			return true;
		}
		return false;
	}

}