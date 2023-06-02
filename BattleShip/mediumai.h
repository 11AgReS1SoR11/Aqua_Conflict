#ifndef MEDIUMAI_H
#define MEDIUMAI_H

#include <ai.h>
#include <QRandomGenerator>
#include <QPair>

class MediumAI : public AI
{
public:
    MediumAI() : AI(), HitLast{-1, -1} {}
    MediumAI(int** field) : AI(field), HitLast{-1, -1} {}
    QPair<int, int> MakeDecision();
    void hit(int, int);
    bool EnableTurn(int, int);
    bool CheckForKillShip(int, int);
    bool CheckForDoubleHit();
    QPair<int, int> FinishHim(int, int);

private:
    QPair<int, int> HitLast;
};

#endif // MEDIUMAI_H
