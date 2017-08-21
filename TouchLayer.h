#ifndef TouchLayer_H
#define TouchLayer_H
#include "cocos2d.h"
USING_NS_CC;
class TouchLayer :
	public Layer
{
public:
	CREATE_FUNC(TouchLayer);
	bool init();

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
};

#endif
