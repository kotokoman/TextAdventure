#include "pch.h"
#include "Enemy.h"

//inicialização para classe inimigo

Enemy::Enemy(string _name, int _health, int _minDMG, int _maxDMG, bool _enemyAlive) {

	name = _name;
	health = _health;
	enemyAlive = _enemyAlive;
	minDMG = _minDMG;
	maxDMG = _maxDMG;
}