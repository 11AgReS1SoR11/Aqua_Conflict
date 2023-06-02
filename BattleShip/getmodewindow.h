#ifndef GETMODEWINDOW_H
#define GETMODEWINDOW_H

#include <QDialog>
#include <mylib.h>
#include <QString>

class GetModeWindow : public QDialog
{
    Q_OBJECT
public:
    GetModeWindow(QWidget *parent = nullptr);
    GetModeWindow(const QString AgreeWord, const QString DisagreeWord, QWidget *parent = nullptr);
    ~GetModeWindow();
    void SetDesign();
    void SetLabel(const QString text);


signals:
    void Result(int);

private slots:
    void onYesButtonClicked();
    void onNoButtonClicked();

private:
    QPushButton* Yes;
    QPushButton* No;
    QLabel* Text;
};

#endif // GETMODEWINDOW_H
