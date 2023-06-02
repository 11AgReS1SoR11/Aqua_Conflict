
#include "battlewindow.h"

BattleWindow::BattleWindow(int activeHit, int activeMiss, QWidget *parent)
    : QMainWindow{parent}, ActiveHit(activeHit), ActiveMiss(activeMiss)
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle("Aqua_Conflict");

    int sizeX = 450, sizeY = 450;
    Field1 = new BattleField((WINDOW_WIDTH / 2 - sizeX) / 2, (WINDOW_HEIGHT - sizeY) / 2, sizeX, sizeY, this);
    Field2 = new BattleField((WINDOW_WIDTH / 2 * 3 - sizeX) / 2, (WINDOW_HEIGHT - sizeY) / 2, sizeX, sizeY, this);
    Field2->ChangeShips();
    Field2->Close();
    Field1->Open();

    sizeX = 100, sizeY = 75;
    change = new QPushButton("Change", this);
    change->setGeometry((WINDOW_WIDTH / 2 - sizeX) / 2, WINDOW_HEIGHT - sizeY * 1.5, sizeX, sizeY);

    sizeX = 100, sizeY = 60;
    returnbutton = new QPushButton("Back", this);
    returnbutton->setGeometry(WINDOW_WIDTH  - sizeX, 0, sizeX, sizeY);


    sizeX = 400, sizeY = 75;
    start = new QPushButton("GO", this);
    start->setGeometry((WINDOW_WIDTH - sizeX) / 2, WINDOW_HEIGHT - sizeY * 1.5, sizeX, sizeY );

    sizeX = 200, sizeY = 60;
    player1 = new QLabel("PLAYER_1", this);
    player1->setAlignment(Qt::AlignCenter);
    player1->setGeometry(Field1->getX() + (Field1->width() - sizeX) / 2, Field1->getY() - sizeY, sizeX, sizeY);

    player2 = new QLabel("PLAYER_2", this);
    player2->setAlignment(Qt::AlignCenter);
    player2->setGeometry(Field2->getX() + (Field2->width() - sizeX) / 2, Field2->getY() - sizeY, sizeX, sizeY);

    sizeX = Field2->getX() - (Field1->getX() + Field1->width() + 5) - 5, sizeY = 75;
    Turn = new QLabel("", this);
    Turn->setAlignment(Qt::AlignCenter);
    Turn->setGeometry(Field1->getX() + Field1->width() + 5,  Field1->getY() + Field1->width() / 5, sizeX, sizeY);
    Turn->hide();

    sizeX = 400, sizeY = 60;
    LastTurn = new QLabel("Last turn: ", this);
    LastTurn->setAlignment(Qt::AlignCenter);
    LastTurn->setGeometry(0,  0, sizeX, sizeY);

    sizeX = 150, sizeY = 100;
    counter = new QLabel("Score\n20:20", this);
    counter->setAlignment(Qt::AlignCenter);
    counter->setGeometry((WINDOW_WIDTH - sizeX) / 2, (WINDOW_HEIGHT - sizeY) / 2, sizeX, sizeY);

    connect(start, &QPushButton::clicked, this, &BattleWindow::onStartButtonClicked);
    connect(change, &QPushButton::clicked, this, &BattleWindow::onChangeButtonClicked);
    connect(returnbutton, &QPushButton::clicked, this, &BattleWindow::onReturnButtonClicked);
    connect(Field1, &BattleField::tmpsignal, this, &BattleWindow::NextStep);
    connect(Field2, &BattleField::tmpsignal, this, &BattleWindow::NextStep);
    connect(Field1, &BattleField::Hitsignal, this, &BattleWindow::Scoreboard);
    connect(Field2, &BattleField::Hitsignal, this, &BattleWindow::Scoreboard);
    // обработчик победы
    connect(Field1, &BattleField::Hitsignal, this, &BattleWindow::CСССongratulationsWin);
    connect(Field2, &BattleField::Hitsignal, this, &BattleWindow::CСССongratulationsWin);


    SetDesign();
    Field1->SetHitSettings(GetDesign("BattleFieldTrue").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boom" + QString::number(ActiveHit+1) + ".png"));
    Field1->SetMissSettings(GetDesign("BattleFieldTrue").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boubles" + QString::number(ActiveMiss+1) + ".png"));
    Field2->SetHitSettings(GetDesign("BattleFieldTrue").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boom" + QString::number(ActiveHit+1) + ".png"));
    Field2->SetMissSettings(GetDesign("BattleFieldTrue").arg(QDir::currentPath() + "/Design/Settings/BattleShip_Boubles" + QString::number(ActiveMiss+1) + ".png"));
}

BattleWindow::~BattleWindow()
{
    delete Field1;
    delete Field2;
    delete start;
    delete change;
    delete returnbutton;
    delete player1;
    delete player2;
    delete Turn;
    delete LastTurn;
    delete counter;
}

void BattleWindow::SetDesign()
{
    QString ButtonsDesign = GetDesign("MainButtons").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg");
    start->setStyleSheet(ButtonsDesign);
    change->setStyleSheet(ButtonsDesign);
    returnbutton->setStyleSheet(ButtonsDesign);

    const QString TitleDesign = GetDesign("PlayTitles").arg(QDir::currentPath() + "/Design/BattleShip_WoodBackground.jpg");
    player1->setStyleSheet(TitleDesign);
    player2->setStyleSheet(TitleDesign);
    Turn->setStyleSheet(TitleDesign);
    LastTurn->setStyleSheet(TitleDesign);
    counter->setStyleSheet(TitleDesign);

    SetBackground(this, QDir::currentPath() + "/Design/BattleShip_Paluba.png");
}

// жеребьёвка
int BattleWindow::Drawing()
{
    return QRandomGenerator::global()->bounded(1, 3);
}

int BattleWindow::GetWidth()
{
    return WINDOW_WIDTH;
}

int BattleWindow::GetHeight()
{
    return WINDOW_HEIGHT;
}

void BattleWindow::ChangeStartButtonText(const QString &text)
{
    start->setText(text);
}

QString BattleWindow::Player1Name()
{
    return player1->text();
}

QString BattleWindow::Player2Name()
{
    return player2->text();
}

void BattleWindow::BlockChange1Button()
{
    change->setEnabled(false);
}

void BattleWindow::onStartButtonClicked()
{
    // начинается игра
    if (Drawing() == 1)
    {
        Turn->setText("Turn:\n" + player1->text());
        Field2->IsClickable(true);
    }
    else
    {
        Turn->setText("Turn:\n" + player2->text());
        Field1->IsClickable(true);
    }
    Turn->show();
    start->setEnabled(false);
    change->setEnabled(false);
}

void BattleWindow::onChangeButtonClicked()
{
    Field1->ChangeShips();
}

void BattleWindow::onReturnButtonClicked()
{
    parentWidget()->show();
    this->close();
}

void BattleWindow::NextStep(QPair<int, int> XY)
{
    BattleField* ClickedField = qobject_cast<BattleField*>(sender());
    if (ClickedField) {
        if (ClickedField == Field1) {
            Field1->IsClickable(false);
            Field2->IsClickable(true);
            Turn->setText("Turn:\n" + player1->text());
            LastTurn->setText("Last turn: " + player2->text() + "  (" + QString::number(XY.first) + "-" + QString(QChar('A' + XY.second - 1)) + ")");
        } else if (ClickedField == Field2) {
            Field1->IsClickable(true);
            Field2->IsClickable(false);
            Turn->setText("Turn:\n" + player2->text());
            LastTurn->setText("Last turn: " + player1->text() + "  (" + QString::number(XY.first) + "-" + QString(QChar('A' + XY.second - 1)) + ")");
        }
    }
}

GetModeWindow* BattleWindow::СongratulationsWin()
{
    if (Field1->HowMuchShips() != 0 && Field2->HowMuchShips() != 0)
        return nullptr; // никто не проиграл
    GetModeWindow* win = new GetModeWindow("Retry", "Back", this);
    if (Field1->HowMuchShips() == 0) win->SetLabel("Win: " + player2->text());
    else win->SetLabel("Win: " + player1->text());
    win->setWindowTitle("Сongratulations");
    return win;
}

void BattleWindow::CСССongratulationsWin()
{
    GetModeWindow* win = СongratulationsWin();
    if (win)
    {
        connect(win, &GetModeWindow::Result, this, &BattleWindow::GetChoose);
        win->exec();
    }
}

void BattleWindow::RestartAllWidgets()
{
    change->setEnabled(true);
    start->setEnabled(true);
    LastTurn->setText("Last turn: ");
    counter->setText("Score\n20:20");
    Turn->setText("");

    Field2->ChangeShips();
    Field1->ChangeShips();

    Field1->Close();
    Field2->Close();
    Field1->Open();
    Field1->SetCount(20);
    Field2->SetCount(20);

    Field1->IsClickable(false);
    Field2->IsClickable(false);
}

void BattleWindow::GetChoose(int res)
{
    if (res)
    {
        RestartAllWidgets();
    }
    else
    {
        this->parentWidget()->show();
        this->close();
    }
}

void BattleWindow::Scoreboard(QPair<int, int> XY)
{
    BattleField* ClickedField = qobject_cast<BattleField*>(sender());
    if (ClickedField) {
        if (ClickedField == Field1) {
            Turn->setText("Turn:\n" + player1->text());
            LastTurn->setText("Last turn: " + player2->text() + "  (" + QString::number(XY.first) + "-" + QString(QChar('A' + XY.second - 1)) + ")");
        } else if (ClickedField == Field2) {
            Turn->setText("Turn:\n" + player2->text());
            LastTurn->setText("Last turn: " + player1->text() + "  (" + QString::number(XY.first) + "-" + QString(QChar('A' + XY.second - 1)) + ")");
        }
    }
    counter->setText("Score\n" + QString::number(Field1->HowMuchShips()) + ":" + QString::number(Field2->HowMuchShips()));
}
