#ifndef FishingNet_H
#define FishingNet_H
#include "cocos2d.h"
#include "Cannon.h"
USING_NS_CC;
typedef enum Weapon_Type
{
	k_Weapon_Bullet,
	k_Weapon_FishNet,
	k_Weapon_Count,
};
class Weapon :
	public Node
{
public:
	static Weapon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type=k_Cannon_Type_1);

	void shootTo(const Vec2& pos);
	void shootEnd();
	void removeFishNet();

	Rect getFishNetCollisionArea();

public:
	Sprite* _bullet;
	Sprite* _fishNet;
	Vec2 _collisionPos;

	
};

#endif
