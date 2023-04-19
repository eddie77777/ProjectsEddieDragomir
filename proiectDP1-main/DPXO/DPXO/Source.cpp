#include <iostream>
#include "HPlayer.h"
#include "ConsoleGame.h"
#include "ConsoleListener.h"
#include <stdlib.h>
#include <string>

//Choose the game mode. Receive input from user and validate it.
int ChooseGameMode()
{
	std::string s_mode;
	int mode;
	while (true)
	{
		std::cout << "Choose game mode: [0] Single Player  || [1] Multi Player\n";
		std::cin >> s_mode;
		try {
			mode = std::stoi(s_mode);
			if (mode != 0 && mode != 1)
				std::cout << "Invalid game mode!\n";
			else
				break;
		}
		catch (std::invalid_argument e)
		{
			std::cout << "Invalid game mode!\n";
		}
	}
	return mode;
}

//Choose the stratgy type for the game. Receive input from user and validate it.
int ChooseStrategy()
{
	std::string s_level;
	int level;
	while (true)
	{
		std::cout << "Choose level: [0] Easy  ||  [1] Medium  ||  [2] Hard \n";
		std::cin >> s_level;
		try {
			level = std::stoi(s_level);
			if (level != 0 && level != 1 && level != 2)
				std::cout << "Invalid strategy!\n";
			else
				break;
		}
		catch (std::invalid_argument e)
		{
			std::cout << "Invalid strategy!\n";
		}
	}
	return level;
}

int main()
{
	EStrategyType strategyType = EStrategyType::Easy;
	EGameMode gameMode;
	while (true)
	{
		system("CLS");
		int mode = ChooseGameMode();
		if (mode)
		{
			std::cout << "You chose MULTi PLAYER MODE. Have fun!\n\n";
			gameMode = EGameMode::Multiplayer;
		}
		else
		{
			gameMode = EGameMode::Singleplayer;
			std::cout << "You chose SiNGLE PLAYER MODE. Have fun!\n";
			int strategy = ChooseStrategy();
			if (strategy == 0)
			{
				std::cout << "You chose Easy Level. Have fun!\n\n";
				strategyType = EStrategyType::Easy;
			}
			else if (strategy == 1)
			{
				std::cout << "You chose Medium Level. Have fun!\n\n";
				strategyType = EStrategyType::Medium;
			}
			else
			{
				std::cout << "You chose Hard Level. Have fun!\n\n";
				strategyType = EStrategyType::Difficult;

			}
		}

		//Create a console game with the set difficult level just before
		std::unique_ptr consoleGame = std::make_unique<ConsoleGame>(strategyType);

		//Add Listener for Console Game
		auto consoleGameObserver = std::make_shared<ConsoleListener>(1, consoleGame->GetGame());
		consoleGame->GetGame()->AddListener(consoleGameObserver);

		//Gameplay
		consoleGameObserver->ShowTable(std::cout, 1);
		while (consoleGame->GetGame()->GetState() == EGameState::Playing)
		{
			consoleGame->MakeMove(gameMode);
		}
		consoleGame->GetGame()->GameOver();
		consoleGame->GetGame()->RemoveListener(consoleGameObserver);

		std::string exit;
		std::cout << "Press [0] to exit.\n";
		std::cout << "Press a key to continue playing.\n";
		std::cin >> exit;
		if (exit == "0")
			break;
		else
			continue;
	}
	return 0;
}