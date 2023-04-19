#include <gtest/gtest.h>
#include "Game.h"
#include <iostream>
#include <string>


TEST(TestUpdate, Board)
{
    Board board;
    const std::pair<uint16_t, uint16_t> pos = { 1,1 };
    board.UpdateBoard(pos, ECellState::Cross);
    EXPECT_EQ(board.GetMatrix()[1][1], ECellState::Cross);
}

TEST(TestGetEmptyPosition,Board)
{
    Board board;
    std::pair<uint16_t, uint16_t> pos = { 1,1 };
    board.UpdateBoard(pos, ECellState::Cross);
    for (uint16_t i = 0; i < board.GetEmptyPositions().size(); i++)
    {
        std::pair<uint16_t, uint16_t> pos2 = board.GetEmptyPositions()[i];
        EXPECT_NE(pos, pos2);
    }
       
}

TEST(TestMakeMoveSinglePlayerOnSamePos,Game)
{
    Game game(EStrategyType::Easy);
    std::pair<uint16_t, uint16_t> pos = { 1,1 };
    EXPECT_EQ(EMoveResult::Success, game.MakeMove(pos, EGameMode::Singleplayer));
    EXPECT_EQ(EMoveResult::Fail, game.MakeMove(pos, EGameMode::Singleplayer));
}

TEST(TestMakeMoveMultiPlayer, Game)
{
    Game game;
    std::pair<uint16_t, uint16_t> pos = { 1,1 };
    EXPECT_EQ(EMoveResult::Success, game.MakeMove(pos, EGameMode::Multiplayer));
    EXPECT_EQ(EMoveResult::Fail, game.MakeMove(pos, EGameMode::Multiplayer));
}


TEST(GameStateWinRow, Game)
{
    Game game;
    for (uint16_t i = 0; i < 2; ++i)
    {
        game.MakeMove({ 0,i }, EGameMode::Multiplayer);
        game.MakeMove({ 1,i }, EGameMode::Multiplayer);
    }
    game.MakeMove({ 0,2 }, EGameMode::Multiplayer);

    EXPECT_EQ(game.GetState(),EGameState::Win);
}

TEST(GameStateWinColumn, Game)
{
    Game game;
    for (uint16_t i = 0; i < 2; ++i)
    {
        game.MakeMove({ i,0 }, EGameMode::Multiplayer);
        game.MakeMove({ i,1 }, EGameMode::Multiplayer);
    }
    game.MakeMove({ 2,0 }, EGameMode::Multiplayer);

    EXPECT_EQ(game.GetState(), EGameState::Win);
}

TEST(GameStateWinPrincipalDiagonal, Game)
{
    Game game;
    for (uint16_t i = 0; i < 2; ++i)
    {
        game.MakeMove({ i,i }, EGameMode::Multiplayer);
        game.MakeMove({ i+1,0 }, EGameMode::Multiplayer);
    }
    game.MakeMove({ 2,2 }, EGameMode::Multiplayer);

    EXPECT_EQ(game.GetState(), EGameState::Win);
}

TEST(GameStateWinSecondarylDiagonal, Game)
{
    Game game;
    for (uint16_t i = 0; i < 2; ++i)
    {
        game.MakeMove({ i,2 - i }, EGameMode::Multiplayer);
        game.MakeMove({ i,0 }, EGameMode::Multiplayer);
    }
    game.MakeMove({ 2,0 }, EGameMode::Multiplayer);
        
    EXPECT_EQ(game.GetState(), EGameState::Win);
}


TEST(GameStateTie, Game)
{
    Game game;
    game.MakeMove({ 0,0 }, EGameMode::Multiplayer);
    game.MakeMove({ 0,1 }, EGameMode::Multiplayer);
    game.MakeMove({ 0,2 }, EGameMode::Multiplayer);
    game.MakeMove({ 1,1 }, EGameMode::Multiplayer);
    game.MakeMove({ 1,0 }, EGameMode::Multiplayer);
    game.MakeMove({ 1,2 }, EGameMode::Multiplayer);
    game.MakeMove({ 2,2 }, EGameMode::Multiplayer);
    game.MakeMove({ 2,0 }, EGameMode::Multiplayer);
    game.MakeMove({ 2,1 }, EGameMode::Multiplayer);

    EXPECT_EQ(game.GetState(), EGameState::Tie);
}

TEST(AddObserverAndDeleteObserver, Game)
{
    IGameListenerWeakPtr observer;
    Game game;
    game.AddListener(observer);
    game.RemoveListener(observer);
}

int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
