#include "easyai.h"

QPair<int, int> EasyAI::MakeDecision()
{
    int X = QRandomGenerator::global()->bounded(1, 11);
    int Y = QRandomGenerator::global()->bounded(1, 11);
    QPair<int, int> A = {X, Y};
    return A;
}
