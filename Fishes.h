#ifndef Fishes_H
#define Fishes_H
#include "cocos2d.h"
USING_NS_CC;
typedef enum {
	k_Fish_One = 0,
	k_Fish_Two,
	k_Fish_Three,
	k_Fish_Four,
	k_Fish_Five,
	k_Fish_Six,
	k_Fish_Seven,
	k_Fish_Eight,
	k_Fish_Nine,
	k_Fish_Ten,
	k_Fish_Eleven,
	k_Fish_Twelve,
	k_Fish_Thirteen,
	k_Fish_Fourteen,
	k_Fish_Count
}FishType;
class Fishes:
	public Node
{
public:
	static Fishes* create(FishType type = k_Fish_One);
	bool init(FishType type = k_Fish_One);

	/*
	 * 2017/08/18
	 * @brief 鱼的移动的相关函数
	 */
	void moveToAction(Vec2 destination);
	void moveActionEnd();
	/*
	 * 2017/08/18
	 * @brief 重新设置鱼的状态为初始状态
	 */
	void reset();


	/*
	 * 2017/08/21
	 * @brief 鱼被捕捉的函数
	 */
	void beCaught();

public:
	FishType _type;
	Sprite* _sprite;
	
};

#endif
