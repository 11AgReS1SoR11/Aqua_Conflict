#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>

#include "mylib.h"

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    void SetDesign();
    void SetActiveImg(int, int);

signals:
    void EndSetting(int, int);

private slots:
    void onOkButtonClicked();

private:
    QPushButton* Boom1 = nullptr;
    QPushButton* Boom2 = nullptr;
    QPushButton* Boom3 = nullptr;
    QPushButton* Boubles1 = nullptr;
    QPushButton* Boubles2 = nullptr;
    QPushButton* Boubles3 = nullptr;
    QLabel* FrameBoom;
    QLabel* FrameBouble;
    int ActiveBoom = 2;
    int ActiveBouble = 0;
    QPushButton* Ok;
};

#endif // SETTINGS_H
