#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <limits>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Enemy.h"
#include <algorithm>
#include <cctype>

using namespace std;


Player player;    //
Enemy enemy;      // instância para classes de player e inimigo

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------LOGIN----------------------

void login() { //função de login para guardar nome do jogador e resetar atributos do jogador

	system("cls");

	cout <<
		"  Player Name: \n\n"
		"  >";
	cin >> player.name;

	player.healthMax = 100;
	player.health = player.healthMax;
	player.hpotions = 0;
	player.lpotions = 0;
	player.luckyTurn = 0;
	player.bombs = 0;
	player.key = 0;
	player.sword = 0;
	player.armor = 0;
	player.playerAlive = true;
	enemy.health = 0;
	enemy.minDMG = 0;
	enemy.maxDMG = 0;
	player.minDMG = 1;
	player.maxDMG = 9;
	
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ENEMYSORTER----------------

void enemySorter() { //função para sortear 1 entre 8 monstros com suas respectivas vidas.

	int ind;

	srand(time(NULL));

	ind = rand() % 99 + 1;   //randomiza o indice de 'enemies'

	if (ind <= 23) {
		enemy.name = "Slime";
		enemy.health = 15;
		enemy.minDMG = 1;
		enemy.maxDMG = 4;
	}
	else if (ind > 23 && ind <= 42) {
		enemy.name = "Goblin";
		enemy.health = 35;
		enemy.minDMG = 4;
		enemy.maxDMG = 4;
	}
	else if (ind > 42 && ind <= 58) {
		enemy.name = "Kobold";
		enemy.health = 45;
		enemy.minDMG = 9;
		enemy.maxDMG = 6;
	}
	else if (ind > 58 && ind <= 70) {
		enemy.name = "Skeleton";
		enemy.health = 60;
		enemy.minDMG = 13;
		enemy.maxDMG = 7;
	}
	else if (ind > 70 && ind <= 80) {
		enemy.name = "Naga";
		enemy.health = 80;
		enemy.minDMG = 17;
		enemy.maxDMG = 8;
	}
	else if (ind > 80 && ind <= 88) {
		enemy.name = "Hell Hound";
		enemy.health = 100;
		enemy.minDMG = 27;
		enemy.maxDMG = 13;
	}
	else if (ind > 88 && ind <= 95) {
		enemy.name = "Banshee";
		enemy.health = 140;
		enemy.minDMG = 30;
		enemy.maxDMG = 20;
	}
	else if (ind > 95) {
		enemy.name = "Hydra";
		enemy.health = 500;
		enemy.minDMG = 180;
		enemy.maxDMG = 20;
	}

	enemy.enemyAlive = true;     // seta o inimigo para vivo
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------GAMEOVER-------------------

void gameOver() {     // tela de final de jogo quando o player morre. encerra o jogo

	system("cls");

	cout <<
		"\n                                                              YOU DIED\n\n"
		"                                                     Better luck on the next time\n\n\n"
		"  Press ANY KEY to exit the game . . .";

	_getch();

	exit(0);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------GAMEENDED------------------

void gameEnded(){    // tela de final de jogo para quando o jogador encontra uma chave e desbloqueia a porta secreta. encerra o jogo

	system("cls");

	cout <<
		"\n       After an exhausting journey through the long, long corridor of death, you manage to escape alive just to find out\n"
		"  that everything outside was swallowed by the darkness, and the place you escaped was actually keeping you alive . . .\n\n\n"
		"  Press ANY KEY to exit the game . . .";

	_getch();
	exit(0);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------LOADING--------------------

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------HEALTHUPDATER--------------

int healthUpdater(int playerDamage, int enemyDamage) { //recebe os parametros de dano do personagem e do inimigo e desconta das vidas respectivas

	player.health -= enemyDamage;
	enemy.health -= playerDamage;

	if (enemy.enemyAlive == false) {   //reseta a UI caso o inimigo morra
		enemy.name = "";
		enemy.health = 0;
	}

	return 0;
	
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------UI-------------------------

void UI() { //loader que desenha e atualiza a UI para o usuario

	cout <<
		"  |----------------------------------------------------------|\n"
		"  | "<<player.name<<"                    | Enemy: "<<enemy.name<<"               |\n"
		"  | Health: "<<player.health<<"                | Health: "<<enemy.health<<"                  |\n"
		"  |----------------------------------------------------------|\n"
		"  |                          ITEMS                           |\n"
		"  |                                                          |\n"
		"  | Health Potions: "<<player.hpotions<<"          | Lucky Potions: "<<player.lpotions<<"            |\n"
		"  | Bombs: " << player.bombs << "                   | Secret Key: " << player.key << "               |\n"
		"  | Sword: +"<< player.sword <<"                  | Armor: +"<< player.armor <<"                   | \n"
		"  |----------------------------------------------------------|\n\n";
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ENEMYDROP------------------

void enemyDrop() { // função para verificar o que o inimigo vai dropar aleatoriamente quando morrer

	system("cls");
	
	player.luckyTurn = 0;
	UI();                //atualiza a UI

	cout <<
		"  Congratulations ! You killed the enemy "<<enemy.name<<" !\n\n";

	srand(time(NULL));
	int droprand = rand() % 99 + 1;

	if (enemy.name == "Hydra" && player.key == 0) {
		
		player.key++;

		cout <<
			"  And it dropped a SECRET KEY ! I wonder what it could be used for...\n\n"
			"  Press ANY KEY to continue . . .";

		_getch();
		healthUpdater(0, 0);   //reseta o nome e hp do inimigo
	}
	else {
	
		if (droprand <= 25) {
			cout <<
				"  But it didn't drop anything...\n\n"
				"  Press ANY KEY to continue . . .";

			_getch();
			healthUpdater(0, 0);   //reseta o nome e hp do inimigo
		}
		else if (droprand > 25 && droprand <= 60) {

			player.hpotions ++;
			player.lpotions++;

			cout <<
				"  And it dropped 1 Health Potion and 1 Lucky Potion !\n\n"
				"  Press ANY KEY to continue . . .";

			_getch();
			healthUpdater(0, 0);   //reseta o nome e hp do inimigo
		}
		else if (droprand > 60 && droprand <= 80) {

			if (player.sword == 0) {

				player.sword++;
				player.minDMG = 10;
				player.maxDMG = 10;
			}
			else if (player.sword > 0) {
				player.sword++;
				player.minDMG += 10;
			}

			cout <<
				"  And it dropped a Sword ! Your damage was increased by 10 points !\n\n"
				"  Press ANY KEY to continue . . .";

			_getch();
			healthUpdater(0, 0);   //reseta o nome e hp do inimigo
		}
		else if (droprand > 80) {

			player.armor ++;
			player.healthMax += 20;
			player.health += 20;

			cout <<
				"  And it dropped an Armor ! Your maximum health and actual health were increased by 20 points !\n\n"
				"  Press ANY KEY to continue . . .";

			_getch();
			healthUpdater(0, 0);   //reseta o nome e hp do inimigo
		}
	}
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------COMBAT_ENEMY---------------

void Gameplay_Combat_Enemy() {    //função que executa o turno de combate do inimigo

	system("cls");

	int hitRandom, enemyDMG;
	srand(time(NULL));

	UI();

	cout <<
		"  Enemy attacking . . .";
	Sleep(1000);
	cout <<
		"\n  . . .";
	Sleep(700);

	hitRandom = rand() % 10;  //randomiza a chance do inimigo acertar ou não o golpe no player
	

	if (hitRandom < 5) {

		srand(time(NULL));
		enemyDMG = rand() % enemy.maxDMG + enemy.minDMG;    // randomiza o dano do inimigo

		healthUpdater(0, enemyDMG);      //atualiza a vida do jogador com base no dano do inimigo
		if (enemyDMG == (enemy.minDMG + enemy.maxDMG)) {
			cout << "\n LUCKY STRIKE ! ! !\n";
		}
		if (enemyDMG == enemy.minDMG) {
			cout << "\n AWFUL MISFORTUNE . . .\n";
		}
		cout <<
			" Your block failed. Enemy hit you by " << enemyDMG << " damage\n\n"
			"  Press ANY KEY to continue . . .";
		_getch();
		
		if (player.health <= 0) {     //se a vida do jogador <= 0, seta jogador para morto e executa a tela de gameover

			player.playerAlive = false;
			gameOver();
		}

	}

	else {

		cout <<
			" Succesfully blocked the enemy attack\n\n"
			"  Press ANY KEY to continue . . .";
		_getch();

	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------COMBAT_PLAYER--------------

void Gameplay_Combat_Player() {

	int hitRandom, playerDMG, bombDMG = 30;
	string combatOption;

	do {

		system("cls");

		srand(time(NULL));

		UI();

		cout <<
			"  Type:\n"
			"     - 'attack' to damage your enemy\n"
			"     - 'heal' to use a health potion\n"
			"     - 'lucky' to use a lucky potion\n"
			"     - 'bomb' to throw a bomb at the enemy\n\n"
			"  >";
		cin >> combatOption;          //pega a opção do jogador (punch ou heal)

		for_each(combatOption.begin(), combatOption.end(), [](char& c) {  //
			c = ::tolower(c);                                             //
		});                                                               //  método para percorrer todos os caracteres da variavel combatOption e transformar eles em lower case (minusculo)

		if (combatOption == "attack") {         //se o usuario escolher golpear o inimigo

			if (player.sword == 0) {

				cout <<
					"\n  Punching . . .";
				Sleep(1000);
				cout <<
					"\n  . . .";
				Sleep(700);

				if (player.luckyTurn > 0) {
					hitRandom = 1;
				}
				else {
					srand(time(NULL));
					hitRandom = rand() % 10;    //randomiza a sorte do jogador de acertar ou errar o golpe no inimigo
				}
				
				if (hitRandom <= 6) {

					srand(time(NULL));

					playerDMG = rand() % player.maxDMG + player.minDMG;          //randomiza o dano do jogador

					healthUpdater(playerDMG, 0);         //atualiza a vida do inimigo com base no dano do jogador
					if (playerDMG == (player.maxDMG + player.minDMG)) {
						cout << "\n LUCKY STRIKE ! ! !\n";
					}
					if (playerDMG == player.minDMG) {
						cout << "\n AWFUL MISFORTUNE . . .\n";
					}
					if (player.luckyTurn > 0) {
						player.luckyTurn--;
						cout <<
							" Succesfully punched the enemy dealing " << playerDMG << " damage\n"
							"  Lucky potion turns remaining: " << player.luckyTurn << "\n"
							"  Press ANY KEY to continue . . .";
						_getch();
					}
					else {
						cout <<
							" Succesfully punched the enemy dealing " << playerDMG << " damage\n\n"
							"  Press ANY KEY to continue . . .";
						_getch();
					}

					if (enemy.health <= 0) {     //se a vida do inimigo <= 0, seta ele para morto e chama a tela para verificar o drop

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
						"  Press ANY KEY to continue . . .";
					_getch();
					Gameplay_Combat_Enemy();

				}
			}
			else if (player.sword > 0) {
				
				cout <<
					"\n  Slashing . . .";
				Sleep(1000);
				cout <<
					"\n  . . .";
				Sleep(700);

				if (player.luckyTurn > 0) {
					hitRandom = 1;
				}
				else {
					srand(time(NULL));
					hitRandom = rand() % 10;    //randomiza a sorte do jogador de acertar ou errar o golpe no inimigo
				}

				if (hitRandom <= 6) {

					playerDMG = rand() % player.maxDMG + player.minDMG;          //randomiza o dano do jogador

					healthUpdater(playerDMG, 0);         //atualiza a vida do inimigo com base no dano do jogador
					if (playerDMG == (player.maxDMG + player.minDMG)) {
						cout << "\n LUCKY STRIKE ! ! !\n";
					}
					if (playerDMG == player.minDMG) {
						cout << "\n AWFUL MISFORTUNE . . .\n";
					}
					if (player.luckyTurn > 0) {
						player.luckyTurn--;
						cout <<
							" Succesfully slashed the enemy dealing " << playerDMG << " damage\n"
							"  Lucky potion turns remaining: " << player.luckyTurn << "\n"
							"  Press ANY KEY to continue . . .";
						_getch();
					}
					else {
						cout <<
							" Succesfully slashed the enemy dealing " << playerDMG << " damage\n\n"
							"  Press ANY KEY to continue . . .";
						_getch();
					}
					
					if (enemy.health <= 0) {     //se a vida do inimigo <= 0, seta ele para morto e chama a tela para verificar o drop

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
						"  Press ANY KEY to continue . . .";
					_getch();
					Gameplay_Combat_Enemy();

				}
			}
		}


		else if (combatOption == "heal") {        // se o usuario escolher se curar
			
			if (player.hpotions >= 1 && player.health<100) {   //verifica o numero de poçoes restantes e se o jogador perdeu vida

				cout <<
					"\n  Using Health Potion . . .";
				Sleep(2300);
				cout <<
					"\n  . . .";
				Sleep(700);


				//recupera 25 de vida do jogador até 75 de hp. se o hp for maior de 75, calcula a vida restante até a vida maxima do jogador e recupera.

				if (player.health <= 75) {

					player.health += 25;
					cout <<
						" Recovered 25 HP\n\n"
						"  Press ANY KEY to continue . . .";
					_getch();
					Gameplay_Combat_Enemy();

				}

				else {

					int healthDif = player.healthMax - player.health;

					player.health += healthDif;
					cout <<
						"   Recovered " << healthDif << " HP\n\n"
						"  Press ANY KEY to continue . . .";
					_getch();
					Gameplay_Combat_Enemy();

				}

				player.hpotions--;

			}

			else if (player.health == 100) {       // se o player estiver com a vida cheia

				cout <<
					"\n  Your health is full\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();

			}

			else {       //se o player nao tiver mais poçoes restantes

				cout <<
					"\n  You have no health potions left\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();

			}
			
		}

		else if (combatOption == "lucky") {

			if (player.lpotions >= 1 && player.luckyTurn <=0) {   //verifica o numero de poçoes restantes e se o jogador não está com poção sendo utilizada

				cout <<
					"\n  Using Lucky Potion . . .";
				Sleep(1000);
				cout <<
					"\n  . . .";
				Sleep(700);


				//Adiciona 3 turnos de 100% de chance de acerto de golpe no inimigo.

				player.luckyTurn += 3;
				player.lpotions--;

				cout <<
					" Added 3 turns with 100% chance of hitting the enemy\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();				
			
			}

			else if (player.luckyTurn > 0) {       // se o player estiver com turnos de sorte

				cout <<
					"\n  You already have a lucky potion being used\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();

			}

			else {       //se o player nao tiver mais poçoes restantes

				cout <<
					"\n  You have no lucky potions left\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();

			}
		}
		else if (combatOption == "bomb") {

			if (player.bombs >= 1) {   //verifica o numero de poçoes restantes e se o jogador não está com poção sendo utilizada

				cout <<
					"\n  Throwing bomb at the enemy . . .";
				Sleep(1000);
				cout <<
					"\n  . . .";
				Sleep(700);

				enemy.health -= bombDMG;
				player.bombs--;
				cout <<
					" Succesfully threw a bomb at the enemy dealing " << bombDMG << " damage\n"
					"  Press ANY KEY to continue . . .";
				_getch();

				if (enemy.health <= 0) {     //se a vida do inimigo <= 0, seta ele para morto e chama a tela para verificar o drop

					enemy.enemyAlive = false;
					enemyDrop();

				}
				else {

					Gameplay_Combat_Enemy();

				}

			}
			else {
				cout <<
					"\n  You have no bombs left\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();
			}
		}

		else {

			cout << "\n  Invalid Option";
			Sleep(600);
			Gameplay_Combat_Player();

		}

	} while (enemy.enemyAlive == true);        // executar todo o codigo enquanto o inimigo ainda estiver vivo
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------WALKSORTER-----------------

void walkSorter() {         // função para sortear o que acontece quando o jogador escolhe caminhar no jogo

	int randomCaminho, randomOpenDoorInside, randomChestObject, randomQtdHPotions, randomQtdLPotions, randomQtdBombs;
	srand(time(NULL));

	randomCaminho = rand() % 29 + 1;    //randomizador de caminhos

	if (randomCaminho <= 10) {      //nao aconteceu/encontrou nada

		cout <<
			" But you found nothing.\n\n"
			"  Press ANY KEY to continue . . .";
		_getch();
		
	}
	else if (randomCaminho > 10 && randomCaminho <= 20) {   //encontrou uma porta aberta

		cout << " You found an open door...";

		srand(time(NULL));

		randomOpenDoorInside = rand() % 49 + 1;   //randomizador para definir o que o usuario encontrará ao abrir a porta

		if (randomOpenDoorInside <= 25) {      //encontrou um inimigo

			enemySorter();
			cout <<
				" WITH AN ENEMY INSIDE\n\n"
				"  Press ANY KEY to continue . . .";
			_getch();
			Gameplay_Combat_Player();

		}
		else {     //encontrou um baú 

			srand(time(NULL));

			randomChestObject = rand() % 99 + 1;

			if (randomChestObject <= 59) {

				srand(time(NULL));

				randomQtdHPotions = rand() % 5 + 1;       //randomizador de quantidade de poções encontradas de 1 a 6

				cout <<
					" WITH A CHEST INSIDE IT CONTAINING " << randomQtdHPotions << " HEALTH POTIONS\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();

				player.hpotions += randomQtdHPotions;

			}
			else if (randomChestObject > 59 && randomChestObject <= 84) {

				srand(time(NULL));

				randomQtdLPotions = rand() % 3 + 1;       //randomizador de quantidade de poções encontradas de  a 4

				cout <<
					" WITH A CHEST INSIDE IT CONTAINING " << randomQtdLPotions << " LUCKY POTIONS\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();

				player.lpotions += randomQtdLPotions;

			}
			else if (randomChestObject > 84) {

				srand(time(NULL));

				randomQtdBombs = rand() % 1 + 1;       //randomizador de quantidade de poções encontradas de 1 a 2

				cout <<
					" WITH A CHEST INSIDE IT CONTAINING " << randomQtdBombs << " BOMBS\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();

				player.bombs += randomQtdBombs;

			}
		}
	}

	else if (randomCaminho > 20) {         //encontrou uma porta secreta trancada

		cout <<
			" YOU FOUND A SECRET DOOR... But it's locked...\n\n"
			"  Press ANY KEY to continue . . .";
		_getch();

		if (player.key == 1) {      // se o jogador já tiver a chave termina o jogo

			gameEnded();

		}

	}

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------WALK-----------------------

void Gameplay_Walk() {

	do {

		system("cls");
		
		int healthDif;
		string walkOption;
		
		UI();        //atualiza a UI

		cout <<
			"  Type:\n"
			"     - 'walk' to move forward\n"
			"     - 'rest' to recover your full health for (missing health/2) seconds.\n\n"
			"  >";
		cin >> walkOption;             // recebe a opção do jogador

		for_each(walkOption.begin(), walkOption.end(), [](char& c) {      //
			c = ::tolower(c);                                             //
		});                                                               //  método para percorrer todos os caracteres da variavel walkOption e transformar eles em lower case (minusculo)

		if (walkOption == "walk") {         //se o jogador caminhar, chama a variavel para definir o que acontece

			cout <<
				"\n  Walking . . .";
			Sleep(1000);
			cout <<
				"\n  . . .";
			Sleep(700);

			walkSorter();

		}

		else if (walkOption == "rest") {          //se o jogador escolher descansar

			if (player.health < player.healthMax) {

				healthDif = player.healthMax - player.health;     //calcula a diferença de HP para recuperar

				for (int i = healthDif / 2; i >= 0; i--) {        //descansa por (diferença de HP/2) segundos

					system("cls");
					UI();
					cout <<
						"\n  Resting . . . "<<i<<" Seconds";
					Sleep(1000);

				}

				cout <<
					"\n  . . .";
				Sleep(700);
								
				player.health += healthDif;     //acrescenta na vida do jogador

				cout <<
					" Recovered " << healthDif << " HP\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Walk();
				
			}

			else if (player.health == player.healthMax) {     //não descansa se a vida do jogador estiver cheia

				cout <<
					"\n  Your health is full\n\n"
					"  Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Walk();

			}

		}

		else if (walkOption == "getallofit") {           // código para testes de poções, bombas e equipamentos
			
			player.hpotions += 99;
			player.lpotions += 99;
			player.bombs += 99;
			player.sword += 99;
			player.minDMG = 10*99;
			player.maxDMG = 10;
			player.armor += 99;
			player.healthMax += 20*99;
			player.health = player.healthMax;
			
			cout <<
				"\n  You obtained 99 Health Potions, 99 Lucky Potions, 99 Bombs, a Sword and an Armor from the cheat code 'getallofit' \n\n"
				"  Press ANY KEY to continue . . .";
			_getch();

			Gameplay_Walk();
		}
		else if (walkOption == "annacarolanna") {           // código para testes de poções, bombas e equipamentos

			player.hpotions += 43;
			player.lpotions += 20;
			player.bombs += 4;
			player.sword += 5;
			player.minDMG = 10 * 5;
			player.maxDMG = 10;
			player.armor += 11;
			player.healthMax += 20 * 11;
			player.health = player.healthMax;

			cout <<
				"\n  SAVE SUCCESFULLY LOADED \n\n"
				"  Press ANY KEY to continue . . .";
			_getch();

			Gameplay_Walk();
		}

		else if (walkOption == "getsecretkey") {           // código para testes de chave

			player.key = 1;

			cout <<
				"\n  You obtained a Secret Key from the cheat code 'getsecretkey' \n\n"
				"  Press ANY KEY to continue . . .";
			_getch();

			Gameplay_Walk();
		}

		else {

			cout << "\n  Invalid Option";
			Sleep(600);
			Gameplay_Walk();

		}

	} while (player.playerAlive == true && enemy.enemyAlive == false);         //executar o codigo enquanto o player estiver vivo e o inimigo morto/não encontrado
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------START----------------------

void Start() {         // função com um pouco de lore do jogo. executado após o usuario escolher a opção 1 no Main Menu. chama o login, conta o lore e chama a gameplay

	loading();

	login();

	system("cls");
	cout <<
		"  	- H-How did I end up here? W-What's going on?\n\n"

		"	  You were sleeping, and, when you woke up, you were inside a dark dungeon, lighten up only by torches. "
		"  The walls made of an old type of stone, wet, covered with moss...\n\n"

		"  Press ANY KEY to continue . . .";
	_getch();

	system("cls");
	cout <<
		"	  The only thing you knew, is that you had to get out of there, and the only path to follow is forward...\n\n"

		"	  And you have a long way to go...\n\n"

		"  Press ANY KEY to continue . . .";
	_getch();

	system("cls");
	loading();

	Gameplay_Walk();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------CREDITS--------------------

void Credits() { //tela de creditos do menu principal

	system("cls");

	cout <<
		"                                                     CREDITS:\n\n\n"


		"                                             Inspiration: Tilen Berlak\n"
		"                                      Basically Everything Else: Yuri Kotoman\n\n\n"


		"  Press ANY KEY to return to the Main Menu . . .";

	_getch();

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------CREDITS--------------------

void Rules() { //tela de creditos do menu principal

	system("cls");

	cout <<
		"                                                      RULES:\n\n\n"

		"                                                  WHILE WALKING:\n\n"

		"                               1. You have a 33% chance of finding nothing when walking.\n"
		"                               2. You have a 33% chance of finding an open door when walking.\n"
		"                               3. You have a 33% chance of finding a secret locked door when walking.\n"
		"                               4. You have a 50% chance of finding an enemy on the open door when walking.\n"
		"                               5. You have a 50% chance of finding a chest on the open door when walking.\n"

		"                                                    ENEMIES:\n\n"

		"                               1. Slime - Health: 15 - Damage: 1-5 - 23% chances of appearing.\n"
		"                               2. Goblin - Health: 35 - Damage: 4-8 - 19% chances of appearing.\n"
		"                               3. Kobold - Health: 45 - Damage: 9-15 - 16% chances of appearing.\n"
		"                               4. Skeleton - Health: 60 - Damage: 13-20 - 12% chances of appearing.\n"
		"                               5. Naga - Health: 80 - Damage: 17-25 - 10% chances of appearing.\n"
		"                               6. Hell Hound - Health: 100 - Damage: 27-40 - 8% chances of appearing.\n"
		"                               7. Banshee - Health: 140 - Damage: 30-50 - 7% chances of appearing.\n"
		"                               8. Hydra - Health: 200 - Damage: 80-100 - 5% chances of appearing.\n\n\n"
		 
		"                                                 WHILE ON COMBAT:\n\n"

		"                               1. You have a 60% chance of hitting the enemy.\n"
		"                               2. You have a 40% chance of your attack get blocked by the enemy.\n"
		"                               3. The enemy has a 40% chance of hitting you.\n"
		"                               4. The enemy has a 60% chance of getting its attack blocked by you.\n\n\n"

		"                                                    ITEMS:\n\n"

		"                               1. Health Potions:\n"
		"                                   Heals you for 25 health points. Loses one turn.\n"
		"                               2. Lucky Potions:\n"
		"                                   Increases your chances of hitting an enemy to 100% for 3 turns.\n"
		"                               3. Bombs:\n"
		"                                   Throw a bomb at the enemy dealing 30 damage. Cannot be blocked.\n"
		"                               4. Secret Key:\n"
		"                                   Unlocks a Secret Door.\n"
		"                               5. Sword:\n"
		"                                   Each sword stack increases your minimum damage and maximum damage by 10 points. Your initial damage is 1-10 points.\n"
		"                               6. Armor:\n"
		"                                   Each stack increases your Max Health by 20 points and heals you for 20 points.\n\n\n"
		
		"                                                  CHEST DROPS:\n\n"

		"                               1. The chest has a 60% chance of containing from 1 to 6 Health Potions inside.\n"
		"                               2. The chest has a 25% chance of containing from 1 to 4 Lucky Potions inside.\n"
		"                               3. The chest has a 15% chance of containing from 1 to 2 Bombs inside.\n\n\n"
		
		"                                                  ENEMY'S DROPS:\n\n"

		"                               1. You have 35% chances of dropping 1 Health Potion and 1 Lucky Potion.\n"		
		"                               2. You have 25% chances of dropping nothing.\n"
		"                               3. You have 20% chances of dropping a Sword.\n"
		"                               4. You have 20% chances of dropping an Armor.\n"
		"                               5. If you kill the Hydra and don't have a secret key yet, you'll drop a Secret Key.\n\n\n"

		"  Press ANY KEY to return to the Main Menu . . .";

	_getch();

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------MAIN-----------------------

int main(){       //Main Menu que redireciona para as telas de cada opção

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	int gameOn = 0, menuChoice = 0;
	
	do {

		system("cls");

		cout << "                                                   TEXT ADVENTURE\n\n\n";
		cout <<
			"  MAIN MENU\n\n"

			"  1. Start\n"
			"  2. Rules\n"
			"  3. Credits\n"
			"  4. Exit\n"
			"  >";

		while (!(cin >> menuChoice)) {
			cin.clear();
			cin.ignore(123, '\n');
			cout << "   Please, enter a number!";
			Sleep(1000);
			main();
		}

		switch (menuChoice) {

		case 1:
			gameOn = 1;
			Start();
			break;
		case 2:
			Rules();
			break;
		case 3:
			Credits();
			break;
		case 4:
			exit(0);
		default:
			cout << "  Invalid Option";
			Sleep(600);
			main();
		}

	} while (gameOn == 0);     // executar o codigo enquanto o jogador não startar o jogo

}