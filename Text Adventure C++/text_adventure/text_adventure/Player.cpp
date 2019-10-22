#include "pch.h"
#include "Player.h"

Player::Player(string _name, int _health, int _healthMax, int _potions, int _key, bool _playerAlive) {

	name = _name;
	health = _health;
	healthMax = _healthMax;
	potions = _potions;
	key = _key;
	playerAlive = _playerAlive;
}