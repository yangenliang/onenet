/***************************************************
* @filename	epoll_server.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-05 22:45:44.
***************************************************/

#include "epoll_server.h"
#include "one_socket.h"
#include <sys/epoll.h>

EpollServer::EpollServer()
:stop_(false)
{
}

EpollServer::~EpollServer()
{
}

void EpollServer::stop()
{
	stop_ = true; 
}

int EpollServer::start_server(const char* addr, unsigned int port)
{
	addr_ = addr; 
	port_ = port; 

	int listen_fd = onenet::one_socket(); 
	if (-1 == listen_fd)
	{
		printf("failed to create socket\n");
		return -1; 
	}

	onenet::one_set_nonbloking(listen_fd); 
	onenet::one_set_buff_size(listen_fd, 102400, 102400); 

	if (onenet::one_bind(listen_fd, addr, port))
	{
		printf("failed to bind\n");
		return -1; 
	}

	if (onenet::one_listen(listen_fd, 20))
	{
		printf("failed to listen\n");
		return -1; 
	}

	ep_fd_ = epoll_create(MAX_EPOLL_SIZE); 
	if (-1 == ep_fd_)
	{
		printf("failed to create epoll\n");
		return -1; 
	}

	struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.fd = listen_fd;
    
    if (-1 == epoll_ctl(ep_fd_, EPOLL_CTL_ADD, listen_fd, &ev))
    {
    	printf("failed to add listen fd to epoll\n");
    	return -1; 
    }

    printf("start_server:%s:%d, success.\n", addr, port);
    return 0; 
}

int EpollServer::run_loop(const char* addr, unsigned int port)
{
	int ret = start_server(addr, port); 
	if (ret)
	{
		return ret; 
	}

	struct epoll_event ev;
    struct epoll_event events[MAX_EPOLL_SIZE];

    int event_count = 1; 
    while(!stop_)
    {
    	int nfds = epoll_wait(ep_fd_, events, event_count, EPOLL_TIMEOUT); 
    	if (-1 == nfds)
    	{
    		if (errno == EINTR)
    		{
    			continue; 
    		}
    		else
    		{    			
    			printf("epoll_wait error\n");
    			break; 
    		}
    	}
    	else if (0 == nfds)
    	{
    		printf("epoll_wait time out.\n");
    	}

    	for (int n = 0; n < nfds; ++n)
    	{
    		int fd = events[n].data.fd; 
    		// todo
    	}

    }
    return 0; 
}