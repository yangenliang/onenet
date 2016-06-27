/***************************************************
* @filename	game.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 15:50:59.
***************************************************/

#include "game.h"
#include "imodule.h"

bool Game::register_module(const char* name, IModule* module)
{
	if (module_map_[name])
		return false; 
	module_map_[name] = module; 
	return true; 
}

IModule* Game::query_module(const char* name)
{
	return nullptr; 
}

void Game::run()
{
	for(auto& _map : module_map_)
	{
		if (_map.second->init() == IModule::SUCC) 
		{
			inited_list.emplace_back(_map.second); 
		}
	}
	do{
		for(auto& module : inited_list)
		{
			if (module->start() == IModule::SUCC)
			{
				started_list.emplace_back(module); 
			}
		}

		if (started_list.size() == 2)
		{
			break; 
		}

	}while(1); 
}

void Game::stop()
{
}