#pragma once
#include <cstdint>
#include "IGame.h"
#include "Board.h"

using IStrategyPtr = std::shared_ptr<class IStrategy>;

class Game : public IGame
{
public:
	//Constructors
	Game() = default;
	Game(EStrategyType strategyType);

	//Override
	EMoveResult MakeMove(Position position, EGameMode gameMode) override;
	BoardContent GetBoardContent() override;
	EGameState GetState() override;
	void GameOver() override;
	void AddListener(IGameListenerWeakPtr observer) override;
	void RemoveListener(IGameListenerWeakPtr observer) override;
	
	//Methods
	void CallGameOver(EGameState gameState);
	ECellState GetCellState();
	std::vector<IGameListenerWeakPtr> GetObservers() const;
	void SetStrategy(IStrategyPtr newStrategy);

private:
	//Methods
	bool CheckIfAddOnPos(Position pos) const;
	void SetContentOnPos(Position pos, ECellState cellState);
	

private:
	Board m_board;
	uint16_t m_moveNo = 0;
	std::vector<IGameListenerWeakPtr> m_observers; 
	IStrategyPtr m_strategy;
};

