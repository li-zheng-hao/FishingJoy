#include "Weapon.h"
#include "GameData.h"
bool Weapon::init(CannonType type)
{
	
	/*
	 * 2017/08/20
	 * @brief 创建渔网
	 */
	 _fishNet= Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("net11")));
	 _fishNet->setVisible(false);
	this->setContentSize(_fishNet->getContentSize());//将渔网的大小设置为最后一张图片的大小，也就是最大的那张图
	this->addChild(_fishNet);
	/*
	 * 2017/08/20
	 * @brief 创建子弹
	 */
	auto bulletName = String::createWithFormat("Shell%d", type + 1);
	_bullet = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(bulletName->getCString())));
	_bullet->setVisible(false);
	this->addChild(_bullet);

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


void Weapon::shootTo(const Vec2 & pos)
{
	CCLOG("Weap::ShootTo-----%f-%f", pos.x, pos.y);
	_collisionPos = pos;
	_bullet->setVisible(true);
	float angle = ccpAngleSigned(ccpSub(this->getPosition(), pos), CCPointMake(0, 1));
	_bullet->setRotation(CC_RADIANS_TO_DEGREES(angle));
	float speed = ccpDistance(this->getPosition(), pos) / 500.0f;
	auto flyTo = MoveTo::create(speed, pos);
	auto callfunc = CallFunc::create(this, CC_CALLFUNC_SELECTOR(Weapon::shootEnd));
	auto seq = Sequence::create(flyTo, callfunc, NULL);
	this->runAction(seq);

	
}

void Weapon::shootEnd()
{
	_bullet->removeFromParent();
	_fishNet->setVisible(true);
	//_fishNet->setPosition(_collisionPos);
	auto animation = AnimationCache::getInstance()->getAnimation("net");
	auto aniamte = Animate::create(animation);
	auto callfunc = CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(Weapon::removeFishNet));
	auto seq = Sequence::create(aniamte, callfunc, NULL);
	_fishNet->runAction(seq);
}

void Weapon::removeFishNet()
{
	if (_fishNet->getParent())
	{
		_fishNet->removeFromParent();
	}
}
