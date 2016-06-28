/***************************************************
* @filename	gamemodule.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 16:31:16.
***************************************************/

#ifndef _GAME_MODULE_H_
#define _GAME_MODULE_H_

#include "../lib/module/imodule.h" 

class INetCallback; 

class GameModule : public IModule
{
public:
	GameModule(); 
	~GameModule(); 
	
public:
	int init(); 
	int start(); 
	int update(); 
	int stop(); 
	int release(); 

private:
	INetCallback* net_callback_; 
}; 

#endif // _GAME_MODULE_H_
