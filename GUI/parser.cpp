#include "parser.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
Parser::Parser(QString &FileName)
{
    ParsingModules(FileName);
}
void Parser::ParsingModules(QString &FileName){

    bool InMod = false;
    Module Temp();
    QVector<Port> Inputs;
    QVector<Port> Outputs;
    QString ModuleName;
    QFile file(FileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while(!in.atEnd()){

        int pos = 0;
        QString Value  = in.readLine(75);
        RegExp.setPattern("\\bmodule (\\w+)");

        if((pos = RegExp.indexIn(Value,pos)) != -1){

            ModuleName = RegExp.cap(1);
            InMod = true;
            pos += RegExp.matchedLength();

        }

        pos = (pos == -1) ? 0 : pos;

        RegExp.setPattern("parameter (\\w+)");

        while((pos = RegExp.indexIn(Value,pos)) != -1){
            pos += RegExp.matchedLength();
        }

        pos = (pos == -1) ? 0 : pos;

        RegExp.setPattern("(input|output) \\w+\\s?\\[?(\\d*):?(\\d*)\\]?\\s?(\\w+)");

        while((pos = RegExp.indexIn(Value,pos)) != -1){
            Port Temp;
            if(RegExp.cap(2) != "" && RegExp.cap(3) != ""){
                Temp.SetBusWidth(RegExp.cap(2).toInt() - RegExp.cap(3).toInt()+1);
                Temp.SetName(RegExp.cap(4));
            }
            else{
                Temp.SetBusWidth(1);
                Temp.SetName(RegExp.cap(4));
            }

            if(RegExp.cap(1) == "input")
                Inputs << Temp;
            else
                Outputs<<Temp;

            pos += RegExp.matchedLength();
        }

        pos = (pos == -1) ? 0 : pos;

        RegExp.setPattern("endmodule");
        if((pos = RegExp.indexIn(Value,pos)) != -1){
            Module Temp(Inputs.size(), Outputs.size(), ModuleName);
            int InputTotal=0, OutputTotal=0;
            for(int i = 0; i < Inputs.size();i++){
                Temp.Inputs[i] = Inputs[i];
                InputTotal += Inputs[i].BusWidth;
            }
            for(int i = 0; i < Outputs.size();i++){
                Temp.Outputs[i] = Outputs[i];
                OutputTotal += Outputs[i].BusWidth;
            }
            Temp.InputsTotal = InputTotal;
            Temp.OutputsTotal = OutputTotal;
            ModulesIF<<Temp;
            Inputs.clear();
            Outputs.clear();
        }
    }
}
