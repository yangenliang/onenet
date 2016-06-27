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
public:
	IModule() {}
	virtual ~IModule() {}

public:
	enum
	{
		SUCC,
		FAIL,
		PENDING,
	}; 

public:
	virtual int init() = 0; 
	virtual int start() = 0; 
	virtual int update() = 0; 
	virtual int stop() = 0; 
	virtual int release() = 0; 

}; 

#endif // _IMODULE_H_
