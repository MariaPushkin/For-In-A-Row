#include "gamewindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGraphicsScene>
//#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QTextStream>

#include <time.h>


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor::fromRgb(127,134,148));;
    this->setPalette(palette);
    //this->setStyleSheet("background-color: rgb(216,209,209)");
    this->setStyleSheet("QPushButton { color: white ; background-color: rgb(20,44,138); font: bold 13px;} QPushButton:hover { background-color: rgb(75,93,164)} ");

    gameButton = new QPushButton("New game");
    //gameButton->setStyleSheet("color: black ; background-color: rgb(154,179,143); font: bold 15px; min-width: 4em; padding: 8px;");
    //gameButton->setStyleSheet(":hover { background-color: rgb(155,17,143);}");
    stateButton = new QPushButton("Statistic");
    exitButton = new QPushButton("Exit");
    turn1 = new QLabel("⊙﹏⊙");
    turn1->setStyleSheet("font : bold 120px");
    turn2 = new QLabel("⊙﹏⊙");
    turn2->setStyleSheet("font : bold 120px");
    stepLab = new QLabel("First step - \n user");
    stepLab->setStyleSheet("color: white; font : bold 15px");
    firstStep = new QSlider(Qt::Horizontal);
    firstStep->setRange(0,1);
    firstStep->setValue(0);
    //picture = new QLabel();

    //QPalette pic;
    //pic.setBrush(picture->backgroundRole(), QBrush(QPixmap("1.jpg")));
    //pic.setBrush(picture->backgroundRole(), QBrush(QPixmap("2.png")));
    //picture->setPalette(pic);
    //picture->resize(100,200);
    //picture->setAutoFillBackground(true);

    /*QVBoxLayout *left = new QVBoxLayout;
    //left->addStretch(1);
    left->addWidget(gameButton);
    left->addWidget(stepLab);
    left->addWidget(firstStep);
    left->addWidget(setButton);
    left->addWidget(exitButton);
    //left->addStretch(2);
    //left->addWidget(turn1);
    //left->addWidget(turn2);*/

    QGridLayout *left = new QGridLayout;
    left->addWidget(turn1,0,40,5,50);
    left->addWidget(gameButton,10,50,1,20);
    left->addWidget(stepLab,11,50,1,20);
    left->addWidget(firstStep,12,50,1,20);
    left->addWidget(stateButton,13,50,1,20);
    left->addWidget(exitButton,14,50,1,20);
    //left->addWidget(picture,12,0,8,50);
    left->addWidget(turn2,15,40,5,50);

    /*QVBoxLayout *forPic = new QVBoxLayout;
    forPic->addWidget(picture);

    QVBoxLayout *mainLeft = new QVBoxLayout;
    mainLeft->addStretch(2);
    mainLeft->addLayout(left);
    mainLeft->addStretch(1);
    mainLeft->addLayout(forPic);*/

    //turn2->setText("!!!!");

    loginButton = new QPushButton("Login");
    logoutButton = new QPushButton("Logout");
    regButton = new QPushButton("Registration");
    hello = new QLabel("Hello, Nick!");
    hello->setStyleSheet("color: black ; background-color: rgb(127,134,148); font: bold 13px;");
    logoutButton->setVisible(false);
    hello->setVisible(false);

    QHBoxLayout  *log = new QHBoxLayout;
    log->addStretch(1);
    log->addWidget(loginButton);
    log->addWidget(regButton);
    log->addWidget(hello);
    log->addWidget(logoutButton);

    colm1 = new QPushButton("1");
    colm2 = new QPushButton("2");
    colm3 = new QPushButton("3");
    colm4 = new QPushButton("4");
    colm5 = new QPushButton("5");
    colm6 = new QPushButton("6");
    colm7 = new QPushButton("7");

    /*ms = new gameCircle* [7]; // семь строк в массиве
    for (int count = 0; count < 7; count++)
        ms[count] = new gameCircle [6];*/
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addStretch(1);
    buttons->addWidget(colm1);
    buttons->addWidget(colm2);
    buttons->addWidget(colm3);
    buttons->addWidget(colm4);
    buttons->addWidget(colm5);
    buttons->addWidget(colm6);
    buttons->addWidget(colm7);
    buttons->addStretch(1);

    showBox = new QGraphicsView;
    //showBox->setFixedSize(600,600);
    showBox->setMinimumSize(800,750);
    showBox->setMaximumSize(1000,1000);
    showBox->setStyleSheet("background-color: rgb(127,134,148);");

    scene = new QGraphicsScene;
    showBox->setScene(scene);

    //QPainter p(this); // Создаём новый объект рисовальщика
    QPen pen(Qt::black);
    QBrush brush(Qt::white, Qt::SolidPattern);
    pen.setWidth(2);
    //p.setPen(pen);
    //circl = new QGraphicsEllipseItem* [42]; // 42 элемента в массиве
        //for (int count = 0; count < 7; count++)
           // circle[count] = new QGraphicsEllipseItem[6];
    //circle[42] = new QGraphicsEllipseItem[42];
    /*int n = 0;
    for(int i=10;i<=610;i=i+120)
        for(int j=10;j<=670;j=j+110)
            circl[n++] = scene->addEllipse(j,i,100,100,pen,brush);*/

    elements = new circle* [6];   //6 строк
    for (int count = 0; count < 6; count++)
        elements[count] = new circle[7];   //7 столбцов

    for(int i=10,a=0;i<=610;i=i+120,a++)
        for(int j=10,b=0;j<=670;j=j+110,b++)
            elements[a][b].setCir(scene->addEllipse(j,i,100,100,pen,brush));
    //circle[0] = scene->addEllipse(10,10,100,100,pen,brush);
    //circle[1] = scene->addEllipse(130,10,100,100,pen,brush);
    //circle[2] = scene->addEllipse(250,10,100,100,pen,brush);
    //circle[3] = scene->addEllipse(370,10,100,100,pen,brush);
    //circle[4] = scene->addEllipse(490,10,100,100,pen,brush);
    //circle[5] = scene->addEllipse(610,10,100,100,pen,brush);
    //p.setBrush(QBrush(Qt::white, Qt::SolidPattern));  //раскраска внутренности
    //p.drawEllipse(5,5,width()-10,height()-10);
    //circle[2]->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    //if(circl[3]->isSelected()) circl[2]->setBrush(QBrush(Qt::red, Qt::SolidPattern));

    QHBoxLayout *ll = new QHBoxLayout;
    //ll->addStretch(1);
    ll->addWidget(showBox);
    //ll->addStretch(1);

    //buttons->addWidget(showBox,1,0,7,6);

    /*for (int i = 1; i < 8; i++)
        for (int j = 0; j < 6; j++)
            field->addWidget(&(ms[i-1][j]),i,j);*/
    QGroupBox *fieldBox = new QGroupBox;
    fieldBox->setLayout(ll);

    QVBoxLayout *right = new QVBoxLayout;
    right->addLayout(log);
    right->addLayout(buttons);
    right->addWidget(fieldBox);


    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget); //центральный слой
    mainLayout->addLayout(left);
    //mainLayout->addLayout(mainLeft);
    mainLayout->addLayout(right);

    isGame = false; //игра еще не начата
    frStep = true;   //по умолчанию первый ход человека

    connect(gameButton,SIGNAL(clicked(bool)),this,SLOT(newGame()));
    connect(colm1,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(colm2,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(colm3,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(colm4,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(colm5,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(colm6,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(colm7,SIGNAL(clicked(bool)),this,SLOT(course()));
    connect(firstStep,SIGNAL(valueChanged(int)),this,SLOT(setFirstStep(int)));
    connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(stateButton,SIGNAL(clicked(bool)),this,SLOT(showState()));
    connect(loginButton,SIGNAL(clicked(bool)),this,SLOT(login()));
    connect(regButton,SIGNAL(clicked(bool)),this,SLOT(registration()));
    connect(logoutButton,SIGNAL(clicked(bool)),this,SLOT(logout()));

    //bear *a = new bear("Lisa",5,6,7);
    //bear *b = new bear("Vitalii",3,4,6);
    //bear *c = new bear("c",3,6,2);
    //bearList.push(a);
    //bearList.push(b);
    //bearList.push(c);
    fromFile();
}

void GameWindow::fromFile()       //чтение из файла
{
    QFile myFile("MYFILE.txt");
    if(!myFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,"Error","Somthing wrong with statistic file! 1");
        return;
    }
    //myFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&myFile);
    QString bf, ln1,s1,s2, s3,s4;
    std::string str;
    int ln;
    int n1,n2,n3,n4;
    //ln = stream.readLine().toInt();
    stream >> ln1;                   //считали длину первого списка
    ln = deCode(ln1.toStdString());   //расшифровка
    if(ln < -1)
    {
        QMessageBox::information(this,"Error","Somthing wrong with statistic file! 2");
        myFile.flush();
        myFile.close();
        return;
    }
    if(ln != -1)    //если -1, то список останентся пустым
    {
        while(bearList.getLength() < ln)
        {
            bear *ads = new bear();
            //str = stream.readLine().toStdString();
            stream >> bf;
            str = deCodes(bf.toStdString());
            if(!ads->setName(str))
            {
                QMessageBox::information(this,"Error","Somthing wrong with statistic file! 3");
                myFile.flush();
                myFile.close();
                return;
            }
            //ads->setName(str);
            stream >> s1;
            n1 = deCode(s1.toStdString());
            stream >> s2;
            n2 = deCode(s2.toStdString());
            stream >> s3;
            n3 = deCode(s3.toStdString());
            stream >> s4;
            n4 = deCode(s4.toStdString());
            //if(checkOther(n1,n2,n3,n4)) ads->setOther(n1,n2,n3,n4);
            if(!ads->setOther(n1,n2,n3,n4))
            {
                QMessageBox::information(this,"Error","Somthing wrong with statistic file! 4");
                myFile.flush();
                myFile.close();
                return;
            }
            stream >> s1;
            n1 = deCode(s1.toStdString());
            stream >> s2;
            n2 = deCode(s2.toStdString());
            //stream >> n3;
            stream >> s3;
            n3 = deCode(s3.toStdString());
            //if(checkDate(n1,n2,n3)) ads->setDate(n1,n2,n3);
            if(!ads->setDate(n1,n2,n3))
            {
                QMessageBox::information(this,"Error","Somthing wrong with statistic file! 5");
                myFile.flush();
                myFile.close();
                return;
            }
            bearList.push(ads);
        }
    }
    stream >> ln1;
    ln = deCode(ln1.toStdString());
    if(ln < -1)
    {
        QMessageBox::information(this,"Error","Somthing wrong with statistic file! 6");
        myFile.flush();
        myFile.close();
        return;
    }
    if(ln != -1)
    {
        while(rabbitList.getLength() < ln)
        {
            rabbit *ads = new rabbit();
            stream >> bf;
            str = deCodes(bf.toStdString());
            if(!ads->setName(str))
            {
                QMessageBox::information(this,"Error","Somthing wrong with statistic file! 7");
                myFile.flush();
                myFile.close();
                return;
            }
            //ads->setName(str);
            stream >> s1;
            n1 = deCode(s1.toStdString());
            stream >> s2;
            n2 = deCode(s2.toStdString());
            stream >> s3;
            n3 = deCode(s3.toStdString());
            stream >> s4;
            n4 = deCode(s4.toStdString());
            if(!ads->setOther(n1,n2,n3,n4))
            {
                QMessageBox::information(this,"Error","Somthing wrong with statistic file! 8");
                myFile.flush();
                myFile.close();
                return;
            }
            stream >> s1;
            n1 = deCode(s1.toStdString());
            stream >> s2;
            n2 = deCode(s2.toStdString());
            //stream >> n3;
            stream >> s3;
            n3 = deCode(s3.toStdString());
            if(!ads->setDate(n1,n2,n3))
            {
                QMessageBox::information(this,"Error","Somthing wrong with statistic file! 9");
                myFile.flush();
                myFile.close();
                return;
            }
            rabbitList.push(ads);
        }
    }
    myFile.flush();
    myFile.close();
}

GameWindow::~GameWindow()
{
    //wgt1->deleteLater();
}


void GameWindow::course()   //ход
{
    if(isGame)
    {
        int a;
        int y;
        //определяем какая из кнопок была нажата
        if(QObject::sender() == colm1) {a = curgame->getp(0); y = 0;}    //от какой из 7 кнопок пришел сигнал
        if(QObject::sender() == colm2) {a = curgame->getp(1); y = 1;}
        if(QObject::sender() == colm3) {a = curgame->getp(2); y = 2;}
        if(QObject::sender() == colm4) {a = curgame->getp(3); y = 3;}
        if(QObject::sender() == colm5) {a = curgame->getp(4); y = 4;}
        if(QObject::sender() == colm6) {a = curgame->getp(5); y = 5;}
        if(QObject::sender() == colm7) {a = curgame->getp(6); y = 6;}

        if(a == 0) return;
        elements[a-1][y].colored(1);  //окрашиваем соответствующий кружок
        curgame->incp(y); //увеличили значение заполненности соответсвующего столбика
        int endG = curgame->isVictory();
        if (endG == 1 || endG == 3)   //проверяем победу игрока или ничью
        {
            QMessageBox msg;
            if(endG == 1)
            {
                msg.setText("You win!");
                if(gamerType == 1) bearList[playerNum].makeWin();
                if(gamerType == 2) rabbitList[playerNum].makeWin();
            }
            else
            {
                msg.setText("Its is a draw!");
                if(gamerType == 1) bearList[playerNum].makeDraw();
                if(gamerType == 2) rabbitList[playerNum].makeDraw();
            }
            msg.exec();
            isGame = false;   //ставим флаг, что игра не идет
        }
        else
        {
            curgame->course(2,0);   //оценка хода и сам ход компьютера
            endG = curgame->isVictory();
            if (endG == 2 || endG == 3)   //проверяем победу компьютера
            {
                QMessageBox msg;
                if(endG == 2)
                {
                    msg.setText("You lose!");
                    if(gamerType == 1) bearList[playerNum].makeLose();
                    if(gamerType == 2) rabbitList[playerNum].makeLose();
                }
                else
                {
                    msg.setText("Its is a draw!");
                    if(gamerType == 1) bearList[playerNum].makeDraw();
                    if(gamerType == 2) rabbitList[playerNum].makeDraw();
                }
                msg.exec();
                isGame = false;
            }
        }
    }
}

void GameWindow::newGame()
{
    if(!isGame)   //если игра не идет
    {
        if(!isLogin)   //если игрок не в системе
        {
            QMessageBox msg;
            msg.setText("Login or register!");
            msg.exec();
        }
        else
        {
            for(int i = 0;i < 6;i++)    //очистка поля
                for(int j = 0;j < 7;j++)
                    elements[i][j].colored(0);
            curgame = new game(elements);   //создание игры
            isGame = true;          //флаг - идет игра
            if(frStep == false) curgame->course(2,0);   //если компьютер ходит первый, то он делает ход
        }
    }
}

void GameWindow::setFirstStep(int a)   //в зависимости от того, кто выбран для первого хода показывается текст
{
    if(a == 0) {stepLab->setText("First step -\n user"); frStep=true;}
    if(a == 1) {stepLab->setText("First step -\n computer"); frStep=false;}
}

void GameWindow::showState()   //показ статистики
{
    stateWin = new stateWindow(this);
    stateWin->show();
    if(!bearList.isEmpty())
    {
        node<bear> *curr = new node<bear>;
        curr = bearList.getTop();
        for(int i = 0; i <= bearList.getLength(); i++)
        {
            stateWin->showBears->append(QString::fromStdString(curr->data->print()));
            stateWin->showBears->append("\n");
            curr = curr->next;
        }
    }
    else
        stateWin->showBears->append(QString::fromStdString("Bears would be here!"));
    if(!rabbitList.isEmpty())
    {
        node<rabbit> *curr = new node<rabbit>;
        curr = rabbitList.getTop();
        for(int i = 0; i <= rabbitList.getLength(); i++)
        {
            stateWin->showRabbits->append(QString::fromStdString(curr->data->print()));
            stateWin->showRabbits->append("\n");
            curr = curr->next;
        }
    }
    else
        stateWin->showRabbits->append(QString::fromStdString("Rabbits would be here!"));
}

void GameWindow::registration()    //регистрация игрока
{
    regDialog = new inputDialog(this);
    regDialog->show();
    //regDialog->exec();
    connect(regDialog->confirmButton,SIGNAL(clicked(bool)),this,SLOT(addUser()));
}

void GameWindow::login()
{
    logDialog = new inputDialog(this);
    logDialog->show();
    //logDialog->exec();
    connect(logDialog->confirmButton,SIGNAL(clicked(bool)),this,SLOT(searchUser()));
}

void GameWindow::logout()   //показать кнопки входа и регистрации и скрыть кнопку выхода, если игрок вышел из системы
{
    isLogin = false;
    loginButton->setVisible(true);
    regButton->setVisible(true);
    logoutButton->setVisible(false);
    hello->setVisible(false);
}

void GameWindow::addUser()  //добавление новго пользователя в список
{
    if(regDialog->getTeam() == 0)
    {
        QMessageBox msg;
        msg.setText("Choose your team!");
        msg.exec();
    }
    else
    {
        if(regDialog->getTeam() == 1)   //тип команды
        {
            gamerType = 1;
            this->addBear();
        }
        else if(regDialog->getTeam() == 2)
        {
            gamerType = 2;
            this->addRabbit();
        }
    }
}

void GameWindow::addBear()  //добавление мишки
{
    bool ch=true;
    bear *newUser = new bear;
    std::string a = regDialog->getName();
    if(!newUser->setName(a))
    {
        QMessageBox msg;
        msg.setText("Invalid symbols in your name!");
        msg.exec();
    }
    else
    {
        node<bear> *curr = new node<bear>;
        curr = bearList.getTop();
        for(int i = 0; i <= bearList.getLength(); i++)   //проверка что такого имени в команде еще нет
        {
            if (a == curr->data->getName()) {ch=false; break;}
            curr = curr->next;
        }
        if (ch == false)
        {
            QMessageBox msg;
            msg.setText("Such name has already exist! Try somtehing new!");
            msg.exec();
        }
        else
        {
            time_t t;   //получение системного времени
            tm *tk;
            time(&t);
            tk = localtime(&t);
            //printf ( "Текущее время и дата: %s", asctime (tk));
            newUser->setDate(tk->tm_mday,1+tk->tm_mon,1900+tk->tm_year);
            bearList.push(newUser);
            playerNum = bearList.getLength();
            isLogin = true;     //флаг - игрок залогинен
            showName(a);
            QMessageBox msg;
            msg.setText("Your bear was added!");
            msg.exec();
        }
    }
}

void GameWindow::addRabbit()   //добавление кролика
{
    bool ch=true;
    rabbit *newUser = new rabbit;
    std::string a = regDialog->getName();
    if(!newUser->setName(a))
    {
        QMessageBox msg;
        msg.setText("Invalid symbols in your name!");
        msg.exec();
    }
    else
    {
        node<rabbit> *curr = new node<rabbit>;
        curr = rabbitList.getTop();
        for(int i = 0; i <= rabbitList.getLength(); i++)
        {
            if (a == curr->data->getName()) {ch=false; break;}
            curr = curr->next;
        }
        if (ch == false)
        {
            QMessageBox msg;
            msg.setText("Such name has already exist! Try somtehing new!");
            msg.exec();
        }
        else
        {
            time_t t;
            tm *tk;
            time(&t);
            tk = localtime(&t);
            //printf ( "Текущее время и дата: %s", asctime (tk));
            newUser->setDate(tk->tm_mday,1+tk->tm_mon,1900+tk->tm_year);
            rabbitList.push(newUser);
            playerNum = rabbitList.getLength();
            isLogin = true;
            showName(a);
            QMessageBox msg;
            msg.setText("Your rabbit was added!");
            msg.exec();
        }
    }
}

void GameWindow::searchUser()    //поиск заданного пользователя в списке
{
    if(logDialog->getTeam() == 0)
    {
        QMessageBox msg;
        msg.setText("Choose your team!");
        msg.exec();
    }
    else
    {
        std::string a = logDialog->getName();
        if(logDialog->getTeam() == 1)
        {
            bool ch = false;
            gamerType = 1;
            node<bear> *curr = new node<bear>;
            curr = bearList.getTop();
            for(int i = 0; i <= bearList.getLength(); i++)   //поиск по списку заданного имени
            {
                if (a == curr->data->getName())
                {
                    playerNum = i;
                    ch = true;
                    isLogin = true;
                    QMessageBox msg;
                    msg.setText("Your bear is found!");
                    msg.exec();
                    showName(a);
                    break;
                }
                curr = curr->next;
            }
            if (ch == false)
            {
                QMessageBox msg;
                msg.setText("Bear team dont have any player with such name! Try another name or register new!");
                msg.exec();
            }
        }
        else if(logDialog->getTeam() == 2)
        {
            bool ch = false;
            gamerType = 2;
            node<rabbit> *curr = new node<rabbit>;
            curr = rabbitList.getTop();
            for(int i = 0; i <= rabbitList.getLength(); i++)
            {
                if (a == curr->data->getName())
                {
                    playerNum = i;
                    ch = true;
                    isLogin = true;
                    QMessageBox msg;
                    msg.setText("Your rabbit is found!");
                    msg.exec();
                    showName(a);
                    break;
                }
                curr = curr->next;
            }
            if (ch == false)
            {
                QMessageBox msg;
                msg.setText("Rabbit team dont have any player with such name! Try another name or register new!");
                msg.exec();
            }

        }
    }
}

void GameWindow::showName(std::string a)  //скрытие кнопки входа и регистрации и показ кнопку выхода, если игрок вошел из системы
{
    loginButton->setVisible(false);
    regButton->setVisible(false);
    logoutButton->setVisible(true);
    hello->setVisible(true);
    std::string s = "Hello, ";
    hello->setText(QString::fromStdString(s+a));
}

void GameWindow::closeEvent(QCloseEvent *a)   //перед закрытием приложения нужно сохранить статстику в файл
{
    //QFile myFile(":/files/MYFILE.txt");
    QFile myFile("MYFILE.txt");
    /*if(!myFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this,"Error","Somthing wrong with statistic file!");
    }*/
    myFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&myFile);
    stream << code(bearList.getLength()) << "\n";
    myFile.close();
    node<bear> *curr = new node<bear>;
    curr = bearList.getTop();
    for(int i = 0; i <= bearList.getLength(); i++)   //записываем команду мишек
    {
        curr->data->toFile("MYFILE.txt");
        curr = curr->next;
    }
    myFile.open(QFile::Append | QFile::Text);
    //QTextStream stream(&myFile);
    stream << code(rabbitList.getLength()) << "\n";
    myFile.close();
    node<rabbit> *curr2 = new node<rabbit>;
    curr2 = rabbitList.getTop();
    for(int i = 0; i <= rabbitList.getLength(); i++)    //записываем команду кроликов
    {
        curr2->data->toFile("MYFILE.txt");
        curr2 = curr2->next;
    }
    //myFile.flush();
    //myFile.close();
}


