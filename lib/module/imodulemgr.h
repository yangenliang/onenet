/***************************************************
* @filename	imodulemgr.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 10:06:25.
***************************************************/

#ifndef _IMODULE_MGR_H_
#define _IMODULE_MGR_H_

class IModule; 

class IModuleMgr
{
public:
	virtual ~IModuleMgr() {} 
	
public:
	virtual bool register_module(const char* name, IModule* module) = 0; 
	virtual IModule* query_module(const char* name) = 0; 

}; 

#endif // _IMODULE_MGR_H_
