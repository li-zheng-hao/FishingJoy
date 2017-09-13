#ifndef StaticData_H
#define StaticData_H
#include "cocos2d.h"
USING_NS_CC;
//-----------------进行一些宏定义	begin---------------------
#define STATIC_DATA_STRING(key) StaticData::getInstance()->getStringFromKey(key)
#define STATIC_DATA_INT(key) StaticData::getInstance()->getIntFromKey(key)
#define STATIC_DATA_FLOAT(key) StaticData::getInstance()->getFloatFromKey(key)
#define STATIC_DATA_BOOL(key) StaticData::getInstance()->getBoolFromKey(key)
#define winSize Director::getInstance()->getWinSize()
//-----------------进行一些宏定义	end-----------------------

class StaticData
{
public:
	/*
	 * 2017/08/17
	 * @brief 数据是单例模式
	 */
	static StaticData* getInstance();
	void init();
	~StaticData();
	
	/*
	 * 2017/08/17
	 * @brief 将Dictionary的一些接口进行进一步的封装
	 */
	const char* getStringFromKey(const std::string &key)const ;
	int getIntFromKey(const std::string &key)const;
	float getFloatFromKey(const std::string &key)const;
	bool getBoolFromKey(const std::string &key)const;
protected:
	static StaticData* _sharedStaticData;
	Dictionary* _data;
private:
		//防止通过这种方式进行创建
	StaticData();

};
#endif

