/***************************************************
* @filename	game.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 15:50:59.
***************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include <list>
#include <unordered_map>
#include "imodulemgr.h"

class Game : public IModuleMgr
{
	typedef std::unordered_map<std::string, IModule*> ModuleMap; 
	typedef std::list<IModule*> ModuleList; 
public:
	Game(){}
	~Game(){}
	
private:
	Game(const Game&);
	Game& operator=(const Game&);

public:
	bool register_module(const char* name, IModule* module); 
	IModule* query_module(const char* name); 

public:
	void run(); 
	void stop(); 

private:
	ModuleMap module_map_; 
	ModuleList inited_list; 
	ModuleList started_list; 

}; 

#endif // _GAME_H_
