#ifndef MODULO_H
#define MODULO_H

#include<QString>
#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include "canvas.h"
#include "line.h"


class Modulo : public QGraphicsItem
{
public:
    Modulo(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
    int x, y;
    QColor color;
    QString nombre;
    QString direccionImagen;
    int cantidadEntradas,cantidadSalidas;
    QList<line> inputs;
    QList<line> outputs;
};

#endif // MODULO_H
