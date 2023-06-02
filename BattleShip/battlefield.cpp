
#include "battlefield.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define COUNTCELL 12


BattleField::BattleField(const int x, const int y, int width, int height, QMainWindow *parent) : QWidget(parent)
{
    width = width / COUNTCELL * COUNTCELL;
    height = height / COUNTCELL * COUNTCELL;
    attackTimer = new QTimer(this);
    attackTimer->setSingleShot(true);
    M = new Map(CELLS);
    Field = new QLabel(parent);
    Field->setGeometry(x, y, width, height);
    // Создание палитры с black цветом фона
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    Field->setAutoFillBackground(true);
    Field->setPalette(palette);

    SetPicture(Field, QDir::currentPath() + "/Design/BattleShip_Sea.jpg");

    Fill_Cells(x, y, x + width, y + height, parent);
    IsClickable(false);
}

BattleField::~BattleField()
{
    delete Field;
    delete M;
    delete Field;
    delete attackTimer;
}

void BattleField::Open()
{
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            QString ButtonUsedDesign;
            if (CELLS[i][j].GetShip()) ButtonUsedDesign = GetDesign("BattleFieldTrue").arg(QDir::currentPath() + "/Design/BattleShip_MyShip2.png");
            else ButtonUsedDesign = GetDesign("BattleFieldFalse");
            CELLS[i][j].setStyleSheet(ButtonUsedDesign);
        }
    }
}

void BattleField::Close()
{
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            CELLS[i][j].setStyleSheet(GetDesign("BattleFieldFalse"));
}

void BattleField::IsClickable(bool c)
{
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            CELLS[i][j].setEnabled(c);
}

bool BattleField::isEnabled()
{
    return CELLS[1][1].isEnabled();
}

int BattleField::HowMuchShips()
{
    return Count;
}

void BattleField::ChangeShips()
{
    M->ChangeMap();
    Close();
    Open();
}

bool BattleField::CheckForNeighboor(Cell* ClickedCell)
{
    bool key = true;
    RecCheck(ClickedCell, key, 0);
    return key;
}

void BattleField::RecCheck(Cell *ClickedCell, bool &key, int way)
{
    QPair<int, int> XY = ClickedCell->GetXY();
    if (!key) return;
    if (ClickedCell->GetShip() && !ClickedCell->GetUsed())
    {
        key = false;
        return;
    }
    if (!ClickedCell->GetShip()) return;
    if (XY.first > 1 && way != DOWN)
        RecCheck(&CELLS[XY.first-1][XY.second], key, UP); // check up
    if (XY.first < 10 && way != UP)
        RecCheck(&CELLS[XY.first+1][XY.second], key, DOWN); // check down
    if (XY.second > 1 && way != RIGHT)
        RecCheck(&CELLS[XY.first][XY.second-1], key, LEFT); // check left
    if (XY.second < 10 && way != LEFT)
        RecCheck(&CELLS[XY.first][XY.second+1], key, RIGHT); // check right
}

void BattleField::ShipDead(Cell *ClickedCell, int way)
{
    QPair<int, int> XY = ClickedCell->GetXY();
    if (!ClickedCell->GetShip())
        return;
    else // Атакую всё вокруг
    {
        if (XY.first > 1 && XY.second > 1) CELLS[XY.first-1][XY.second-1].Attack(hitSettings, missSettings);
        if (XY.first > 1) CELLS[XY.first-1][XY.second].Attack(hitSettings, missSettings);
        if (XY.first > 1 && XY.second < 10) CELLS[XY.first-1][XY.second+1].Attack(hitSettings, missSettings);
        if (XY.second > 1) CELLS[XY.first][XY.second-1].Attack(hitSettings, missSettings);
        if (XY.second < 10) CELLS[XY.first][XY.second+1].Attack(hitSettings, missSettings);
        if (XY.first < 10 && XY.second > 1) CELLS[XY.first+1][XY.second-1].Attack(hitSettings, missSettings);
        if (XY.first < 10) CELLS[XY.first+1][XY.second].Attack(hitSettings, missSettings);
        if (XY.first < 10 && XY.second < 10) CELLS[XY.first+1][XY.second+1].Attack(hitSettings, missSettings);
    }

    if (XY.first > 1 && way != DOWN)
        ShipDead(&CELLS[XY.first-1][XY.second], UP); // check up
    if (XY.first < 10 && way != UP)
        ShipDead(&CELLS[XY.first+1][XY.second], DOWN); // check down
    if (XY.second > 1 && way != RIGHT)
        ShipDead(&CELLS[XY.first][XY.second-1], LEFT); // check left
    if (XY.second < 10 && way != LEFT)
        ShipDead(&CELLS[XY.first][XY.second+1], RIGHT); // check right
}

int **BattleField::GetShipMap()
{
    int** arr = new int*[COUNTCELL];
    for (int i = 0; i < COUNTCELL; ++i)
        arr[i] = new int[COUNTCELL];

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            arr[i][j] = CELLS[i][j].GetShip();

    for (int j = 0; j < COUNTCELL; j++) arr[0][j] = 0;
    for (int i = 0; i < COUNTCELL; i++) arr[i][0] = 0;

    return arr;
}

int **BattleField::GetUsedMap()
{
    int** arr = new int*[COUNTCELL];
    for (int i = 0; i < COUNTCELL; ++i)
        arr[i] = new int[COUNTCELL];

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            arr[i][j] = CELLS[i][j].GetUsed();

    for (int j = 0; j < COUNTCELL; j++) arr[0][j] = 1;
    for (int i = 0; i < COUNTCELL; i++) arr[i][0] = 1;

    return arr;
}

bool BattleField::Attack(int x, int y)
{
    if (x > 0 && x <= 10 && y > 0 && y <= 10 && !CELLS[x][y].GetUsed())
    {
        attackTimer->setInterval(375);
        attackTimer->start();
        while (attackTimer->isActive()) // ждём
            QApplication::processEvents();
        emit CELLS[x][y].clicked();

        attackTimer->setInterval(375);
        attackTimer->start();
        while (attackTimer->isActive()) // ждём
            QApplication::processEvents();

        if (CELLS[x][y].GetShip())
            return true;
        else
            return false;
    }

    return true; // выполняем ещё раз, если мимо площадки
}

bool BattleField::IsShip(int x, int y)
{
    return CELLS[x][y].GetShip();
}

int BattleField::width()
{
    return Field->width();
}

int BattleField::height()
{
    return Field->height();
}

int BattleField::getX()
{
    return Field->x();
}

int BattleField::getY()
{
    return Field->y();
}

void BattleField::SetHitSettings(const QString &set)
{
    hitSettings = set;
}

void BattleField::SetMissSettings(const QString &set)
{
    missSettings = set;
}

void BattleField::SetCount(int a)
{
    Count = a;
}

void BattleField::tmpsignalslot()
{
    Cell* ClickedCell = qobject_cast<Cell*>(sender());
    if (ClickedCell)
    {
        ClickedCell->Attack(hitSettings, missSettings);
        if (ClickedCell->GetShip())
        {
            --Count;
            if (CheckForNeighboor(ClickedCell)) ShipDead(ClickedCell, 0); // обвести корабль
            emit Hitsignal(ClickedCell->GetXY());
        }
        else emit tmpsignal(ClickedCell->GetXY());
    }
}

void BattleField::Fill_Cells(const int x1, const int y1, const int x2, const int y2, QWidget* context)
{
    // Считывание кораблей
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            connect(&CELLS[i][j], &Cell::clicked, this, &BattleField::tmpsignalslot);

    // Добавление клеток
    const int cell_sizeX = (x2 - x1) / COUNTCELL;
    const int cell_sizeY = (y2 - y1) / COUNTCELL;

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            CELLS[i][j].setParent(context);
            CELLS[i][j].setGeometry(x1 + cell_sizeX * j, y1 + cell_sizeY * i, cell_sizeX, cell_sizeY);
            CELLS[i][j].setStyleSheet(GetDesign("BattleFieldFalse"));
            CELLS[i][j].SetXY(i, j);
        }
    }

    for (int i = 0; i < COUNTCELL; i++)
    {
        CELLS[i][0].setParent(context);
        CELLS[i][0].setStyleSheet(GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg"));
        CELLS[i][0].setText(QString::number(i));
        CELLS[i][0].setGeometry(x1, y1 + cell_sizeY * i, cell_sizeX, cell_sizeY);
        CELLS[i][11].setParent(context);
        CELLS[i][11].setStyleSheet(GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg"));
        CELLS[i][11].setText(QString::number(i));
        CELLS[i][11].setGeometry(x1 + cell_sizeX * 11, y1 + cell_sizeY * i, cell_sizeX, cell_sizeY);
    }

    for (int j = 1; j < COUNTCELL; j++)
    {
        CELLS[0][j].setParent(context);
        CELLS[0][j].setStyleSheet(GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg"));
        CELLS[0][j].setText(QString(QChar('A' + j - 1)));
        CELLS[0][j].setGeometry(x1 + cell_sizeX * j, y1, cell_sizeX, cell_sizeY);
        CELLS[11][j].setParent(context);
        CELLS[11][j].setStyleSheet(GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg"));
        CELLS[11][j].setText(QString(QChar('A' + j - 1)));
        CELLS[11][j].setGeometry(x1 + cell_sizeX * j, y1 + cell_sizeY * 11, cell_sizeX, cell_sizeY);
    }

    CELLS[0][0].setText("#");
    CELLS[11][11].setText("#");
    CELLS[11][0].setText("#");
    CELLS[0][11].setText("#");
}


