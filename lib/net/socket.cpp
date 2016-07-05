/***************************************************
* @filename	socket.c
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-01 23:22:44.
***************************************************/

#include "socket.h"

namespace onenet
{
	bool one_set_nonbloking(int fd)
	{
		return -1 != fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK); 
	}

	int  one_socket()
	{
		return socket(AF_INET, SOCK_STREAM, 0); 
	}

	int  one_bind(int fd, const char* addr, unsigned int port)
	{
		struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(port);

        if(addr == NULL || strcmp(addr, "") == 0)
        {
            addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else
        {
            addr_in.sin_addr.s_addr = inet_addr(addr);
        }

        int flag = 1;
        int len = sizeof(int);
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, len);
        return bind(fd, (struct sockaddr*)&addr_in, sizeof(addr_in) );
    }

	int  one_listen(int fd, int back_log)
	{
		return listen(fd, back_log); 
	}

	int  one_connect(int fd, const char* addr, unsigned int port)
	{
        struct sockaddr_in addr_in;
        memset(&addr_in, 0, sizeof(addr_in));
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(port);
        addr_in.sin_addr.s_addr = inet_addr(addr);

        return connect(fd, (sockaddr*)&addr_in, sizeof(addr_in));
	}

	void one_set_buff_size(int fd, int recv_len, int snd_len)
	{
		setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (const int*)&recv_len, sizeof(int));	
		setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (const int*)&snd_len, sizeof(int));
	} 

	void one_get_buff_size(int fd)
	{
		int n1 = 0,n2 = 0;
		socklen_t nn1 = sizeof(n1),nn2=sizeof(n2);
		getsockopt(fd, SOL_SOCKET, SO_RCVBUF, (int*)&n1, &nn1);
		getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (int*)&n2, &nn2);
		//printf("222fd=%d;rcv=%d;snd=%d\n", fd, n1, n2);
	}

	int  one_async_read(int fd, void* buf, size_t size, int timeout)
	{
		fd_set rfds;       
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = 0;

        int ret = select(fd+1, &rfds, NULL, NULL, &tv);
        if(ret > 0)
        {
            return ::read(fd, buf, size);
        }
        
        return ret;
	}
}; 
