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
class Instance;
class Parser;
class line;
class Core;
class Sprite : public QGraphicsPixmapItem{
public:
    Sprite();
    int type() const;
    QPainterPath shape() const;

    void initPos();

};


class FigureEditor : public QGraphicsView {
    Q_OBJECT

public:
    FigureEditor(QGraphicsScene&, QWidget* parent=0, const char* name=0, Qt::WindowFlags f=0);
    void clear();

signals:
    void status(const QString&);
};


class Main : public QMainWindow {
    Q_OBJECT

public:
    Main(QGraphicsScene *canvas1,QWidget* parent=0, Qt::WindowFlags f=0);
    ~Main();
    int setActualItem(Core *Item);
    int setLineToClean(line *toClean){
        this->toClean = toClean;
        return 0;
    }
    line *ultimo;
    bool isValid;
    bool isBus;
    int bitNumber;
    bool isSecondClick;
    bool isInput;
    QColor color;
    QList<QGraphicsTextItem*> modulos, *modulosH;
    QMultiHash<int,line*> inputs;
    QMultiHash<int,line*> outputs;
    QMultiHash<int,line*> *inputsH;
    QMultiHash<int,line*> *outputsH;
    QHash<QString,int> ModInDesign;
    QHash<QString,QString> PortWireConnection;
    QVector<QString> Wires;

public slots:
    void help();
    void erase();
    void downHierarchie();
    void cleanConnections();

private slots:
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
    void ChangeScene();
private:
    QGraphicsScene *canvas,*tempcanvas;
    int Prueba;
    FigureEditor *editor;
    Core *actualItem;
    QMenu* options;
    line *toClean;
    void AddModulesToDB(Parser &);
    void addModulo(QString , int , int , QVector<QString> &in, QVector<QString> &out,QMultiHash<int,line*>& Inputs, QMultiHash<int,line*> &Outputs, QList<QGraphicsTextItem*>& Modulos);//(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color, QString *in, QString *out);
#if !defined(Q_OS_SYMBIAN)
    QPrinter* printer;
#endif
};

#endif
