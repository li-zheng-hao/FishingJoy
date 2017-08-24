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
	_shootEnd = false;
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
	_bullet->setVisible(false);
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
	_fishNet->setVisible(false);
	_shootEnd = true;
	//this->removeFromParentAndCleanup(false);
}

cocos2d::Rect Weapon::getFishNetCollisionArea()
{
	if ((int)this->getWeaponStatus()==2)
	{
		/*CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
		CCSize size = _fishNet->getContentSize();
		
		return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);*/
		return this->getBoundingBox();
	}
	else
	{
		return Rect::ZERO;
	}

	
}

Weapon_Type Weapon::getWeaponStatus()
{
	if (_bullet->isVisible()==true)
	{
		return k_Weapon_Bullet;
	}
	else if (_fishNet->isVisible()==true)
	{
		return k_Weapon_Count;
	}
	return k_Weapon_None;
}

