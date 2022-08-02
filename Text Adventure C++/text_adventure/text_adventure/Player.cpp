#include "pch.h"
#include "Player.h"

//inicialização da classe player

Player::Player(string _name, int _health, int _healthMax, int _hpotions, int _minDMG, int _maxDMG, int _lpotions, int _luckyTurn, int _bombs, int _key, int _sword, int _armor, bool _playerAlive) {

	name = _name;
	health = _health;
	healthMax = _healthMax;
	hpotions = _hpotions;
	lpotions = _lpotions;
	luckyTurn = _luckyTurn;
	bombs = _bombs;
	key = _key;
	sword = _sword;
	minDMG = _minDMG;
	maxDMG = _maxDMG;
	armor = _armor;
	playerAlive = _playerAlive;
}