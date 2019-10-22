#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Enemy.h"
#include <algorithm>

using namespace std;

Player player;
Enemy enemy;

void login() { //função de login para guardar nome do jogador e iniciar valores

	system("cls");

	cout <<
		"Player Name: \n\n"
		">";
	cin >> player.name;

	player.healthMax = 100;
	player.health = player.healthMax;
	player.potions = 0;
	player.key = 0;
	player.playerAlive = true;
	
}

void enemySorter() { //função para sortear 1 entre 4 monstros com suas respectivas vidas.
	int ind;

	string enemies[4] = { "Goblin", "Kobold", "Skeleton", "Naga"};

	ind = rand() % 3;

	enemy.name = enemies[ind];

	switch (ind){
	case 0:
		enemy.health = 35;
		break;
	case 1:
		enemy.health = 40;
		break;
	case 2:
		enemy.health = 60;
		break;
	case 3:
		enemy.health = 75;
		break;
	}

	enemy.enemyAlive = true;
}


void gameOver() { // tela de game over para retornar para o menu principal

	system("cls");

	cout <<
		"\n\n\n\n\n\n\n                                                 YOU DIED\n\n"
		"                                                     Better luck on the next time\n\n\n"
		"Press any key to return to the Main Menu";

	_getch();

	exit(0);

}

void gameEnded(){

	system("cls");

	cout <<
		"lore lore lore lore lore lore lore lore "
		"Press ANY KEY to return to the Main Menu";

	_getch();
	exit(0);

}

void loading() { //sistema fake de loading

	for (int f = 1; f <= 2; f++) {

		for (int i = 1; i <= 3; i++) {
			if (i == 1) {
				system("cls");
				cout << "                                            LOADING .";
				Sleep(400);
			}
			else if (i == 2) {
				system("cls");
				cout << "                                           LOADING . .";
				Sleep(400);
			}
			else if (i == 3) {
				system("cls");
				cout << "                                          LOADING . . .";
				Sleep(400);
			}
		}
	}

}

int UIupdater(int playerDamage, int enemyDamage) { //recebe os parametros de dano do personagem e do inimigo e desconta das vidas respectivas

	player.health -= enemyDamage;
	enemy.health -= playerDamage;

	if (enemy.enemyAlive == false) {
		enemy.name = "";
		enemy.health = 0;
	}

	return 0;
	
}

void UI() { //loader que desenha a UI para o usuario

	cout <<
		"|----------------------------------------------------------|\n"
		"| "<<player.name<<"                    | Enemy: "<<enemy.name<<"               |\n"
		"| Health: "<<player.health<<"                | Health: "<<enemy.health<<"                  |\n"
		"|----------------------------------------------------------|\n"
		"|                          ITEMS                           |\n"
		"|                                                          |\n"
		"| Health Potions: "<<player.potions<<"          | Keys: "<<player.key<<"                     |\n"
		"|----------------------------------------------------------|\n\n";
}

void enemyDrop() { // função para verificar o drop do inimigo

	system("cls");

	UIupdater(0,0);
	UI();

	cout <<
		"CONGRATULATIONS ! YOU KILLED THE ENEMY !\n\n";

	int droprand = rand() % 98 + 1;

	if (player.key == 0) {

		if (droprand <= 45) {
			cout <<
				"But it didn't drop anything...\n\n"
				"Press any key to continue . . .";

			_getch();
		}
		else if (droprand > 45 && droprand <= 75) {

			player.potions += 1;

			cout <<
				"And it dropped a Health Potion !\n\n"
				"Press any key to continue . . .";

			_getch();
		}
		else if (droprand > 75) {

			player.key += 1;

			cout <<
				"And it dropped a mysterious key... what could it be for ?\n\n"
				"Press any key to continue . . .";

			_getch();
		}
	}

	else if (player.key == 1) {

		if (droprand > 0 && droprand <= 50) {
			cout <<
				" But it didn't drop anything...\n\n"
				"Press any key to continue . . .";

			_getch();
		}
		else if (droprand > 50 && droprand <= 99) {

			player.potions += 1;

			cout <<
				" And it dropped a Health Potion !\n\n"
				"Press any key to continue . . .";

			_getch();
		}
	}

}

void Credits() { //tela de creditos

	system("cls");

	cout <<
		"                                                     CREDITS:\n\n\n"


		"                                             Inspiration: Tilen Berlak\n"
		"                                      Basically Everything Else: Yuri Kotoman\n\n\n"


		"Press any key to return to the Main Menu . . .";

	_getch();

}

void Gameplay_Combat_Enemy() {

	system("cls");

	string combatOption;

	int random, dmg;
	srand(time(NULL));

	UI();
	cout <<
		"Enemy attacking . . .";
	Sleep(2000);
	cout <<
		"\n. . .";
	Sleep(1000);
	random = rand() % 10;
	

	if (random < 6) {
		dmg = rand() % 14 + 1;
		UIupdater(0, dmg);
		cout <<
			" Your block failed. Enemy hit you by " << dmg << " damage\n\n"
			"Press ANY KEY to continue . . .";
		_getch();

		if (player.health <= 0) {

			player.playerAlive = false;
			gameOver();
		}
	}

	else {
		cout <<
			" Succesfully blocked the enemy attack\n\n"
			"Press ANY KEY to continue . . .";
		_getch();
	}
}

void Gameplay_Combat_Player() {

	int random, dmg;
	string combatOption;

	do {
		system("cls");

		srand(time(NULL));

		UI();
		cout <<
			"Type:\n"
			"	- 'punch' to damage your enemy\n"
			"	- 'heal' to use a health potion and recover 25 Health\n\n"
			">";
		cin >> combatOption;

		for_each(combatOption.begin(), combatOption.end(), [](char& c) {
			c = ::tolower(c);
		});

		if (combatOption == "punch") {
			cout <<
				"\nPunching . . .";
			Sleep(2000);
			cout <<
				"\n. . .";
			Sleep(1000);

			random = rand() % 10;

			

			if (random < 6) {
				dmg = rand() % 14 + 1;
				UIupdater(dmg, 0);
				cout <<
					" Succesfully punched the enemy dealing " << dmg << " damage\n\n"
					"Press ANY KEY to continue . . .";
				_getch();

				if (enemy.health <= 0) {
					enemy.enemyAlive = false;
					enemyDrop();
				}
				else {
					Gameplay_Combat_Enemy();
				}
			}

			else {
				cout <<
					" The enemy blocked your damage\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Enemy();
			}
		}

		else if (combatOption == "heal") {
			
			if (player.potions >= 1 && player.health<100) {

				cout <<
					"\nUsing Health Potion . . .";
				Sleep(4000);
				cout <<
					"\n. . .";
				Sleep(1000);

				if (player.health <= 75) {
					player.health += 25;
					cout <<
						" Recovered 25 HP\n\n"
						"Press ANY KEY to continue . . .";
					_getch();
					Gameplay_Combat_Enemy();
				}
				else {
					int healthDif = player.healthMax - player.health;

					player.health += healthDif;
					cout <<
						" Recovered " << healthDif << " HP\n\n"
						"Press ANY KEY to continue . . .";
					_getch();
					Gameplay_Combat_Enemy();
				}

				player.potions -= 1;
			}

			else if (player.health == 100) {
				cout <<
					"\nYour health is full\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();
			}

			else {
				cout <<
					"\nYou have no potions left\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();
			}
			
		}

		else {
			cout << "\nInvalid Option";
			Sleep(600);
			Gameplay_Combat_Player();
		}
	} while (enemy.enemyAlive == true);
}

void walkSorter() {

	int rnd, rnd2, qtdPotions;

	rnd = rand() % 29 + 1;

	if (rnd <= 10) {
		cout <<
			" But nothing happened\n\n"
			"Press ANY KEY to continue . . .";
		_getch();
		
	}
	else if (rnd > 10 && rnd <= 20) {
		cout <<
			"You found an open door...";

		rnd2 = rand() % 49 + 1;

		if (rnd2 <= 25) {
			enemySorter();
			cout <<
				" WITH AN ENEMY INSIDE\n\n"
				"Press ANY KEY to continue . . .";
			_getch();
			Gameplay_Combat_Player();
		}
		else {

			qtdPotions = rand() % 5 + 1;

			cout <<
				" WITH A CHEST INSIDE IT CONTAINING " << qtdPotions << " HEALTH POTIONS\n\n"
				"Press ANY KEY to continue . . .";
			_getch();

			player.potions += qtdPotions;

		}
	}

	else if (rnd > 20) {
		cout <<
			"YOU FOUND A SECRET DOOR... But it's locked...\n\n"
			"Press ANY KEY to continue . . .";
		_getch();

		if (player.key == 1) {
			gameEnded();
		}
	}

}


void Gameplay_Walk() {

	do {

		system("cls");

		srand(time(NULL));

		string walkOption;
		
		UI();
		cout <<
			"Type:\n"
			"	- 'walk' to move forward\n"
			"	- 'rest' to recover your full health for (missing health/2) seconds.\n\n"
			">";
		cin >> walkOption;

		for_each(walkOption.begin(), walkOption.end(), [](char& c) {
			c = ::tolower(c);
		});

		if (walkOption == "walk") {
			cout <<
				"\nWalking . . .";
			Sleep(2000);
			cout <<
				"\n. . .";
			Sleep(1000);
			walkSorter();
		}

		else if (walkOption == "rest") {

			if (player.health < 100) {

				int healthDif = player.healthMax - player.health;
				for (int i = healthDif / 2; i >= 0; i--) {
					system("cls");
					UI();
					cout <<
						"\nResting . . . "<<i<<" Seconds";
					Sleep(1000);
				}
				cout <<
					"\n. . .";
				Sleep(1000);
								
				player.health += healthDif;
				cout <<
					" Recovered " << healthDif << " HP\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Walk();
				
			}

			else if (player.health == 100) {
				cout <<
					"\nYour health is full\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Walk();
			}

		}

		else if (walkOption == "fefo" && player.key == 0) {
			
			player.potions += 99;
			player.key += 1;
			
			cout <<
				"\nYou obtained 99 Health Potions and a Secret Key from the cheat code 'fefo' \n\n"
				"Press ANY KEY to continue . . .";
			_getch();

			Gameplay_Walk();
		}

		else {
			cout << "\nInvalid Option";
			Sleep(600);
			Gameplay_Walk();
		}

	} while (player.playerAlive == true && enemy.enemyAlive == false);
}

void Start() {

	loading();

	login();

	system("cls");
	cout <<
		"	- H-How did I end up here? W-What's going on?\n\n"

		"	You were sleeping, and, when you woke up, you were inside a dark dungeon, lighten up only by torches. "
		"The walls made of an old type of stone, wet, covered with moss...\n\n"

		"Press ANY KEY to continue . . .";
	_getch();

	system("cls");
	cout <<
		"	The only thing you knew, is that you had to get out of there, and the only path to follow is forward...\n\n"

		"	And you have a long way to go...\n\n"

		"Press ANY KEY to continue . . .";
	_getch();

	system("cls");
	loading();

	Gameplay_Walk();
}

int main(){
	int gameOn = 0, menuChoice = 0;

	do {
		system("cls");

		cout << "                                             TEXT ADVENTURE SENAC\n\n\n";
		cout <<
			"MAIN MENU\n\n"

			"1. Start\n"
			"2. Credits\n"
			"3. Exit\n"
			">";

		cin >> menuChoice;

		switch (menuChoice) {

		case 1:
			gameOn = 1;
			Start();
			break;
		case 2:
			Credits();
			break;
		case 3:
			exit(0);
		default:
			cout << "Invalid Option";
			Sleep(600);
			main();
		}
	} while (gameOn == 0);
}