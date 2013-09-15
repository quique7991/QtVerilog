#include "line.h"

#include <QtGui>
line::line(Main* const Parent, const QColor &color, int x1, int x2, int y, bool isInput, QGraphicsItem *padre, QGraphicsScene *canvas,QString nombre)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y = y;
    this->color = color;
    this->isInput=isInput;
    this->isConnected=false;
    this->padre=padre;///Es un texto, que hace referencia al módulo.
    this->nombre=nombre;
    this->canvas=canvas;
    this->parent=Parent;
    this->width=10;
    setZValue((x1 + y) % 2);
    setFlags(ItemIsSelectable);
    setToolTip(nombre);
}

QRectF line::boundingRect() const
{
    return QRectF(x1-width/2,y-width/2,x2-x1+width,width);
}

QPainterPath line::shape() const
{
    QPainterPath path;
    path.addRect(x1-width/2,y-width/2,x2-x1+width,width);
    return path;
}

int line::setConnection(line *asociado, QColor color){
    this->color = color;
    this->asociada = asociado;
    ///Aqui se dibuja el cuadrado.
    if(isInput){
        this->rectangle=canvas->addRect(QRectF(x1-0.5*width,y-0.5*width,width,width));//x1-width/2,y-width/2,width,width))
    }
    else{
        this->rectangle=canvas->addRect( QRectF(x2-width/2,y-width/2,width,width));
    }
    canvas->update();
    return 0;
}
int line::setAsociada(line *asociada){
    this->asociada=asociada;
    return 0;
}

int line::setConnected(bool con){
    this->isConnected=con;
    return 0;
}

void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    QBrush b = painter->brush();
    painter->setPen(QPen(Qt::gray, 1));
    this->line1 = new QLine(x1,y,x2,y);
    painter->drawLine(*line1);
    if(isConnected){
        if(isInput){
            painter->setPen(QPen(color, 1));
            painter->drawRect(QRectF(x1-0.5*width,y-0.5*width,width,width));
        }
        else{
            painter->setPen(QPen(color, 1));
            painter->drawRect(QRectF(x2-width/2,y-width/2,width,width));
            //this->rectangle=canvas->addRect( QRectF(x2-width/2,y-width/2,width,width));
        }
    }
}


void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(isInput){
        QRectF comp = boundingRect();
        if(comp.contains(event->pos())){
            if(parent->ultimo!=this){
                if(!(parent->isValid)){
                    if(this->isConnected){
                        (this->asociada)->setAsociada(0);
                        (this->asociada)->setConnected(false);
                        canvas->update();
                    }
                    isConnected=true;
                    parent->isValid=true;
                    parent->isSecondClick=true;
                    parent->ultimo=this;
                    this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                    parent->color=this->color;
                    parent->isInput=true;
                }
                else{
                    if((parent->isInput)==!(this->isInput)){
                        if(this->isConnected){
                            (this->asociada)->setAsociada(0);
                            (this->asociada)->setConnected(false);
                            canvas->update();
                        }
                        isConnected=true;
                        parent->isValid=false;
                        parent->isSecondClick=false;
                        (parent->ultimo)->setAsociada(this);
                        this->asociada = parent->ultimo;
                        parent->ultimo=0;
                        this->color=parent->color;
                    }
                    else{///Se vuelve a presionar algun linea cuando aún hay otra activa en que no se ha terminado de conectar.
                        if(this->isConnected){
                            (this->asociada)->setAsociada(0);
                            (this->asociada)->setConnected(false);
                            canvas->update();
                        }
                        (parent->ultimo)->setConnected(false);
                        (parent->ultimo)->setAsociada(0);
                        isConnected=true;
                        parent->isValid=true;
                        parent->isSecondClick=true;
                        parent->ultimo=this;
                        this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                        parent->color=this->color;
                        parent->isInput=true;
                    }
                }

            }
        }
    }
    else{
        QRectF comp = boundingRect();
        if(comp.contains(event->pos())){
            if(parent->ultimo!=this){
                if(!(parent->isValid)){
                    if(this->isConnected){
                        (this->asociada)->setAsociada(0);
                        (this->asociada)->setConnected(false);
                        canvas->update();
                    }
                    isConnected=true;
                    parent->isValid=true;
                    parent->isSecondClick=true;
                    parent->ultimo=this;
                    this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                    parent->color=this->color;
                    parent->isInput=false;
                }
                else{
                    if((parent->isInput)==!(this->isInput)){
                        if(this->isConnected){
                            (this->asociada)->setAsociada(0);
                            (this->asociada)->setConnected(false);
                            canvas->update();
                        }
                        isConnected=true;
                        parent->isValid=false;
                        parent->isSecondClick=false;
                        parent->ultimo->setAsociada(this);
                        this->asociada = parent->ultimo;
                        parent->ultimo=0;
                        this->color=parent->color;
                    }
                    else{///Se vuelve a presionar algun linea cuando aún hay otra activa en que no se ha terminado de conectar.
                        if(this->isConnected){
                            (this->asociada)->setAsociada(0);
                            (this->asociada)->setConnected(false);
                            canvas->update();
                        }
                        parent->ultimo->setConnected(false);
                        parent->ultimo->setAsociada(0);
                        isConnected=true;
                        parent->isValid=true;
                        parent->isSecondClick=true;
                        parent->ultimo=this;
                        this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                        parent->color=this->color;
                        parent->isInput=false;
                    }
                }
            }
        }

    }
   update();
}

void line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

}

void line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

bool line::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        QToolTip::showText(helpEvent->pos(), "this->nombre");

        return true;
    }
    return false;
}

QString line::getNombre(){
    return nombre;
}
