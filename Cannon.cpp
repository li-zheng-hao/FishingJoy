#include "Cannon.h"
#include "StaticData.h"

Cannon * Cannon::create(CannonType type)
{
	auto ptr = new Cannon();
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

bool Cannon::init(CannonType type)
{
	Sprite::init();

	_cannonSprites.reserve(k_Cannon_Type_Count);
	for (int i=k_Cannon_Type_1;i<k_Cannon_Type_Count;i++)
	{
		auto findName = String::createWithFormat("Cannon%d_1", i + 1);

		auto filename = String::create(STATIC_DATA_STRING(findName->getCString()));

		auto cannon = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filename->getCString()));

		_cannonSprites.pushBack(cannon);
	}
	_cannonType = type;
	auto sprite=(Sprite*)_cannonSprites.at(_cannonType);
	this->addChild(sprite);

	return true;
}

Sprite * Cannon::getCurrentSprite()
{
	return (Sprite*)_cannonSprites.at(_cannonType);
}

void Cannon::setCannon(CannonType type)
{
	if (_cannonType!=type)
	{
		if (type>k_Cannon_Type_Super)
		{
			type = k_Cannon_Type_1;
		}else if (type<k_Cannon_Type_1)
		{
			type = k_Cannon_Type_Super;
		}
		this->removeAllChildrenWithCleanup(false);
		auto newCannon = (Sprite*)_cannonSprites.at(type);
		this->addChild(newCannon, 0, type);
		_cannonType = type;
	}
}

CannonType Cannon::getCannonType()
{
	return _cannonType;
}

void Cannon::setAngle(const Vec2 & pos)
{
	
	float angle = ccpAngleSigned(ccpSub(pos,this->getPosition()),Vec2(0,1));
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));//弧度转换成度数

}

void Cannon::runShootAction()
{

	auto newCannon = (Sprite*)_cannonSprites.at(_cannonType);
	String* cannonAnimationName = String::createWithFormat("cannonanimation%d", this->getCannonType());
	auto animation = AnimationCache::getInstance()->getAnimation(cannonAnimationName->getCString());
	auto animate = Animate::create(animation);
	newCannon->runAction(animate);
}
