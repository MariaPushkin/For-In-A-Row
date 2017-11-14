#ifndef DIALOGS_H
#define DIALOGS_H
#include <QDialog>
#include <QWidget>
#include <QTextBrowser>
#include <QTabWidget>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>

class stateWindow :public QDialog   //окно статистики
{
    Q_OBJECT
public:
    stateWindow(QWidget *parent = 0);
    //~stateWindow();
    QTextBrowser *showBears;
    QTextBrowser *showRabbits;
private:
    QWidget *firstTab;
    QWidget *secondTab;
    QTabWidget *tab;   //вкладки
};

class inputDialog :public QDialog   //окно входа/регистрации
{
    Q_OBJECT
public:
    inputDialog(QWidget *parent = 0);
    QPushButton *confirmButton;
    std::string getName();
    int getTeam();
private:
    QLabel *nameLabel;
    QPushButton *cancelButton;
    QRadioButton *teamButton1;
    QRadioButton *teamButton2;
    QLineEdit *nameEdit;
};

#endif // DIALOGS_H
