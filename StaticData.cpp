#include "StaticData.h"
#define DATA_PATH "file.plist"
StaticData* StaticData::_sharedStaticData = nullptr;

StaticData::StaticData()
{

}

StaticData * StaticData::getInstance()
{
	if (!_sharedStaticData)
	{
		_sharedStaticData = new StaticData();
		_sharedStaticData->init();
	}
	return _sharedStaticData;
}

void StaticData::init()
{
	_data = Dictionary::createWithContentsOfFile(DATA_PATH);
	/*
	 * 2017/08/17
	 * @brief retain之后记得release
	 */
	CC_SAFE_RETAIN(_data);
}

StaticData::~StaticData()
{
	/*
	 * 2017/08/17
	 * @brief 防止内存泄漏
	 */
	CC_SAFE_RELEASE(_data);
	CC_SAFE_DELETE(_sharedStaticData);
}

//-----------------下面是将字典的一些接口进一步封装begin---------------------
const char* StaticData::getStringFromKey(const std::string& key) const
{
	return _data->valueForKey(key)->getCString();
}

int StaticData::getIntFromKey(const std::string &key) const
{
	return _data->valueForKey(key)->intValue();
}

float StaticData::getFloatFromKey(const std::string &key) const
{
	return _data->valueForKey(key)->floatValue();
}

bool StaticData::getBoolFromKey(const std::string & key) const
{
	return _data->valueForKey(key)->boolValue();
}


//-----------------下面是将字典的一些接口进一步封装 end-----------------------