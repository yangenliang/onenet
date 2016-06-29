/***************************************************
* @filename	net.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-23 21:42:08.
***************************************************/

#include "net.h"

#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h>	     /* epoll function */
#include <fcntl.h>	      	 /* nonblocking */
#include <sys/resource.h>    /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <thread>

#define MAXEPOLLSIZE 100000
#define MAXLINE      1024

int handle(int connfd); 

int setnonbloking(int sock_fd)
{
	if (-1 ==fcntl(sock_fd, F_SETFL, fcntl(sock_fd, F_GETFD, 0) | O_NONBLOCK)) {
		return -1; 
	}
	return 0; 
}

int start_net()
{
	int srv_port = 6000; 
	int listenq = 1024; 

	int listen_fd, conn_fd, kdp_fd, nfds, n, curfds, accept_count = 0; 
	sockaddr_in srv_addr, client_addr; 
	socklen_t socklen = sizeof(struct sockaddr_in); 
	epoll_event ev; 
	epoll_event events[MAXEPOLLSIZE]; 
	rlimit rt; 
	char   buf[MAXLINE]; 

	rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE; 
	if (-1 == setrlimit(RLIMIT_NOFILE, &rt)) {
		perror("setrlimit error"); 
		return -1; 
	}

	memset(&srv_addr, 0, sizeof(srv_addr)); 
	srv_addr.sin_family = AF_INET; 
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	srv_addr.sin_port = htons(srv_port); 

	listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (-1 == listen_fd) {
		perror("Can't create socket file"); 
		return -1; 
	}

	int opt = 1; 
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 

	if (setnonbloking(listen_fd) < 0) {
		perror("setnonblock error"); 
	}

	if (-1 == bind(listen_fd, (struct sockaddr*)&srv_addr, sizeof(struct sockaddr))) {
		perror("bind error"); 
		return -1; 
	}

	if (-1 == listen(listen_fd, listenq)) {
		perror("listen error"); 
		return -1; 
	}

	kdp_fd = epoll_create(MAXEPOLLSIZE); 
	ev.events = EPOLLIN | EPOLLET; 
	ev.data.fd = listen_fd; 
	if (epoll_ctl(kdp_fd, EPOLL_CTL_ADD, listen_fd, &ev) < 0) {
		fprintf(stderr, "epoll set insertion error:%d\n", listen_fd); 
		return -1; 
	}
	curfds = 1; 

	printf("epollserver startup, port %d, max connection is %d, backlog is %d\n", srv_port, MAXEPOLLSIZE, listenq); 

	for (;;) {
		nfds = epoll_wait(kdp_fd, events, curfds, -1); 
		if (-1 == nfds) {
			perror("epoll_wait"); 
			continue; 
		}

		for (n = 0; n < nfds; ++n) {
			if (events[n].data.fd == listen_fd) {
				conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &socklen); 
				if (conn_fd < 0) {
					perror("accept error"); 
					continue; 
				}

				sprintf(buf, "accept from %s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port); 
				printf("%d:%s", ++accept_count, buf); 

				if (curfds >= MAXEPOLLSIZE) {
					fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE); 
					close(conn_fd); 
					continue; 
				}
				if (setnonbloking(conn_fd) < 0) {
					perror("sernonbloking error"); 
				}
				ev.events = EPOLLIN | EPOLLET; 
				ev.data.fd = conn_fd; 
				if (epoll_ctl(kdp_fd, EPOLL_CTL_ADD, conn_fd, &ev) < 0) {
					fprintf(stderr, "add socket '%d' to epoll failed: %s\n", conn_fd, strerror(errno)); 
					return -1; 
				}
				curfds++; 
				continue; 

			}
			if (handle(events[n].data.fd) < 0) {
				epoll_ctl(kdp_fd, EPOLL_CTL_DEL, events[n].data.fd, &ev); 
				--curfds;  
			}
		}
	}

	close(listen_fd); 
	return 0; 
}

int handle(int connfd)
{
	int nread; 
	char buf[MAXLINE]; 
	nread = read(connfd, buf, MAXLINE); 

	if (0 == nread) {
		printf("client close the connection\n"); 
		close(connfd); 
		return -1; 
	}
	if (nread < 0) {
		perror("read error"); 
		close(connfd); 
		return -1; 
	}
	write(connfd, buf, nread); 
	return 0; 
}

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
