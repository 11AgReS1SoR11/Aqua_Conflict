#include "battlesolo.h"

BattleSolo::BattleSolo(int ActiveHIt, int ActiveMiss, AI* bot, QWidget *parent) : BattleWindow(ActiveHIt, ActiveMiss, parent), Bot(bot)
{
    int** Ships1 = Field1->GetUsedMap();
    if (!Bot) Bot = new EasyAI(Ships1);
    else Bot->UpdateField(Ships1);
}

void BattleSolo::BotTurn()
{
    QPair<int, int> XY = {-1, -1};
    while(Field1->Attack(XY.first, XY.second))
    {
        Bot->UpdateField(Field1->GetUsedMap());
        XY = Bot->MakeDecision();
        if (Field1->IsShip(XY.first, XY.second))
            Bot->hit(XY.first, XY.second);
    }
    Bot->UpdateField(Field1->GetUsedMap());
}

void BattleSolo::NextStep(QPair<int, int> XY)
{
    BattleWindow::NextStep(XY);
    BattleField* ClickedField = qobject_cast<BattleField*>(sender());

    if (ClickedField == Field2)
        BotTurn();
}

void BattleSolo::onStartButtonClicked()
{
    BattleWindow::onStartButtonClicked();
    if (Field1->isEnabled())
        BotTurn();
}
