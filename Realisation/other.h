#ifndef OTHER_H
#define OTHER_H
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <sstream>

class circle   //игровой элемент(кружок)
{
public:
    circle();
    ~circle();
    QGraphicsEllipseItem* getCir(){return cir;}
    void setCir(QGraphicsEllipseItem* a){cir = a;}
    void colored(int);
    int getFill(){return fill2;}
    void clearFills(){fill2 = fill;}   //очистить кружок после оценки хода
    void doFill(int a){fill2 = a;}  //заполнить кружок для оценки хода
private:
    QGraphicsEllipseItem *cir; //сам кружок
    int fill; //заполненность кружка. 0 - не заполнен; 1 - заполнен игроком; 2 - заполнен компьютером
    int fill2; //заполненность кружка для оценки ходов
};

//КОДИРОВАНИЕ/ДЕКОДИРОВАНИЕ

QString code(std::string);
QString code(int);
QString mainCode(std::string);
int deCode(std::string);
std::string deCodes(std::string);
//bool checkOther(int,int,int,int);
//bool checkDate(int,int,int);


#endif // OTHER_H
