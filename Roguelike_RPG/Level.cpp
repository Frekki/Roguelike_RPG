#include "Level.h"

using std::cout;

Level::Level()
{

}

void Level::load(string fileName, Player &player)
{
	// Loads the level
	ifstream file;

	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}

	string line;

	while (getline(file, line))
	{
		_levelData.push_back(line);
	}

	file.close();

	// Process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++)
	{
		for (int j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];

			switch (tile)
			{
			case '@':	// Player
				player.setPosition(j, i);
				break;
			// Enemies
			case 'S':
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'g':
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'O':
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 40, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
				_enemies.back().setPosition(j, i);
				break;
			case 'B':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPosition(j, i);
				break;
			default:
				break;
			}
		}
	}
}

void Level::print()
{
	cout << string(100, '\n');

	for (int i = 0; i < _levelData.size(); i++)
	{
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
}

void Level::movePlayer(char input, Player &player)
{
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	switch (input)
	{
	case 'w':	// Up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':	// Down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':	// Left
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd':	// Right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("INVALID INPUT!\n");
		system("pause");
		break;
	}
}

void Level::updateEnemies(Player &player)
{
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++)
	{
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);
		switch (aiMove)
		{
		case 'w':	// Up
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's':	// Down
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a':	// Left
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':	// Right
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleEnemy(player, targetX, targetY);
		break;
	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::battleEnemy(Player &player, int targetX, int targetY)
{
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;
	string enemyName;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();

		if (targetX == enemyX && targetY == enemyY)
		{
			// Battle
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0)
			{
				setTile(targetX, targetY, '.');
				print();
				printf("\nPlayer attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
				printf("Monster died!\n");

				// Remove the enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				system("pause");
				player.addExperience(attackResult);				
				return;
			}

			// Monster turn
			attackRoll = _enemies[i].attack();
			printf("%s attacked player with a roll of %d\n",enemyName.c_str(), attackRoll);
			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0)
			{
				setTile(playerX, playerY, 'X');
				print();
				printf("%s attacked player with a roll of %d\n", enemyName.c_str(), attackRoll);
				printf("You died!\n");
				system("pause");
				exit(0);
			}

			system("pause");
			return;
		}
	}
}