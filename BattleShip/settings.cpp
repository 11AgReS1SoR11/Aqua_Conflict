#include "settings.h"

Settings::Settings(QWidget *parent)
    : QDialog{parent}
{
    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 400;
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle("Settings");

    int sizeX = WINDOW_WIDTH / 3 - 14, sizeY = 100;
    Boom1 = new QPushButton(this);
    Boom1->setGeometry(7, WINDOW_HEIGHT / 5, sizeX, sizeY);
    Boom2 = new QPushButton(this);
    Boom2->setGeometry(WINDOW_WIDTH / 3 + 7, WINDOW_HEIGHT / 5, sizeX, sizeY);
    Boom3 = new QPushButton(this);
    Boom3->setGeometry(WINDOW_WIDTH / 3 * 2 + 7, WINDOW_HEIGHT / 5, sizeX, sizeY);
    Boubles1 = new QPushButton(this);
    Boubles1->setGeometry(7, WINDOW_HEIGHT * 2 / 4, sizeX, sizeY);
    Boubles2 = new QPushButton(this);
    Boubles2->setGeometry(WINDOW_WIDTH / 3 + 7, WINDOW_HEIGHT * 2 / 4, sizeX, sizeY);
    Boubles3 = new QPushButton(this);
    Boubles3->setGeometry(WINDOW_WIDTH / 3 * 2 + 7, WINDOW_HEIGHT * 2 / 4, sizeX, sizeY);
    sizeX = 100, sizeY = 50;
    Ok = new QPushButton("OK", this);
    Ok->setGeometry(WINDOW_WIDTH - sizeX - 15, WINDOW_HEIGHT - sizeY - 15, sizeX, sizeY);

    connect(Ok, &QPushButton::clicked, this, &Settings::onOkButtonClicked);
}

Settings::~Settings()
{
    delete Boom1; delete Boom2; delete Boom3;
    delete Boubles1; delete Boubles2; delete Boubles3;
    delete FrameBoom; delete FrameBouble;
    delete Ok;
}

void Settings::SetDesign()
{
    QString ButtonDesign = GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg");
    Ok->setStyleSheet(ButtonDesign);

    ButtonDesign = GetDesign("SettingsButtons").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boom1.png");
    Boom1->setStyleSheet(ButtonDesign);
    ButtonDesign = GetDesign("SettingsButtons").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boom2.png");
    Boom2->setStyleSheet(ButtonDesign);
    ButtonDesign = GetDesign("SettingsButtons").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boom3.png");
    Boom3->setStyleSheet(ButtonDesign);
    ButtonDesign = GetDesign("SettingsButtons").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boubles1.png");
    Boubles1->setStyleSheet(ButtonDesign);
    ButtonDesign = GetDesign("SettingsButtons").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boubles2.png");
    Boubles2->setStyleSheet(ButtonDesign);
    ButtonDesign = GetDesign("SettingsButtons").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boubles3.png");
    Boubles3->setStyleSheet(ButtonDesign);

    QPushButton* booms[3] = {Boom1, Boom2, Boom3};
    QPushButton* boubles[3] = {Boubles1, Boubles2, Boubles3};

    FrameBoom = new QLabel(this);
    FrameBoom->setStyleSheet(GetDesign("SettingsButtonsClicked"));
    FrameBoom->setGeometry(booms[ActiveBoom]->x(), booms[ActiveBoom]->y(), booms[ActiveBoom]->width(), booms[ActiveBoom]->height());
    FrameBouble = new QLabel(this);
    FrameBouble->setStyleSheet(GetDesign("SettingsButtonsClicked"));
    FrameBouble->setGeometry(boubles[ActiveBouble]->x(), boubles[ActiveBouble]->y(), boubles[ActiveBouble]->width(), boubles[ActiveBouble]->height());

    for (int i = 0; i < 3; ++i) {
        QObject::connect(booms[i], &QPushButton::clicked, [this, i, booms]() {
            FrameBoom->setGeometry(booms[i]->x(), booms[i]->y(), booms[i]->width(), booms[i]->height());
            ActiveBoom = i;
        });
        QObject::connect(boubles[i], &QPushButton::clicked, [this, i, boubles]() {
            FrameBouble->setGeometry(boubles[i]->x(), boubles[i]->y(), boubles[i]->width(), boubles[i]->height());
            ActiveBouble = i;
        });
    }


    SetBackground(this, QDir::currentPath() + "/Design/BattleShp_ExitBackground.jpg");
}

void Settings::SetActiveImg(int hit, int mis)
{
    ActiveBoom = hit;
    ActiveBouble = mis;
}

void Settings::onOkButtonClicked()
{
    emit EndSetting(ActiveBoom, ActiveBouble);
    delete FrameBoom;
    delete FrameBouble;
    this->close();
}
