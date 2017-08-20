#include "TouchLayer.h"
#include "MainScene.h"

bool TouchLayer::init()
{
	auto listener= EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

bool TouchLayer::onTouchBegan(Touch * touch, Event * event)
{
	auto mainscene=(MainScene*)this->getParent();
	mainscene->cannonAimAt(touch->getLocation());
	return true;
}

void TouchLayer::onTouchMoved(Touch * touch, Event * event)
{
	auto mainscene = (MainScene*)this->getParent();
	mainscene->cannonAimAt(touch->getLocation());
}

void TouchLayer::onTouchEnded(Touch * touch, Event * event)
{
	auto mainscene = (MainScene*)this->getParent();
	mainscene->cannonShootTo(touch->getLocation());
	CCLOG("TouchLayer::onTouchEnded-----%f-%f", touch->getLocation().x, touch->getLocation().y);

}
