#include "user.h"
#include <sstream>
#include <QFile>
#include <QTextStream>

user::user()
{
    name="None";
    regDate.d=0; regDate.m=0; regDate.y=0;
    //type=0;
    gameCount=0;
    wins=0;
    losses=0;
    draws=0;
}

user::user(std::string n, int dd,int mm,int yy)
{
    name=n;
    regDate.d=dd; regDate.m=mm; regDate.y=yy;
    //type=0;
    gameCount=0;
    wins=0;
    losses=0;
    draws=0;
}

user::user(const user & copy)
{
    name = copy.name;
    //type = copy.type;
    gameCount = copy.gameCount;
    wins =copy.wins;
    losses = copy.losses;
    draws = copy.draws;
    regDate.d = copy.regDate.d;
    regDate.m = copy.regDate.m;
    regDate.y = copy.regDate.y;
}

bool user::setName(std::string a)
{
    if(!a[0]) return false;
    for(int i=0; i < a.length(); i++)
    {
        if(!isalpha(a[i]))
            return false;
    }
    name=a;
    return true;
}

bool user::setDate(int d,int m,int y)
{
    if(d < 0 || m < 0 || y < 0) return false;
    if (m==2 && (d==30 || d==31)) return false;
    if ((m==4 || m==6 || m==9 || m==11) && d==31 ) return false;
    if (y != 2016) return false;
    if (d > 31) return false;
    if (m > 12) return false;
    regDate.d = d;
    regDate.m = m;
    regDate.y = y;
    return true;
}

bool user::setOther(int g, int w, int l, int d)
{
    if(g < 0 || w < 0 || l < 0 || d < 0) return false;
    if(g != w+l+d) return false;
    gameCount = g;
    wins = w;
    losses = l;
    draws = d;
    return true;
}

std::string user::print()
{
    std::ostringstream ss;
    ss << "There is nothing here. Sorry. -___- ";
    return ss.str();
}

void user::toFile(std::string a)    //запись в файл
{
    QFile myFile(QString::fromStdString(a));
    myFile.open(QFile::Append | QFile::Text);
    QTextStream st(&myFile);
    st << code(this->name) << " ";
    st << code(this->gameCount) << " ";
    st << code(this->wins) << " ";
    st << code(this->losses) << " ";
    st << code(this->draws) << " ";
    st << code(this->regDate.d) << " ";
    st << code(this->regDate.m) << " ";
    st << code(this->regDate.y) << "\n";
    myFile.close();
}

std::string bear::print()    //вывод на экран для мишек
{
    std::ostringstream ss;
    ss << this->name << " the bear:" << "\n";
    ss << "Joined the team: " << this->regDate.d << ":" << this->regDate.m << ":" << this->regDate.y << "\n";
    ss << "Go hunting " << this->gameCount << " times (";
    ss << "Wins: " << this->wins << "   ";
    ss << "Losses: " << this->losses << "   ";
    ss << "Draws: " << this->draws << ")\n";
    if(wins < 10) ss << "Status: Teddy-Bear";
    if(wins >= 10 && wins < 20) ss << "Status: Super hunter";
    if(wins >= 20) ss << "Status: SUPER-MEGA BEAR-LEADER";
    return ss.str();
}

std::string rabbit::print()       //вывод на экран для кроликов
{
    std::ostringstream ss;
    ss << this->name << " the rabbit:" << "\n";
    ss << "Joined the team: " << this->regDate.d << ":" << this->regDate.m << ":" << this->regDate.y << "\n";
    ss << "Go carrots collecting " << this->gameCount << " times (";
    ss << "Wins: " << this->wins << "   ";
    ss << "Losses: " << this->losses << "   ";
    ss << "Draws: " << this->draws << ")\n";
    if(gameCount < 20) ss << "Status: Junior carrot collector";
    if(gameCount >= 20 && gameCount < 40) ss << "Status: Amateur cruncher";
    if(gameCount >= 40) ss << "Status: KARROT KING";
    return ss.str();
}

