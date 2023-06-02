
#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QMainWindow>
#include <battlefield.h>
#include <QPushButton>
#include <QLabel>
#include <QRandomGenerator>
#include <QPair>

#include <ai.h>
#include <mylib.h>
#include <getmodewindow.h>

class BattleWindow : public QMainWindow
{
    Q_OBJECT
public:
    BattleWindow(int ActiveHit, int ActiveMiss, QWidget *parent = nullptr);
    virtual ~BattleWindow();
    void SetDesign();
    void StartGame();
    int Drawing();
    int GetWidth();
    int GetHeight();
    void ChangeStartButtonText(const QString& text);
    QString Player1Name();
    QString Player2Name();
    void BlockChange1Button();
    GetModeWindow* СongratulationsWin();
    void RestartAllWidgets();

public slots:
    virtual void NextStep(QPair<int, int> XY);
    virtual void onStartButtonClicked();
    virtual void GetChoose(int);
    virtual void CСССongratulationsWin();

private slots:
    void onChangeButtonClicked();
    void onReturnButtonClicked();
    void Scoreboard(QPair<int, int> XY);

protected:
    BattleField* Field1;
    BattleField* Field2;

private:
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    int ActiveHit;
    int ActiveMiss;
    QPushButton* start;
    QPushButton* change;
    QPushButton* returnbutton;
    QLabel* player1;
    QLabel* player2;
    QLabel* Turn;
    QLabel* LastTurn;
    QLabel* counter;
};

#endif // BATTLEWINDOW_H
