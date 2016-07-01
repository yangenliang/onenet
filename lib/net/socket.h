/***************************************************
* @filename	socket.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-01 23:16:58.
***************************************************/

#ifndef _SOCKET_H_
#define _SOCKET_H_

static int setnonbloking(int fd); 
static int init_socket(int srv_port); 
static int init_epoll(int listen_fd); 
static int start_epoll(int ep_fd); 
static int start_net(); 

#endif // _SOCKET_H_
