#ifndef UILayer_H
#define UILayer_H
#include "cocos2d.h"
USING_NS_CC;
class UILayer :
	public Layer
{
public:
	CREATE_FUNC(UILayer);
	bool init();
protected:
	Sprite* _menu1;
	Sprite* _menu2;

};

#endif
