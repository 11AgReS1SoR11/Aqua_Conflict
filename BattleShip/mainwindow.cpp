
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Установка размеров окна
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle("Menu");

    int sizeX = 350, sizeY = 75, X = (WINDOW_WIDTH - sizeX) / 2, Y = (WINDOW_HEIGHT - sizeY) * 0.5;

    startButton = CreateButton(this, "Start", X, Y, sizeX, sizeY, 25, "Pristina");
    settingsButton = CreateButton(this, "Settings", X, Y + sizeY * 1.2, sizeX, sizeY, 25, "Pristina");
    exitButton = CreateButton(this, "Exit", X, Y + sizeY * 2.4, sizeX, sizeY, 25, "Pristina");

    Title = CreateTitle(this, "Main menu", X, Y / 2 + sizeY / 2, sizeX, sizeY);
    AquaConflict = CreateTitle(this, "Aqua Conflict", 0, 0, WINDOW_WIDTH, 200);

    ChooseModeWin = new StartChooseWin(this);
    set = new Settings(this);

    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onexitButtonClicked);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::onsettingsButtonClicked);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onstartButtonClicked);
    connect(ChooseModeWin, &StartChooseWin::ModeSelected, this, &MainWindow::onModeButtonClicked);
    connect(set, &Settings::EndSetting, this, &MainWindow::ChangeSettings);

    SetDesign();
}

MainWindow::~MainWindow()
{
    delete Title;
    delete AquaConflict;
    delete startButton;
    delete settingsButton;
    delete exitButton;

    delete ChooseModeWin;
    delete battle;
    delete set;
}

void MainWindow::SetDesign()
{
    const QString DesignForButton = GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg");
    startButton->setStyleSheet(DesignForButton);
    settingsButton->setStyleSheet(DesignForButton);
    exitButton->setStyleSheet(DesignForButton);

    const QString DesingForTitle = GetDesign("MainTitles");
    Title->setStyleSheet(DesingForTitle);

    const QString pictureName = "BattleShip_MainBackground.jpg";
    SetBackground(this, QDir::currentPath() + "/Design/" + pictureName);

    const QString DesignForAquaConflict = GetDesign("AquaConflict");
    AquaConflict->setStyleSheet(DesignForAquaConflict);
}

void MainWindow::onexitButtonClicked()
{
    GetModeWindow* win = new GetModeWindow("Yes", "No", this);
    connect(win, &GetModeWindow::Result, this, &MainWindow::GetChoose);
    win->SetLabel("Are you sure?");
    win->setWindowTitle("Exit");
    win->exec();
}

void MainWindow::GetChoose(int res)
{
    if (res) qApp->quit();
}

void MainWindow::onsettingsButtonClicked()
{
    set->SetActiveImg(SettingsHit, SettingsMiss);
    set->SetDesign();

    set->exec();
}

void MainWindow::onstartButtonClicked()
{
    ChooseModeWin->SetSettings(SettingsHit, SettingsMiss);
    ChooseModeWin->exec();
}


void MainWindow::onModeButtonClicked(BattleWindow* A)
{
    // Закрыть окно выбора режима игры
    ChooseModeWin->close();
    // Закрыть главное меню
    this->hide();
    // Открыть окно игры
    battle = A;
    battle->show();
}

void MainWindow::ChangeSettings(int hit, int miss)
{
    SettingsHit = hit;
    SettingsMiss = miss;
}
