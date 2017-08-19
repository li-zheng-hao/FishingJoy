#ifndef BackGroundLayer_H
#define BackGroundLayer_H
#include "cocos2d.h"
#include "GameData.h"
USING_NS_CC;
class BackGroundLayer :
	public Layer
{
public:
	CREATE_FUNC(BackGroundLayer);
	bool init();
protected:
	Sprite* _background;

};

#endif
