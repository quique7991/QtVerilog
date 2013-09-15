#ifndef LINE_H
#define LINE_H

#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include "canvas.h"

class Main;

class line : public QGraphicsItem
{
public:
    line(Main* const parent,const QColor &color, int x1,int x2, int y,bool isInput,QGraphicsItem *padre, QGraphicsScene *canvas,QString nombre);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    int setConnection(line *asociado, QColor color);
    int setAsociada(line *asociada);
    int setConnected(bool con);
    QString getNombre();
    bool getConnected(){return isConnected;}
    line* getAsociado(){return asociada;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool event(QEvent *event);

private:
    int x1,x2, y;
    bool isInput,isConnected;
    QGraphicsItem *padre;
    int width;
    Main *parent;
    QColor color;
    line *asociada;
    QString nombre;
    QList<QPointF> stuff;
    QGraphicsRectItem *rectangle;
    QLine *line1;
    QGraphicsScene *canvas;
};

#endif //LINE_H
