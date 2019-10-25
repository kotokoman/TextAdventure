#pragma once
#include "pch.h"
#include <iostream>
#include <string>

//header para criação da classe do inimgo

using namespace std;

class Enemy {

public:

	string name;
	int health;
	bool enemyAlive = false;

	Enemy(string _name, int _health, bool _enemyAlive);

	Enemy() {};
};