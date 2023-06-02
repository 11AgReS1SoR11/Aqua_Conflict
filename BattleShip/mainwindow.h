
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

#include <battlewindow.h>
#include <mylib.h>
#include <startchoosewin.h>
#include <getmodewindow.h>
#include <settings.h>


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetDesign();

private slots:
    void onexitButtonClicked();
    void onsettingsButtonClicked();
    void onstartButtonClicked();
    void GetChoose(int);
    void onModeButtonClicked(BattleWindow*);
    void ChangeSettings(int, int);

private:
    QLabel *Title;
    QLabel *AquaConflict;
    QPushButton *startButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;

    StartChooseWin* ChooseModeWin;
    BattleWindow* battle;
    Settings* set;

    int SettingsHit = 2; // defoult settings
    int SettingsMiss = 0; // defoult settings
};

#endif // MAINWINDOW_H
