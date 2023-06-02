
#ifndef MYLIB_H
#define MYLIB_H

#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>

void CallCompliteWindow(const QString& Text);
QPushButton* CreateButton(QWidget *window, QString text, const int X, const int Y, const int sizeX, const int sizeY, const int sizeFont, const QString& family = "Calibri");
QLabel* CreateTitle(QWidget *window, QString text, const int X, const int Y, const int sizeX, const int sizeY);
QString GetDesign(const QString parametrButton);
bool SetBackground(QWidget* window, const QString& ImagePath);
bool SetBackground(QPushButton* button, const QString& imagePath);
void SetPicture(QLabel* Image, const QString &filename);
bool writeToFile(const QString &filePath, const QString &content);
QString readFromFile(const QString& filePath);

#endif // MYLIB_H
