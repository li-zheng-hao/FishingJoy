#include "MainScene.h"
enum
{
	k_MainScene_TouchLayer,
	k_MainScene_CannonLayer,
	k_MainScene_FishLayer,
	k_MainScene_UILayer,
	k_MainScene_BackgroundLayer,
	k_MainScene_LayerCount
};
bool MainScene::init()
{
	if (Scene::init())
	{
		/*
		 * 2017/08/17
		 * @brief 游戏数据初始化
		 */
		preloadSources();
		

		/*
		 * 2017/08/17
		 * @brief 所有层的加载
		 */
		_touchLayer = TouchLayer::create();
		this->addChild(_touchLayer, 5,k_MainScene_TouchLayer);

		_cannonLayer = CannonLayer::create();
		this->addChild(_cannonLayer,4,k_MainScene_CannonLayer);

		_fishLayer = FishLayer::create();
		this->addChild(_fishLayer, 2,k_MainScene_FishLayer);
		
		_uiLayer = UILayer::create();
		this->addChild(_uiLayer,3,k_MainScene_UILayer);

		_backGroundLayer = BackGroundLayer::create();
		this->addChild(_backGroundLayer, 1,k_MainScene_BackgroundLayer);


		this->schedule(schedule_selector(MainScene::checkAreaBetweenFishAndFishNet));
		return true;
	}
	return false;
	
}

void MainScene::preloadSources()
{
	StaticData::getInstance();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("data.plist");

	/*
	 * 2017/08/17
	 * @brief 加载鱼类的动画
	 */
	auto animationcache = AnimationCache::getInstance();
	int framecount = STATIC_DATA_INT("fishframecount");
	for (int type=k_Fish_One;type<k_Fish_Count;type++ )
	{
		Vector<SpriteFrame*> frames(framecount);
		for (int i=1;i<=framecount;i++)
		{
			String key = STATIC_DATA_STRING("fish_frame_name_count");
			String* filename = String::createWithFormat(STATIC_DATA_STRING("fish_frame_name_count"), type+1, i);
			String realfilename = STATIC_DATA_STRING(filename->getCString());
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(filename->getCString()));
			frames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(frames);
		animation->setDelayPerUnit(0.1f);
		String* animationName = String::createWithFormat(STATIC_DATA_STRING("fishanimationformat"),type);

		animationcache->addAnimation(animation, animationName->getCString());
	}

	/*
	 * 2017/08/19
	 * @brief 加载炮台发射炮弹时放大动画
	 */
	
	for (int fishtype=k_Cannon_Type_1;fishtype<k_Cannon_Type_Count;fishtype++)
	{
		Vector<SpriteFrame*> newframes(2);
		for (int j=1;j<=2;j++)
		{
			String* frameName = String::createWithFormat("Cannon%d_%d", fishtype + 1, j);
			SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(frameName->getCString()));
			newframes.pushBack(sprite);
		}
		auto animation = Animation::createWithSpriteFrames(newframes);
		animation->setDelayPerUnit(0.2f);
		String* animationName = String::createWithFormat("cannonanimation%d",fishtype);
		AnimationCache::getInstance()->addAnimation(animation, animationName->getCString());
	}

	/*
	 * 2017/08/19
	 * @brief 加载渔网的动画
	 */
	Vector<SpriteFrame*> frames(11);
	for (int j = 1; j <= 11; j++)
	{
		String* frameName = String::createWithFormat("net%d",j);
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
	 for (;fishtype<=fishcaughttype;fishtype++)
	 {
		 Vector<SpriteFrame*> vec(framecount);
		 for (int j=1;j<=framecount;j++)
		 {

			 String* framename = String::createWithFormat("fish%d_catch_%d",fishtype,j);
			 CCLOG("framename :%s", framename->getCString());
			 SpriteFrame* spr = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(framename->getCString()));
			 vec.pushBack(spr);
		 }
		 auto animation = Animation::createWithSpriteFrames(vec);
		 animation->setDelayPerUnit(0.2f);
		 auto animationName = String::createWithFormat("fishcaught%d", fishtype);
		 AnimationCache::getInstance()->addAnimation(animation,animationName->getCString());
	 }
	 fishcaughttype = STATIC_DATA_INT("fishcaughtcounttwo");

	 framecount = STATIC_DATA_INT("fishcaughtcounttwoframes");
	 for (;fishtype<=fishcaughttype;fishtype++)
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

void MainScene::cannonAimAt(const Vec2 & pos)
{
	_cannonLayer->cannonAimAt(pos);
}

void MainScene::cannonShootTo(const Vec2 & pos)
{
	_cannonLayer->cannonShootTo(pos);
}

void MainScene::checkAreaBetweenFishAndFishNet(float dt)
{
	if (_cannonLayer->isShoot())
	{
		Vector<Fishes*> vec = _fishLayer->_fishes;
		Rect fishNetArea = _cannonLayer->getFishNetCollisionArea();
		for(auto iter:vec)
		{
			Fishes* fish=(Fishes*)iter;
			if (fish->isRunning())
			{
				
				auto size = fish->getFishRect();
				if (size.intersectsRect(fishNetArea))
				{
					fish->beCaught();
				}
			}
			
		}
	}

}

