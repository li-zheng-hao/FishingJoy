#include "FishLayer.h"
#include "GameData.h"
bool FishLayer::init()
{
	if (!Layer::init())
		return false;

	_fishes.reserve(50);

	for (int i=0;i<50;i++)
	{
		int type = random(0, 13);//鱼的类型
		auto fish = Fishes::create((FishType)type);
		_fishes.pushBack(fish);
	}
	this->schedule(schedule_selector(FishLayer::addFish), 3);
	return true;
}

void FishLayer::addFish(float dt)
{
	
	int fishesWillAddedNumber = random(5, 15);
	//int fishesWillAddedNumber = 10;//todo
	int fishesHasAdded = 0;
	Fishes* fish;
	for (auto iter:_fishes)
	{
		fish = (Fishes*)iter;
		if (fish->getParent()==nullptr)
		{
			this->resetFish(fish);
			this->addChild(fish);
			/*
			 * 2017/08/18
			 * @brief 这些鱼是重复利用的，所以每次加入之后要重新设置它的状态
			 */
			fishesHasAdded++;
			if (fishesWillAddedNumber==fishesHasAdded)
			{
				break;
			}
		}
	}
	int freeFiss = 0;
	for (int i = 0; i < _fishes.size(); i++)
	{
		Fishes* fish = (Fishes*)_fishes.at(i);
		if (fish->getParent() == nullptr)
		{
			freeFiss++;
		}
	}
	CCLOG("current free fish::%d", freeFiss);
}

void FishLayer::resetFish(Fishes * fish)
{
	fish->reset();
	Vec2 startPoint, destination;
	auto fishSize = fish->_sprite->getContentSize();
	int direction = random(0, 1);
	/*
	 * 2017/08/18
	 * @brief 两个方向，一个从左往右，一个从右往左
	 */
	if (direction)
	{
		fish->setRotation(0);
		startPoint.x = winSize.width + fishSize.width / 2;
		destination.x = -fishSize.width/2;
	}
	else
	{
		fish->setRotation(180);
		startPoint.x = -fishSize.width/2;
		destination.x = winSize.width + fishSize.width / 2;
	}
	startPoint.y = CCRANDOM_0_1()*(winSize.height - fishSize.height) + fishSize.height / 2;
	destination.y = startPoint.y;
	fish->setPosition(startPoint);
	fish->moveToAction(destination);
}
