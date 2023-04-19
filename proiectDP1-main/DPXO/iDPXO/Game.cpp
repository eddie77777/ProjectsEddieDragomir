#include "Game.h"
#include <iostream>
#include "EasyStrategy.h"
#include "MediumStrategy.h"
#include "DifficultStrategy.h"

Game::Game(EStrategyType strategyType)
{
	switch (strategyType)
	{
	case EStrategyType::Easy:
		m_strategy = std::make_shared<EasyStrategy>();
		break;
	case EStrategyType::Difficult:
		m_strategy = std::make_shared<DifficultStrategy>();
		break;
	case EStrategyType::Medium:
		m_strategy = std::make_shared<MediumStrategy>();
		break;
	default:
		break;
	}
}

IGamePtr IGame::Produce(EStrategyType strategyType)
{
	return std::make_shared<Game>(strategyType);
}


EMoveResult Game::MakeMove(Position position, EGameMode gameMode)
{
	if (gameMode == EGameMode::Multiplayer)
	{
		if (CheckIfAddOnPos(position))
		{
			SetContentOnPos(position, GetCellState());
			m_moveNo++;
			return EMoveResult::Success;
		}
		else
			return EMoveResult::Fail;
	}
	else
	{
		if (CheckIfAddOnPos(position))
		{
			SetContentOnPos(position, GetCellState());
			m_moveNo++;
			if (GetState() == EGameState::Playing)
			{
				SetContentOnPos(m_strategy->GetPosition(m_board), GetCellState());
				m_moveNo++;
			}
			return EMoveResult::Success;
		}
		else
			return EMoveResult::Fail;
	}
}

BoardContent Game::GetBoardContent()
{
	return m_board.GetMatrix();
}

EGameState Game::GetState()
{
	if (m_board.GetMatrix()[0][0] == m_board.GetMatrix()[0][1] && m_board.GetMatrix()[0][0] == m_board.GetMatrix()[0][2] && m_board.GetMatrix()[0][0] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[1][0] == m_board.GetMatrix()[1][1] && m_board.GetMatrix()[1][0] == m_board.GetMatrix()[1][2] && m_board.GetMatrix()[1][0] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[2][0] == m_board.GetMatrix()[2][1] && m_board.GetMatrix()[2][0] == m_board.GetMatrix()[2][2] && m_board.GetMatrix()[2][0] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[0][0] == m_board.GetMatrix()[1][0] && m_board.GetMatrix()[0][0] == m_board.GetMatrix()[2][0] && m_board.GetMatrix()[0][0] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[0][1] == m_board.GetMatrix()[1][1] && m_board.GetMatrix()[0][1] == m_board.GetMatrix()[2][1] && m_board.GetMatrix()[0][1] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[0][2] == m_board.GetMatrix()[1][2] && m_board.GetMatrix()[0][2] == m_board.GetMatrix()[2][2] && m_board.GetMatrix()[0][2] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[0][0] == m_board.GetMatrix()[1][1] && m_board.GetMatrix()[0][0] == m_board.GetMatrix()[2][2] && m_board.GetMatrix()[0][0] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetMatrix()[0][2] == m_board.GetMatrix()[1][1] && m_board.GetMatrix()[0][2] == m_board.GetMatrix()[2][0] && m_board.GetMatrix()[0][2] != ECellState::Empty)
		return EGameState::Win;
	if (m_board.GetEmptyPositions().empty())
		return EGameState::Tie;
	return EGameState::Playing;
}

void Game::GameOver()
{
	if (GetState() == EGameState::Win)
	{
		CallGameOver(EGameState::Win);
	}
	else if (GetState() == EGameState::Tie)
	{
		CallGameOver(EGameState::Tie);
	}
}

void Game::AddListener(IGameListenerWeakPtr observer)
{
	m_observers.push_back(observer);
}

void Game::RemoveListener(IGameListenerWeakPtr observer)
{
	for (auto it = m_observers.begin(); it != m_observers.end(); )
	{
		if (auto sp = it->lock())
		{
			if (sp == observer.lock())
				it = m_observers.erase(it);
			else
				it++;
		}
		else
		{
			it = m_observers.erase(it);
		}
	}
}


void Game::CallGameOver(EGameState gameState)
{

	for (auto obs : m_observers)
		if (auto sp = obs.lock())
		{
			sp->OnGameOver((m_moveNo - 1) % 2 + 1, gameState);
		}
}

ECellState Game::GetCellState()
{
	ECellState symbol;
	if (m_moveNo % 2 == 0)
		symbol = ECellState::Cross;
	else
		symbol = ECellState::Zero;
	return symbol;
}

bool Game::CheckIfAddOnPos(Position pos) const
{
	if (pos.first < 0 || pos.second < 0)
		return false;
	if (pos.first >= m_board.GetMatrix().size() || pos.second >= m_board.GetMatrix().size())
		return false;
	if (m_board.GetMatrix()[pos.first][pos.second] != ECellState::Empty)
		return false;
	return true;
}

void Game::SetContentOnPos(Position pos, ECellState cellState)
{
	m_board.UpdateBoard(pos, cellState);
	for (auto obs : m_observers)
		if (auto sp = obs.lock())
		{
			sp->OnMakeMove(pos, m_moveNo % 2 + 1);
		}
}

std::vector<IGameListenerWeakPtr> Game::GetObservers() const
{
	return m_observers;
}

void Game::SetStrategy(IStrategyPtr newStrategy)
{
	m_strategy = newStrategy;
}