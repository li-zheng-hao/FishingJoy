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
	Rect getFishNetCollisionArea();
	void switchCannon(Ref* callfunc);

	bool isShoot();
protected:
	Cannon* _cannon;
	MenuItemSprite* _add_button;
	MenuItemSprite* _reduce_button;
	Weapon* _weapon;
	int _cannonLevel;
};
#endif

