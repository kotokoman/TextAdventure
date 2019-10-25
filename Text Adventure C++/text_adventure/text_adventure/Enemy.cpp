#include "pch.h"
#include "Enemy.h"

//inicialização para classe inimigo

Enemy::Enemy(string _name, int _health, bool _enemyAlive) {

	name = _name;
	health = _health;
	enemyAlive = _enemyAlive;
}