#include "map.h"

Map::Map(Cell (&A)[12][12]) : CellsArray(A)
{
    const QString filename = QDir::currentPath() + "/Ships_setting/1.txt";
    Fill(filename);
}

void Map::ChangeMap()
{
    const QString filename = GetPathRandomMap();
    Fill(filename);
}

QString Map::GetPathRandomMap()
{
    QString directoryPath = QDir::currentPath();
    QDir directory(directoryPath);
    QString RandomMap;

    if (directory.exists())
    {
        // Устанавливаем фильтр на файлы
        directory.setFilter(QDir::Files);

        // Переходим в папку "Ships_setting"
        directory.cd("Ships_setting");

        QStringList fileList = directory.entryList(QStringList() << "*.txt", QDir::Files);

        if (!fileList.isEmpty())
        {
            // Генерируем случайный индекс
            int randomIndex = QRandomGenerator::global()->bounded(0, fileList.size());
            RandomMap = directory.absoluteFilePath(fileList[randomIndex]);
        }
    }

    return RandomMap;
}

void Map::Fill(const QString& filename)
{
    QFile in(filename);
    if (in.open(QIODevice::ReadOnly))
    {
        QTextStream Stream(&in);
        int ship;
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                Stream >> ship;
                CellsArray[i][j].SetShip(ship);
                CellsArray[i][j].SetUsed(0);
            }
        }
    }
    else
    {
        qDebug() << "Can't read file";
    }
}
