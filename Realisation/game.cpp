#include "game.h"
#include <iostream>
#include <cstdlib>

game::game(circle **a)
{
    p = new int[7];    //все колонки пустые
    for(int i = 0;i<7;i++)
        p[i] = 6;
    sp = new int[7];
    for(int i = 0;i<7;i++)
        sp[i] = 6;
    //p1=p2=p3=p4=p5=p6=p7=0;
    //h1=h2=h3=h4=h5=h6=h7=0;
    elements = a;    //связываем игровые элементы на поля с игровыми элементами определенными в классе game
}

game::~game()
{
    delete p;
    delete sp;
}


int game::isVictory()
{
    int a = horizontalCheck(), b = verticalCheck(), c = diagonalCheck();
    if(a == 1 || b == 1 || c == 1) return 1;   //проверка на победу игрока
    if(a == 2 || b == 2 || c == 2) return 2;   //проверка на победу компьютера
    for(int i = 0;i < 6;i++)    //проверка на ничью
        for(int j = 0;j < 7;j++)
            if(elements[i][j].getFill() == 0) return 0;   //если хоть один из элементов не заполнен - не ничья
    return 3;
}

int game::horizontalCheck()   //проверка по горизонтали
{
    int vik1, vik2;
    vik1=vik2=0;
    for(int i = 0;i < 6;i++)   //идем по строкам
    {
        for(int j = 0;j < 7;j++)  //идем по столбцам
        {
            if (elements[i][j].getFill() == 1) {vik1++; vik2=0;}  //проверка цепочки заполненности для игрока
            if (elements[i][j].getFill() == 2) {vik2++; vik1=0;}   //для компьютера
            if (elements[i][j].getFill() == 0) {vik1=vik2=0;}
            if(vik1 == 4) return 1;  //если у кого-то собралось 4 в ряд
            if(vik2 == 4) return 2;
        }
        vik1=vik2=0;
    }
    return 0;
}

int game::verticalCheck()   //проверка по вертикали
{
    int vik1, vik2;
    vik1=vik2=0;
    for(int i = 0;i < 7;i++)   //идем по столбцам
    {
        for(int j = 0;j < 6;j++)  //идем по строкам
        {
            if (elements[j][i].getFill() == 1) {vik1++; vik2=0;}
            if (elements[j][i].getFill() == 2) {vik2++; vik1=0;}
            if (elements[j][i].getFill() == 0) {vik1=vik2=0;}
            if(vik1 == 4) return 1;
            if(vik2 == 4) return 2;
        }
        vik1=vik2=0;
    }
    return 0;
}

int game::diagonalCheck()    //проверка по диагонали
{
    int vik1, vik2;
    vik1=vik2=0;
    //проверка вниз вправо(вверх влево)
    for(int i = 0;i < 6;i++)   //идем по строкам
    {
        for(int j = 0;j < 7;j++)  //идем по столбцам
        {
            for(int b = j, a = i;b < 7 && a < 6 ;b++, a++)
            {
                if (elements[a][b].getFill() == 1) {vik1++; vik2=0;}
                if (elements[a][b].getFill() == 2) {vik2++; vik1=0;}
                if (elements[a][b].getFill() == 0) {vik1=vik2=0;}
                if(vik1 == 4) return 1;
                if(vik2 == 4) return 2;
            }
            vik1=vik2=0;
        }
        //vik1=vik2=0;
    }
    //проверка вниз влево(вверх вправо)
    for(int i = 0;i < 6;i++)   //идем по строкам
    {
        for(int j = 6;j > -1;j--)  //идем по столбцам
        {
            for(int b = j, a = i;b > -1 && a < 6 ;b--, a++)
            {
                if (elements[a][b].getFill() == 1) {vik1++; vik2=0;}
                if (elements[a][b].getFill() == 2) {vik2++; vik1=0;}
                if (elements[a][b].getFill() == 0) {vik1=vik2=0;}
                if(vik1 == 4) return 1;
                if(vik2 == 4) return 2;
            }
            vik1=vik2=0;
        }
        //vik1=vik2=0;
    }
    return 0;
}

int game::course(int type, int lvl)   //ход компьютера
{
    int val1 = 100, val2 = -1, clvl=lvl, cur1, cur2,typep,x,y,mainx,mainy;
    if(lvl == 2)   //если достигли указанного уровня вложенности
    {
        int cur = courseValue();  //оцениваем сложившееся положение на поле
        //std::cout << cur;
        return cur;
    }
    else
    {
        for(int i = 0; i < 7; i++)   //идем по каждому столбцу и "делаем" ход
        {
            if(getp(i) != 0)   //если столбец не заполнен и можно ходить
            //else
            {
                //if(lvl == 0) value=0;
                x = getp(i) - 1;    //координаты кружка, в который будет сделан пробный ход
                y = i;

                elements[x][y].doFill(type); //делаем ход для дальнейшей оценки
                this->incp2(y);
                typep = 3 - type;  //меняем значение типа игрока, чтобы в дальнейшем рассмотреть его ходы
                clvl=lvl+1;        //переход на следующий уровен вложенности
                int a = isVictory();   //проверка победы
                if(a != 0  && lvl !=0)   //если кто-то выигрывает после сделанного хода, но не на 0 уровне вложенности
                {
                    elements[x][y].clearFills();  //очищаем ячейку, в которую был сделан пробный ход
                    clearp(y);
                    if (a == 1) return 0;
                    if (a == 2) return 50;     //возвращаем значение в зависимости от того, кто предположительно победит
                    if (a == 3) return 25;
                }
                else if(a != 0 && lvl == 0)   //если кто-то выигрывает после сделанного хода и мы на 0 уровне
                {
                    if(a == 2)   //если победитель компьютер
                    {
                        //break;
                        elements[x][y].clearFills();   //очистка
                        clearp(y);
                        elements[x][y].colored(2); //компьютер делает ход
                        this->incp(y);
                        return 0;
                    }
                    if(a == 3)
                    {
                        val2 = 25;
                        mainx = x;
                        mainy = y;

                    }
                }
                else if(a == 0)   //если после хода игра еще не закончена
                {
                    cur1 = cur2 = this->course(typep, clvl);   //рекурсивно вызываем эту же функцию, но уже для другого игрока и на следующем уровне вложенности
                    if ((cur1 <= val1 && type == 1) || (cur2 >= val2 && type == 2))  //сравниваем полученную итоговую оценку ходов
                    {                                                                //выбираем наибольшую для компьютера и наименьшую для игрока
                        if ((cur1 == val1 && type == 1) || (cur2 == val2 && type == 2))  //если оценки свопадают выбираем рандомно
                        {
                            int ra = rand() % 10 + 1;  //генерация рандомное число от 1 до 10
                            //std::cout << ra;
                            if(ra <= 5)    //если число получилось меньше или равно 5 сохраняем координаты этого хода
                            {
                                val1 = cur1;
                                val2 = cur2;
                                mainx = x;
                                mainy = y;
                            }
                        }
                        else
                        {
                            val1 = cur1;
                            val2 = cur2;
                            mainx = x;
                            mainy = y;
                        }
                    }
                }
                elements[x][y].clearFills();   //очистка полей после оценки
                clearp(y);
            }
        }
        if(lvl != 0)    //если не на 0 уровне возвращаем полученную оценку
        {
            if (type == 1) return val1;
            if (type == 2) return val2;
        }
        //if(lvl == 0)
        //{
            //возвращаем все поля заполненностей в исходные состояния до оценки
            //for(int i=0;i<7;i++)
            //    for(int j=0;j<6;j++)
            //        elements[i][j].clearFills();
            //for(int i=0;i<7;i++)
             //   this->clearp(i);
         elements[mainx][mainy].colored(2); //компютер делает ход
         this->incp(mainy);
        //}
    }
}

int game::courseValue()    //оценка хода
{
//0 - проигрыш
//10 - 3 кружка игрока, открыты с обоих сторон(проигрыш через ход)
//15 - 3 кружка игрока, открыты с одной стороны
//20 - 2 кружка игрока
//25 - прочие нейтральные позиции + ничья
//30 - 2 кружка компьютера
//35 - 3 кружка компьютера, открыты с одной стороны
//40 - 3 кружка компьютера, открыты с обоих сторон(выигрыш через ход)
//50 - выигрыш
    int v = isVictory();
    if(v == 1) return 0;
    if(v == 2) return 50;
    if(v == 3) return 25;
    //bool a;  //чей ход оценивается, компьютера или игрока, true - игрок; false - компьютер
    //if(elements[x][y].getFill() == 1) a = true;
    //if(elements[x][y].getFill() == 2) a = false;
    //if (type == 1) a = true;
    //if (type == 2) a = false;
    //горизонталь
    int b = horizontalValue();
    int c = verticalValue();
    int d = diagonalValue();
    return b+c+d;
}

int game::horizontalValue()    //оценика хода по горизонтали
{
    int sum1,sum2,cur1,cur2,ret1=0,ret2=0;
    sum1=sum2=cur1=cur2=0;

    int poten1=0,poten2=0;   //потенциал для дальнейших ходов

    for(int i = 5;i >= 0;i--)   //идем по строкам
    {        
        for(int j = 0;j < 7;j++)  //идем по столбцам
        {
            if (elements[i][j].getFill() == 0)  //если пустой кружок
            {
                if (i == 5 || (i != 5 && elements[i+1][j].getFill() != 0))  //если столбец еще не заполнен или заполнен до уровня рассматриваемой ячейки
                {
                    poten1++; //увеличиваем потенциал для обоих игроков
                    poten2++;
                    if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))  //если заполнено два кружка игрока и потенциал ходов больше 2
                    {                                                             //или если заполнено три и можно сделать еще один ход
                        if(sum1 < cur1)                                           //и если оценка больше предыдущей
                            sum1 = cur1;                                          //запоминаем ее в sum
                    }
                    if((cur2 == 2 && poten2 >= 2) || (cur2 == 3 && poten2 >= 1))  //аналогичная проверка для второго игрока
                    {
                        if(sum2 < cur2)
                            sum2 = cur2;
                    }
                }
                else                               //если столбик не заполнен до уровня рассматриваемой ячейки (в нее нельзя пока совершить ход)
                    poten1=poten2=cur1=cur2=0;     //приравниваем все потенциалы и собранные комбинации игроков к 0

            }
            if(elements[i][j].getFill() == 1)     //если ячейка заполнена игроком
            {
                cur1++;                       //увеличиваем счетчик кружков для игрока
                cur2=0;                       //приравниваем такой же счетчик для компьютера к 0
                poten2=0;                     //приравниваем потенциал ходов компьютера к 0
                if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                {
                    if(sum1 < cur1)
                        sum1 = cur1;
                }
            }
            if(elements[i][j].getFill() == 2)    //аналогичные действия для компьютера
            {
                cur2++;
                cur1=0;
                poten1=0;
                if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                {
                    if(sum1 < cur1)
                        sum1 = cur1;
                }
            }
        }
        cur1=cur2=poten1=poten2=0;    //после рассмотрения каждой строчки приравниваем временные параметры к 0
    }
    if(sum1 == 3) ret1 = 8;    //обработка полученных результатов
    if(sum2 == 3) ret2 = 12;   //3 - рассмотренный игрок собрал комбинацию из 3 кружков и может еще поставить 4
    if(sum1 == 2) ret1 = 5;    //2 - собрал комбинацию из 2 и есть место для еще 2
    if(sum2 == 2) ret2 = 10;
    if(sum2 == 0) ret2 = 8;
    return ret2 - ret1;
}

int game::verticalValue()    //оценика хода по вертикали
{
    int sum1,sum2,cur1,cur2,ret1=0,ret2=0;
    sum1=sum2=cur1=cur2=0;
    for(int i = 0;i < 7;i++)   //идем по столбцам
    {
        if (getp(i) > 0)
        {
            for(int j = 5;j >= 0;j--)  //идем по строкам
            {
                if (elements[j][i].getFill() == 1)    //если кружок заполнен игроком
                {                                     //увеличиваем его счетчик и обнуляем счетчик компьютера
                    cur1++;                           //аналогично, если кружок заполнен компьютером
                    //if(sum2 < cur2)
                    //    sum2=cur2;
                    cur2=0;
                }
                if (elements[j][i].getFill() == 2)
                {
                    cur2++;
                    //if(sum1 < cur1)
                    //    sum1=cur1;
                    cur1=0;
                }
                if (elements[j][i].getFill() == 0)    //если кружок не заполнен
                {
                    if(sum1 < cur1)       //если текущий счетчик больше чем сохраненный до этого
                    {                                                    //если счетчик 3 или 2, но есть возможность поставить еще 2 кружка в столбец
                        if(cur1 == 3 || (cur1 == 2 && getp(i) > 1))      //сохраняем текущий счетчик
                            sum1=cur1;
                    }
                    if(sum2 < cur2)
                    {
                        if(cur2 == 3 || (cur2 == 2 && getp(i) > 1))
                            sum2=cur2;
                    }
                    cur1=cur2=0;  //обнуление
                    break;
                }
            }
        }
        cur1=cur2=0;   //обнуление
    }
    if(sum1 == 3) ret1 = 8;         //оценка полученных результатов
    if(sum2 == 3) ret2 = 12;
    if(sum1 == 2) ret1 = 5;
    if(sum2 == 2) ret2 = 10;
    if(sum2 == 0) ret2 = 8;
    return ret2 - ret1;
}

int game::diagonalValue()     //оценка хода по диагонали
{
    //оценка ведется аналогично оценке по горизонатали за исключением того, что здесь идем по диагонали от каждой выбранной ячейки по диагонали(вверх вправо и вверх влево)
    //оцениваются потенциалы ячеек, и если набирается 3 кружка и возможность поставить еще четвертый, то счетчик сохраняет значение 3
    //если набирается 2 кружка и есть возможность поставить еще 2, то сохраняется значение 2
    int sum1,sum2,cur1,cur2,ret1=0,ret2=0;
    sum1=sum2=cur1=cur2=0;
    int poten1=0,poten2=0;

    //вверх вправо

    for(int i = 5;i >= 0;i--)   //идем по строкам
    {
        for(int j = 0;j < 7;j++)  //идем по столбцам
        {
            for(int b = j, a = i;b < 7 && a >= 0 ;b++, a--)   //идем по диагонали от каждого значения (вверх вправо)
            {
                if (elements[a][b].getFill() == 0)
                {
                    if (a == 5 || (a != 5 && elements[a+1][b].getFill() != 0))
                    {
                        poten1++;
                        poten2++;
                        if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                        {
                            if(sum1 < cur1)
                                sum1 = cur1;
                        }
                        if((cur2 == 2 && poten2 >= 2) || (cur2 == 3 && poten2 >= 1))
                        {
                            if(sum2 < cur2)
                                sum2 = cur2;
                        }
                    }
                    else
                        poten1=poten2=cur1=cur2=0;

                }
                if(elements[a][b].getFill() == 1)
                {
                    cur1++;
                    cur2=0;
                    poten2=0;
                    if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                    {
                        if(sum1 < cur1)
                            sum1 = cur1;
                    }
                }
                if(elements[a][b].getFill() == 2)
                {
                    cur2++;
                    cur1=0;
                    poten1=0;
                    if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                    {
                        if(sum1 < cur1)
                            sum1 = cur1;
                    }
                }
            }
        }
        cur1=cur2=poten1=poten2=0;
    }
    for(int i = 5;i >= 0;i--)   //идем по строкам
    {
        for(int j = 6;j >= 0;j--)  //идем по столбцам
        {
            for(int b = j, a = i;b >=0 && a >= 0 ;b--, a--)   //идем по диагонали (вверх влево)
            {
                if (elements[a][b].getFill() == 0)
                {
                    if (a == 5 || (a != 5 && elements[a+1][b].getFill() != 0))
                    {
                        poten1++;
                        poten2++;
                        if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                        {
                            if(sum1 < cur1)
                                sum1 = cur1;
                        }
                        if((cur2 == 2 && poten2 >= 2) || (cur2 == 3 && poten2 >= 1))
                        {
                            if(sum2 < cur2)
                                sum2 = cur2;
                        }
                    }
                    else
                        poten1=poten2=cur1=cur2=0;

                }
                if(elements[a][b].getFill() == 1)
                {
                    cur1++;
                    cur2=0;
                    poten2=0;
                    if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                    {
                        if(sum1 < cur1)
                            sum1 = cur1;
                    }
                }
                if(elements[a][b].getFill() == 2)
                {
                    cur2++;
                    cur1=0;
                    poten1=0;
                    if((cur1 == 2 && poten1 >= 2) || (cur1 == 3 && poten1 >= 1))
                    {
                        if(sum1 < cur1)
                            sum1 = cur1;
                    }
                }
            }
        }
        cur1=cur2=poten1=poten2=0;
    }
    if(sum1 == 3) ret1 = 8;      //анализ резаультатов
    if(sum2 == 3) ret2 = 12;
    if(sum1 == 2) ret1 = 5;
    if(sum2 == 2) ret2 = 10;
    if(sum2 == 0) ret2 = 8;
    return ret2 - ret1;
}

