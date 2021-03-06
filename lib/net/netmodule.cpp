/***************************************************
* @filename	netmodule.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 10:30:24.
***************************************************/

#include "net.h"
#include "netmodule.h"
#include "../module/imodulemgr.h"

namespace NetModule
{
	void Register(IModuleMgr* module_mgr, const char* module_name)
	{
		module_mgr->register_module(module_name, new Net());
	} 
}
