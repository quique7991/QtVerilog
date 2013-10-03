#include <QDateTime>
#include <QMainWindow>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QLabel>
#include <QImage>
#include <QProgressDialog>
#include <QPixmap>
#include <QMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QFileDialog>
#include <QtSql>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include "instance.h"
#include "canvas.h"
#include "line.h"
#include "core.h"
#include "parser.h"
#include "fromfile.h"
#include "addfromdb.h"
#include "hierarchidialog.h"
FigureEditor::FigureEditor(
	QGraphicsScene& c, QWidget* parent,
	const char* name, Qt::WindowFlags f) :
    QGraphicsView(&c,parent)
{
    setObjectName(name);
    setWindowFlags(f);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void FigureEditor::clear()
{
    scene()->clear();
}

Sprite::Sprite(){
    QString fileName = QFileDialog::getOpenFileName(0,"Open file","","*.*");

    setPixmap(QPixmap(fileName));
}


int Sprite::type() const{
    return 1234;
}

void Sprite::initPos(){
}

QPainterPath Sprite::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

Main::Main(QGraphicsScene *canvas1, QWidget* parent, Qt::WindowFlags f) :
    QMainWindow(parent, f),
    canvas(canvas1)
{
    this->isValid=false;
    this->isInput=false;
    this->ultimo=0;
    this->isSecondClick=false;
    editor = new FigureEditor(*canvas,this);

    QMenuBar* menu = menuBar();

    QMenu* file = new QMenu("&File", menu );
    file->addAction("&Fill canvas", this, SLOT(init()), Qt::CTRL+Qt::Key_F);
    file->addAction("&Erase canvas", this, SLOT(clear()), Qt::CTRL+Qt::Key_E);
    file->addAction("&New view", this, SLOT(newView()), Qt::CTRL+Qt::Key_N);
    file->addSeparator();
    file->addAction("&Print...", this, SLOT(print()), Qt::CTRL+Qt::Key_P);
    file->addSeparator();
    file->addAction("E&xit", qApp, SLOT(quit()), Qt::CTRL+Qt::Key_Q);
    menu->addMenu(file);

    QMenu* edit = new QMenu("&Edit", menu );
    edit->addAction("Add &Sprite",this,SLOT(addSpriteMine()),Qt::ALT+Qt::Key_B);
    edit->addAction("Add Modules",this,SLOT(ProcessModules()/*(0,0,"Modulo",3,3,"BLA",Qt::blue,bla1,bla2)*/),Qt::ALT+Qt::Key_1);
    QMenu *DropModule = edit->addMenu("Drop Module");
    DropModule->addAction("From &Database", this, SLOT(DropModuleFromDB()));
    DropModule->addAction("From &File", this, SLOT(DropModuleFromFile()));
    edit->addAction("Imprimir Conexiones",this,SLOT(print2()),Qt::ALT+Qt::Key_A);
    menu->addMenu(edit);
    QMenu* view = new QMenu("&View", menu );
    view->addAction("&Hierarchy", this, SLOT(ChangeScene()), Qt::CTRL+Qt::Key_H);
    view->addAction("&Enlarge", this, SLOT(enlarge()), Qt::SHIFT+Qt::CTRL+Qt::Key_Plus);
    view->addAction("Shr&ink", this, SLOT(shrink()), Qt::SHIFT+Qt::CTRL+Qt::Key_Minus);
    view->addSeparator();
    view->addAction("&Rotate clockwise", this, SLOT(rotateClockwise()), Qt::CTRL+Qt::Key_PageDown);
    view->addAction("Rotate &counterclockwise", this, SLOT(rotateCounterClockwise()), Qt::CTRL+Qt::Key_PageUp);
    view->addAction("&Zoom in", this, SLOT(zoomIn()), Qt::CTRL+Qt::Key_Plus);
    view->addAction("Zoom &out", this, SLOT(zoomOut()), Qt::CTRL+Qt::Key_Minus);
    view->addAction("Translate left", this, SLOT(moveL()), Qt::CTRL+Qt::Key_Left);
    view->addAction("Translate right", this, SLOT(moveR()), Qt::CTRL+Qt::Key_Right);
    view->addAction("Translate up", this, SLOT(moveU()), Qt::CTRL+Qt::Key_Up);
    view->addAction("Translate down", this, SLOT(moveD()), Qt::CTRL+Qt::Key_Down);
    view->addAction("&Mirror", this, SLOT(mirror()), Qt::CTRL+Qt::Key_Home);
    menu->addMenu(view);

    menu->addSeparator();

    QMenu* help = new QMenu("&Help", menu );
    help->addAction("&About", this, SLOT(help()), Qt::Key_F1);
    menu->addMenu(help);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");/*#*/
    db.setDatabaseName("Prueba");/*#*/
    db.setUserName("root");/*#*/
    db.setPassword("KarenPa0la");/*#*/
    if(!db.open()){
        QMessageBox::critical(this, tr("DB Error"),tr("Could not login to db"),QMessageBox::Ok);
    }
    Prueba = 1;
    statusBar();

    setCentralWidget(editor);

    QSqlQuery Query("create table Modules(id int unsigned not null auto_increment, Name varchar(30) not null, Inputs int not null, Outputs int not null, ImageFile varchar(200), PortInfoFile varchar(200), primary key(id), unique key(Name))");

#if !defined(Q_OS_SYMBIAN)
    printer = 0;
#endif

    init();
}

void Main::ChangeScene(){
    if(Prueba){
        HierarchiDialog Dialog(this, &ModInDesign);
        QList<line*>  inputValues;
        QList<line*> outputValues;
        if(Dialog.exec() == QDialog::Accepted){
            tempcanvas = canvas;
            canvas = new QGraphicsScene();
            editor->setScene(canvas);
            inputsH = new QMultiHash<int,line*>();
            outputsH = new QMultiHash<int,line*>();
            modulosH = new QList<QGraphicsTextItem*>();
            Prueba = 0;
            QString PreQuery = QString("Select PortInfoFile from Modules where Name='%1'").arg(Dialog.Selection);
            QSqlQuery Query(PreQuery);
            while(Query.next()){
                QFile file(Query.value(0).toString());
                file.open(QFile::ReadOnly | QFile::Text);
                while(!file.atEnd()){
                    QString line = file.readLine();
                    QRegExp RegExp;
                    RegExp.setPattern("Hierarchy");
                    if(RegExp.indexIn(line) != -1){
                        int contador = 0;
                        while(!file.atEnd()){
                            line = file.readLine();
                            if(contador){
                            } else {
                                contador ++;
                                QStringList Modulos = line.split(";" , QString::SkipEmptyParts);
                                for(int i = 0; i < Modulos.size(); ++i){
                                    QVector<QString> inputs_arg, outputs_arg;
                                    QStringList Arg = Modulos.at(i).split(":");
                                    QSqlQuery Query(QString("Select * from Modules where Name='%1'").arg(Arg[0]));
                                    if(!Query.size()){
                                         QMessageBox::critical(this, tr("Info"),tr("There is a problem with the modules\ncheck that all the instance modules were added to the database\n"),QMessageBox::Ok);
                                        return;
                                    }
                                    else{
                                        while(Query.next()){
                                            QFile file(Query.value(5).toString());
                                            file.open(QIODevice::ReadOnly | QIODevice::Text);
                                            QTextStream in(&file);
                                            int counter = 0;
                                            while(!in.atEnd()){
                                                QString Ports(in.readLine());
                                                if(Ports == "FinPuertos"){
                                                    break;
                                                }
                                                QList<QString> Prueba = Ports.split(';');
                                                if(!counter)
                                                    inputs_arg = QVector<QString>::fromList(Prueba);
                                                else
                                                    outputs_arg = QVector<QString>::fromList(Prueba);
                                                counter++;
                                            }
                                            for(int b=1; b <= Arg.at(1).toInt(); ++b){
                                                QString Nombre = Query.value(1).toString()+QString::number(b);
                                                addModulo(Nombre, Query.value(2).toInt(), Query.value(3).toInt(), inputs_arg, outputs_arg,*inputsH,*outputsH,*modulosH);
                                            }
                                            qDebug() << outputsH->values().size();
                                            if(outputsH->values().size() > inputsH->values().size()){
                                                inputValues = inputsH->values();
                                                outputValues = outputsH->values();
                                                for(int c = 0;c<inputValues.size();++c){
                                                    outputValues[c]->setColor(QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8));
                                                    inputValues[c]->setColor(outputValues[c]->getColor());
                                                    inputValues[c]->setConnected(true,0);
                                                    outputValues[c]->setConnected(true,0);
                                                    inputValues[c]->update();
                                                    outputValues[c]->update();
                                                }
                                            } else{
                                                outputValues = outputsH->values();
                                                inputValues = inputsH->values();
                                                for(int c = 0;c<outputValues.size();++c){
                                                    outputValues[c]->setColor(QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8));
                                                    outputValues[c]->setConnected(true,0);
                                                    outputValues[c]->update();
                                                }
                                                for(int c = 0; c<inputValues.size();++c){
                                                    inputValues[c]->setColor(outputValues[c%outputValues.size()]->getColor());
                                                    inputValues[c]->setConnected(true,0);
                                                    inputValues[c]->update();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
    } else{
        Prueba = 1;
        canvas->clear();
        delete canvas;
        canvas = tempcanvas;
        editor->setScene(canvas);
        delete inputsH;
        delete outputsH;
        delete modulosH;
    }

}

void Main::init()
{
    clear();
}

Main::~Main()
{
#if !defined(Q_OS_SYMBIAN)
    delete printer;
#endif
}

void Main::newView()
{
    // Open a new view... have it delete when closed.
    Main *m = new Main(0); // AKr, Qt::WA_DeleteOnClose);
    m->show();
}

void Main::clear()
{
    editor->clear();
}

void Main::help()
{
    static QMessageBox* about = new QMessageBox( "Verilog Module editor",
        "<h3>Graphic verilog editor</h3>"
	    "<ul>"
        "<li> For help talk with Hugo and Enrique"
            "</ul>", QMessageBox::Information, 1, 0, 0, this, 0);
    about->setButtonText( 1, "Dismiss" );
    about->show();
}

void Main::aboutQt()
{
    QMessageBox::aboutQt( this, "Qt-based program" );
}

void Main::enlarge()
{
    canvas->setSceneRect(0, 0, canvas->width()*4/3, canvas->height()*4/3);
}

void Main::shrink()
{
    canvas->setSceneRect(0, 0, qMax(canvas->width()*3/4, qreal(1.0)), qMax(canvas->height()*3/4, qreal(1.0)));
}

void Main::rotateClockwise()
{
    editor->rotate( 22.5 );
}

void Main::rotateCounterClockwise()
{

    editor->rotate( -22.5 );
}

void Main::zoomIn()
{
    editor->scale( 2.0, 2.0 );
}

void Main::zoomOut()
{
    editor->scale( 0.5, 0.5 );
}

void Main::mirror()
{
    editor->scale( -1, 1 );
}

void Main::moveL()
{
    editor->translate( -16, 0 );
}

void Main::moveR()
{
    editor->translate( +16, 0 );
}

void Main::moveU()
{
    editor->translate( 0, -16 );
}

void Main::moveD()
{
    editor->translate( 0, +16 );
}

void Main::print()
{
#if !defined(Q_OS_SYMBIAN)
    if ( !printer ) printer = new QPrinter;
    QPrintDialog dialog(printer, this);
    if(dialog.exec()) {
        QPainter pp(printer);
        canvas->render(&pp);
    }
#endif
}

void Main::addSpriteMine()
{
    Sprite* i = new Sprite;
    i->setFlag(QGraphicsItem::ItemIsMovable);
    canvas->addItem(i);
    i->initPos();
    i->setZValue(qrand()%256);
}

/*QList<QGraphicsItem*> modulos;
QMultiHash<int,line*> conexiones;
*/
void Main::ProcessModules(){
    QString filename = QFileDialog::getOpenFileName();
    //QString filename = "/home/hugo/Desktop/IISem2013/DigII/tareas/tarea1/src/LatchCounter.v";
    Parser pars(filename);
    AddModulesToDB(pars);
    QMessageBox::information(this, tr("Info"),tr("The modules were added to the database\n"),QMessageBox::Ok);


}

void Main::AddModulesToDB(Parser &pars){
    QString Query = "";
    for(int i = 0; i<pars.ModulesIF.size(); ++i){
        QString ModName = pars.ModulesIF[i].Name;
        QString FileName("/home/hugo/Desktop/QtVerilogFiles/."+ModName);/*#*/
        Query.append(QString("INSERT INTO Modules (Name, Inputs, Outputs,PortInfoFile) VALUES ('%1','%2','%3','%4')").arg(ModName).arg(pars.ModulesIF[i].Inputs.size()).arg(pars.ModulesIF[i].Outputs.size()).arg(FileName));
        QSqlQuery Condition(QString("SELECT * FROM Modules where Name='%1'").arg(ModName));
        if(Condition.size())
            qDebug()<<"No Funciona";
        else{
            QFile file(FileName);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            QSqlQuery QuerySql(Query);
            for(int p = 0; p < pars.ModulesIF[i].Inputs.size(); ++p){
                out << pars.ModulesIF[i].Inputs[p].Name << ":" << pars.ModulesIF[i].Inputs[p].BusWidth << ";";
            }
            out<<"\n";
            for(int p = 0; p < pars.ModulesIF[i].Outputs.size(); ++p){
                out << pars.ModulesIF[i].Outputs[p].Name << ":" << pars.ModulesIF[i].Outputs[p].BusWidth << ";";
            }            
            out<<"\nFinPuertos\n";
            QList<QString> Prueba = pars.ModulesIF[i].instances.ModQuant.keys();
            if(Prueba.size()){
                out << "Hierarchy\n";
            }
            for(int p = 0; p < Prueba.size(); ++p){
                out << Prueba[p] << ":" << pars.ModulesIF[i].instances.ModQuant[Prueba[p]]<<";";
            }
            out<<"\n";
            QList<QString> Wires = pars.ModulesIF[i].instances.Wires.keys();
            for(int p = 0; p < Wires.size(); ++p){
                out<<Wires[p]<<":";
                for(int j = 0; j <  pars.ModulesIF[i].instances.Wires[Wires[p]]->size(); ++j){
                    out<<pars.ModulesIF[i].instances.Wires[Wires[p]]->at(j)<<";";
                }
                out<<"\n";
            }
            out<<"\n";
        }

        Query.clear();
        Condition.clear();
    }
}

void Main::DropModuleFromDB(){
    AddFromDB Dialog(this);
    if(Dialog.exec() == QDialog::Accepted){
        QString QueryTemp("SELECT * from Modules WHERE id=");
        QueryTemp += QString::number(Dialog.Location4+1);
        QSqlQuery Query(QueryTemp);
        QVector<QString> inputs_arg, outputs_arg;
        while(Query.next()){
            QFile file(Query.value(5).toString());
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream in(&file);
            int counter = 0;
            while(!in.atEnd()){
                QString Ports(in.readLine());
                if(Ports == "FinPuertos"){
                    break;
                }
                QList<QString> Prueba = Ports.split(';');
                if(!counter)
                    inputs_arg = QVector<QString>::fromList(Prueba);
                else
                    outputs_arg = QVector<QString>::fromList(Prueba);
                counter++;
            }
            if(ModInDesign.contains(Query.value(1).toString())){
                ModInDesign[Query.value(1).toString()] += 1;
            } else {
                ModInDesign[Query.value(1).toString()] = 1;
            }
            QString ToModulo = Query.value(1).toString() +  QString::number(ModInDesign[Query.value(1).toString()]);
            addModulo(ToModulo, Query.value(2).toInt(), Query.value(3).toInt(), inputs_arg, outputs_arg,inputs,outputs,modulos);
        }
    }
}

void Main::DropModuleFromFile(){
    QString filename = QFileDialog::getOpenFileName();
    Parser pars(filename);
    FromFile Dialog(this,&pars);
    int row;
    if(Dialog.exec() == QDialog::Accepted){
        row = Dialog.Location;
        QVector<QString> inputs_arg(pars.ModulesIF[row].Inputs.size());
        QVector<QString> outputs_arg(pars.ModulesIF[row].Outputs.size());
        for(int i = 0; i<pars.ModulesIF[row].Inputs.size(); ++i){
            inputs_arg[i]= pars.ModulesIF[row].Inputs[i].Name+":"+QString::number(pars.ModulesIF[row].Inputs[i].BusWidth);
        }

        for(int i = 0; i<pars.ModulesIF[row].Outputs.size(); ++i){
            outputs_arg[i] = pars.ModulesIF[row].Outputs[i].Name+":"+QString::number(pars.ModulesIF[row].Outputs[i].BusWidth);
        }
        QString name_arg = pars.ModulesIF[row].Name;
        int InputsQuant = pars.ModulesIF[row].Inputs.size();
        int OutputsQuant = pars.ModulesIF[row].Outputs.size();
        if(ModInDesign.contains(name_arg)){
            ModInDesign[name_arg] += 1;
        } else {
            ModInDesign[name_arg] = 1;
        }
        QString ToModulo = name_arg+QString::number(ModInDesign[name_arg]);
        addModulo(ToModulo, InputsQuant, OutputsQuant, inputs_arg, outputs_arg,inputs,outputs,modulos);
    }

}

void Main::addModulo(QString nombre_arg, int cantidadEntradas_Arg, int cantidadSalidas_Arg, QVector<QString> &in, QVector<QString> &out, QMultiHash<int,line*>& Inputs, QMultiHash<int,line*> &Outputs, QList<QGraphicsTextItem*> &Modulos){//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out,bool force,int width,int height){
    int x=0;
    int y=0;
    bool force= false;
    QString nombre =nombre_arg;
    int cantidadEntradas = cantidadEntradas_Arg;
    int cantidadSalidas = cantidadSalidas_Arg;
    int width=150;
    int height=150;
    QString direccionImagen = "/home/hugo/Desktop/QtVerilog/GUI/images.jpeg";/*#*/
    QColor color = Qt::blue;
    int minHeight = 100;
    if(cantidadEntradas>cantidadSalidas){
        minHeight = cantidadEntradas*10+8;
    }
    else{
        minHeight = cantidadSalidas*10+8;
    }
    if(minHeight<100){
        minHeight=100;
    }
    int minWidth=100;///Luego es necsario comparar la altura contra la imágen que va adentro.
    if(force){
        minHeight=width;
        minWidth=height;
    }
    //Objeto central del modulo
    QGraphicsItem *rectangulo = new Core(Modulos.size(),x+20,y+14,direccionImagen,color,cantidadEntradas,cantidadSalidas,this,force,width,height);
    rectangulo->setPos(0,0);
    canvas->addItem(rectangulo);
    ///Escribir el nombre, sobre el objeto
    QGraphicsTextItem *text = new QGraphicsTextItem(nombre);
    text->setPos(20,-10);
    canvas->addItem(text);
    text->setParentItem(rectangulo);
    Modulos<<text;
    int posicion = Modulos.lastIndexOf(text);
    ///Shadows

    for(int i = 0; i<cantidadEntradas;++i){
        line *lineInput;
        QStringList NamWidth = in[i].split(":");
        if(cantidadEntradas != 1){
            lineInput = new line(this,Qt::black,x,x+20-1,y+18+i*((minHeight-10)/(cantidadEntradas-1)),true,0,canvas,NamWidth[0],NamWidth[1].toInt());
        }else
            lineInput = new line(this,Qt::black,x,x+20-1,y+18+((minHeight-10)/2),true,0,canvas,QString::number(posicion)+"_"+NamWidth[0],NamWidth[1].toInt());
        lineInput->setPos(QPointF(0, 0));
        canvas->addItem(lineInput);
        lineInput->setParentItem(rectangulo);
        Inputs.insert(posicion,lineInput);
    }
    for(int i = 0; i<cantidadSalidas;++i){
         line *lineOutput;
         QStringList NamWidth = out[i].split(":");
         if(cantidadSalidas !=1 )
            lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)/(cantidadSalidas-1)),false,0,canvas,QString::number(posicion)+"_"+NamWidth[0],NamWidth[1].toInt());
        else
            lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+((minHeight-10)/2),false,0,canvas,QString::number(posicion)+"_"+NamWidth[0],NamWidth[1].toInt());//lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)*2),false,0,&canvas,out[i]);
        lineOutput->setPos(QPointF(0, 0));
        canvas->addItem(lineOutput);
        lineOutput->setParentItem(rectangulo);
        Outputs.insert(posicion,lineOutput);
    }
}

void Main::print2(){
    QList<connection> con;
    for (int i = 0; i < modulos.size(); ++i) {
        if(modulos.at(i)!=0){///Un cero en la lista significa que fue borrado.
            qDebug()<<"Modulo";
            qDebug()<<modulos.at(i)->toPlainText();
            QList<line*> values = outputs.values(i);
            for(int j=0;j<values.size();++j){
                qDebug()<<"Salidas";
                qDebug()<<values.at(j)->getNombre();
                QString WireName = values.at(j)->getNombre();
                QString PortName = WireName;
                if(values.at(j)->getConnected()){
                    //qDebug()<<"Conectados a:";
                    for(int i=0;i<values.at(j)->getCantidadBits();++i){
                        qDebug()<<"-Bit "+QString::number(i);
                        qDebug()<<"     Conectados a:";
                        if(values.at(j)->getConnected(i)){
                            con = values.at(j)->getAsociado(i);
                            QStringList EntryPorts;
                            for(int z=0; z<con.size();++z){
                                EntryPorts << con.at(z).conexion->getNombre();
                                WireName += con.at(z).conexion->getNombre();
                            }
                            Wires<<WireName;
                            if(PortWireConnection.contains(PortName))
                                PortWireConnection[PortName] = WireName+","+PortWireConnection[PortName];
                            else
                                PortWireConnection[PortName] = WireName;
                            for(int n = 0; n<EntryPorts.size(); ++n){
                                if(PortWireConnection.contains(EntryPorts[n]))
                                    PortWireConnection[EntryPorts[n]] = WireName+","+PortWireConnection[PortName];
                                else
                                    PortWireConnection[EntryPorts[n]] = WireName;
                            }
                        }
                        else{
                            qDebug()<<"     *No Conectado";
                        }
                    }
                }
                else{
                    qDebug()<<"Sin Conexión";
                }
            }
        }
    }
    QFile file("/home/hugo/Desktop/QtVerilogFiles/testbench");/*#*/
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out<<"module testbench();\n";
    out<<"wire ";
    for(int i = 0; i<Wires.size()-1;++i){
        out<<Wires[i]<<",";
    }
    out<<Wires[Wires.size()-1]<<";\n";
    for(int i = 0; i < modulos.size(); ++i){
        QRegExp RegExp;
        RegExp.setPattern("([^0-9]*)");
        RegExp.indexIn(modulos.at(i)->toPlainText());
        out<<RegExp.cap(0)<<" "<<modulos.at(i)->toPlainText()<<"(\n";
        QList<line*> values = outputs.values(i);
        for(int j=0;j<values.size();++j){
            QStringList portList = values.at(j)->getNombre().split("_");
            out<<"\t."<<portList[1]<<"({"<<PortWireConnection[values.at(j)->getNombre()]<<"}),\n";
        }
        values = inputs.values(i);
        for(int j=0;j<values.size()-1;++j){
            QStringList portList = values.at(j)->getNombre().split("_");
            out<<"\t."<<portList[1]<<"({"<<PortWireConnection[values.at(j)->getNombre()]<<"}),\n";
        }
        QStringList portList = values.at(values.size()-1)->getNombre().split("_");
        out<<"\t."<<portList[1]<<"({"<<PortWireConnection[values.at(values.size()-1)->getNombre()]<<"}));\n";
    }
    out<<"endmodule";
}

int Main::setActualItem(Core *Item){
    this->actualItem = Item;
    return 0;
}

void Main::downHierarchie(){
    ///Aqui va una función que abre una nueva ventna del tipo Main, el cual va a contener todo el circuito interno del modulo (si existe).
}

void Main::erase(){
    canvas->removeItem(actualItem);
    int index = actualItem->getIndex();
    QList<line*> out = outputs.values(actualItem->getIndex());
    QList<connection> con;
    ///Outputs puede ir a multiples entradas.
    for(int j=0;j<out.size();++j){
        for(int z=0;z<out.at(j)->getCantidadBits();++z){
            con = out.at(j)->getAsociado(z);
            for(int i=0;i<con.size();++i){
                con.at(i).conexion->eraseConnection(out.at(j),con.at(i).bit,z);
            }

        }
    }
    QList<line*> in = inputs.values(actualItem->getIndex());
    for(int j=0;j<in.size();++j){
        for(int z=0;z<in.at(j)->getCantidadBits();++z){
            con = in.at(j)->getAsociado(z);
            for(int i=0;i<con.size();++i){
                con.at(i).conexion->eraseConnection(out.at(j),con.at(i).bit,z);
            }

        }
    }
    modulos.replace(index,0);
    inputs.remove(index);
    outputs.remove(index);
}

void Main::cleanConnections(){
    toClean->clearAllConnections();
}
