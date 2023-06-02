#ifndef BATTLETOGETHER_H
#define BATTLETOGETHER_H

#include <battlewindow.h>

class BattleTogether : public BattleWindow
{
    Q_OBJECT
public:
    BattleTogether(int ActiveHIt, int ActiveMiss, QWidget *parent = nullptr);
    ~BattleTogether();

public slots:
    void GetChoose(int);
    void CСССongratulationsWin();

private slots:
    void onChange2ButtonClicked();
    void onStartButtonClicked();


private:
    QPushButton* change2;
    int StartClickCounter = 0;
};

#endif // BATTLETOGETHER_H
