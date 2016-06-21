/***************************************************
* @filename	game.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-21 15:50:59.
***************************************************/

#include "game.h"
#include <iostream>

void Game::start()
{
	std::cout << "game start" << std::endl; 
	main_loop(); 
}

void Game::end()
{
	std::cout << "game end" << std::endl; 
}

void Game::main_loop()
{
	for (int i = 0; i < 100; ++i)
	{
		std::cout << "main_loop:" << i << std:: endl; 
	}
}
