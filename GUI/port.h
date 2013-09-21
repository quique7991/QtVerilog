#ifndef PORT_H
#define PORT_H
#include <QString>

class Port
{
public:
    Port(int Width_A = 0, QString Name_A = "")
        : BusWidth(Width_A),
          Name(Name_A)
          {}
//    Port(){};
    void SetBusWidth(int Width_A){
        BusWidth = Width_A;
    }
    void SetName(QString Name_A){
        Name = Name_A;
    }
    int BusWidth;
    QString Name;

};

#endif // PORT_H
