
#ifndef STARTCHOOSEWIN_H
#define STARTCHOOSEWIN_H

#include <QMessageBox>
#include <QPushButton>
#include <QDialog>
#include <mylib.h>
#include <battlewindow.h>

#include <easyai.h>
#include <ai.h>
#include <mediumai.h>
#include <battlesolo.h>
#include <battletogether.h>
#include <getmodewindow.h>


class StartChooseWin : public QDialog
{
    Q_OBJECT
public:
    StartChooseWin(QWidget *parent = nullptr);
    void SetDesign();
    ~StartChooseWin();
    void SetSettings(int, int);

signals:
    void ModeSelected(BattleWindow*);

private slots:
    void onSoloButtonClicked();
    void onTogetherButtonClicked();
    void onMultiplayerButtonClicked();
    void GetChoose(int);

private:
    QPushButton *Solo;
    QPushButton *Together;
    QPushButton *Multiplayer;
    int ActiveHit = 2; // defoult settings
    int ActiveMiss = 0; // defoult settings
    AI* Bot = nullptr;
};

#endif // STARTCHOOSEWIN_H
