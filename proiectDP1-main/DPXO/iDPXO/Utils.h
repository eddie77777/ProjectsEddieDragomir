#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include <memory>

//Enums

/*! The current state of the game */
enum class EGameState {
	Playing, /*!< Players are still placing symbols on the board */
	Win, /*!< The game finished and it's won by a player */
	Tie /*!< The game finished, but nobody won, there is draw */
};

/*! The current state of the game */
enum class EMoveResult {
	Fail,/*!< The move was made on a cell which is not empty */
	Success /*!< The move took place successfully */
};

/*! The game mode */
enum class EGameMode {
	Singleplayer, /*!< The user is playing against computer */
	Multiplayer /*!< The user has control over the placement of both symbols  */
};

/*! The way how computer chooses positions where to place its symbol */
enum class EStrategyType {
	Easy, /*!< User has high chances to win */
	Medium, /*!< User has lower chances to win */
	Difficult /*!< It is pretty hard for user to win */
};

/*! The symbols that is filling a cell at the moment */
enum class ECellState {
	Zero, /*!< This means the char '0' on the board */
	Cross, /*!< This means the char 'X' on the board */
	Empty /*!< The cell is empty */
};



//Typdefs

/** This is the data structure that holds the game board */
using BoardContent = std::array<std::array<ECellState, 3>, 3>;

/** This is a container that holds only the cells that are still empty */
using EmptyPositions = std::vector<std::pair<int, int>>;

/** This is a shared pointer to an object of IGame type */
using IGamePtr = std::shared_ptr<class IGame>;

/** This is a position in the game board */
using Position = std::pair<int, int>;

/** This is a weak pointer to an object of IGameListener type */
using IGameListenerWeakPtr = std::weak_ptr<class IGameListener>;

/** This is a shared pointer to an object of IStrategy type */
using IStrategyPtr = std::shared_ptr<class IStrategy>;
