#ifndef FishLayer_H
#define FishLayer_H
#include "cocos2d.h"
#include "Fishes.h"
USING_NS_CC;

class FishLayer :
	public Layer
{
public:
	CREATE_FUNC(FishLayer);
	bool init();
	/*
	 * 2017/08/18
	 * @brief 对鱼的一些操作
	 */
	void addFish(float dt);
	void resetFish(Fishes* fish);

public:

	Vector<Fishes*> _fishes;
};

#endif
