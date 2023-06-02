#include "getmodewindow.h"

GetModeWindow::GetModeWindow(QWidget *parent) : QDialog(parent)
{
    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 400;
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

GetModeWindow::GetModeWindow(const QString AgreeWord, const QString DisagreeWord, QWidget *parent) : QDialog(parent)
{
    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 400;
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    Yes = new QPushButton(AgreeWord, this);
    No = new QPushButton(DisagreeWord, this);
    Text = new QLabel(this);
    int sizeX = WINDOW_WIDTH / 2 - 25, sizeY = 100;
    Yes->setGeometry(0 + 15, WINDOW_HEIGHT / 2, sizeX, sizeY);
    No->setGeometry(WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT / 2, sizeX, sizeY);

    sizeX = WINDOW_WIDTH - 100; sizeY = WINDOW_HEIGHT / 2 - 15;
    Text->setGeometry((WINDOW_WIDTH - sizeX) / 2, Yes->y() - sizeY, sizeX, sizeY);
    Text->setAlignment(Qt::AlignCenter);

    connect(Yes, &QPushButton::clicked, this, &GetModeWindow::onYesButtonClicked);
    connect(No, &QPushButton::clicked, this, &GetModeWindow::onNoButtonClicked);

    SetDesign();
}

GetModeWindow::~GetModeWindow()
{
    delete Yes;
    delete No;
    delete Text;
}

void GetModeWindow::SetDesign()
{
    const QString ButtonDesing = GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg");
    Yes->setStyleSheet(ButtonDesing);
    No->setStyleSheet(ButtonDesing);

    const QString TitleDesign = GetDesign("ExitTitles");
    Text->setStyleSheet(TitleDesign);

    SetBackground(this, QDir::currentPath() + "/Design/BattleShp_ExitBackground.jpg");
}

void GetModeWindow::SetLabel(const QString text)
{
    Text->setText(text);
}

void GetModeWindow::onYesButtonClicked()
{
    emit Result(1);
    close();
}

void GetModeWindow::onNoButtonClicked()
{
    emit Result(0);
    close();
}
