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
#include "canvas.h"
#include "line.h"
#include "core.h"
#include "parser.h"
#include "fromfile.h"
#include "addfromdb.h"
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

Main::Main(QGraphicsScene& c, QWidget* parent, Qt::WindowFlags f) :
    QMainWindow(parent, f),
    canvas(c)
{
    this->isValid=false;
    this->isInput=false;
    this->ultimo=0;
    this->isSecondClick=false;

    editor = new FigureEditor(canvas,this);

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
    db.setHostName("localhost");
    db.setDatabaseName("Prueba");
    db.setUserName("prueba");
    db.setPassword("KarenPa0la");
    if(!db.open()){
        QMessageBox::critical(this, tr("DB Error"),tr("Could not login to db"),QMessageBox::Ok);
    }

    statusBar();

    setCentralWidget(editor);

    QSqlQuery Query("create table IF NOT EXISTS Modules(id int unsigned not null auto_increment, Name varchar(30) not null, Inputs int not null, Outputs int not null, ImageFile varchar(30), PortInfoFile varchar(30), primary key(id))");

#if !defined(Q_OS_SYMBIAN)
    printer = 0;
#endif

    init();
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
    Main *m = new Main(canvas, 0); // AKr, Qt::WA_DeleteOnClose);
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
    canvas.setSceneRect(0, 0, canvas.width()*4/3, canvas.height()*4/3);
}

void Main::shrink()
{
    canvas.setSceneRect(0, 0, qMax(canvas.width()*3/4, qreal(1.0)), qMax(canvas.height()*3/4, qreal(1.0)));
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
        canvas.render(&pp);
    }
#endif
}

void Main::addSpriteMine()
{
    Sprite* i = new Sprite;
    i->setFlag(QGraphicsItem::ItemIsMovable);
    canvas.addItem(i);
    i->initPos();
    i->setZValue(qrand()%256);
}

QList<QGraphicsItem*> modulos;
QMultiHash<int,line*> conexiones;

void Main::ProcessModules(){
    QString filename = QFileDialog::getOpenFileName();
    Parser pars(filename);
    AddModulesToDB(pars);
    QMessageBox::information(this, tr("Info"),tr("The modules were added to the database\n"),QMessageBox::Ok);


}

void Main::AddModulesToDB(Parser &pars){
    QString Query = "";
    for(int i = 0; i<pars.ModulesIF.size(); ++i){
        QString ModName = pars.ModulesIF[i].Name;
        std::cout<<"Module:"<<ModName.toStdString()<<std::endl;
        Query.append(QString("INSERT INTO Modules (Name, Inputs, Outputs) VALUES ('%1','%2','%3')").arg(ModName).arg(pars.ModulesIF[i].InputsTotal).arg(pars.ModulesIF[i].OutputsTotal));
        std::cout<<Query.toStdString()<<std::endl;
        QSqlQuery QuerySql(Query);
        Query.clear();
    }
}

void Main::DropModuleFromDB(){
    AddFromDB Dialog(this);
    if(Dialog.exec() == QDialog::Accepted){
        QString QueryTemp("SELECT * from Modules WHERE id=");
        QueryTemp += QString::number(Dialog.Location4+1);
        std::cout<<QueryTemp.toStdString()<<std::endl;
        std::cout << Dialog.Location4 << std::endl ;
        QSqlQuery Query(QueryTemp);
        QVector<QString> inputs, outputs;
        while(Query.next()){
        for(int i = 0 ; i<Query.value(2).toInt(); ++i){
            inputs << QString("IN")+QString::number(i+1);
        }
        for(int i = 0; i<Query.value(3).toInt(); ++i)
            outputs << QString("OUT")+QString::number(i+1);

        addModulo(Query.value(1).toString(), Query.value(2).toInt(), Query.value(3).toInt(), inputs, outputs);
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
        QVector<QString> inputs(pars.ModulesIF[row].InputsTotal);
        QVector<QString> outputs(pars.ModulesIF[row].OutputsTotal);
        QString Temp;
        int temp = 0;
        for(int i = 0; i<pars.ModulesIF[row].Inputs.size(); ++i){
            for(int j = 0; j < pars.ModulesIF[row].Inputs[i].BusWidth; ++j){
                Temp = pars.ModulesIF[row].Inputs[i].Name+QString::number(j);
                inputs[temp] = Temp;
                Temp.clear();
                temp += 1;
            }
        }

        temp = 0;
        for(int i = 0; i<pars.ModulesIF[row].Outputs.size(); ++i){
            for(int j = 0; j < pars.ModulesIF[row].Outputs[i].BusWidth; ++j){
                Temp = pars.ModulesIF[row].Outputs[i].Name+QString::number(j);
                outputs[temp] += Temp;
                Temp.clear();
                temp += 1;
            }
        }
        QString name_arg = pars.ModulesIF[row].Name;
        int InputsQuant = pars.ModulesIF[row].InputsTotal;
        int OutputsQuant = pars.ModulesIF[row].OutputsTotal;
        addModulo(name_arg, InputsQuant, OutputsQuant, inputs, outputs);
    }

}

void Main::addModulo(QString nombre_arg, int cantidadEntradas_Arg, int cantidadSalidas_Arg, QVector<QString> &in, QVector<QString> &out){//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out,bool force,int width,int height){
    int x=0;
    int y=0;
    bool force= false;
    QString nombre =nombre_arg;
    int cantidadEntradas = cantidadEntradas_Arg;
    int cantidadSalidas = cantidadSalidas_Arg;
    int width=150;
    int height=150;
    QString direccionImagen = "/home/quique/Desktop/QtVerilog/GUI/images.jpeg";
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
    QGraphicsItem *rectangulo = new Core(modulos.size(),x+20,y+14,direccionImagen,color,cantidadEntradas,cantidadSalidas,this,force,width,height);
    rectangulo->setPos(0,0);
    canvas.addItem(rectangulo);
    ///Escribir el nombre, sobre el objeto
    QGraphicsTextItem *text = new QGraphicsTextItem(nombre);
    text->setPos(20,-10);
    canvas.addItem(text);
    text->setParentItem(rectangulo);
    modulos<<text;
    int posicion = modulos.lastIndexOf(text);
    ///Shadows
    for(int i = 0; i<cantidadEntradas;++i){
        line *lineInput;
        if(cantidadEntradas !=1 )
            lineInput = new line(this,Qt::black,x,x+20-1,y+18+i*((minHeight-10)/(cantidadEntradas-1)),true,0,&canvas,in[i],3);
        else
            lineInput = new line(this,Qt::black,x,x+20-1,y+18+((minHeight-10)/2),true,0,&canvas,in[i],3);
        lineInput->setPos(QPointF(0, 0));
        canvas.addItem(lineInput);
        lineInput->setParentItem(rectangulo);
        inputs.insert(posicion,lineInput);
    }
    for(int i = 0; i<cantidadSalidas;++i){
         line *lineOutput;
        if(cantidadSalidas !=1)
            lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)/(cantidadSalidas-1)),false,0,&canvas,out[i],1);
        else
            lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+((minHeight-10)/2),false,0,&canvas,out[i],1);//lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)*2),false,0,&canvas,out[i]);
        lineOutput->setPos(QPointF(0, 0));
        canvas.addItem(lineOutput);
        lineOutput->setParentItem(rectangulo);
        outputs.insert(posicion,lineOutput);
    }
}

void Main::print2(){
    QList<connection> con;
    for (int i = 0; i < modulos.size(); ++i) {
        if(modulos.at(i)!=0){///Un cero en la lista significa que fue borrado.
            qDebug()<<"Modulo";
            qDebug()<<modulos.at(i)->toPlainText();
            QList<line*> values1 = inputs.values(i);
            for(int j=0;j<values1.size();++j){
                qDebug()<<"Entradas";
                qDebug()<<values1.at(j)->getNombre();
                if(values1.at(j)->getConnected()){
                    //qDebug()<<"Conectados a:";
                    for(int i=0;i<values1.at(j)->getCantidadBits();++i){
                        qDebug()<<"-Bit "+QString::number(i);
                        qDebug()<<"     Conectados a:";
                        if(values1.at(j)->getConnected(i)){
                            con = values1.at(j)->getAsociado(i);
                            for(int z=0; z<con.size();++z){
                                qDebug()<<"     *"+con.at(z).conexion->getNombre();
                                qDebug()<<"         @"+QString::number(con.at(z).bit);
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
            QList<line*> values = outputs.values(i);
            for(int j=0;j<values.size();++j){
                qDebug()<<"Salidas";
                qDebug()<<values.at(j)->getNombre();
                if(values.at(j)->getConnected()){
                    //qDebug()<<"Conectados a:";
                    for(int i=0;i<values.at(j)->getCantidadBits();++i){
                        qDebug()<<"-Bit "+QString::number(i);
                        qDebug()<<"     Conectados a:";
                        if(values.at(j)->getConnected(i)){
                            con = values.at(j)->getAsociado(i);
                            for(int z=0; z<con.size();++z){
                                qDebug()<<"     *"+con.at(z).conexion->getNombre();
                                qDebug()<<"         @"+QString::number(con.at(z).bit);
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
}

int Main::setActualItem(Core *Item){
    this->actualItem = Item;
    return 0;
}

void Main::downHierarchie(){
    ///Aqui va una función que abre una nueva ventna del tipo Main, el cual va a contener todo el circuito interno del modulo (si existe).
}

void Main::erase(){
    canvas.removeItem(actualItem);
    int index = actualItem->getIndex();
    modulos.replace(index,0);
    inputs.remove(index);
    outputs.remove(index);
    QList<line*> out = outputs.values(actualItem->getIndex());
    QList<connection> con;
    ///Outputs puede ir a multiples entradas.
    for(int j=0;j<out.size();++j){
        for(int z=0;z<out.at(j)->getCantidadBits();++z){
            con = out.at(j)->getAsociado(z);
            for(int i=0;i<con.size();++i){
                con.at(i).conexion->eraseConnection(out.at(j),z,con.at(i).bit);
            }

        }
    }
    QList<line*> in = inputs.values(actualItem->getIndex());
    for(int j=0;j<in.size();++j){
        for(int z=0;z<in.at(j)->getCantidadBits();++z){
            con = in.at(j)->getAsociado(z);
            for(int i=0;i<con.size();++i){
                con.at(i).conexion->eraseConnection(out.at(j),z,con.at(i).bit);
            }

        }
    }
}
