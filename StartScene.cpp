#include "StartScene.h"
#include "GameData.h"
#include "StaticData.h"
#include "TouchLayer.h"
#include "FishLayer.h"
#include "CannonLayer.h"
#include "UILayer.h"
#include "BackGroundLayer.h"
#include "Fishes.h"
#include "Cannon.h"
#include "GameData.h"
bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/*
	 * 2017/09/12
	 * @brief 后期从其他地方拼凑来的游戏资源，所以可能会有些地方不同步
	 */
	this->preloadSources();

	//背景层的添加
	auto bg = BackGroundLayer::create();
	this->addChild(bg);

	//游戏标题
	auto title = Sprite::create(STATIC_DATA_STRING("title"));
	title->setPosition(Vec2(winSize.width/2,winSize.height/2+200));
	title->setScale(1.5);
	this->addChild(title);

	return true;
}

void StartScene::preloadSources()
{
	StaticData::getInstance();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("data.plist");

	/*
	* 2017/08/17
	* @brief 加载鱼类的动画
	*/
	auto animationcache = AnimationCache::getInstance();
	int framecount = STATIC_DATA_INT("fishframecount");
	for (int type = k_Fish_One; type<k_Fish_Count; type++)
	{
		Vector<SpriteFrame*> frames(framecount);
		for (int i = 1; i <= framecount; i++)
		{
			String key = STATIC_DATA_STRING("fish_frame_name_count");
			String* filename = String::createWithFormat(STATIC_DATA_STRING("fish_frame_name_count"), type + 1, i);
			String realfilename = STATIC_DATA_STRING(filename->getCString());
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(filename->getCString()));
			frames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(frames);
		animation->setDelayPerUnit(0.1f);
		String* animationName = String::createWithFormat(STATIC_DATA_STRING("fishanimationformat"), type);

		animationcache->addAnimation(animation, animationName->getCString());
	}

	/*
	* 2017/08/19
	* @brief 加载炮台发射炮弹时放大动画
	*/

	for (int fishtype = k_Cannon_Type_1; fishtype<k_Cannon_Type_Count; fishtype++)
	{
		Vector<SpriteFrame*> newframes(2);
		for (int j = 1; j <= 2; j++)
		{
			String* frameName = String::createWithFormat("Cannon%d_%d", fishtype + 1, j);
			SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(frameName->getCString()));
			newframes.pushBack(sprite);
		}
		auto animation = Animation::createWithSpriteFrames(newframes);
		animation->setDelayPerUnit(0.2f);
		String* animationName = String::createWithFormat("cannonanimation%d", fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}

	/*
	* 2017/08/19
	* @brief 加载渔网的动画
	*/
	Vector<SpriteFrame*> frames(11);
	for (int j = 1; j <= 11; j++)
	{
		String* frameName = String::createWithFormat("net%d", j);
		SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(frameName->getCString()));
		frames.pushBack(sprite);
	}
	auto animation = Animation::createWithSpriteFrames(frames);
	animation->setDelayPerUnit(0.04f);
	AnimationCache::getInstance()->addAnimation(animation, "net");


	/*
	* 2017/08/22
	* @brief 鱼被捕捉成功的动画,一共两种，第一种有2帧，第二种有4帧
	*/

	int fishcaughttype = STATIC_DATA_INT("fishcaughtcountone");
	// CCLOG("mainscene fishcaughttypeone:%d ", fishcaughttype);
	framecount = STATIC_DATA_INT("fishcaughtcountoneframes");
	int fishtype = 1;
	for (; fishtype <= fishcaughttype; fishtype++)
	{
		Vector<SpriteFrame*> vec(framecount);
		for (int j = 1; j <= framecount; j++)
		{

			String* framename = String::createWithFormat("fish%d_catch_%d", fishtype, j);
			CCLOG("framename :%s", framename->getCString());
			SpriteFrame* spr = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(framename->getCString()));
			vec.pushBack(spr);
		}
		auto animation = Animation::createWithSpriteFrames(vec);
		animation->setDelayPerUnit(0.2f);
		auto animationName = String::createWithFormat("fishcaught%d", fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}
	fishcaughttype = STATIC_DATA_INT("fishcaughtcounttwo");

	framecount = STATIC_DATA_INT("fishcaughtcounttwoframes");
	for (; fishtype <= fishcaughttype; fishtype++)
	{
		Vector<SpriteFrame*> vec(framecount);
		for (int j = 1; j <= framecount; j++)
		{
			String* framename = String::createWithFormat("fish%d_catch_%d", fishtype, j);
			SpriteFrame* spr = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(framename->getCString()));
			vec.pushBack(spr);
		}
		auto animation = Animation::createWithSpriteFrames(vec);
		animation->setDelayPerUnit(0.2f);
		auto animationName = String::createWithFormat("fishcaught%d", fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}

}

