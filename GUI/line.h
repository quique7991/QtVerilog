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
    int setConnected(bool con);
    int eraseConnection(line *conexion);
    int addConnection(line *conexion);
    int setColor(QColor color);
    QList<line*>& getAsociado();
    QString getNombre();
    bool getConnected();
    bool getVarConnected();

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
    QList<line*> asociada;
    QString nombre;
    QList<QPointF> stuff;
    QGraphicsRectItem *rectangle;
    QLine *line1;
    QGraphicsScene *canvas;
};

#endif //LINE_H
