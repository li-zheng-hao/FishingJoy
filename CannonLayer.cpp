#include "CannonLayer.h"
#include "GameData.h"

bool CannonLayer::init()
{
	if (Layer::init())
	{
		_cannon = Cannon::create(k_Cannon_Type_1);
		_cannon->setPosition(Vec2(winSize.width/2+20,40));
		this->addChild(_cannon,2);

		 _add_button=MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("button_add"))), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("button_add"))),
			this,
			menu_selector(CannonLayer::switchCannon));
		 _reduce_button= MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("button_reduce"))), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("button_reduce"))),
			this,
			menu_selector(CannonLayer::switchCannon));
		
		auto menu = Menu::create(_reduce_button,_add_button, NULL);
		menu->alignItemsHorizontallyWithPadding(_cannon->getContentSize().width + 100);
		menu->setPosition(winSize.width / 2+20, _reduce_button->getContentSize().height);
		this->addChild(menu,2);
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

	_cannon->runShootAction();
	


	_weapon = Weapon::create(_cannon->getCannonType());
	_weapon->setPosition(_cannon->getPosition());
	_weapon->setPositionY(_weapon->getPositionY());
	this->addChild(_weapon,1);

	_weapon->shootTo(pos);
}

Rect CannonLayer::getFishNetCollisionArea()
{
	return this->_weapon->getFishNetCollisionArea();
}

void CannonLayer::switchCannon(Ref * callfunc)
{
	CannonType type = _cannon->getCannonType();
	if (callfunc==_reduce_button)
	{
		type = (CannonType)(type - 1);
	}
	else if(callfunc==_add_button)
	{
		type = (CannonType)(type + 1);
	}
	_cannon->setCannon(type);
}

bool CannonLayer::isShoot()
{
	if (_weapon)
	{
		return true;
	}
	return false;
}
