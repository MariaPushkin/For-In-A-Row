#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QSlider>

#include "game.h"
#include "other.h"
#include "user.h"
#include "mylist.h"
#include "dialogs.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void addBear();
    void addRabbit();
    void showName(std::string);   //отображение имени игрока, выбранного для игры
    void closeEvent(QCloseEvent *);
    void fromFile();
private:
    QWidget *centralWidget;
    QPushButton *gameButton;
    QPushButton *stateButton;
    QPushButton *exitButton;
    QPushButton *loginButton;
    QPushButton *regButton;
    QPushButton *logoutButton;

    QSlider *firstStep;
    QLabel *stepLab;
    //QLabel *login;
    //QLabel *password;
    QLabel *hello;
    //QLineEdit *loginEdit;
    //QLineEdit *passEdit;
    QLabel *turn1;
    QLabel *turn2;
    //QLabel *picture;

    QPushButton *colm1;
    QPushButton *colm2;
    QPushButton *colm3;
    QPushButton *colm4;
    QPushButton *colm5;
    QPushButton *colm6;
    QPushButton *colm7;

    //gameCircle **ms;

    QGraphicsView *showBox;   //поле игры
    QGraphicsScene *scene;
    //QGraphicsEllipseItem **circl;  //кружки для игры

    circle **elements;   //элементы игры

    bool turn; //ход true = игрок, false = компьютер

    game *curgame;
    bool isGame;
    bool frStep;
    bool isLogin;  //залогинен ли игрок
    int gamerType; //кролик(2) или мишка(1)
    int playerNum;  //номер икрока в списке

    list<bear> bearList;
    list<rabbit> rabbitList;

    stateWindow *stateWin;
    inputDialog *logDialog;
    inputDialog *regDialog;
private slots:
    void course();  //ход игрока(раскраска соответствующего кружка)
    void newGame();
    void setFirstStep(int);
    void showState();
    void registration();
    void login();
    void searchUser();
    void addUser();
    void logout();
};

#endif // GAMEWINDOW_H
