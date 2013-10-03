#include "parser.h"
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include "instance.h"
#include <iostream>
#include<QStringList>
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
    Instance TempInst;
    QString InstanceMod;
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

        RegExp.setPattern("(\\w+)(\\s#\\((\\w*,)*\\w*\\))?\\s+\\w*\\(");

        if((pos = RegExp.indexIn(Value,pos)) != -1){
            InstanceMod = RegExp.cap(1);
            if(InstanceMod != "module"){
                if(TempInst.ModQuant.contains(InstanceMod))
                    TempInst.ModQuant[InstanceMod] = TempInst.ModQuant[InstanceMod] + 1;
                else
                    TempInst.ModQuant[InstanceMod] = 1;
            }
        }

        pos = (pos == -1) ? 0 : pos;

        RegExp.setPattern("\\.(\\w*)\\(\\{?(([^{]*,)*\\w*)\\}?\\)");

        if((pos = RegExp.indexIn(Value,pos)) != -1){
            QStringList WiresToPort = RegExp.cap(2).split(",");
            QString PortName = RegExp.cap(1);
            int AssumedWidth = 0;
            for(int i = 0; i < WiresToPort.size();++i){
                if(TempInst.WireLength.contains(WiresToPort[i]))
                    AssumedWidth += TempInst.WireLength[WiresToPort[i]];
            }
            int beginning = 0;
            for(int i = WiresToPort.size() - 1; i >=0 ;--i){
                if(TempInst.Wires.contains(WiresToPort[i])){
                 //   qDebug() << WiresToPort[i]  << ":" << beginning + TempInst.WireLength[WiresToPort[i]] -1<<":"<<TempInst.WireLength[WiresToPort[i]];
                    int end = beginning + TempInst.WireLength[WiresToPort[i]] -1;
                    QString PortBits = PortName+"["+QString::number(end)+":"+QString::number(beginning)+"]";
                    TempInst.Wires[WiresToPort[i]]->append(InstanceMod+QString::number(TempInst.ModQuant[InstanceMod])+"_"+PortBits);
                    beginning = end + 1;
                }
            }

        }

        pos = (pos == -1) ? 0 : pos;

        RegExp.setPattern("^\\s*wire\\s?\\[?(\\d*)\\s?:?\\s?(\\d*)\\]?\\s?((\\w*,\\s?)*\\w*)");

        if((pos = RegExp.indexIn(Value,pos)) != -1){
            QStringList WireNames = RegExp.cap(3).split(",");
            int WireWidth;
            if (RegExp.cap(1) != "")
                WireWidth = RegExp.cap(1).toInt() - RegExp.cap(2).toInt()+1;
            else
                WireWidth = 1;
            for(int i = 0; i < WireNames.size(); ++i){
                QString WireName = WireNames.at(i).trimmed();
                if(TempInst.Wires.contains(WireName)){
                    qDebug() << "Ya Existe";
                } else {
                    TempInst.Wires[WireName] = new QVector<QString>();
                    TempInst.WireLength[WireName] = WireWidth;
                }
            }
           // qDebug() << RegExp.cap(3);
        }

        pos = (pos == -1) ? 0 : pos;

        RegExp.setPattern("\\);");

        if((pos = RegExp.indexIn(Value,pos)) != -1){
            InstanceMod.clear();
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
            Temp.instances = TempInst;
            ModulesIF<<Temp;
            std::cout<<Temp.instances.Wires.keys().size()<<std::endl;
            /*QList<QString> Keys = TempInst.Wires.keys();
            std::cout<<ModuleName.toStdString();
            for(int i = 0; i < Keys.size() ; ++i){
                std::cout<<Keys[i].toStdString()<<std::endl;
                for(int j = 0; j < TempInst.Wires[Keys[i]]->size(); ++j){
                    std::cout<<"\t"<<TempInst.Wires[Keys[i]]->at(j).toStdString()<<" ";
                }
                std::cout<<"\n";
            }*/
            Inputs.clear();
            Outputs.clear();
            TempInst.ClearInst();
        }
    }
}
