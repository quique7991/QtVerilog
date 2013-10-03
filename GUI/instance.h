#ifndef INSTANCE_H
#define INSTANCE_H
#include<QHash>
class Instance
{
public:
    Instance(){}
    QHash<QString,int> ModQuant;
    QHash<QString,QVector<QString> *> Wires;
    QHash<QString,int> WireLength;
    void ClearInst(){ModQuant.clear();Wires.clear();WireLength.clear();}
};

#endif // INSTANCE_H
