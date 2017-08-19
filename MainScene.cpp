#include "MainScene.h"


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
		this->addChild(_touchLayer, 5);

		_cannonLayer = CannonLayer::create();
		this->addChild(_cannonLayer,4);

		_fishLayer = FishLayer::create();
		this->addChild(_fishLayer, 2);
		
		_uiLayer = UILayer::create();
		this->addChild(_uiLayer,3);

		_backGroundLayer = BackGroundLayer::create();
		this->addChild(_backGroundLayer, 1);
		return true;
	}
	return false;
	
}

void MainScene::preloadSources()
{
	GameData::getInstance();
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
	for (int i=k_Cannon_Type_1;i<k_Cannon_Type_Count;i++)
	{
		Vector<SpriteFrame*> frames(2);
		for (int j=1;j<=2;j++)
		{
			String* frameName = String::createWithFormat("Cannon%d_%d", i + 1, j);
			SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(STATIC_DATA_STRING(frameName->getCString()));
			frames.pushBack(sprite);
		}
		auto animation = Animation::createWithSpriteFrames(frames);
		animation->setDelayPerUnit(0.1f);
		String* animationName = String::createWithFormat("cannonanimation%d",i);
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

}

void MainScene::cannonAimAt(const Vec2 & pos)
{
	_cannonLayer->cannonAimAt(pos);
}

void MainScene::cannonShootTo(const Vec2 & pos)
{
	_cannonLayer->cannonShootTo(pos);
	//todo
}

