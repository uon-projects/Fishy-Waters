//The Main Character Class Implementation...

//Header Files
#include "../../header/player/EnemyCharacter.h"

EnemyCharacter::EnemyCharacter()
{
//Local Variables

//Main "EnemyCharacter()"

}

EnemyCharacter::~EnemyCharacter()
{
//Local Variables

//Main "~EnemyCharacter()"

}

void EnemyCharacter::Init(std::string TextureName, sf::Vector2f Position, float MovingSpeed)
{
//Local Variables

//Main "Init()"
    EnemyCharacterMovingSpeed = MovingSpeed;
    EnemyCharacterPosition = Position;

    EnemyCharacterTexture.loadFromFile(TextureName.c_str()); //We Load The Texture.

    EnemyCharacterSprite.setTexture(
            EnemyCharacterTexture); //We Create The Enemy Character Sprite & We Attach A Texture To It.
    EnemyCharacterSprite.setPosition(EnemyCharacterPosition);
    EnemyCharacterSprite.setOrigin(EnemyCharacterTexture.getSize().x / 2, EnemyCharacterTexture.getSize().y / 2);
}

void EnemyCharacter::Update(float Speed)
{
//Local Variables

//Main "Update()"
    EnemyCharacterSprite.move(EnemyCharacterMovingSpeed * Speed / 3, 0);
}

sf::Sprite EnemyCharacter::GetSprite()
{
//Local Variables

//Main "GetSprite()"

    return EnemyCharacterSprite;
}