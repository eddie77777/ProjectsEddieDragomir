#include <gtest/gtest.h>
#include "MockIGameListener.h"
#include "MockIStrategy.h"
#include "Game.h"
#include "EasyStrategy.h"

using namespace ::testing;

TEST(Game, CallOnMakeMove)
{
	
	Game game;
	std::shared_ptr<IGameListener> listener = std::make_shared<MockIGameListener>();
	game.AddListener(listener);
	const Position pos = { 1,1 };
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnMakeMove(_, _));
	game.MakeMove(pos, EGameMode::Multiplayer);
	
}


TEST(Game, CallOnGameOver)
{

	Game game;
	std::shared_ptr<IGameListener> listener = std::make_shared<MockIGameListener>();
	game.AddListener(listener);
	Position pos1 = { 0,0 }, pos2 = { 2,1 };
	Position pos3 = { 0,1 }, pos4 = { 2,2 };
	Position pos5 = { 0,2 };
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnMakeMove(_, _));
	game.MakeMove(pos1, EGameMode::Multiplayer);
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnMakeMove(_, _));
	game.MakeMove(pos2, EGameMode::Multiplayer);
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnMakeMove(_, _));
	game.MakeMove(pos3, EGameMode::Multiplayer);
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnMakeMove(_, _));
	game.MakeMove(pos4, EGameMode::Multiplayer);
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnMakeMove(_, _));
	game.MakeMove(pos5, EGameMode::Multiplayer);
	EXPECT_CALL(*dynamic_cast<MockIGameListener*>(game.GetObservers()[0].lock().get()), OnGameOver(_, _));
	game.GameOver();

}

TEST(Game, Strategy)
{
	std::shared_ptr<MockIStrategy> ez = std::make_shared<MockIStrategy>();
	Game game(EStrategyType::Easy);
	game.SetStrategy(ez);
	Position pos1 = { 0,0 };
	EXPECT_CALL(*ez.get(), GetPosition(_));
	game.MakeMove(pos1, EGameMode::Singleplayer);
	
}