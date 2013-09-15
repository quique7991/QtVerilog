#ifndef CORE_H
#define CORE_H

#include <QGraphicsItem>
#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include <QtGui>
#include <QPainter>
#include <QMenu>


class Core : public QGraphicsItem
{
public:
    Core(int left,int top, QString direccionImagen,QColor color,int cantidadEntradas,int cantidadSalidas,QGraphicsScene *canvas);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private slots:
    void downHierarchie();
    void erase();

private:
    int left,top,minWidth,minHeight,z;
    QString direccionImagen;
    QColor color;
    QGraphicsScene *canvas;
};

#endif // CORE_H
