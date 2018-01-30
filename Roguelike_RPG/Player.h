#pragma once
#include <random>
#include <ctime>

using std::default_random_engine;
using std::uniform_int_distribution;

class Player
{
public:
	Player();
	void init(int, int, int, int, int);

	int attack();
	int takeDamage(int);

	// Setters
	void setPosition(int, int);
	void addExperience(int);

	// Getters
	void getPosition(int&, int&);

private:
	// Properties
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;

	// Position
	int _x;
	int _y;
};

