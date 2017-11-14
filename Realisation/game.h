#ifndef GAME_H
#define GAME_H

#include "other.h"


class game
{
public:
    game(circle **a);
    ~game();
    int getp(int a){return p[a];}
    //void setp(int num, int val){p[num]=val;}
    void incp(int a){p[a]--; sp[a]--;}
    void incp2(int a) {p[a]--;}  //для оценки
    void clearp(int a){p[a]=sp[a];}

    int isVictory();        //0 - игра продолжается; 1 - победа игрока; 2 = победа компьютера; 3 - ничья
    int horizontalCheck();
    int verticalCheck();
    int diagonalCheck();
    int course(int type, int lvl); //минимакс
    int courseValue();   //оценка хода
    int horizontalValue(); //оценка хода по горизонтали
    int verticalValue();
    int diagonalValue();
private:
    int *p;
    int *sp;

    /*int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
    int p7; */

    circle **elements;   //элементы игры
};

#endif // GAME_H
