#pragma once
#include "Istrategy.h"
#include <gmock/gmock.h>

class MockIStrategy: public IStrategy {
public:
    MOCK_METHOD(Position, GetPosition, (const Board& board), (override));
};