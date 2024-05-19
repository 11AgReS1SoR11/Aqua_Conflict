#ifndef EASYAI_H
#define EASYAI_H

#include <QRandomGenerator>
#include <QPair>

#include "ai.h"

class EasyAI : public AI
{
public:
    EasyAI() : AI() {}
    EasyAI(int** A) : AI(A) {}
    QPair<int, int> MakeDecision();
};

#endif // EASYAI_H
