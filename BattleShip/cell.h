
#ifndef CELL_H
#define CELL_H


#include <QWidget>
#include <QPushButton>
#include <QPair>

#include "mylib.h"

class Cell : public QPushButton
{
    Q_OBJECT
public:
    Cell(QWidget* parent = nullptr);
    void Deth();
    void SetShip(bool);
    void SetUsed(bool);
    bool GetShip();
    bool GetUsed();
    void SetXY(int x, int y);
    QPair<int, int> GetXY();
    void Attack(const QString&, const QString&);

signals:
    void buttonClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool IsShip = false;
    bool IsUsed = false;
    QPair<int, int> XY = {0, 0};
};

#endif // CELL_H
