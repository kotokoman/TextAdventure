#pragma once
#include "pch.h"
#include <iostream>
#include <string>

//header para criação da classe do inimgo

using namespace std;

class Enemy {

public:

	string name;
	int health, minDMG, maxDMG;
	bool enemyAlive = false;

	Enemy(string _name, int _health, int _minDMG, int _maxDMG, bool _enemyAlive);

	Enemy() {};
};