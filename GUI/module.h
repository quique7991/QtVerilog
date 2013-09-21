#ifndef MODULE_H
#define MODULE_H
#include <QVector>
#include "port.h"
class Module
{
public:
    Module(int NumInputs, int NumOutputs, QString Name_A):
        Inputs(NumInputs),
        Outputs(NumOutputs),
        Name(Name_A),
        InputsTotal(0),
        OutputsTotal(0)
    {}
    Module(){}
    QVector<Port> Inputs;
    QVector<Port> Outputs;
    int InputsTotal;
    int OutputsTotal;
    QString Name;
};

#endif // MODULE_H
