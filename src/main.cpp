/***************************************************
* @filename	main.cpp
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 13:49:32.
***************************************************/

#include "stdafx.h"

int main(void)
{
	std::cout << "onenet stared" << std::endl; 
	Game game; 
	NetModule::Register(&game, NET_MODULE); 
	game.register_module(GAME_MODULE, new GameModule());
	game.run(); 
	return 0; 
}
