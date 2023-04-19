#include "tictactoe.h"

TicTacToe::TicTacToe(QWidget* parent)
    : QMainWindow(parent)
{
    // Set up main window
    setWindowTitle("Tic Tac Toe");
    setFixedSize(500, 400);

    // Set up title label
    titleLabel = new QLabel("Welcome to Tic Tac Toe!", this);
    titleLabel->setFont(QFont("Arial", 20));
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setGeometry(QRect(100, 50, 300, 50));

    // Set up "play with computer" button
    playWithComputerButton = new QPushButton("Play with Computer", this);
    playWithComputerButton->setGeometry(QRect(50, 120, 200, 50));
    connect(playWithComputerButton, &QPushButton::clicked, this, &TicTacToe::startGameWithComputer);

    // Set up "play with player" button
    playWithPlayerButton = new QPushButton("Play with Player", this);
    playWithPlayerButton->setGeometry(QRect(playWithComputerButton->x() + playWithComputerButton->width() + 20, 120, 200, 50));
    connect(playWithPlayerButton, &QPushButton::clicked, this, &TicTacToe::startGameWithPlayer);

    // Set up "choose difficulty" label
    chooseDifficultyLabel = new QLabel("Choose difficulty:", this);
    chooseDifficultyLabel->setGeometry(QRect(50, 200, 100, 30));

    // Set up difficulty combo box
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->setGeometry(QRect(160, 200, 90, 30));
    difficultyComboBox->addItem("Easy");
    difficultyComboBox->addItem("Medium");
    difficultyComboBox->addItem("Hard");
    difficultyComboBox->setCurrentIndex(0); // set the default to Easy

}

void TicTacToe::startGameWithComputer()
{
    EGameMode gameMode = EGameMode::Singleplayer;
    EStrategyType strategy;
    QString selectedDifficulty = difficultyComboBox->currentText();
    if (selectedDifficulty == "Easy")
    {
        strategy = EStrategyType::Easy;
    }
    else if (selectedDifficulty == "Medium")
    {
        strategy = EStrategyType::Medium;
    }
    else
    {
        strategy = EStrategyType::Difficult;
    }
    MainWindow* game = new MainWindow(gameMode, strategy);
    game->show();
    auto uiListener = std::make_shared<UIListener>(1, game->GetGame());
    game->GetGame()->AddListener(uiListener);
    hide();
}

void TicTacToe::startGameWithPlayer()
{
    EGameMode gameMode = EGameMode::Multiplayer;
    EStrategyType strategy = EStrategyType::Easy;
    MainWindow* game = new MainWindow(gameMode, strategy);
    auto uiListener = std::make_shared<UIListener>(1, game->GetGame());
    game->show();
    game->GetGame()->AddListener(uiListener);
    game->SetListener(uiListener);
    hide();
}