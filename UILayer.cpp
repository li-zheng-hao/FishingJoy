#include "UILayer.h"
#include "GameData.h"
bool UILayer::init()
{
	if (Layer::init())
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("data.plist");

		GameData::getInstance();
		_menu1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("uibox1")));
		_menu1->setPosition(Vec2(winSize.width/2,winSize.height-_menu1->getContentSize().height/2));
		this->addChild(_menu1);
		_menu2= Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("uibox2")));
		_menu2->setAnchorPoint(Vec2(0,0));
		_menu2->setPosition(Vec2(0,0));
		this->addChild(_menu2);
		
		return true;
	}
	return false;
}
