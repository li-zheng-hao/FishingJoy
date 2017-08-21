#ifndef GameData_H
#define GameData_H
#include "cocos2d.h"
USING_NS_CC;
#define STATIC_DATA_STRING(key) GameData::getInstance()->getStringFromKey(key)
#define STATIC_DATA_INT(key) GameData::getInstance()->getIntFromKey(key)
#define STATIC_DATA_FLOAT(key) GameData::getInstance()->getFloatFromKey(key)
#define STATIC_DATA_BOOL(key) GameData::getInstance()->getBoolFromKey(key)
#define winSize Director::getInstance()->getWinSize()
class GameData
{
public:
	/*
	 * 2017/08/17
	 * @brief 数据是单例模式
	 */
	static GameData* getInstance();
	void init();
	~GameData();
	
	/*
	 * 2017/08/17
	 * @brief 将Dictionary的一些接口进行进一步的封装
	 */
	const char* getStringFromKey(const std::string &key)const ;
	int getIntFromKey(const std::string &key)const;
	float getFloatFromKey(const std::string &key)const;
	bool getBoolFromKey(const std::string &key)const;
protected:
	static GameData* _sharedGameData;
	Dictionary* _data;
	
};
#endif

