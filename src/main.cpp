/***************************************************
* @filename	main.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 13:49:32.
***************************************************/

#include <iostream>
#include "../lib/module/game.h"
#include "../lib/net/netmodule.h"

static const char* NET_MODULE = "NET_MODULE"; 

int main(void)
{
	std::cout << "onenet stared" << std::endl; 
	Game game; 
	NetModule::Register(&game, NET_MODULE); 
	// game.register_module(); 
	return 0; 
}
