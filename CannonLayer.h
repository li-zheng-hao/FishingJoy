#ifndef CannonLayer_H
#define CannonLayer_H
#include "cocos2d.h"
#include "Cannon.h"
#include "Weapon.h"
USING_NS_CC;
class CannonLayer :
	public Layer
{
public:
	CREATE_FUNC(CannonLayer);
	bool init();

	void cannonAimAt(const Vec2& pos);
	void cannonShootTo(const Vec2& pos);
protected:
	Cannon* _cannon;
	Sprite* _add_button;
	Sprite* _reduce_button;
	int _cannonLevel;
};
#endif

