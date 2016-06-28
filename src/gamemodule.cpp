/***************************************************
* @filename	gamemodule.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 16:32:46.
***************************************************/

#include "gamemodule.h"

int GameModule::init()
{
	return IModule::SUCC; 
}

int GameModule::start()
{
	return IModule::SUCC; 
}

int GameModule::update()
{
	printf("game module update\n");
	return IModule::SUCC; 
}

int GameModule::stop()
{
	return IModule::SUCC; 
}

int GameModule::release()
{
	return IModule::SUCC; 
}
