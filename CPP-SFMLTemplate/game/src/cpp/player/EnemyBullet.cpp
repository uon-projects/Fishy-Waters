//The Enemy Bullet Class Implementation...

//Header Files
#include "../../header/player/MainCharacterBullet.h"

EnemyBullet::EnemyBullet()
{
//Local Variables

//Main "EnemyBullet()"

}

EnemyBullet::~EnemyBullet()
{
//Local Variables

//Main "~EnemyBullet()"

}

void EnemyBullet::Init(std::string TextureName, sf::Vector2f Position, float BulletSpeed, int type)
{
//Local Variables

//Main "Init()"
    EnemyBulletSpeed = BulletSpeed;
    BulletPosition = Position;
    classType = type;

    switch (classType)
    {
        case 1:
            EnemyBulletSpeed *= 0.8;
            BulletTexture.loadFromFile(TextureName.c_str());
            BulletSize = BulletTexture.getSize();
            BulletSize.x /= 10;
            BulletSize.y /= 5;
            lifes = 1;
            break;
        case 2:
            EnemyBulletSpeed *= 2;
            BulletTexture.loadFromFile(TextureName.c_str());
            BulletSize = BulletTexture.getSize();
            BulletSize.x /= 11;
            BulletSize.y /= 6;
            lifes = 2;
            break;
        default:
            return;
    }

    BulletPosition.y += 30;
    BulletPosition.x += 5;

    BulletSprite.setSize(sf::Vector2f(60, 110));
    BulletSprite.setTexture(&BulletTexture);
    BulletSprite.setTextureRect(sf::IntRect(BulletSize.x * 0, BulletSize.y * 0, BulletSize.x, BulletSize.y));
    BulletSprite.setPosition(BulletPosition);
    BulletSprite.setScale(sf::Vector2f(0.6, 0.6));
    BulletSprite.setRotation(-90);
    BulletSprite.setOrigin(BulletSize.x / 2, BulletSize.y / 2);
}

void EnemyBullet::Update(float Speed)
{
//Local Variables

//Main "Update()"

    BulletSprite.move(EnemyBulletSpeed * Speed, 0);
}

sf::RectangleShape EnemyBullet::GetSprite()
{
//Local Variables

//Main "GetSprite()"

    return BulletSprite;
}

bool EnemyBullet::decreaseLife()
{
    lifes--;
    return lifes == 0;
}