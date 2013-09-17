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

#include "canvas.h"
#include "line.h"
#include "core.h"

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
    edit->addAction("Add Modulo",this,SLOT(addModulo()/*(0,0,"Modulo",3,3,"BLA",Qt::blue,bla1,bla2)*/),Qt::ALT+Qt::Key_1);
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

    statusBar();

    setCentralWidget(editor);

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


void Main::addModulo(){//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out,bool force,int width,int height){
    int x=0;
    int y=0;
    QString nombre="Modulo";
    bool force= false;
    int cantidadEntradas=5;
    int cantidadSalidas=5;
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
        line *lineInput = new line(this,Qt::black,x,x+20-1,y+18+i*((minHeight-10)/(cantidadEntradas-1)),true,0,&canvas,"bla"+QString::number(i)+"in");
        lineInput->setPos(QPointF(0, 0));
        canvas.addItem(lineInput);
        lineInput->setParentItem(rectangulo);
        inputs.insert(posicion,lineInput);
    }
    for(int i = 0; i<cantidadSalidas;++i){
        line *lineOutput = new line(this,Qt::black,x+21+minWidth,x+41+minWidth,y+18+i*((minHeight-10)/(cantidadSalidas-1)),false,0,&canvas,"bla"+QString::number(i)+"out");
        lineOutput->setPos(QPointF(0, 0));
        canvas.addItem(lineOutput);
        lineOutput->setParentItem(rectangulo);
        outputs.insert(posicion,lineOutput);
    }
}

void Main::print2(){
    /*for (int i = 0; i < modulos.size(); ++i) {
        qDebug()<<"Modulo";
        qDebug()<<modulos.at(i)->toPlainText();
        QList<line*> values1 = inputs.values(i);
        for(int j=0;j<values1.size();++j){
            qDebug()<<"Entradas";
            qDebug()<<values1.at(j)->getNombre();
            if(values1.at(j)->getConnected()){
                qDebug()<<values1.at(j)->getAsociado()->getNombre();
            }
            else{
                qDebug()<<"Sin Conectar";
            }
        }
        QList<line*> values = outputs.values(i);
        for(int j=0;j<values.size();++j){
            qDebug()<<"Salidas";
            qDebug()<<values.at(j)->getNombre();
            if(values.at(j)->getConnected()){
                qDebug()<<values.at(j)->getAsociado()->getNombre();
            }
            else{
                qDebug()<<"Sin Conectar";
            }
        }

    }*/
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
    QList<line*> out = outputs.values(actualItem->getIndex());
    QList<line*> con;
    ///Outputs puede ir a multiples entradas.
    for(int j=0;j<out.size();++j){
        con = out.at(j)->getAsociado();
        for(int i=0;i<con.size();++i){
            con.at(i)->eraseConnection(out.at(j));
        }
    }
    QList<line*> in = inputs.values(actualItem->getIndex());
    for(int j=0;j<in.size();++j){
        QList<line*> con = in.at(j)->getAsociado();
        for(int i=0;i<con.size();++i){
            con.at(i)->eraseConnection(in.at(j));
        }
    }
}
