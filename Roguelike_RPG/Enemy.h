#pragma once
#include <string>
#include <random>
#include <ctime>

using std::default_random_engine;
using std::uniform_int_distribution;
using std::string;

class Enemy
{
public:
	Enemy(string, char, int, int, int, int, int);

	// Setters
	void setPosition(int, int);

	// Getters
	void getPosition(int&, int&);
	string getName() { return _name; }
	char getTile() { return _tile; }

	int attack();
	int takeDamage(int);

	// Gets AI move command
	char getMove(int, int);

private:
	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;

	// Position
	int _x;
	int _y;
};

