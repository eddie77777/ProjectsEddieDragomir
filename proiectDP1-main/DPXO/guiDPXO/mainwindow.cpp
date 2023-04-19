#include "mainwindow.h"
#include "QMessageBox"
#include "QVBoxLayout"

MainWindow::MainWindow(EGameMode gameMode, EStrategyType strategyType, QWidget* parent)
    : QMainWindow(parent), m_gameMode(gameMode), m_strategy(strategyType)
{
    // Create game board
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            buttons[row][col] = new QPushButton("", this);
            buttons[row][col]->setProperty("row", row);
            buttons[row][col]->setProperty("col", col);
            buttons[row][col]->setFixedSize(50, 50);
            connect(buttons[row][col], &QPushButton::clicked, this, &MainWindow::HandleButton);
        }
    }
    // Create layout and add widgets
    QGridLayout* layout = new QGridLayout;
    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            layout->addWidget(buttons[row][col], row, col);
        }
    }
    // Set the layout on the central widget of the main window
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    // Set the initial size of the main window to 300x300
    setFixedSize(300, 300);
    m_game = IGame::Produce(strategyType);
}

MainWindow::~MainWindow()
{
}

void MainWindow::HandleButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();
    m_game->MakeMove({ row, col }, m_gameMode);
    UpdateGUI();
    button->setEnabled(false);
    if (m_game->GetState() != EGameState::Playing)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                buttons[row][col]->setEnabled(false);
            }
        }
        m_game->GameOver();
    }  
}

IGamePtr MainWindow::GetGame()
{
    return m_game;
}

void MainWindow::SetListener(std::shared_ptr<IGameListener> listener)
{
    m_listener = listener;
}

char MainWindow::ECellStateToChar(ECellState cellState)
{
    if (cellState == ECellState::Zero)
        return '0';
    else if (cellState == ECellState::Cross)
        return 'X';
    return ' ';
}

void MainWindow::UpdateGUI()
{
    auto board = m_game->GetBoardContent();
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            buttons[row][col]->setText(QString(ECellStateToChar(board[row][col])));
            if(buttons[row][col]->text()!=" ")
                buttons[row][col]->setEnabled(false);
        }
    }
}