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

Player player;    //
Enemy enemy;      // instancia para classes de player e inimigo

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------LOGIN----------------------

void login() { //função de login para guardar nome do jogador e resetar atributos do jogador

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ENEMYSORTER----------------

void enemySorter() { //função para sortear 1 entre 4 monstros com suas respectivas vidas.
	int ind;

	string enemies[4] = { "Goblin", "Kobold", "Skeleton", "Naga"};

	ind = rand() % 3;   //randomiza o indice do vetor 'enemies'

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

	enemy.enemyAlive = true;     // seta o inimigo para vivo
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------GAMEOVER-------------------

void gameOver() {     // tela de final de jogo quando o player morre. encerra o jogo

	system("cls");

	cout <<
		"\n\n\n\n\n\n\n                                                 YOU DIED\n\n"
		"                                                     Better luck on the next time\n\n\n"
		"Press any key to return to the Main Menu";

	_getch();

	exit(0);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------GAMEENDED------------------

void gameEnded(){    // tela de final de jogo para quando o jogador encontra uma chave e desbloqueia a porta secreta. encerra o jogo

	system("cls");

	cout <<
		"lore lore lore lore lore lore lore lore \n\n\n"
		"Press ANY KEY to return to the Main Menu";

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
		"|----------------------------------------------------------|\n"
		"| "<<player.name<<"                    | Enemy: "<<enemy.name<<"               |\n"
		"| Health: "<<player.health<<"                | Health: "<<enemy.health<<"                  |\n"
		"|----------------------------------------------------------|\n"
		"|                          ITEMS                           |\n"
		"|                                                          |\n"
		"| Health Potions: "<<player.potions<<"          | Keys: "<<player.key<<"                     |\n"
		"|----------------------------------------------------------|\n\n";
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ENEMYDROP------------------

void enemyDrop() { // função para verificar o que o inimigo vai dropar aleatoriamente quando morrer

	system("cls");

	healthUpdater(0,0);   //reseta o nome e hp do inimigo
	UI();                //atualiza a UI

	cout <<
		"CONGRATULATIONS ! YOU KILLED THE ENEMY !\n\n";

	int droprand = rand() % 98 + 1;

	if (player.key == 0) {  // drops se o player ainda não tiver a chave

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

	else if (player.key == 1) {      // drops se o player já tiver a chave

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------CREDITS--------------------

void Credits() { //tela de creditos do menu principal

	system("cls");

	cout <<
		"                                                     CREDITS:\n\n\n"


		"                                             Inspiration: Tilen Berlak\n"
		"                                      Basically Everything Else: Yuri Kotoman\n\n\n"


		"Press any key to return to the Main Menu . . .";

	_getch();

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------COMBAT_ENEMY---------------

void Gameplay_Combat_Enemy() {    //função que executa o turno de combate do inimigo

	system("cls");

	int hitRandom, enemyDMG;

	UI();

	cout <<
		"Enemy attacking . . .";
	Sleep(1000);
	cout <<
		"\n. . .";
	Sleep(700);

	hitRandom = rand() % 10;  //randomiza a chance do inimigo acertar ou não o golpe no player
	

	if (hitRandom < 6) {

		enemyDMG = rand() % 14 + 1;    // randomiza o dano do inimigo de 1 a 15

		healthUpdater(0, enemyDMG);      //atualiza a vida do jogador com base no dano do inimigo

		cout <<
			" Your block failed. Enemy hit you by " << enemyDMG << " damage\n\n"
			"Press ANY KEY to continue . . .";
		_getch();

		if (player.health <= 0) {     //se a vida do jogador <= 0, seta jogador para morto e executa a tela de gameover

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------COMBAT_PLAYER--------------

void Gameplay_Combat_Player() {

	int hitRandom, playerDMG;
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
		cin >> combatOption;          //pega a opção do jogador (punch ou heal)

		for_each(combatOption.begin(), combatOption.end(), [](char& c) {  //
			c = ::tolower(c);                                             //
		});                                                               //  método para percorrer todos os caracteres da variavel combatOption e transformar eles em lower case (minusculo)

		if (combatOption == "punch") {         //se o usuario escolher golpear o inimigo

			cout <<
				"\nPunching . . .";
			Sleep(1000);
			cout <<
				"\n. . .";
			Sleep(700);

			hitRandom = rand() % 10;    //randomiza a sorte do jogador de acertar ou errar o golpe no inimigo

			if (hitRandom < 6) {

				playerDMG = rand() % 14 + 1;          //randomiza o dano do jogador de 1 a 15

				healthUpdater(playerDMG, 0);         //atualiza a vida do inimigo com base no dano do jogador

				cout <<
					" Succesfully punched the enemy dealing " << playerDMG << " damage\n\n"
					"Press ANY KEY to continue . . .";
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
					" The enemy blocked your damage\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Enemy();

			}
		}

		else if (combatOption == "heal") {        // se o usuario escolher se curar
			
			if (player.potions >= 1 && player.health<100) {   //verifica o numero de poçoes restantes e se o jogador perdeu vida

				cout <<
					"\nUsing Health Potion . . .";
				Sleep(2300);
				cout <<
					"\n. . .";
				Sleep(700);


				//recupera 25 de vida do jogador até 75 de hp. se o hp for maior de 75, calcula a vida restante até a vida maxima do jogador e recupera.

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

			else if (player.health == 100) {       // se o player estiver com a vida cheia

				cout <<
					"\nYour health is full\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Combat_Player();

			}

			else {       //se o player nao tiver mais poçoes restantes

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

	} while (enemy.enemyAlive == true);        // executar todo o codigo enquanto o inimigo ainda estiver vivo
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------WALKSORTER-----------------

void walkSorter() {         // função para sortear o que acontece quando o jogador escolhe caminhar no jogo

	int randomCaminho, randomOpenDoorInside, randomQtdPotions;

	randomCaminho = rand() % 29 + 1;    //randomizador de caminhos

	if (randomCaminho <= 10) {      //nao aconteceu/encontrou nada

		cout <<
			" But you found nothing.\n\n"
			"Press ANY KEY to continue . . .";
		_getch();
		
	}
	else if (randomCaminho > 10 && randomCaminho <= 20) {   //encontrou uma porta aberta

		cout << "You found an open door...";

		randomOpenDoorInside = rand() % 49 + 1;   //randomizador para definir o que o usuario encontrará ao abrir a porta

		if (randomOpenDoorInside <= 25) {      //encontrou um inimigo

			enemySorter();
			cout <<
				" WITH AN ENEMY INSIDE\n\n"
				"Press ANY KEY to continue . . .";
			_getch();
			Gameplay_Combat_Player();

		}
		else {     //encontrou um baú com poções

			randomQtdPotions = rand() % 5 + 1;       //randomizador de quantidade de poções encontradas

			cout <<
				" WITH A CHEST INSIDE IT CONTAINING " << randomQtdPotions << " HEALTH POTIONS\n\n"
				"Press ANY KEY to continue . . .";
			_getch();

			player.potions += randomQtdPotions;

		}
	}

	else if (randomCaminho > 20) {         //encontrou uma porta secreta trancada

		cout <<
			"YOU FOUND A SECRET DOOR... But it's locked...\n\n"
			"Press ANY KEY to continue . . .";
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
			"Type:\n"
			"	- 'walk' to move forward\n"
			"	- 'rest' to recover your full health for (missing health/2) seconds.\n\n"
			">";
		cin >> walkOption;             // recebe a opção do jogador

		for_each(walkOption.begin(), walkOption.end(), [](char& c) {      //
			c = ::tolower(c);                                             //
		});                                                               //  método para percorrer todos os caracteres da variavel walkOption e transformar eles em lower case (minusculo)

		if (walkOption == "walk") {         //se o jogador caminhar, chama a variavel para definir o que acontece

			cout <<
				"\nWalking . . .";
			Sleep(1000);
			cout <<
				"\n. . .";
			Sleep(700);

			walkSorter();

		}

		else if (walkOption == "rest") {          //se o jogador escolher descansar

			if (player.health < 100) {

				healthDif = player.healthMax - player.health;     //calcula a diferença de HP para recuperar

				for (int i = healthDif / 2; i >= 0; i--) {        //descansa por (diferença de HP/2) segundos

					system("cls");
					UI();
					cout <<
						"\nResting . . . "<<i<<" Seconds";
					Sleep(1000);

				}

				cout <<
					"\n. . .";
				Sleep(700);
								
				player.health += healthDif;     //acrescenta na vida do jogador

				cout <<
					" Recovered " << healthDif << " HP\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Walk();
				
			}

			else if (player.health == 100) {     //não descansa se a vida do jogador estiver cheia

				cout <<
					"\nYour health is full\n\n"
					"Press ANY KEY to continue . . .";
				_getch();
				Gameplay_Walk();

			}

		}

		else if (walkOption == "cheatcode" && player.key == 0) {           // código para testes de poção e chave
			
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

	} while (player.playerAlive == true && enemy.enemyAlive == false);         //executar o codigo enquanto o player estiver vivo e o inimigo morto/não encontrado
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------START----------------------

void Start() {         // função com um pouco de lore do jogo. executado após o usuario escolher a opção 1 no Main Menu. chama o login, conta o lore e chama a gameplay

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------MAIN-----------------------

int main(){       //Main Menu que redireciona para as telas de cada opção

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

	} while (gameOn == 0);     // executar o codigo enquanto o jogador não startar o jogo

}