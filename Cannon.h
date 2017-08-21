#ifndef Cannon_H
#define Cannon_H
#include "cocos2d.h"
USING_NS_CC;
typedef enum CannonType
{
	k_Cannon_Type_1=0,
	k_Cannon_Type_2,
	k_Cannon_Type_3,
	k_Cannon_Type_4,
	k_Cannon_Type_5,
	k_Cannon_Type_6,
	k_Cannon_Type_7,
	k_Cannon_Type_Super,
	k_Cannon_Type_Count,
};
class Cannon :
	public Sprite
{
public:
	static Cannon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type = k_Cannon_Type_1);
	Sprite* getCurrentSprite();
	/*
	 * 2017/08/19
	 * @brief 每次点击加减的时候改变炮台的level
	 */
	void setCannon(CannonType type);
	CannonType getCannonType();
	/*
	 * 2017/08/19
	 * @brief 设置炮台的角度
	 */
	void setAngle(const Vec2& pos);

	void runShootAction();
public:
	CannonType _cannonType;
	Vector<Sprite*> _cannonSprites;
};

#endif
