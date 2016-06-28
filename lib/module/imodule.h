/***************************************************
* @filename	imodule.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 00:03:29.
***************************************************/

#ifndef _IMODULE_H_
#define _IMODULE_H_

class IModule
{
	friend class Game; 
public:
	IModule()
	:state_(ST_RELEASED)
	{}
	virtual ~IModule() {}

public:
	enum
	{
		SUCC,
		FAIL,
		PENDING,
	}; 

	enum
	{
		ST_INITING,
		ST_INITED,
		ST_STARTING,
		ST_STARTED,
		ST_UPDATING,
		ST_UPDATED,
		ST_STOPPING,
		ST_STOPPED,
		ST_RELEASING,
		ST_RELEASED,
		ST_FAIL,
	};

public:
	virtual int init() = 0; 
	virtual int start() = 0; 
	virtual int update() = 0; 
	virtual int stop() = 0; 
	virtual int release() = 0; 

private:
	int state_; 

}; 

#endif // _IMODULE_H_
