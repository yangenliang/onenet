/***************************************************
* @filename	one_socket.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-01 23:16:58.
***************************************************/

#ifndef _ONE_SOCKET_H_
#define _ONE_SOCKET_H_

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

namespace onenet
{
	bool one_set_nonbloking(int fd); 
	int  one_socket(); 
	int  one_bind(int fd, const char* addr, unsigned int port); 
	int  one_listen(int fd, int back_log = 5); 
	int  one_connect(int fd, const char* addr, unsigned int port); 
	void one_set_buff_size(int fd, int recv_len, int snd_len); 
	void one_get_buff_size(int fd); 
	int  one_async_read(int fd, void* buf, size_t size, int timeout); 
}; 

#endif // _ONE_SOCKET_H_
