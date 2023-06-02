#include "battletogether.h"

BattleTogether::BattleTogether(int ActiveHIt, int ActiveMiss, QWidget *parent) : BattleWindow(ActiveHIt, ActiveMiss, parent)
{
    const int WINDOW_WIDTH = GetWidth();
    const int WINDOW_HEIGHT = GetHeight();

    int sizeX = 100, sizeY = 75;
    change2 = new QPushButton("Change2", this);
    change2->setGeometry(WINDOW_WIDTH - sizeX * 2, WINDOW_HEIGHT - sizeY * 1.5, sizeX, sizeY);

    Field2->Close();
    change2->setEnabled(false);
    change2->setStyleSheet(GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg"));
    ChangeStartButtonText(Player1Name() + " Ready!");

    connect(change2, &QPushButton::clicked, this, &BattleTogether::onChange2ButtonClicked);
}

BattleTogether::~BattleTogether()
{
    delete change2;
    BattleWindow::~BattleWindow();
}

void BattleTogether::CСССongratulationsWin()
{
    GetModeWindow* win = СongratulationsWin();
    if (win)
    {
        connect(win, &GetModeWindow::Result, this, &BattleTogether::GetChoose);
        win->exec();
    }
}

void BattleTogether::GetChoose(int res)
{
    if (res)
    {
        StartClickCounter = 0;
        ChangeStartButtonText(Player1Name() + " Ready!");
    }
    BattleWindow::GetChoose(res);
}

void BattleTogether::onChange2ButtonClicked()
{
    Field2->ChangeShips();
}

void BattleTogether::onStartButtonClicked()
{
    ++StartClickCounter;
    if (StartClickCounter == 1)
    {
        ChangeStartButtonText(Player2Name() + " Ready!");
        Field1->Close();
        Field2->Open();
        BlockChange1Button();
        change2->setEnabled(true);
    }
    if (StartClickCounter == 2)
    {
        ChangeStartButtonText("Battle!");
        Field2->Close();
        change2->setEnabled(false);
    }
    if (StartClickCounter == 3)
    {
        BattleWindow::onStartButtonClicked();
    }
}
