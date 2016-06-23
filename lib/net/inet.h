/***************************************************
* @filename	inet.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-23 20:49:10.
***************************************************/

#ifndef _INET_H_
#define _INET_H_

typedef unsigned int NetId; 
typedef unsigned int Ip; 
typedef unsigned int Port; 

class INetCallback; 

class INet
{
public:
	virtual ~INet() = 0; 

public:
	virtual void register_callback(INetCallback* callback) = 0; 
	virtual bool listen(Port port, NetId* netid_out) = 0; 
	virtual bool connect(const char* ip, Port port, 
						NetId *netid_out, unsigned long time_out = 3000) = 0; 
	virtual bool connect(Ip ip, Port port, 
						NetId *netid_out, unsigned long time_out = 3000) = 0; 
	virtual bool send(NetId netid, const char* data, unsigned int length) = 0; 
	virtual bool disconnect(NetId netid) = 0; 

}; 

class INetCallback
{
public:
	virtual ~INetCallback() = 0; 

public:
	virtual void on_accepted(NetId netid, Ip ip, Port port) = 0; 
	virtual void on_received(NetId netid, const char* data, int length) = 0; 
	virtual void on_disconnected(NetId netid) = 0; 
	virtual void on_connected() = 0; 
}; 

#endif // _INET_H_
