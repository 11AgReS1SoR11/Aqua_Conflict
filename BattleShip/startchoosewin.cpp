
#include "startchoosewin.h"
#include <QDebug>

StartChooseWin::StartChooseWin(QWidget *parent) : QDialog(parent)
{
    qDebug() << "CCC";
    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 400;
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle("ChooseGame");

    int sizeX = 350, sizeY = 75, X = (WINDOW_WIDTH - sizeX) / 2, Y = sizeY;
    Solo = CreateButton(this, "Solo", X, Y, sizeX, sizeY, 25, "Pristina");
    Together = CreateButton(this, "Together", X, Y + sizeY * 1.2, sizeX, sizeY, 25, "Pristina");
    Multiplayer = CreateButton(this, "Multiplayer", X, Y + sizeY * 2.4, sizeX, sizeY, 25, "Pristina");

    connect(Solo, &QPushButton::clicked, this, &StartChooseWin::onSoloButtonClicked);
    connect(Together, &QPushButton::clicked, this, &StartChooseWin::onTogetherButtonClicked);
    connect(Multiplayer, &QPushButton::clicked, this, &StartChooseWin::onMultiplayerButtonClicked);

    SetDesign();
}

void StartChooseWin::SetDesign()
{
    qDebug() << "CCC";
    const QString ButtonDesign = GetDesign("MainButtons").arg(QDir::currentPath() + "/../Design/BattleShip_WoodBackground.jpg");
    Solo->setStyleSheet(ButtonDesign);
    Together->setStyleSheet(ButtonDesign);
    Multiplayer->setStyleSheet(ButtonDesign);

    const QString pictureName = "BattleShip_ChooseBackground.jpg";
    SetBackground(this, QDir::currentPath() + "/../Design/" + pictureName);
    qDebug() << "DDD";
}

StartChooseWin::~StartChooseWin()
{
    delete Solo;
    delete Together;
    delete Multiplayer;
}

void StartChooseWin::SetSettings(int activeHit, int activeMiss)
{
    this->ActiveHit = activeHit;
    this->ActiveMiss = activeMiss;
}


void StartChooseWin::onSoloButtonClicked()
{
    GetModeWindow* win = new GetModeWindow("Easy", "Hard", this);
    connect(win, &GetModeWindow::Result, this, &StartChooseWin::GetChoose);
    win->SetLabel("Choose AI");
    win->setWindowTitle("AI");
    win->exec();

    BattleWindow* mode = new BattleSolo(ActiveHit, ActiveMiss, Bot, this->parentWidget());
    emit ModeSelected(mode);
}

void StartChooseWin::GetChoose(int res)
{
    if (res) Bot = new EasyAI();
    else Bot = new MediumAI();
}

void StartChooseWin::onTogetherButtonClicked()
{
    BattleWindow* mode = new BattleTogether(ActiveHit, ActiveMiss, this->parentWidget());
    emit ModeSelected(mode);
}

void StartChooseWin::onMultiplayerButtonClicked()
{
    QMessageBox::warning(this, tr("WARNING"),
                         tr("this game mode is not available yet"),
                         QMessageBox::Ok);
}


