#pragma once
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

//header para criação da classe do jogador


class Player {

public:

	string name;
	int health, healthMax, hpotions, lpotions, luckyTurn, bombs, key, sword, armor, minDMG, maxDMG;
	bool playerAlive = false;

	Player(string _name, int _health, int _healthMax, int _hpotions, int _lpotions, int _luckyTurn, int _bombs, int _key, int _sword, int _minDMG, int _maxDMG, int _armor, bool _playerAlive);

	Player() {};
};