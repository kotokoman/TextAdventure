#pragma once
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

//header para criação da classe do jogador


class Player {

public:

	string name;
	int health, healthMax, potions, key;
	bool playerAlive = false;

	Player(string _name, int _health, int _healthMax, int _potions, int _key, bool _playerAlive);

	Player() {};
};