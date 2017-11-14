#include <QVBoxLayout>
#include "dialogs.h"

//ОКНО СТАТИСТИКИ

stateWindow::stateWindow(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(450,600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor::fromRgb(127,134,148));;
    this->setPalette(palette);

    firstTab = new QWidget();
    secondTab = new QWidget();

    showBears = new QTextBrowser;
    showBears->setStyleSheet("color: white ; background-color: rgb(20,44,138); font: bold 12px;");
    showRabbits = new QTextBrowser;
    showRabbits->setStyleSheet("color: white ; background-color: rgb(20,44,138); font: bold 12px;");

    QVBoxLayout *bea = new QVBoxLayout(firstTab);
    bea->addWidget(showBears);
    QVBoxLayout *rab = new QVBoxLayout(secondTab);
    rab->addWidget(showRabbits);

    tab = new QTabWidget(this);
    tab->addTab(firstTab,"Bears");
    tab->addTab(secondTab, "Rabbits");
    tab->setStyleSheet("color: black; background-color: rgb(20,44,138); font: bold 12px;");
    //this->setCentralWidget(tab);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tab);

    this->setLayout(mainLayout);
}

//ОКНО ВХОДА/РЕГИСТРАЦИИ

inputDialog::inputDialog(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(210,110);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor::fromRgb(127,134,148));;
    this->setPalette(palette);
    this->setStyleSheet("QPushButton { color: white ; background-color: rgb(20,44,138); font: bold 13px;} QPushButton:hover { background-color: rgb(75,93,164)} ");

    confirmButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    nameLabel = new QLabel("Name");
    nameEdit = new QLineEdit;
    teamButton1 = new QRadioButton("Bears");
    teamButton2 = new QRadioButton("Rabbits");

    QGridLayout *inpLayout = new QGridLayout;
    inpLayout->addWidget(nameLabel,0,0);
    inpLayout->addWidget(nameEdit,0,1,1,4);
    inpLayout->addWidget(teamButton1,1,1,1,2);
    inpLayout->addWidget(teamButton2,1,4,1,2);
    inpLayout->addWidget(cancelButton,2,0);
    inpLayout->addWidget(confirmButton,2,4);

    this->setLayout(inpLayout);

    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}

std::string inputDialog::getName()  //возвращание написанного в текстэтиде имени
{
    return nameEdit->text().toStdString();
}

int inputDialog::getTeam()   //возвращение выбранной команды
{
    if(teamButton1->isChecked()) return 1;
    else if(teamButton2->isChecked()) return 2;
    else return 0;
}

