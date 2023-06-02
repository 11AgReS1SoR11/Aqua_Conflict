#ifndef AI_H
#define AI_H

#include <QPair>

class AI
{
public:
    AI();
    AI(int** field): Field(field) {}
    ~AI();
    void UpdateField(int** newfield);
    virtual QPair<int, int> MakeDecision() = 0;
    virtual void hit(int, int);

protected:
    int** Field;
};

#endif // AI_H
