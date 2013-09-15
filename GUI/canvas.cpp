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
#include "modulo.h"
#include "core.h"

class ImageItem: public QGraphicsRectItem
{
public:
    ImageItem( QImage img );
protected:
    void paint( QPainter *, const QStyleOptionGraphicsItem *option, QWidget *widget );
private:
    QImage image;
    QPixmap pixmap;
};


ImageItem::ImageItem( QImage img )
    : image(img)
{
    setRect(0, 0, image.width(), image.height());
    setFlag(ItemIsMovable);
#if !defined(Q_WS_QWS)
    pixmap.fromImage(image, Qt::OrderedAlphaDither);
#endif
}

void ImageItem::paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget * )
{
// On Qt/Embedded, we can paint a QImage as fast as a QPixmap,
// but on other platforms, we need to use a QPixmap.
#if defined(Q_WS_QWS)
    p->drawImage( option->exposedRect, image, option->exposedRect, Qt::OrderedAlphaDither );
#else
    p->drawPixmap( option->exposedRect, pixmap, option->exposedRect );
#endif
}

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


void Main::addModulo(){//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out){
    int x=0;
    int y=0;
    QString nombre="Modulo";
    int cantidadEntradas=5;
    int cantidadSalidas=5;
    QString direccionImagen = "bla";
    QColor color = Qt::blue;
    int minHeight = 150;
    if(cantidadEntradas>cantidadSalidas){
        minHeight = cantidadEntradas*10+8;
    }
    else{
        minHeight = cantidadSalidas*10+8;
    }
    if(minHeight<50){
        minHeight=50;
    }
    int minWidth=100;///Luego es necsario comparar la altura contra la imágen que va adentro.
    //Objeto central del modulo
    QGraphicsItem *rectangulo = new Core(x+20,y+14,direccionImagen,color,cantidadEntradas,cantidadSalidas,&canvas);
    /*QGraphicsRectItem *rectangulo = canvas.addRect( QRectF(x+20,y+14,minWidth,minHeight) );
    rectangulo->setFlag(QGraphicsItem::ItemIsMovable);
    int z = qrand()%256;
    rectangulo->setBrush( QColor(z,z,z) );
    rectangulo->setPen( QPen(QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8), 6) );
    rectangulo->setZValue(z);*/
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
/*  QGraphicsLineItem *line1 =  QString nombrecanvas.addLine(QLineF(20,minHeight+14,20+minWidth,minHeight+14) );
    QGraphicsLineItem *line2 = canvas.addLine(QLineF(20+minWidth,14+minHeight,20+minWidth,20) );
    line1->setPen(QPen(Qt::gray, 1));
    line2->setPen(QPen(Qt::black, 0));
    line1->setParentItem(rectangulo);
    line2->setParentItem(rectangulo);*/
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
    for (int i = 0; i < modulos.size(); ++i) {
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

    }
}
