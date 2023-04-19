#pragma once
#include "IGameListener.h"
#include <gmock/gmock.h>

class MockIGameListener : public IGameListener {
public:
    MOCK_METHOD(void, OnMakeMove, ((Position pos), int currentPlayer), (override));
    MOCK_METHOD(void, OnGameOver, (int currentPlayer, EGameState gameState), (override));
};