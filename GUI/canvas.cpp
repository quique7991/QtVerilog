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
#include "canvas.h"
#include "line.h"
#include "core.h"
#include "parser.h"
#include "fromfile.h"
#include "addfromdb.h"
/*
Es la clase que contiene a todos los objetos incluyendo el canvas y es la que permite dibujar los modulos.
*/
FigureEditor::FigureEditor(
	QGraphicsScene& c, QWidget* parent,
	const char* name, Qt::WindowFlags f) :
    QGraphicsView(&c,parent)
{
    ///En el constructor solo se asignan las varibles correspondientes, y se definen algunos parámetros.
    setObjectName(name);
    setWindowFlags(f);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}
/*
    Se borran todas las figuras en el figureEidtor.
*/
void FigureEditor::clear()
{
    scene()->clear();
}

Sprite::Sprite(){///Constructor del Sprite, permite elegir el sprite que se va a abrir.
    QString fileName = QFileDialog::getOpenFileName(0,"Open file","","*.*");

    setPixmap(QPixmap(fileName));
}

/*
    Función sobrecargada, se devuelve un valor defaullt.
*/
int Sprite::type() const{
    return 1234;
}

/*
    Función legacy requerida.
*/
void Sprite::initPos(){
}
/*
  Función requerida por la clase padre.
*/
QPainterPath Sprite::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
/*
  Constructor de Main
  */
Main::Main(QGraphicsScene& c, QWidget* parent, Qt::WindowFlags f) :
    QMainWindow(parent, f),
    canvas(c)
{
    ///Se inicializan las varibles que se utilizan para almacenar información en un click en una conexión de un modulo.
    this->isValid=false;
    this->isInput=false;
    this->ultimo=0;
    this->isSecondClick=false;

    ///Se crea el editor de figuras.
    editor = new FigureEditor(canvas,this);

    ///Se agrega un menu a la ventana.
    QMenuBar* menu = menuBar();

    //Se agregan las distintas acciones al menu y se conectan a su resepectiva función y shortcut.
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

    ///Se agrega la conexión a la base de datos. Es necesario alterar estas líneas para un computador distinto
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Prueba");
    db.setUserName("root");
    db.setPassword("password");
    if(!db.open()){
        QMessageBox::critical(this, tr("DB Error"),tr("Could not login to db"),QMessageBox::Ok);
    }

    statusBar();

    setCentralWidget(editor);

    ///Se hace el query para crear la tabla si no existe.
    QSqlQuery Query("create table Modules(id int unsigned not null auto_increment, Name varchar(30) not null, Inputs int not null, Outputs int not null, ImageFile varchar(200), PortInfoFile varchar(200), primary key(id), unique key(Name))");

#if !defined(Q_OS_SYMBIAN)
    printer = 0;
#endif

    init();///Se inicializa el main.
}

/*
    Se limpia la ventana
*/
void Main::init()
{
    clear();
}

/*
    Destructor de Main, dado que qt borra automaticamente muchos de los objetos creados, principalmente los agregados a layouts no es necesario,limpiar muchos de los punteros.
*/
Main::~Main()
{
#if !defined(Q_OS_SYMBIAN)
    delete printer;
#endif
}

/*
    Se crea una ventana nueva y limpia.
*/
void Main::newView()
{
    // Open a new view... have it delete when closed.
    Main *m = new Main(canvas, 0); // AKr, Qt::WA_DeleteOnClose);
    m->show();
}

/*
    Se limpia el editor de figuras.
*/
void Main::clear()
{
    editor->clear();
}

/*
    Se genera un mensaje de help, básico.
*/
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

/*
    About para el programa
*/
void Main::aboutQt()
{
    QMessageBox::aboutQt( this, "Qt-based program" );
}

/*
    Se acercan los objetos.
*/
void Main::enlarge()
{
    canvas.setSceneRect(0, 0, canvas.width()*4/3, canvas.height()*4/3);
}

/*
    Se alejan los objetos
*/

void Main::shrink()
{
    canvas.setSceneRect(0, 0, qMax(canvas.width()*3/4, qreal(1.0)), qMax(canvas.height()*3/4, qreal(1.0)));
}
/*
    Se rotan los objetos
*/
void Main::rotateClockwise()
{
    editor->rotate( 22.5 );
}
/*
    Se rotan los objetos
*/

void Main::rotateCounterClockwise()
{
    editor->rotate( -22.5 );
}
/*
    Se acercan los objetos.
*/

void Main::zoomIn()
{
    editor->scale( 2.0, 2.0 );
}
/*
    Se alejan los objetos.
*/

void Main::zoomOut()
{
    editor->scale( 0.5, 0.5 );
}
/*
    Se refleja respecto al eje X.
*/
void Main::mirror()
{
    editor->scale( -1, 1 );
}

/*
    Se mueven a la izquierda los objetos.
*/
void Main::moveL()
{
    editor->translate( -16, 0 );
}
/*
  Se mueven a la derecha los objetos.
  */
void Main::moveR()
{
    editor->translate( +16, 0 );
}
/*
    Se mueven hacia arriba.
*/
void Main::moveU()
{
    editor->translate( 0, -16 );
}
/*
    Se mueven hacia abajo.
*/
void Main::moveD()
{
    editor->translate( 0, +16 );
}
/*
    Imprimir lo que hay en pantalla.
*/
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
        QString FileName("/home/quique/Desktop/QtVerilog/."+ModName);
        QFile file(FileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        std::cout<<"Module:"<<ModName.toStdString()<<std::endl;
        Query.append(QString("INSERT INTO Modules (Name, Inputs, Outputs,PortInfoFile) VALUES ('%1','%2','%3','%4')").arg(ModName).arg(pars.ModulesIF[i].Inputs.size()).arg(pars.ModulesIF[i].Outputs.size()).arg(FileName));
        QSqlQuery Condition(QString("SELECT * FROM Modules where Name='%1'").arg(ModName));
        std::cout<<Query.toStdString()<<std::endl;
        if(Condition.size())
            std::cout<<"No Funciona"<<std::endl;
        else{
            QSqlQuery QuerySql(Query);
            for(int p = 0; p < pars.ModulesIF[i].Inputs.size(); ++p){
                out << pars.ModulesIF[i].Inputs[p].Name << ":" << pars.ModulesIF[i].Inputs[p].BusWidth << ";";
            }
            out<<"\n";
            for(int p = 0; p < pars.ModulesIF[i].Outputs.size(); ++p){
                out << pars.ModulesIF[i].Outputs[p].Name << ":" << pars.ModulesIF[i].Outputs[p].BusWidth << ";";
            }
            out<<"\nFinPuertos";
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
        QVector<QString> inputs, outputs;
        while(Query.next()){
            qDebug()<<Query.value(5).toString();
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
                for(int j = 0; j < Prueba.size();++j){
                    qDebug()<<Prueba[j];
                }
                if(!counter)
                    inputs = QVector<QString>::fromList(Prueba);
                else
                    outputs = QVector<QString>::fromList(Prueba);
                counter++;
            }
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
        QVector<QString> inputs(pars.ModulesIF[row].Inputs.size());
        QVector<QString> outputs(pars.ModulesIF[row].Outputs.size());
        for(int i = 0; i<pars.ModulesIF[row].Inputs.size(); ++i){
            inputs[i]= pars.ModulesIF[row].Inputs[i].Name+":"+QString::number(pars.ModulesIF[row].Inputs[i].BusWidth);
        }

        for(int i = 0; i<pars.ModulesIF[row].Outputs.size(); ++i){
            outputs[i] = pars.ModulesIF[row].Outputs[i].Name+":"+QString::number(pars.ModulesIF[row].Outputs[i].BusWidth);
        }
        QString name_arg = pars.ModulesIF[row].Name;
        int InputsQuant = pars.ModulesIF[row].Inputs.size();
        int OutputsQuant = pars.ModulesIF[row].Outputs.size();
        addModulo(name_arg, InputsQuant, OutputsQuant, inputs, outputs);
    }

}
/*
    Esta función permite agregar un modulo a la pantalla.
*/
void Main::addModulo(QString nombre_arg, int cantidadEntradas_Arg, int cantidadSalidas_Arg, QVector<QString> &in, QVector<QString> &out){//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out,bool force,int width,int height){
    ///Se inicializa la posición en cero.
    int x=0;
    int y=0;
    ///Esta variable define, si se utiliza el tamaño predeterminado de imagen, o el definido por el usuario.
    bool force= false;
    QString nombre =nombre_arg;///Nombre que sale encima del módulo
    int cantidadEntradas = cantidadEntradas_Arg;///Cantidad de lineas que aparecen a la izquierda, son inputs.
    int cantidadSalidas = cantidadSalidas_Arg;///Cantidad de líneas que aparecen a la derecha son outputs.
    int width=150;//Tamaño base de ancho.
    int height=150;///Tamaño base de altura
    QString direccionImagen = "/home/quique/Desktop/QtVerilog/GUI/images.jpeg";///Imagen defualt
    QColor color = Qt::blue;///Color default
    int minHeight = 100;///altura minima.
    if(cantidadEntradas>cantidadSalidas){///Se corrige el tamaño en caso de que hallan demasiadas entradas.
        minHeight = cantidadEntradas*10+8;
    }
    else{///o demasiadas salidas.
        minHeight = cantidadSalidas*10+8;
    }
    if(minHeight<100){///Si el tama;o es muy pequeño se asigna 100.
        minHeight=100;
    }
    int minWidth=100;///Luego es necsario comparar la altura contra la imágen que va adentro.
    if(force){///Si se forzo el tamaño se asignan los valores correspondintes.
        minHeight=width;
        minWidth=height;
    }
    //Objeto central del modulo
    QGraphicsItem *rectangulo = new Core(modulos.size(),x+20,y+14,direccionImagen,color,cantidadEntradas,cantidadSalidas,this,force,width,height);
    rectangulo->setPos(0,0);///Se asigna su posición relativa al editor de figuras.
    canvas.addItem(rectangulo);///Se agrega al canvas.
    ///Escribir el nombre, sobre el objeto
    QGraphicsTextItem *text = new QGraphicsTextItem(nombre);
    text->setPos(20,-10);///Se asigna la posición del texto
    canvas.addItem(text);///Se agrega el texto
    text->setParentItem(rectangulo);///Se asigna al parent para que se mueva en conjunto con el rectangulo.
    modulos<<text;///Se agrega el texto para definir un modulo en la lista.
    int posicion = modulos.lastIndexOf(text);///Se obtiene el indice de este.
    ///Shadows
    for(int i = 0; i<cantidadEntradas;++i){///Se agrega cada una de las entradas.
        line *lineInput;
        QStringList NamWidth = in[i].split(":");
        std::cout<<"LLegue Aqui"<<std::endl;
        if(cantidadEntradas != 1 || NamWidth[1].toInt() != 1)
            lineInput = new line(this,Qt::black,x,x+20-1,y+18+i*((minHeight-10)/(cantidadEntradas-1)),true,0,&canvas,NamWidth[0],NamWidth[1].toInt());
        else
            lineInput = new line(this,Qt::black,x,x+20-1,y+18+((minHeight-10)/2),true,0,&canvas,NamWidth[0],NamWidth[1].toInt());
        lineInput->setPos(QPointF(0, 0));///Se define la posici[on
        canvas.addItem(lineInput);///Se agrega una linea
        lineInput->setParentItem(rectangulo);//SE asigna el parent
        inputs.insert(posicion,lineInput);///Se agrega al hash de inputs
    }
    for(int i = 0; i<cantidadSalidas;++i){///Se agregan las salidas, equialnete a las entradas, pero al a derecha.
         line *lineOutput;
         QStringList NamWidth = out[i].split(":");
        if(cantidadSalidas !=1)
            lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)/(cantidadSalidas-1)),false,0,&canvas,NamWidth[0],NamWidth[1].toInt());
        else
            lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+((minHeight-10)/2),false,0,&canvas,NamWidth[0],NamWidth[1].toInt());//lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)*2),false,0,&canvas,out[i]);
        lineOutput->setPos(QPointF(0, 0));
        canvas.addItem(lineOutput);
        lineOutput->setParentItem(rectangulo);
        outputs.insert(posicion,lineOutput);
    }
}

/*
    Este función permite imprimir todos los modulos y sus respectivas conexiones en el Canvas.
*/
void Main::print2(){
    QList<connection> con;
    for (int i = 0; i < modulos.size(); ++i) {///Se recorre la lista de modulos.
        if(modulos.at(i)!=0){///Un cero en la lista significa que fue borrado.
            qDebug()<<"Modulo";
            qDebug()<<modulos.at(i)->toPlainText();///Se imprime el nombre.
            QList<line*> values1 = inputs.values(i);///Se obtienen  las entradas asociadas a este
            for(int j=0;j<values1.size();++j){///Se recorre esta lista
                qDebug()<<"Entradas";
                qDebug()<<values1.at(j)->getNombre();///Se imprime la lista
                if(values1.at(j)->getConnected()){// y las conexioens que tiene.
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
                    qDebug()<<"Sin Conexion";
                }
            }
            QList<line*> values = outputs.values(i);///Se obtienen las salidas
            for(int j=0;j<values.size();++j){///Se imprimen las mismas
                qDebug()<<"Salidas";
                qDebug()<<values.at(j)->getNombre();
                if(values.at(j)->getConnected()){///Se imprimen las conexiones existentes.
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

/*
    Permite asignar a lavariable priva actualItem un puntero.
*/
int Main::setActualItem(Core *Item){
    this->actualItem = Item;
    return 0;
}

void Main::downHierarchie(){
    ///Aqui va una función que abre una nueva ventna del tipo Main, el cual va a contener todo el circuito interno del modulo (si existe).
}

/*
    Esta función permite borrar un modulo, y todas las conexiones existentes en este.
*/

void Main::erase(){
    canvas.removeItem(actualItem);///Se borra del canvas.
    int index = actualItem->getIndex();///Se obtiene el indice.
    QList<line*> out = outputs.values(actualItem->getIndex());//Se obtienen las salidas
    QList<connection> con;///Se obtiene la lista dde conexiones.
    ///Outputs puede ir a multiples entradas.
    for(int j=0;j<out.size();++j){///Se recorre toda la lista de slidas.
        for(int z=0;z<out.at(j)->getCantidadBits();++z){///Por cada salida, se obtienen las conexiones y se desconectan.
            con = out.at(j)->getAsociado(z);
            for(int i=0;i<con.size();++i){
                con.at(i).conexion->eraseConnection(out.at(j),con.at(i).bit,z);
            }

        }
    }
    //Mismo proceso para las entradas.
    QList<line*> in = inputs.values(actualItem->getIndex());
    for(int j=0;j<in.size();++j){
        for(int z=0;z<in.at(j)->getCantidadBits();++z){
            con = in.at(j)->getAsociado(z);
            for(int i=0;i<con.size();++i){
                con.at(i).conexion->eraseConnection(out.at(j),con.at(i).bit,z);
            }

        }
    }
    modulos.replace(index,0);///Se borra el valor de la lista (se asigna un cero)
    inputs.remove(index);///Se borran todas las entradas asignadas.
    outputs.remove(index);///Se borran todas las salidas.
}

void Main::cleanConnections(){
    toClean->clearAllConnections();///Se borran las conexiones para una linea en espec[ifico.
}
