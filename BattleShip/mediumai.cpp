#include "mediumai.h"

QPair<int, int> MediumAI::MakeDecision()
{
    int X = 0, Y = 0;
    // если в последний раз попали и не убили
    if (HitLast.first != -1 && !CheckForKillShip(HitLast.first, HitLast.second))
    {
        if (CheckForDoubleHit())
        {
            return FinishHim(HitLast.first, HitLast.second);
        }
        // стреляем вокруг
        while (!EnableTurn(X,Y))
        {
            int Randum = QRandomGenerator::global()->bounded(0, 2);
            if (Randum) // меняем x
            {
                X = QRandomGenerator::global()->bounded(HitLast.first-1, HitLast.first+2);
                Y = HitLast.second;
            }
            else // меняем y
            {
                X = HitLast.first;
                Y = QRandomGenerator::global()->bounded(HitLast.second-1, HitLast.second+2);
            }
        }
    }
    else
    {
        while (!EnableTurn(X,Y))
        {
            X = QRandomGenerator::global()->bounded(1, 11);
            Y = QRandomGenerator::global()->bounded(1, 11);
        }
    }
    return QPair<int, int>(X, Y);
}

bool MediumAI::EnableTurn(int X, int Y)
{
    if (!(X > 0 && X <= 10 && Y > 0 && Y <= 10))
        return false;
    if (Field[X][Y] != 0)
        return false;

    return true;
}

void MediumAI::hit(int x, int y)
{
    HitLast.first = x;
    HitLast.second = y;
    AI::hit(x, y); // корабль
}

bool MediumAI::CheckForKillShip(int x , int y)
{
    // если он одиночный
    if (Field[x][y] == 2 && Field[x-1][y] == 1 && Field[x+1][y] == 1 && Field[x][y-1] == 1 && Field[x][y+1] == 1)
        return true;

    // если он вертикально
    if (Field[x][y] == 2 && (Field[x-1][y] == 2 || Field[x+1][y] == 2))
    {
        int i = 1;
        while (Field[x-i][y] == 2) i++;
        if (Field[x-i][y] == 1)
        {
            i = 1;
            while (Field[x+i][y] == 2) i++;
            if (Field[x+i][y] == 1)
                return true;
            else
                return false;
        }
        return false;
    }
    // если он горизонтально
    if (Field[x][y] == 2 && (Field[x][y-1] == 2 || Field[x][y+1] == 2))
    {
        int i = 1;
        while (Field[x][y-i] == 2) i++;
        if (Field[x][y-i] == 1)
        {
            i = 1;
            while (Field[x][y+i] == 2) i++;
            if (Field[x][y+i] == 1)
                return true;
            else
                return false;
        }
        return false;
    }

    return false;
}

QPair<int, int> MediumAI::FinishHim(int x, int y)
{
   // если он горизонтально
    if (Field[x-1][y] == 2 || Field[x+1][y] == 2)
    {
        int i = 1;
        while (Field[x-i][y] == 2) i++;
        if (Field[x-i][y] == 1)
        {
            i = 1;
            while (Field[x+i][y] == 2) i++;
            return QPair<int, int>(x+i, y);
        }
        return QPair<int, int>(x-i, y);
    }
    // если он вертикально
    if (Field[x][y-1] == 2 || Field[x][y+1] == 2)
    {
        int i = 1;
        while (Field[x][y-i] == 2) i++;
        if (Field[x][y-i] == 1)
        {
            i = 1;
            while (Field[x][y+i] == 2) i++;
            return QPair<int, int>(x, y+i);

        }
        return QPair<int, int>(x, y-i);
    }

    return QPair<int, int>(QRandomGenerator::global()->bounded(1, 11), QRandomGenerator::global()->bounded(1, 11));
}

bool MediumAI::CheckForDoubleHit()
{
    // если мы попали 2 раза
    if (Field[HitLast.first][HitLast.second] == 2 && (Field[HitLast.first][HitLast.second-1] == 2 || Field[HitLast.first][HitLast.second+1] == 2 || Field[HitLast.first-1][HitLast.second] == 2 || Field[HitLast.first+1][HitLast.second] == 2))
        return true;
    return false;
}
