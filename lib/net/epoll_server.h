/***************************************************
* @filename	epoll_server.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-05 22:42:07.
***************************************************/

#ifndef _EPOLL_SERVER_H_
#define _EPOLL_SERVER_H_

class EpollServer
{
	enum name
	{
		MAX_EPOLL_SIZE	= 1024,
		EPOLL_TIMEOUT 	= 50, 
	};
public:
	EpollServer(); 
	~EpollServer(); 

	void stop(); 

public:
	int run_loop(const char* addr, unsigned int port); 
	int start_server(const char* addr, unsigned int port); 

private:
	const char* addr_; 
	unsigned int port_; 

	int ep_fd_; 
	bool stop_; 

}; 

#endif // _EPOLL_SERVER_H_
