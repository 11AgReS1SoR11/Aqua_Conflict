#include "ai.h"

AI::AI()
{
    Field = new int*[12];
    for (int i = 0; i <= 11; ++i)
        Field[i] = new int[12];

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            Field[i][j] = 0;

    for (int j = 0; j <= 11; j++) Field[0][j] = 1;
    for (int i = 0; i <= 11; i++) Field[i][0] = 1;
    for (int j = 0; j <= 11; j++) Field[11][j] = 1;
    for (int i = 0; i <= 11; i++) Field[i][11] = 1;
}

AI::~AI()
{
    if (Field != nullptr)
    {
        for (int i = 0; i <= 11; ++i)
            if (Field[i] != nullptr)
                delete Field[i];
        delete Field;
    }
}

void AI::UpdateField(int **newfield)
{
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (Field[i][j] != 2)
                Field[i][j] = newfield[i][j];

    for (int i = 0; i <= 10; ++i)
        delete[] newfield[i];
    delete[] newfield;
}

void AI::hit(int x, int y)
{
    Field[x][y] = 2;
}
