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
    Core(int index,int left,int top, QString direccionImagen,QColor color,int cantidadEntradas,int cantidadSalidas,Main *parent,bool force,int width,int height);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    int getIndex();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int left,top,minWidth,minHeight,z;
    QString direccionImagen;
    QColor color;
    Main *parent;
    int index;
};

#endif // CORE_H
