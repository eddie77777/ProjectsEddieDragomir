#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include <memory>
#include "IGameListener.h"

class IGame
{
public:
	//Static Methods

	/// \brief Constructs an object of type Game and wraps it in a std::shared_ptr to IGame
	/// \param strategyType the type of strategy that user chose to play 
	/// \return a shared_ptr to IGame
	static IGamePtr Produce(EStrategyType strategyType);
	//Methods

	/// \brief For each type of game checks if the player can add a symbol on a position and if it's affirmative it adds it and returns the result
	/// \param position a position where the move must be made
	/// \param gameMode the type of game being played
	/// \returns Movement result that is fail or success
	virtual EMoveResult MakeMove(Position position, EGameMode gameMode) = 0;

	/// \brief Gets the matrix of the board
	/// \returns The matrix of the board
	virtual BoardContent GetBoardContent() = 0;

	/// \brief Gets the state of the game ( playing, win, tie )
	/// \returns The state of the game ( playing, win, tie )
	virtual EGameState GetState() = 0;

	/// \brief Tells the observer how the game ended
	virtual void GameOver() = 0;


	//Listeners

	/// \brief Adds a new listener to the observer
	/// \param observer a weak_ptr to IGameListener
	virtual void AddListener(IGameListenerWeakPtr observer) = 0;

	/// \brief Removes a listener from the observer
	/// \param observer a weak_ptr to IGameListener
	virtual void RemoveListener(IGameListenerWeakPtr observer) = 0;

	//Destructor
	virtual ~IGame() = default;
};
