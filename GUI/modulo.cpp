#include "modulo.h"
#include <QtGui>

Modulo::Modulo(int x, int y, QString nombre, int cantidadEntradas, int cantidadSalidas, QString direccionImagen, QColor color)
{
    this->x = x;
    this->y = y;
    this->nombre=nombre;
    this->color=color;
    this->cantidadEntradas=cantidadEntradas;
    this->cantidadSalidas=cantidadSalidas;
    this->direccionImagen=direccionImagen;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptsHoverEvents(true);

}


QRectF Modulo::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}

QPainterPath Modulo::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void Modulo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
    int minimo = 0;
    if(cantidadEntradas>cantidadSalidas){
        minimo = cantidadEntradas*10+8;
    }
    else{
        minimo = cantidadEntradas*10+8;
    }
    if(minimo<150){
        minimo=150;
    }
    painter->drawRect(QRect(20,14,150,minimo));
    painter->setBrush(b);

    ///Shadow
    painter->setPen(QPen(Qt::gray, 1));
    painter->drawLine(21,minimo+4,149,minimo+4);
    painter->drawLine(150,minimo-1,150,20);
    painter->setPen(QPen(Qt::black, 0));

    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->scale(0.1, 0.1);
    painter->drawText(170, 180, nombre.arg(x).arg(y));
    painter->restore();


    // Draw lines
    for(int i = 0; i<=cantidadEntradas;++i){
        //inputs.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
    }
    for(int i = 0; i<=cantidadSalidas;++i){
        //outputs.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
    }
    //painter->drawLines(inputs);
    //painter->drawLines(outputs);

}

void Modulo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Modulo::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Modulo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
