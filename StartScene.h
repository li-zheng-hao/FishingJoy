#ifndef StartScene_H
#define StartScene_H
#include"cocos2d.h"
USING_NS_CC;
class StartScene:public Scene
{
public:
	CREATE_FUNC(StartScene);
	virtual bool init();
private:
	void preloadSources();
	void sourcesCallBack(Texture2D* sender);
	void progressMaxCallBack();
};


#endif
