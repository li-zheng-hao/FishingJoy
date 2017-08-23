#include "Fishes.h"
#include "GameData.h"
typedef enum ActionType
{
	k_Fish_Animate,
	k_Fish_Action
};
Fishes * Fishes::create(FishType type)
{
	auto fish = new Fishes();
	if (fish&&fish->init(type))
	{
		fish->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(fish);
	}
	return fish;
}

bool Fishes::init(FishType type)
{
	_type = type;
	//todo
	auto fishname = String::createWithFormat(STATIC_DATA_STRING("fishanimationformat"), type);
	auto animation = AnimationCache::getInstance()->getAnimation(fishname->getCString());
	auto animate = Animate::create(animation);
	animate->setTag(k_Fish_Animate);
	String* spriteName = String::createWithFormat(STATIC_DATA_STRING("fishtypeformat"), type + 1);
	_sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(spriteName->getCString())));
	String realname = STATIC_DATA_STRING(spriteName->getCString());
	_sprite = Sprite::create(realname.getCString());
	CCLOG("%f,%f", _sprite->getContentSize().width, _sprite->getContentSize().height);
	this->addChild(_sprite);
	_sprite->runAction(RepeatForever::create(animate));
	return true;
}

void Fishes::moveToAction(Vec2 destination)
{
	auto startPoint = this->getPosition();
	float speed = ccpDistance(destination,startPoint) / 200;
	auto movetoAction = MoveTo::create(speed, destination);
	auto moveendAction = CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(Fishes::moveActionEnd));
	auto sequence = Sequence::create(movetoAction, moveendAction, NULL);
	sequence->setTag(k_Fish_Action);
	this->runAction(sequence);
}

void Fishes::moveActionEnd()
{
	this->removeFromParentAndCleanup(false);
}

void Fishes::reset()
{
	
	this->setRotation(0);
	this->setVisible(true);
}

void Fishes::beCaught()
{
	this->stopActionByTag(k_Fish_Action);
	auto animationname = String::createWithFormat("fishcaught%d",(int)_type);//这里出了问题，没有查到帧动画
	auto animation = AnimationCache::getInstance()->getAnimation(animationname->getCString());
	auto animate = Animate::create(animation);
	auto callfun = CallFunc::create(this, callfunc_selector(Fishes::callfunc));
	auto seq = Sequence::create(animate, callfun, NULL);
	this->runAction(seq);
}

void Fishes::callfunc()
{
	this->removeFromParentAndCleanup(false);
}

cocos2d::Rect Fishes::getFishRect()
{
	return _sprite->getBoundingBox();
}
