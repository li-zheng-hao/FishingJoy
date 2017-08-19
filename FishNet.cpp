#include "FishNet.h"
#include "GameData.h"
bool FishNet::init()
{
	auto animation = AnimationCache::getInstance()->getAnimation("net");
	auto aniamte = Animate::create(animation);
	this->runAction(aniamte);
	auto sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING("net11")));
	this->setContentSize(sprite->getContentSize());//将渔网的大小设置为最后一张图片的大小，也就是最大的那张图
	return true;
}
