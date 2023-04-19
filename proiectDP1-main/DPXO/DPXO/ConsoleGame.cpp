#include "ConsoleGame.h"
#include "CPlayer.h"
#include "HPlayer.h"
#include <string>

ConsoleGame::ConsoleGame(EStrategyType strategyType)
{
	std::cout << "Let's start the game!\n";
	m_game = IGame::Produce(strategyType);
}

uint16_t ConsoleGame::ReadPos(std::string axis)
{
	uint16_t input;
	std::string s_input;
	char c = '\0';
	std::cout << axis << ": ";
	while (true)
	{
		std::cin >> s_input;
		try 
		{
			input = std::stoi(s_input);
			if (input > m_game->GetBoardContent().size() || input < 1)
			{
				std::cout << "Input out of range\n";
				std::cout << axis << ": ";
			}
			else
				break;
		}
		catch (std::invalid_argument e)
		{
			std::cout << "Argument invalid (input has to be a number)\n";
			std::cout << axis << ": ";
		}
	}
	return input - 1;
}

void ConsoleGame::MakeMove(EGameMode gameMode)
{
	std::cout << "*choose position*\n";
	uint16_t line = ReadPos("line");
	uint16_t column = ReadPos("column");
	while (m_game->MakeMove({ line , column }, gameMode) == EMoveResult::Fail)
	{
		std::cout << "Position already filled\n";
		line = ReadPos("line");
		column = ReadPos("column");
	}
	static_cast<void>(m_game->MakeMove({ line, column }, gameMode));
}

IGamePtr ConsoleGame::GetGame()
{
	return m_game;
}
