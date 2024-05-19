#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QRandomGenerator>
#include <QFile>
#include <QDir>

#include "cell.h"

class Map
{
public:
    Map(Cell (&A)[12][12]);
    void ChangeMap();
    QString GetPathRandomMap();

private:
    Cell(&CellsArray)[12][12];
    void Fill(const QString& filename);
};

#endif // MAP_H
