#include "CannonLayer.h"
#include "GameData.h"

bool CannonLayer::init()
{
	if (Layer::init())
	{
		_cannon = Cannon::create(k_Cannon_Type_1);
		_cannon->setPosition(Vec2(winSize.width/2+20,40));
		this->addChild(_cannon);

		_add_button= Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("button_add")));
		_add_button->setPosition(Vec2(_cannon->getPositionX()+60,20));
		this->addChild(_add_button);

		_reduce_button= Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("button_reduce")));
		_reduce_button->setPosition(Vec2(_cannon->getPositionX() - 60, 20));
		this->addChild(_reduce_button);

		
		
		return true;
	}
	return false;
}

void CannonLayer::cannonAimAt(const Vec2 & pos)
{
	_cannon->setAngle(pos);
}

void CannonLayer::cannonShootTo(const Vec2 & pos)
{
	_weapon = Weapon::create(_cannon->getCannonType());
	_weapon->setPosition(_cannon->getPosition());
	_weapon->setPositionY(_weapon->getPositionY() + 40);
	this->addChild(_weapon);

	_weapon->shootTo(pos);
	CCLOG("cannonlayer: cannonshootto:%f,%f", pos.x, pos.y);
}
