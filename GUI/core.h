#ifndef CORE_H
#define CORE_H

#include <QGraphicsItem>
#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include <QtGui>
#include <QPainter>
#include <QMenu>
#include "canvas.h"
class Main;
class Core : public QGraphicsItem
{
public:
    ///Constructor.
    Core(int index,int left,int top, QString direccionImagen,QColor color,int cantidadEntradas,int cantidadSalidas,Main *parent,bool force,int width,int height);
    ///Formas necesario para un QGraphicsItem.
    QRectF boundingRect() const;
    QPainterPath shape() const;
    ///Funcion de dibujo del objeto.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    ///Devuelve el índice en el objeto parent.
    int getIndex();

protected:
    ///Eventos de mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    ///Posicion de la imagen.
    int left,top,minWidth,minHeight,z;
    ///Direccion de la imagen. Hace falta incluir una default.
    QString direccionImagen;
    QColor color;
    ///Ventana que contienen a este objeto.
    Main *parent;
    ///Indice dentro de la lista en el parent.
    int index;
};

#endif // CORE_H
