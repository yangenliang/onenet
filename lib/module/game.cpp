/***************************************************
* @filename	game.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 15:50:59.
***************************************************/

#include "game.h"
#include "imodule.h"
#include <algorithm>

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
	inited_list_.clear(); 
	started_list_.clear(); 
	
	loop(module_list_, &IModule::init, &inited_list_, true, IModule::ST_INITED, IModule::ST_INITING); 
	loop(inited_list_, &IModule::start, &started_list_, true, IModule::ST_STARTED, IModule::ST_STARTING); 
	loop(started_list_, &IModule::update, nullptr, true, IModule::ST_UPDATED, IModule::ST_UPDATING); 

	std::reverse(started_list_.begin(), started_list_.end()); 
	loop(started_list_, &IModule::stop, nullptr, true, IModule::ST_STOPPED, IModule::ST_STOPPING); 
	std::reverse(inited_list_.begin(), inited_list_.end()); 
	loop(inited_list_, &IModule::release, nullptr, true, IModule::ST_RELEASED, IModule::ST_RELEASING); 

}

void Game::stop()
{
}

void Game::loop(const ModuleList& module_list, IModuleFunc func, ModuleList* succ_list, bool ignore_exit, int succ_state, int pending_state)
{
	ModuleList loop_list = module_list; 
	while(!loop_list.empty() && ignore_exit)
	{
		auto it = loop_list.begin(); 
		while(it != loop_list.end())
		{
			(*it)->state_ = pending_state; 
			switch(((*it)->*func)())
			{
			case IModule::SUCC:
				if (succ_list)
				{
					succ_list->emplace_back(*it); 
				}
				(*it)->state_ = succ_state; 
				loop_list.erase(it++); 
				break; 
			case IModule::PENDING:
				++it; 
				break; 
			case IModule::FAIL:
				(*it)->state_ = IModule::FAIL; 
				loop_list.erase(it++); 
				break; 
			}
		}

	}
}
