#ifndef EASYAI_H
#define EASYAI_H

#include <ai.h>
#include <QRandomGenerator>
#include <QPair>

class EasyAI : public AI
{
public:
    EasyAI() : AI() {}
    EasyAI(int** A) : AI(A) {}
    QPair<int, int> MakeDecision();
};

#endif // EASYAI_H
