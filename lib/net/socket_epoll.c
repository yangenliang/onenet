/***************************************************
* @filename	socket_epoll.c
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-01 00:21:35.
***************************************************/

#include "socket_epoll.h"
#include <fcntl.h>

static int 
setnonbloking(int fd)
{
	if (-1 ==fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK)) {
		return -1; 
	}
	return 0; 
}