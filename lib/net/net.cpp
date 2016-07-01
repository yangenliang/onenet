/***************************************************
* @filename	net.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-23 21:42:08.
***************************************************/

#include "net.h"
extern "C"
{
#include "socket.h"
}

#include <thread>

Net::Net()
{
	callback_ = 0; 
}

Net::~Net()
{
}

int Net::init()
{
	return IModule::SUCC; 
}

int Net::start()
{
	std::thread t(start_net);
	t.detach();  
	return IModule::SUCC; 
}

int Net::update()
{
	return IModule::PENDING; 
}

int Net::stop()
{
	return IModule::SUCC;
}

int Net::release()
{
	return IModule::SUCC;
}


void Net::register_callback(INetCallback* callback)
{
	callback_ = callback; 
}

bool Net::listen(Port port, NetId* netid_out)
{
	return true; 
}

bool Net::connect(const char* ip, Port port, 
				NetId *netid_out, unsigned long time_out)
{
	return true; 
}

bool Net::connect(Ip ip, Port port, 
				NetId *netid_out, unsigned long time_out)
{
	return true; 
}

bool Net::send(NetId netid, const char* data, unsigned int length)
{
	return true; 
}

bool Net::disconnect(NetId netid)
{
	return true; 
}
