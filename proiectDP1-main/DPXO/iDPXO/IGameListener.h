#pragma once
#include <memory>
#include "Utils.h"

class IGameListener
{
public:
	//Methods

	/// \brief Offers to users info about game state
	/// \param pos the last position which the player made the move on
	/// \param which player made the move
	virtual void OnMakeMove(Position pos, int currentPlayer) = 0;

	/// \brief Offers to users info about how the game ended 
	/// \param which player made the move
	/// \param gameState the state of the game ( tie,win )
	virtual void OnGameOver(int currentPlayer, EGameState gameState) = 0;


	//Destructor
	virtual ~IGameListener() = default;
};
