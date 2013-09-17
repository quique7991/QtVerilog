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

int line::eraseConnection(line *conexion){
    int con = asociada.indexOf(conexion);
    if(con != -1){
        asociada.removeAt(con);
    }
    if(asociada.isEmpty()){
        this->isConnected = false;
    }
    update();
    return 0;
}

int line::addConnection(line *conexion){
    if(isInput){
        if(asociada.isEmpty()){
            asociada.append(conexion);
        }
        else{
            asociada.replace(0,conexion);
        }
    }
    else{
        asociada.append(conexion);
    }
    this->isConnected=true;
    return 0;
}

bool line::getConnected(){
   return !(asociada.isEmpty());
}

QList<line*>& line::getAsociado(){
    return asociada;
}

int line::setConnected(bool con){
    this->isConnected=con;
    update();
    return 0;
}

int line::setColor(QColor color){
    this->color = color;
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


bool line::getVarConnected(){
    return this->isConnected;
}

void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(parent->isSecondClick){///Segundo click
        if(parent->ultimo!=this){//Se verifica que el segundo botón no sea el primero.
            if(parent->isInput!=isInput){///Se verifica si el anterior es del tipo distinto, solo se puede conectar input->output, output->input.
                if(event->modifiers()==Qt::ControlModifier){///Click especial
                    if(isConnected){///Esta conectado
                        if(isInput){
                            if(isConnected){
                                for(int i=0;i<asociada.size();++i){
                                    asociada.at(i)->eraseConnection(this);
                                }
                                this->asociada.clear();
                            }
                            this->color=parent->color;
                            this->addConnection(parent->ultimo);
                            parent->ultimo->addConnection(this);
                        }
                        else{
                            parent->ultimo->setColor(this->color);
                            parent->ultimo->addConnection(this);
                            this->addConnection(parent->ultimo);
                        }
                    }
                    else{///Esta desconectado.
                        this->color=parent->color;
                        this->addConnection(parent->ultimo);
                        parent->ultimo->addConnection(this);
                    }
                }
                else{///Click sencillo.
                    if(isConnected){
                        for(int i=0;i<asociada.size();++i){
                            asociada.at(i)->eraseConnection(this);
                        }
                        this->asociada.clear();
                    }
                    this->color=parent->color;
                    this->addConnection(parent->ultimo);
                    parent->ultimo->addConnection(this);
                }
                parent->ultimo=0;
                parent->isValid=false;
                parent->isSecondClick=false;

            }
            else{///Si son iguales, se va a un paso equivalente a quere fuera un primer click
                if(parent->ultimo->getVarConnected()){
                    parent->ultimo->setConnected(false);
                }
                parent->ultimo=0;

                if(event->modifiers()==Qt::ControlModifier){///Click especial
                    if(isConnected&&(!isInput)){///Si ya se encuentra conetado, y es una salida.
                        parent->ultimo=this;
                        parent->isInput=this;
                        parent->color=this->color;
                        parent->isValid=true;
                        parent->isSecondClick=true;
                    }
                    else{///Equivalente a un click sencillo.
                        for(int i=0;i<asociada.size();++i){
                            asociada.at(i)->eraseConnection(this);
                        }
                        this->asociada.clear();
                        isConnected=true;
                        parent->isValid=true;
                        parent->isSecondClick=true;
                        parent->ultimo=this;
                        this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                        parent->color=this->color;
                        parent->isInput=isInput;
                    }
                }
                else{///Click Sencillo
                    for(int i=0;i<asociada.size();++i){
                        asociada.at(i)->eraseConnection(this);
                    }
                    this->asociada.clear();
                    isConnected=true;
                    parent->isValid=true;
                    parent->isSecondClick=true;
                    parent->ultimo=this;
                    parent->isInput=isInput;
                    this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                    parent->color=this->color;
                }
            }
        }
    }
    else{////Primer Click
        if(event->modifiers()==Qt::ControlModifier){///Click especial
            if(isConnected&&(!isInput)){///Si ya se encuentra conetado, y no es una salida.
                parent->ultimo=this;
                parent->isInput=isInput;
                parent->color=this->color;
                parent->isValid=true;
                parent->isSecondClick=true;
            }
            else{///Equivalente a un click sencillo.
                for(int i=0;i<asociada.size();++i){
                    asociada.at(i)->eraseConnection(this);
                }
                this->asociada.clear();
                isConnected=true;
                parent->isValid=true;
                parent->isSecondClick=true;
                parent->ultimo=this;
                parent->isInput=isInput;
                this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                parent->color=this->color;
            }
        }
        else{///Click Sencillo
            for(int i=0;i<asociada.size();++i){
                asociada.at(i)->eraseConnection(this);
            }
            this->asociada.clear();
            isConnected=true;
            parent->isValid=true;
            parent->isSecondClick=true;
            parent->ultimo=this;
            parent->isInput=isInput;
            this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
            parent->color=this->color;
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
