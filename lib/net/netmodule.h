/***************************************************
* @filename	netmodule.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 10:30:03.
***************************************************/

#ifndef _MET_MODULE_H_
#define _MET_MODULE_H_

#ifdef _MSC_VER
	#ifdef MODULE_EXPORTS
		#define MODULE_API __declspec( dllexport )
	#else
		#define MODULE_API __declspec( dllimport )
	#endif
#else
	#define MODULE_API
#endif

class IModuleMgr; 

namespace NetModule
{
	MODULE_API void Register(IModuleMgr* module_mgr, const char* module_name = 0); 
}


#endif // _MET_MODULE_H_
