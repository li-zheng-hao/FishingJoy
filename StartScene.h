#ifndef StartScene_H
#define StartScene_H
#include"cocos2d.h"
USING_NS_CC;
class StartScene:public Scene
{
public:
	CREATE_FUNC(StartScene);
	virtual bool init();
	void preloadSources();
private:

};


#endif
