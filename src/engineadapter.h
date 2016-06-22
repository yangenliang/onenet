/***************************************************
* @filename	engineadapter.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-22 23:51:11.
***************************************************/

#ifndef _ENGINEADAPTER_H_
#define _ENGINEADAPTER_H_

#include "singleton.h"

class EngineAdapter : public Singleton<EngineAdapter>
{
	friend class Singleton<EngineAdapter>; 
protected:
	EngineAdapter() {}
}; 

#define sEngineAdapter EngineAdapter::get_instance()

#endif // _ENGINEADAPTER_H_
