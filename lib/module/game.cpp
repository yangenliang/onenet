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
	module_list_.emplace_back(module); 
	return true; 
}

IModule* Game::query_module(const char* name)
{
	return module_map_[name]; 
}

void Game::run()
{
	do
	{
		for(auto& module : module_list_)
		{
			if(module->state_ != IModule::ST_INITED)
			{
				module->state_ = IModule::ST_INITING; 
				if (module->init() == IModule::SUCC)
				{
					module->state_ = IModule::ST_INITED; 
					inited_list_.emplace_back(module); 
				}
			}
		}

		if (module_list_.size() == inited_list_.size())
		{
			break; 
		}

	}while(1); 

	do
	{
		for(auto& module : inited_list_)
		{
			if(module->state_ != IModule::ST_INITED)
			{
				module->state_ = IModule::ST_INITING; 
				if (module->init() == IModule::SUCC)
				{
					module->state_ = IModule::ST_INITED; 
					started_list_.emplace_back(module); 
				}
			}
		}

		if (inited_list_.size() == started_list_.size())
		{
			break; 
		}

	}while(1); 

	do
	{
		for(auto& module : started_list_)
		{
			module->state_ = IModule::ST_UPDATING; 
			module->update(); 
			module->state_ = IModule::ST_UPDATED; 
		}
	}while(1); 
}

void Game::stop()
{
}