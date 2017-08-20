#include "Weapon.h"
#include "GameData.h"
bool Weapon::init()
{
	auto animation = AnimationCache::getInstance()->getAnimation("net");
	auto aniamte = Animate::create(animation);
	this->runAction(aniamte);
	auto sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("net11")));
	this->setContentSize(sprite->getContentSize());//将渔网的大小设置为最后一张图片的大小，也就是最大的那张图
	return true;
}

Weapon * Weapon::create(CannonType type)
{
	auto ptr = new Weapon();
	if (ptr&&ptr->init(type))
	{
		ptr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ptr);
	}
	return ptr;
}

bool Weapon::init(CannonType type)
{

	return true;
}

void Weapon::shootTo(const Vec2 & pos)
{
}
