#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "Player.h"
#include "Enemy.h"

using std::string;
using std::vector;
using std::ifstream;

class Level
{
public:
	Level();

	void load(string, Player&);
	void print();

	void movePlayer(char, Player&);
	void updateEnemies(Player&);

	// Getters
	char getTile(int, int);
	// Setters
	void setTile(int, int, char);

private:
	void processPlayerMove(Player&, int, int);
	void processEnemyMove(Player&, int, int, int);
	void battleEnemy(Player&, int, int);

private:
	vector<string> _levelData;
	vector<Enemy> _enemies;
};

