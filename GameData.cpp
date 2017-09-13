#include "GameData.h"
#include "StaticData.h"


GameData* GameData::_sharedGameData=nullptr;

void GameData::reset()
{
	int gold= STATIC_DATA_INT("default_gold");
	this->setGold(gold);
	this->setIsBeginner(true);
	this->setMusicVolume(1);
	this->setSoundVolume(1);
	this->flush();
}

void GameData::purge()
{
}

GameData::GameData()
{
	
}


GameData::~GameData()
{
	this->flush();
}

GameData* GameData::getIntance()
{
	if (!_sharedGameData)
	{
		_sharedGameData = new GameData();
		_sharedGameData->init();
	}
	return _sharedGameData;
}

void GameData::init()
{
	_isBeginner = UserDefault::sharedUserDefault()->getBoolForKey("beginner", true);
	if (_isBeginner)
	{
		this->reset();
		this->flush();
		this->setIsBeginner(false);
	}
	else
	{
		_isBeginner = UserDefault::sharedUserDefault()->getBoolForKey("beginner");
		_gold = UserDefault::sharedUserDefault()->getIntegerForKey("gold");
		_soundVolume = UserDefault::sharedUserDefault()->getFloatForKey("sound");
		_musicVolume = UserDefault::sharedUserDefault()->getFloatForKey("music");
		UserDefault::sharedUserDefault()->purgeSharedUserDefault();

	}
}

void GameData::flush()
{
	UserDefault::sharedUserDefault()->setBoolForKey("beginner", _isBeginner);
	UserDefault::sharedUserDefault()->setIntegerForKey("gold", _gold);
	UserDefault::sharedUserDefault()->setFloatForKey("sound", _soundVolume);
	UserDefault::sharedUserDefault()->setFloatForKey("music", _musicVolume);
	UserDefault::sharedUserDefault()->flush();
	UserDefault::sharedUserDefault()->purgeSharedUserDefault();



}

void GameData::alterGold(int delta)
{
	this->setGold(_gold + delta);
}
