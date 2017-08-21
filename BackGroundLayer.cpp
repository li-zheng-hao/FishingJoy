#include "BackGroundLayer.h"



bool BackGroundLayer::init()
{
	if (!Layer::init())
		return false;
	_background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("background")));
	_background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(_background);
	return true;
}
