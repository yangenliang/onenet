/***************************************************
* @filename	net.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-23 21:41:53.
***************************************************/

#ifndef _NET_H_
#define _NET_H_

#include "inet.h" 

class Net : public INet
{
public:
	Net(); 
	~Net(); 

public:
	void register_callback(INetCallback* callback); 
	bool listen(Port port, NetId* netid_out); 
	bool connect(const char* ip, Port port, 
				NetId *netid_out, unsigned long time_out = 3000); 
	bool connect(Ip ip, Port port, 
				NetId *netid_out, unsigned long time_out = 3000); 
	bool send(NetId netid, const char* data, unsigned int length); 
	bool disconnect(NetId netid); 

private:
	INetCallback*	callback_; 

}; 

#endif // _NET_H_
