#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include "other.h"

struct date
{
    int d,m,y;
};

class user    //базовый юзер
{
protected:
    std::string name;
    //int type;
    int gameCount;  //число игр
    int wins;    //число побед
    int losses;   //проигрышей
    int draws;     //ничьих
    date regDate;    //дата регистрации
    //std::string status;   //статус
public:
    user();
    user(std::string,int,int,int);
    user(const user &);
    ~user();
    std::string getName(){return name;}
    bool setName(std::string);
    bool setDate(int,int,int);
    bool setOther(int,int,int,int);
    //date getDate();
    void makeWin(){gameCount++;wins++;}
    void makeLose(){gameCount++;losses++;}
    void makeDraw(){gameCount++;draws++;}
    virtual std::string print();
    void toFile(std::string);
};

class bear : public user    //медвежонок
{
public:
    bear() :user(){}
    bear(std::string n,int dd,int mm,int yy) :user(n,dd,mm,yy){}
    //~bear();
    std::string print();
};

class rabbit : public user   //кролик
{
public:
    rabbit() :user(){}
    rabbit(std::string n,int dd,int mm,int yy) :user(n,dd,mm,yy){}
    //~rabbit();
    std::string print();
};

#endif // USER_H
