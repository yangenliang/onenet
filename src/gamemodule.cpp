/***************************************************
* @filename	gamemodule.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-24 16:32:46.
***************************************************/

#include "gamemodule.h"
#include "servercommon.h"

#include "../lib/net/inet.h"
#include "../lib/module/imodulemgr.h"

class NetCallback : public INetCallback
{
public:
	void on_accepted(NetId netid, Ip ip, Port port)
	{

	}

	void on_received(NetId netid, const char* data, int length)
	{

	}

	void on_disconnected(NetId netid)
	{

	}

	void on_connected()
	{

	}

}; 

GameModule::GameModule()
{
	net_callback_ = new NetCallback(); 
}

GameModule::~GameModule()
{
	delete net_callback_; 
}

int GameModule::init()
{
	return IModule::SUCC; 
}

int GameModule::start()
{
	net_ = dynamic_cast<INet*>(module_mgr()->query_module(NET_MODULE)); 
	net_->register_callback(net_callback_); 
	return IModule::SUCC; 
}

int GameModule::update()
{
	return IModule::PENDING; 
}

int GameModule::stop()
{
	return IModule::SUCC; 
}

int GameModule::release()
{
	return IModule::SUCC; 
}
