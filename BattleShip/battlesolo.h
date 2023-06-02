#ifndef BATTLESOLO_H
#define BATTLESOLO_H

#include <battlewindow.h>
#include <ai.h>
#include <easyai.h>
#include <mediumai.h>

class BattleSolo : public BattleWindow
{
    Q_OBJECT
public:
    BattleSolo(int ActiveHIt, int ActiveMiss, AI* bot, QWidget *parent = nullptr);
    void BotTurn();

public slots:
    void NextStep(QPair<int, int> XY);
    void onStartButtonClicked();

private:
    AI* Bot;
};

#endif // BATTLESOLO_H
