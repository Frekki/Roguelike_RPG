#pragma once
#include "Player.h"
#include "Level.h"
#include <string>
#include <conio.h>
//#include <iostream>

using std::string;
//using std::cout;

class GameSystem
{
public:
	GameSystem(string);

	void playGame();
	void playerMove();

private:
	Level _level;
	Player _player;
};
