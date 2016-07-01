/***************************************************
* @filename	socket.c
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-07-01 23:22:44.
***************************************************/

#include "socket.h"

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

#define MAXLINE      1024
#define MAXEPOLLSIZE 1024

int handle(int connfd); 

static int 
setnonbloking(int fd)
{
	if (-1 ==fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK)) {
		return -1; 
	}
	return 0; 
}

static int 
init_socket(int srv_port)
{
	int listen_fd = 0; 
	int listenq = 1024; 
	sockaddr_in srv_addr; 

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
	return listen_fd; 
}

static int 
init_epoll(int listen_fd)
{
	int ep_fd = epoll_create(MAXEPOLLSIZE); 
	epoll_event ev; 
	ev.events = EPOLLIN | EPOLLET; 
	ev.data.fd = listen_fd; 

	if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ev) < 0) {
		fprintf(stderr, "epoll set insertion error:%d\n", listen_fd); 
		return -1; 
	}
	printf("epollserver startup"); 

	return ep_fd; 
}

static int 
start_epoll(int ep_fd, int listen_fd)
{
	int nfds = 0; 
	int conn_fd = 0; 
	int curfds = 1; 
	int accept_count = 0; 
	char   buf[MAXLINE]; 
	epoll_event ev; 
	epoll_event events[MAXEPOLLSIZE]; 

	sockaddr_in client_addr; 
	socklen_t socklen = sizeof(struct sockaddr_in); 

	while(1)
	{
		nfds = epoll_wait(ep_fd, events, curfds, -1); 
		if (-1 == nfds) {
			perror("epoll_wait"); 
			continue; 
		}

		for (int n = 0; n < nfds; ++n) {
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
				if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, conn_fd, &ev) < 0) {
					fprintf(stderr, "add socket '%d' to epoll failed: %s\n", conn_fd, strerror(errno)); 
					return -1; 
				}
				curfds++; 
				continue; 

			}
			if (handle(events[n].data.fd) < 0) {
				epoll_ctl(ep_fd, EPOLL_CTL_DEL, events[n].data.fd, &ev); 
				--curfds;  
			}
		}
	}
}

int 
handle(int connfd)
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


static int 
start_net()
{
	int listen_fd = init_socket(6666); 
	int ep_fd = init_epoll(listen_fd); 
	start_epoll(ep_fd, listen_fd); 
}