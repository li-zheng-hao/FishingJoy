#include "Cannon.h"
#include "GameData.h"

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
		if (type>k_Cannon_Type_7)
		{
			type = k_Cannon_Type_1;
		}else if (type<k_Cannon_Type_1)
		{
			type = k_Cannon_Type_Super;
		}
		this->removeChildByTag(_cannonType,false);
		auto newCannon = (Sprite*)_cannonSprites.at(type);
		this->addChild(newCannon, 0, type);
		_cannonType = type;
	}
}

void Cannon::setAngle(const Vec2 & pos)
{
	float angle = ccpAngleSigned(ccpSub(pos,this->getPosition()),Vec2(0,1));
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));//弧度转换成度数

}
