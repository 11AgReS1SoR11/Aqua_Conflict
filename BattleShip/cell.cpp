
#include "cell.h"


Cell::Cell(QWidget *parent) : QPushButton(parent)
{
    int sizeX = 20, sizeY = 20;
    setGeometry(0, 0, sizeX, sizeY);
}

void Cell::Attack(const QString& HitDesign, const QString& MissDesign)
{
    if (GetShip()) setStyleSheet(HitDesign);
    else setStyleSheet(MissDesign);
    IsUsed = true;
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    if (GetUsed()) return;
    QPushButton::mousePressEvent(event);
    emit buttonClicked();
}

void Cell::Deth()
{
    IsUsed = true;
}

void Cell::SetShip(bool c)
{
    IsShip = c;
}

void Cell::SetUsed(bool c)
{
    IsUsed = c;
}

bool Cell::GetShip()
{
    return IsShip;
}

bool Cell::GetUsed()
{
    return IsUsed;
}

void Cell::SetXY(int x, int y)
{
    XY.first = x;
    XY.second = y;
}

QPair<int, int> Cell::GetXY()
{
    return XY;
}
