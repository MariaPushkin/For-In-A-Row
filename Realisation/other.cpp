#include "other.h"

circle::circle()
{
    cir = new QGraphicsEllipseItem;
    fill = fill2 = 0;     //изначельно кружок не заполнен
}

circle::~circle()
{
    delete cir;
}

void circle::colored(int a)   //раскрашиваем кружок в заданый цвет
{
    if(a == 0)
        cir->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    if(a == 1)
        cir->setBrush(QBrush(QColor::fromRgb(194,44,44), Qt::SolidPattern));
    if(a == 2)
        cir->setBrush(QBrush(QColor::fromRgb(32,124,54), Qt::SolidPattern));
    fill = fill2 = a;
}



QString code(int a)
{
    std::ostringstream ss;
    ss << a;
    std::string b = ss.str();
    QString sh="";
    for(int i=0; i < b.length(); i++)
    {
    switch (b[i])
    {
        case '0' : sh=sh+"#"; break;
        case '1' : sh=sh+"f"; break;
        case '2' : sh=sh+"^"; break;
        case '3' : sh=sh+"="; break;
        case '4' : sh=sh+"h"; break;
        case '5' : sh=sh+"a"; break;
        case '6' : sh=sh+"<"; break;
        case '7' : sh=sh+"?"; break;
        case '8' : sh=sh+"l"; break;
        case '9' : sh=sh+":"; break;
        case '-' : sh=sh+"-"; break;
    }
    }
    return sh;
}

QString code(std::string a)
{
    //int t;
    QString b = "";
    for(int i=0; i < a.length(); i++)
    {
    switch (a[i])
    {
        case 'a' : case 'A' : b=b+"#"; break;
        case 'b' : case 'B' : b=b+"f"; break;
        case 'c' : case 'C' : b=b+"^"; break;
        case 'd' : case 'D' : b=b+"="; break;
        case 'e' : case 'E' : b=b+"h"; break;
        case 'f' : case 'F' : b=b+"a"; break;
        case 'g' : case 'G' : b=b+"<"; break;
        case 'h' : case 'H' : b=b+"?"; break;
        case 'i' : case 'I' : b=b+"l"; break;
        case 'j' : case 'J' : b=b+":"; break;
        case 'k' : case 'K' : b=b+"*"; break;
        case 'l' : case 'L' : b=b+"5"; break;
        case 'm' : case 'M' : b=b+"("; break;
        case 'n' : case 'N' : b=b+".#"; break;
        case 'o' : case 'O' : b=b+".f"; break;
        case 'p' : case 'P' : b=b+".^"; break;
        case 'q' : case 'Q' : b=b+".="; break;
        case 'r' : case 'R' : b=b+".h"; break;
        case 's' : case 'S' : b=b+".a"; break;
        case 't' : case 'T' : b=b+".<"; break;
        case 'u' : case 'U' : b=b+".?"; break;
        case 'v' : case 'V' : b=b+".l"; break;
        case 'w' : case 'W' : b=b+".:"; break;
        case 'x' : case 'X' : b=b+".*"; break;
        case 'y' : case 'Y' : b=b+".5"; break;
        case 'z' : case 'Z' : b=b+".("; break;
    }
    }
    //t = atoi(a.c_str());
    return b;
}

int deCode(std::string a)
{
    std::string sh="";
    for(int i=0; i < a.length(); i++)
    {
    switch (a[i])
    {
        case '#' : sh=sh+"0"; break;
        case 'f' : sh=sh+"1"; break;
        case '^' : sh=sh+"2"; break;
        case '=' : sh=sh+"3"; break;
        case 'h' : sh=sh+"4"; break;
        case 'a' : sh=sh+"5"; break;
        case '<' : sh=sh+"6"; break;
        case '?' : sh=sh+"7"; break;
        case 'l' : sh=sh+"8"; break;
        case ':' : sh=sh+"9"; break;
        case '-' : sh=sh+"-"; break;
        default : return -5;
    }
    }
    return atoi(sh.c_str());;
}

std::string deCodes(std::string a)
{
    std::string b = "";
    for(int i=0; i < a.length(); i++)
    {
    switch (a[i])
    {
        case '#' : if(i == 0) b=b+"A"; else b=b+"a"; break;
        case 'f' : if(i == 0) b=b+"B"; else b=b+"b"; break;
        case '^' : if(i == 0) b=b+"C"; else b=b+"c"; break;
        case '=' : if(i == 0) b=b+"D"; else b=b+"d"; break;
        case 'h' : if(i == 0) b=b+"E"; else b=b+"e"; break;
        case 'a' : if(i == 0) b=b+"F"; else b=b+"f"; break;
        case '<' : if(i == 0) b=b+"G"; else b=b+"g"; break;
        case '?' : if(i == 0) b=b+"H"; else b=b+"h"; break;
        case 'l' : if(i == 0) b=b+"I"; else b=b+"i"; break;
        case ':' : if(i == 0) b=b+"J"; else b=b+"j"; break;
        case '*' : if(i == 0) b=b+"K"; else b=b+"k"; break;
        case '5' : if(i == 0) b=b+"L"; else b=b+"l"; break;
        case '(' : if(i == 0) b=b+"M"; else b=b+"m"; break;
        case '.' : switch (a[i+1])
            {
            case '#' : if(i == 0) b=b+"N"; else b=b+"n"; break;
            case 'f' : if(i == 0) b=b+"O"; else b=b+"o"; break;
            case '^' : if(i == 0) b=b+"P"; else b=b+"p"; break;
            case '=' : if(i == 0) b=b+"Q"; else b=b+"q"; break;
            case 'h' : if(i == 0) b=b+"R"; else b=b+"r"; break;
            case 'a' : if(i == 0) b=b+"S"; else b=b+"s"; break;
            case '<' : if(i == 0) b=b+"T"; else b=b+"t"; break;
            case '?' : if(i == 0) b=b+"U"; else b=b+"u"; break;
            case 'l' : if(i == 0) b=b+"V"; else b=b+"v"; break;
            case ':' : if(i == 0) b=b+"W"; else b=b+"w"; break;
            case '*' : if(i == 0) b=b+"X"; else b=b+"x"; break;
            case '5' : if(i == 0) b=b+"Y"; else b=b+"y"; break;
            case '(' : if(i == 0) b=b+"Z"; else b=b+"z"; break;
            default : return "-5";
            }
        i++;
    }
    }
    //t = atoi(a.c_str());
    return b;
}

/*bool checkOther(int g, int w, int l, int d)
{
    if(g < 0 || w < 0 || l < 0 || d < 0) return false;
    if(g != w+l+d) return false;
    return true;
}

bool checkDate(int d, int m, int y)
{
    if(d < 0 || m < 0 || y < 0) return false;
    if (m==2 && (d==30 || d==31)) return false;
    if ((m==4 || m==6 || m==9 || m==11) && d==31 ) return false;
    if (y != 2016) return false;
    if (d > 31) return false;
    if (m > 12) return false;
    return true;
}*/
