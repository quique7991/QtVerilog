#include "line.h"

#include <QtGui>

/*
    Constructor de line
*/
line::line(Main* const Parent, const QColor &color, int x1, int x2, int y, bool isInput, QGraphicsItem *padre, QGraphicsScene *canvas,QString nombre)
{
    //>Se asignan las variables a su correspondiente parámetro.
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
    setFlags(ItemIsSelectable);///Se asigna que el objeto puede ser seleccionado.
    setToolTip(nombre);
}
/*
  Se devuelve el rectangulo envolvente, que define tambien las secciones que estan incluidas para que capture el mouse.
  */
QRectF line::boundingRect() const
{
    return QRectF(x1-width/2,y-width/2,x2-x1+width,width);
}

/*
  Esta función deuvelve la forma de la linea.
  */
QPainterPath line::shape() const
{
    QPainterPath path;
    path.addRect(x1-width/2,y-width/2,x2-x1+width,width);
    return path;
}

/*
    Esta función se encarga de borrar la conexión.
*/

int line::eraseConnection(line *conexion){
    int con = asociada.indexOf(conexion);///Se obtiene el indice en que se encuentra esta conexión.
    if(con != -1){///Si existe
        asociada.removeAt(con);///Se borra
    }
    if(asociada.isEmpty()){///Si esta vacia
        this->isConnected = false;///Se asigna como desconectada la variable
    }
    update();///Se actualiza (se redibuja la linea).
    return 0;
}

/*
    Esta función se encarga de agregar una nueva conexión a esta linea.
*/
int line::addConnection(line *conexion){
    if(isInput){///Si es una entrada solo puede existir una conexion.
        if(asociada.isEmpty()){///Si la lista esta vacia solo se agrega.
            asociada.append(conexion);
        }
        else{///Si ya existe un valor este se sustituye.
            asociada.replace(0,conexion);
        }
    }
    else{///Si es una salida solo se agrega, dado que estas pueden estar asoociadas a varias entradas.
        asociada.append(conexion);
    }
    this->isConnected=true;///>Se asigna  que se dibuje el cuadrado.
    return 0;
}

bool line::getConnected(){///>Devuelve si el nodos se encuentra conectado a esta.
   return !(asociada.isEmpty());
}

QList<line*>& line::getAsociado(){///>Función que devuelve la lista de lineas asociados a esta.
    return asociada;
}

int line::setConnected(bool con){//>Se asigna para que se imprima el cuadrado
    this->isConnected=con;
    update();
    return 0;
}

int line::setColor(QColor color){///>Se asigna el color del cuadrado.
    this->color = color;
    return 0;
}
/*
  Esta función se encarga de dibujar la linea.
  */

void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);///>Se define que se quiere utilizar AntiAliasing para mejorar la linea dibujadas
    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;///Se define el fill del color
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    QBrush b = painter->brush();///Se escoge el color del brush.
    painter->setPen(QPen(Qt::gray, 1));
    this->line1 = new QLine(x1,y,x2,y);///Se crea la nueva linea.
    painter->drawLine(*line1);///Se borra la linea.
    if(isConnected){///Si se encuentra conectado se dibuja el cuadrado.
        ///>Dependiendo si es input o output se dibuja el cuadrado de un lado o el otro.
        if(isInput){
            painter->setPen(QPen(color, 1));
            painter->drawRect(QRectF(x1-0.5*width,y-0.5*width,width,width));
        }
        else{
            painter->setPen(QPen(color, 1));
            painter->drawRect(QRectF(x2-width/2,y-width/2,width,width));
        }
    }
}


bool line::getVarConnected(){///>Devuelve si se esta dibujando el cuadrado o no.
    return this->isConnected;
}
/*
  Esta función se encarga de manejar la conexión de lineas, y definir la maquina de estados que se encarga de manejar este evento.
  */
void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(parent->isSecondClick){///Segundo click
        if(parent->ultimo!=this){//Se verifica que el segundo botón no sea el primero.
            if(parent->isInput!=isInput){///Se verifica si el anterior es del tipo distinto, solo se puede conectar input->output, output->input.
                if(event->modifiers()==Qt::ControlModifier){///Click especial
                    if(isConnected){///Esta conectado
                        if(isInput){//Si es entrada
                            if(isConnected){///y esta conectado
                                for(int i=0;i<asociada.size();++i){///Se desconetan todas las conexiones existentes.
                                    asociada.at(i)->eraseConnection(this);///Se borra este valor de la lista de conexiones.
                                }
                                this->asociada.clear();///Se borra la lista de conexiones
                            }
                            ///>Se conectan los dos nodos (this y el que ya se encontraba almacenado en el parent.
                            this->color=parent->color;
                            this->addConnection(parent->ultimo);
                            parent->ultimo->addConnection(this);
                        }
                        else{///>Si es una salida, pueden haber muchos inputs a una misma salida.
                            ///>Si lo se agrega a la lista del input almacenado en el parent
                            parent->ultimo->setColor(this->color);
                            parent->ultimo->addConnection(this);
                            this->addConnection(parent->ultimo);
                        }
                    }
                    else{///Esta desconectado.
                        ///Se conectan a ambos nodos indiferente de cualquier otra característica.
                        this->color=parent->color;
                        this->addConnection(parent->ultimo);
                        parent->ultimo->addConnection(this);
                    }
                }
                else{///Click sencillo.
                    if(isConnected){///>Si se encuentra conectado.
                        for(int i=0;i<asociada.size();++i){////Se desconectan todos los nodos conectados a este.
                            asociada.at(i)->eraseConnection(this);
                        }
                        this->asociada.clear();///>Se limpia la lista de conexiones del nodo.
                    }
                    ///Se conecta este nodo con el nodo anterior.
                    this->color=parent->color;
                    this->addConnection(parent->ultimo);
                    parent->ultimo->addConnection(this);
                }
                parent->ultimo->update();///Se actualiza el nodo al que se conecto.
                ///>Se limpian las variables en la escena padre.
                parent->ultimo=0;
                parent->isValid=false;
                parent->isSecondClick=false;

            }
            else{///Si son iguales en tipo (input,output), se va a un paso equivalente a quere fuera un primer click
                if(parent->ultimo->getVarConnected()){///>Se desconecta el nodo que no se utilizó anteriormente.
                    parent->ultimo->setConnected(false);
                }
                parent->ultimo=0;

                if(event->modifiers()==Qt::ControlModifier){///Click especial
                    if(isConnected&&(!isInput)){///Si ya se encuentra conetado, y es una salida.
                        ///>Se almacenan las variables en la escena padre.
                        parent->ultimo=this;
                        parent->isInput=this;
                        parent->color=this->color;
                        ///>Se asignan las variables que indican que el siguiente boton es el segundo click.
                        parent->isValid=true;
                        parent->isSecondClick=true;
                    }
                    else{///Equivalente a un click sencillo.
                        for(int i=0;i<asociada.size();++i){///>Se borran todas las conexiones que ya existian con este nodo.
                            asociada.at(i)->eraseConnection(this);
                        }
                        this->asociada.clear();///>Se limpia la lista.
                        ///>Se almacenan las variables para indicar que el siguiente click es el segundo click del botón.
                        isConnected=true;
                        parent->isValid=true;
                        parent->isSecondClick=true;
                        //>Se asignan las variables a la escena padre.
                        parent->ultimo=this;
                        ///>Se generá el color del cuadrado.
                        this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                        parent->color=this->color;
                        parent->isInput=isInput;
                    }
                }
                else{///Click Sencillo
                    for(int i=0;i<asociada.size();++i){///>Se borran las conexiones existentes.
                        asociada.at(i)->eraseConnection(this);
                    }
                    this->asociada.clear();///>Se limpia el vector .
                    ///>Se almacenan las variables y se asignan los colores al presente.
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
            if(isConnected&&(!isInput)){///Si ya se encuentra conetado, y es una salida.
                ///>Solo se alamacenan los valores al partent.
                parent->ultimo=this;
                parent->isInput=isInput;
                parent->color=this->color;
                parent->isValid=true;
                parent->isSecondClick=true;
            }
            else{///Equivalente a un click sencillo.
                for(int i=0;i<asociada.size();++i){///>Se borran las conexiones.
                    asociada.at(i)->eraseConnection(this);
                }
                this->asociada.clear();///>Se borra la lista.
                ///>Se asignan los valores del cuadrado y de conexión tanto al padre como a *this.
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
            for(int i=0;i<asociada.size();++i){///>Se borrann las conexiones.
                asociada.at(i)->eraseConnection(this);
            }
            this->asociada.clear();///>Se limpia las listas
            ///>Se asignan los valores del cuadrado y de conexión tanto al padre como a *this.
            isConnected=true;
            parent->isValid=true;
            parent->isSecondClick=true;
            parent->ultimo=this;
            parent->isInput=isInput;
            this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
            parent->color=this->color;
        }
    }
    update();///>Se actualiza la línea.
}

void line::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    //No se realiza ninguna acci[on.
}

void line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();///Cada vez que se suelta el mouse se actualiza la imagen.
}

/*
  Esta función se encarga de manejar el evento de desplegar información acerca de la salida cuando se acerca el mouse encima, se despliega el nombre.
*/
bool line::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        QToolTip::showText(helpEvent->pos(), "this->nombre");

        return true;
    }
    return false;
}

/*
  Esta funcipon se encarga de devolver el nombre de la inout.
  */
QString line::getNombre(){
    return nombre;
}
