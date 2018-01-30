#include "GameSystem.h"

// Constractor sets up the game
GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 10, 0);

	_level.load(levelFileName, _player);

	system("pause");
}

void GameSystem::playGame()
{
	bool isDone = false;

	while (isDone == false)
	{
		_level.print();
		playerMove();
		_level.updateEnemies(_player);
	}
}

void GameSystem::playerMove()
{
	char input;
	printf("Enter a move command (w/s/a/d): ");
	input = _getch();

	_level.movePlayer(input, _player);
}