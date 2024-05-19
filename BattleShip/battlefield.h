
#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QApplication>
#include <QWidget>
#include <QPair>
#include <QTimer>
#include <QMainWindow>
#include <QLabel>

#include "mylib.h"
#include "cell.h"
#include "map.h"

class BattleField : public QWidget
{
    Q_OBJECT
public:
    BattleField(const int x, const int y, int width, int height, QMainWindow *parent = nullptr);
    ~BattleField();
    void Open();
    void Close();
    void IsClickable(bool);
    bool isEnabled();
    int HowMuchShips();
    void ChangeShips();
    bool CheckForNeighboor(Cell*);
    void ShipDead(Cell*, int);
    int** GetUsedMap();
    bool Attack(int, int);
    bool IsShip(int, int);
    int width();
    int height();
    int getX();
    int getY();
    void SetHitSettings(const QString& set);
    void SetMissSettings(const QString& set);
    void SetCount(int);

signals:
    void tmpsignal(QPair<int, int> XY);
    void Hitsignal(QPair<int, int> XY);

private slots:
    void tmpsignalslot();

private:
    void Fill_Cells(const int x1, const int y1, const int x2, const int y2, QWidget* context);
    void RecCheck(Cell*, bool&, int);

private:
    Cell CELLS[12][12];
    Map* M;
    QLabel* Field;
    int Count = 20;
    bool attacking = false;
    QTimer* attackTimer;
    QString hitSettings;
    QString missSettings;
};

#endif // BATTLEFIELD_H
