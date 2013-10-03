#ifndef CANVAS_H
#define CANVAS_H

#include <QList>
#include <QMultiHash>
#include <QMenu>
#include <QtGui/QColor>
#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "line.h"
#include "core.h"
class Parser;
class line;
class Core;

///Codigo para agregar imagenes flotando
class Sprite : public QGraphicsPixmapItem{
public:
    Sprite();//Constructor
    int type() const;//Tipo de sprite
    QPainterPath shape() const;//Overload de la función padre

    void initPos();///Define la posicíón inicial del Sprite

};


class FigureEditor : public QGraphicsView {///Este es de las parates esenciales del código y es la que contiene os moudlos.
    Q_OBJECT

public:
    FigureEditor(QGraphicsScene&, QWidget* parent=0, const char* name=0, Qt::WindowFlags f=0);///Constructor del editor de figuras.
    void clear();///Borrar todas ls figuras.

signals:
    void status(const QString&);
};


class Main : public QMainWindow {///Ventana principal donde se agregan los modulos.
    Q_OBJECT

public:
    Main(QGraphicsScene&, QWidget* parent=0, Qt::WindowFlags f=0);///Constructor
    ~Main();///Destructor.
    int setActualItem(Core *Item);///Almacena el último objeto que fue presionado
    int setLineToClean(line *toClean){///Almacena el puntero de la línea que quiere limpiarse las conexiones.
        this->toClean = toClean;
        return 0;
    }
    line *ultimo;///puntero que almacena la linea que fue presionada en el primer click.
    bool isValid;///Indica si ultimo es valido, o lo que es equivalente si ya hubo un primer click.
    bool isBus;///Indica si ultimo es un bus o no.
    int bitNumber;///Indica la cantidad de bits en ultimo.
    bool isSecondClick;///Indica si el presente evento es un segundo click
    bool isInput;///Indica si ultimo es una entrada.
    QColor color;///Color de ultimo
    QList<QGraphicsTextItem*> modulos;///Es una lista de todos los modulso que hay en la ventana, es una lista de nombres.
    QMultiHash<int,line*> inputs;///Es un multi hash que contienen todas las entradas, decodificadas por la posición del modulo en la lista anterior.
    QMultiHash<int,line*> outputs;///Es un multi hash que contienen todas las salidas, decodificadas por la posición del modulo en la lista anterior.

public slots:
    void help();///Ventana de información
    void erase();///Borrar un modulo
    void downHierarchie();///Bajar en la jerarquia.
    void cleanConnections();///Limpiar las conexiones en una linea.

private slots:
    ///Modificaciones a FigureEditor
    void aboutQt();
    void print2();
    void newView();
    void clear();
    void init();
    void addSpriteMine();
    void enlarge();
    void shrink();
    void rotateClockwise();
    void rotateCounterClockwise();
    void zoomIn();
    void zoomOut();
    void mirror();
    void moveL();
    void moveR();
    void moveU();
    void moveD();
    void print();
    void DropModuleFromDB();
    void DropModuleFromFile();
    void ProcessModules();

private:
    QGraphicsScene& canvas;///Posicion adonde se dibujan los modulos.
    FigureEditor *editor;//Ya el objeto en si del figureEdtor
    Core *actualItem;//>Es el objeto que se esta trabajando actualmente.
    QMenu* options;///Menu que despliega opciones.
    line *toClean;/// Linea que hay que limpiar.
    void AddModulesToDB(Parser &);
    void addModulo(QString , int , int , QVector<QString> &in, QVector<QString> &out);//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out);
#if !defined(Q_OS_SYMBIAN)
    QPrinter* printer;
#endif
};

#endif
