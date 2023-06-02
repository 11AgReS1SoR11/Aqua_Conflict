
#include "mylib.h"

void CallCompliteWindow(const QString& Text){
    //всплывающее окно, что всё круто
    QMessageBox compite_message;
    compite_message.setText(Text);
    compite_message.exec();
}

QPushButton* CreateButton(QWidget *window, QString text, const int X, const int Y, const int sizeX, const int sizeY, const int sizeFont, const QString& family){
    QPushButton* Button = new QPushButton(text, window); // создаю кнопку
    Button->setGeometry(X, Y, sizeX, sizeY); // указываю размер и координаты
    QFont font = Button->font();
    font.setPointSize(sizeFont);     // устанавливаю размер шрифта
    font.setFamily(family); // шрифт
    font.setBold(true); // жирный
    Button->setFont(font);
    return Button;
}

QLabel* CreateTitle(QWidget *window, QString text, const int X, const int Y, const int sizeX, const int sizeY){
    QLabel* Title = new QLabel(text, window);
    Title->setGeometry(X, Y, sizeX, sizeY);
    Title->setAlignment(Qt::AlignCenter);
    QFont font = Title->font();
    font.setPointSize(25);     // устанавливаю размер шрифта
    //font.setFamily("Pristina"); // шрифт
    font.setBold(true);
    font.setItalic(true);
    Title->setFont(font);
    return Title;
}


QString GetDesign(const QString parametrButton)
{
    const QString filename = QDir::currentPath() + "/Design/" + parametrButton + ".txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray data = file.readAll();
        QString text = QString::fromUtf8(data);
        return text;
    }
}

bool SetBackground(QWidget* window, const QString& ImagePath)
{
    QPixmap bkgnd(ImagePath);
    bkgnd = bkgnd.scaled(window->size(), Qt::IgnoreAspectRatio);
    QPalette p = window->palette();
    p.setBrush(QPalette::Window, bkgnd);
    window->setPalette(p);
    return bkgnd.isNull();
}

bool SetBackground(QPushButton* button, const QString& imagePath)
{
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        return false; // Возвращаем false, если не удалось загрузить изображение
    }
    QSize buttonSize = button->size();
    QPixmap scaledPixmap = pixmap.scaled(buttonSize, Qt::IgnoreAspectRatio);
    QPalette palette = button->palette();
    palette.setBrush(QPalette::Button, scaledPixmap);
    button->setPalette(palette);

    return true;
}


void SetPicture(QLabel* Image, const QString &filename)
{
    QPixmap pixmap(filename);
    pixmap = pixmap.scaled(Image->size(), Qt::KeepAspectRatio);
    Image->setPixmap(pixmap);
    Image->setScaledContents(true);
}

bool writeToFile(const QString &filePath, const QString &content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << content;
    file.close();

    return true;
}

QString readFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    return content;
}
