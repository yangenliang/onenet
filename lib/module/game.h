/***************************************************
* @filename	game.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 15:50:59.
***************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include "imodulemgr.h"

class Game : public IModuleMgr
{
public:
	Game(){}
	~Game(){}
	
private:
	Game(const Game&);
	Game& operator=(const Game&);

public:
	bool register_module(const char* name, IModule* module); 
	IModule* query_module(const char* name); 

}; 

#endif // _GAME_H_
