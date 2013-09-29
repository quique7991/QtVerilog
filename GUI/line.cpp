#include "line.h"

#include <QtGui>

/*
    Constructor de line
*/
line::line(Main* const Parent, const QColor &color, int x1, int x2, int y, bool isInput, QGraphicsItem *padre, QGraphicsScene *canvas,QString nombre,int cantidadBits)
{
    //>Se asignan las variables a su correspondiente parámetro.
    this->x1 = x1;
    this->x2 = x2;
    this->y = y;
    this->paintTemp=false;
    this->color = color;
    this->isInput=isInput;
    this->isConnected=false;
    this->padre=padre;///Es un texto, que hace referencia al módulo.
    this->nombre=nombre;
    this->canvas=canvas;
    this->parent=Parent;
    this->cantidadBits = cantidadBits;
    this->width=10;
    this->isPainted=false;
    this->isConnected = new bool[cantidadBits];
    for(int i=0;i<cantidadBits;++i){
        isConnected[i]=false;
    }
    setZValue((x1 + y) % 2);
    setFlags(ItemIsSelectable);///Se asigna que el objeto puede ser seleccionado.
    setToolTip(nombre);
}
line::~line(){
    delete [] isConnected;
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

int line::eraseConnection(line *conexion, int key, int from){
    qDebug()<<"bla";
    connection prueba(conexion,from);
    if(asociada.contains(key,prueba)){
        asociada.remove(key,prueba);
    }
    if(!asociada.contains(key)){
        isConnected[key]=false;
    }
    /*int con = asociada.indexOf(conexion);///Se obtiene el indice en que se encuentra esta conexión.
    if(con != -1){///Si existe
        asociada.removeAt(con);///Se borra
    }
    if(asociada.isEmpty()){///Si esta vacia
        this->isConnected = false;///Se asigna como desconectada la variable
    }*/
    update();///Se actualiza (se redibuja la linea).
    return 0;
}

/*
    Esta función se encarga de agregar una nueva conexión a esta linea.
*/
int line::addConnection(line *conexion, int to,int from){
    connection prueba(conexion,from);
    QList<connection> container;
    if(isInput){///Si es una entrada solo puede existir una conexion.
        if(asociada.contains(to)){
            container = asociada.values(to);
            for(int i=0;i<container.size();++i){
                container.at(i).conexion->eraseConnection(this,container.at(i).bit,to);
            }
            asociada.replace(to,prueba);
        }
        else{
            asociada.insert(to,prueba);
        }
/*        if(asociada.isEmpty()){///Si la lista esta vacia solo se agrega.
            asociada.append(conexion);
        }
        else{///Si ya existe un valor este se sustituye.
            asociada.replace(0,conexion);
        }*/
    }
    else{///Si es una salida solo se agrega, dado que estas pueden estar asoociadas a varias entradas.
        asociada.insert(to,prueba);
    }
    isConnected[to]=true;///>Se asigna  que se dibuje el cuadrado.
    return 0;
}

bool line::getConnected(int key){///>Devuelve si el nodos se encuentra conectado a esta.
    return asociada.contains(key);
}

bool line::getTrulyConnected(){
    bool respuesta = false;
    for(int i=0;i<cantidadBits;++i){
        respuesta = respuesta|asociada.contains(i);
    }
    return respuesta;
}

QList<connection> line::getAsociado(int key){///>Función que devuelve la lista de lineas asociados a esta.
    return asociada.values(key);
}

int line::setConnected(bool con, int key){//>Se asigna para que se imprima el cuadrado
    (this->isConnected)[key]=con;
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
    isPainted=false;
    for(int i=0;i<cantidadBits;++i){
        isPainted = isPainted || isConnected[i];
    }
    if(isPainted){
        paintTemp = false;
    }
    if(isPainted){///Si se encuentra conectado se dibuja el cuadrado.
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
    if(paintTemp){
        if(isInput){
            painter->setPen(QPen(color, 1,Qt::DashLine));
            painter->drawRect(QRectF(x1-0.5*width,y-0.5*width,width,width));
        }
        else{
            painter->setPen(QPen(color,1,Qt::DashLine));
            painter->drawRect(QRectF(x2-width/2,y-width/2,width,width));
        }
    }
}


bool line::getVarConnected(){///>Devuelve si se esta dibujando el cuadrado o no.
    return this->isPainted;
}

bool line::getConnected(){
    isPainted=false;
    for(int i=0;i<cantidadBits;++i){
        isPainted = isPainted || isConnected[i];
    }
    return isPainted;
}
/*
  Esta función se encarga de manejar la conexión de lineas, y definir la maquina de estados que se encarga de manejar este evento.
  */
void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(parent->isSecondClick){///Segundo click
        if(parent->ultimo!=this){
            if(parent->isBus||(cantidadBits>1)){///Alguno fue un bus
                if(parent->isInput!=isInput){
                    ///Abrir ventana para hacer conexiones.
                    busConnection *conexion= new busConnection(0,this,parent);
                    this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                    conexion->show();
                }
                else{///Equivalente al primer click, pero hay que borrar los datos guardados.
                    if(cantidadBits>1){//Es un bus
                        if(!(parent->ultimo->getTrulyConnected())){

                            parent->ultimo->setPaintTemp(false);
                        }
                        parent->ultimo=this;
                        parent->isInput=isInput;
                        this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                        parent->color=this->color;
                        parent->isValid=true;
                        parent->isSecondClick=true;
                        parent->isBus=true;
                        parent->bitNumber=cantidadBits;
                        this->paintTemp =true;
                    }
                    else{//Es un cable normal
                        if(!(parent->ultimo->getTrulyConnected())){
                            if(parent->ultimo->getCantidadBits()>1){
                                parent->ultimo->setPaintTemp(false);
                            }
                            else{
                                parent->ultimo->setConnected(false,0);
                            }
                        }
                        parent->ultimo=0;
                        parent->isValid=false;
                        parent->isSecondClick=false;
                        if(event->modifiers()==Qt::ControlModifier){///Click especial
                            if(isConnected[0]&&(!isInput)){///Si ya se encuentra conetado, y es una salida.
                                ///>Se almacenan las variables en la escena padre.
                                parent->ultimo=this;
                                parent->isInput=this;
                                parent->color=this->color;
                                ///>Se asignan las variables que indican que el siguiente boton es el segundo click.
                                parent->isValid=true;
                                parent->isSecondClick=true;
                                parent->bitNumber=0;
                                parent->isBus=false;
                            }
                            else{///Equivalente a un click sencillo.
                                QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                                for(int i=0;i<borrar.size();++i){
                                    borrar.at(i).conexion->eraseConnection(this,borrar.at(i).bit,0);///Se borran las conexiones.
                                }
                                this->asociada.remove(0);///Se limpia la lista de conexiones.
                                ///>Se almacenan las variables para indicar que el siguiente click es el segundo click del botón.
                                isConnected[0]=true;
                                parent->isValid=true;
                                parent->isSecondClick=true;
                                //>Se asignan las variables a la escena padre.
                                parent->ultimo=this;
                                ///>Se generá el color del cuadrado.
                                this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                                parent->color=this->color;
                                parent->isInput=isInput;
                                parent->bitNumber=0;
                                parent->isBus=false;
                            }
                        }
                        else{///Click Sencillo
                            QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                            for(int i=0;i<borrar.size();++i){
                                borrar.at(i).conexion->eraseConnection(this,borrar.at(i).bit,0);///Se borran las conexiones.
                            }
                            this->asociada.remove(0);///Se limpia la lista de conexiones.
                            ///>Se almacenan las variables y se asignan los colores al presente.
                            isConnected[0]=true;
                            parent->isValid=true;
                            parent->isSecondClick=true;
                            parent->ultimo=this;
                            parent->isInput=isInput;
                            this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                            parent->color=this->color;
                            parent->isBus=false;
                            parent->bitNumber=0;
                        }
                    }
                }
            }
            else{///Ninguno fue un bus, entonces es una conexion de 1 bit a 1 bit.
                if(parent->ultimo!=this){//Se verifica que el segundo botón no sea el primero.
                    if(parent->isInput!=isInput){///Se verifica si el anterior es del tipo distinto, solo se puede conectar input->output, output->input.
                        if(event->modifiers()==Qt::ControlModifier){///Click especial
                            if(isConnected[0]){///Esta conectado
                                if(isInput){//Si es entrada
                                    QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                                    for(int i=0;i<borrar.size();++i){
                                        borrar.at(i).conexion->eraseConnection(this,borrar.at(i).bit,0);///Se borran las conexiones.
                                    }
                                    this->asociada.remove(0);///Se limpia la lista de conexiones.
                                    ///>Se conectan los dos nodos (this y el que ya se encontraba almacenado en el parent.
                                    this->color=parent->color;
                                    this->addConnection(parent->ultimo,0,0);
                                    parent->ultimo->addConnection(this,0,0);
                                }
                                else{///>Si es una salida, pueden haber muchos inputs a una misma salida.
                                ///>Si lo se agrega a la lista del input almacenado en el parent
                                    parent->ultimo->setColor(this->color);
                                    parent->ultimo->addConnection(this,0,0);
                                    this->addConnection(parent->ultimo,0,0);
                                }
                            }
                            else{///Esta desconectado.
                                ///Se conectan a ambos nodos indiferente de cualquier otra característica.
                                this->color=parent->color;
                                this->addConnection(parent->ultimo,0,0);
                                parent->ultimo->addConnection(this,0,0);
                            }
                        }
                        else{///Click sencillo.
                            QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                            if(isConnected[0]){///>Si se encuentra conectado.                    QList<*line> borrar = asociada.value(0);///Se obtienen todas las lineas asociadas.
                                for(int i=0;i<borrar.size();++i){
                                    borrar.at(i).conexion->eraseConnection(this,0,borrar.at(i).bit);///Se borran las conexiones.
                                }
                                this->asociada.remove(0);///Se limpia la lista de conexiones.
                            }
                            ///Se conecta este nodo con el nodo anterior.
                            this->color=parent->color;
                            this->addConnection(parent->ultimo,0,0);
                            parent->ultimo->addConnection(this,0,0);
                        }
                        parent->ultimo->update();///Se actualiza el nodo al que se conecto.
                        ///>Se limpian las variables en la escena padre.
                        parent->ultimo=0;
                        parent->isValid=false;
                        parent->isSecondClick=false;
                    }
                    else{///Si son iguales en tipo (input,output), se va a un paso equivalente a quere fuera un primer click
                        if(!(parent->ultimo->getTrulyConnected())){
                            parent->ultimo->setConnected(false,0);
                        }
                        parent->ultimo=0;
                        parent->isValid=false;
                        parent->isSecondClick=false;
                        if(event->modifiers()==Qt::ControlModifier){///Click especial
                            if(isConnected[0]&&(!isInput)){///Si ya se encuentra conetado, y es una salida.
                                ///>Se almacenan las variables en la escena padre.
                                parent->ultimo=this;
                                parent->isInput=this;
                                parent->color=this->color;
                                ///>Se asignan las variables que indican que el siguiente boton es el segundo click.
                                parent->isValid=true;
                                parent->isSecondClick=true;
                                parent->bitNumber=0;
                                parent->isBus=false;
                            }
                            else{///Equivalente a un click sencillo.
                                QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                                for(int i=0;i<borrar.size();++i){
                                    borrar.at(i).conexion->eraseConnection(this,0,borrar.at(i).bit);///Se borran las conexiones.
                                }
                                this->asociada.remove(0);///Se limpia la lista de conexiones.
                                ///>Se almacenan las variables para indicar que el siguiente click es el segundo click del botón.
                                isConnected[0]=true;
                                parent->isValid=true;
                                parent->isSecondClick=true;
                                //>Se asignan las variables a la escena padre.
                                parent->ultimo=this;
                                ///>Se generá el color del cuadrado.
                                this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                                parent->color=this->color;
                                parent->isInput=isInput;
                                parent->bitNumber=0;
                                parent->isBus=false;
                            }
                        }
                        else{///Click Sencillo
                            QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                            for(int i=0;i<borrar.size();++i){
                                 borrar.at(i).conexion->eraseConnection(this,0,borrar.at(i).bit);///Se borran las conexiones.
                            }
                            this->asociada.remove(0);///Se limpia la lista de conexiones.
                            ///>Se almacenan las variables y se asignan los colores al presente.
                            isConnected[0]=true;
                            parent->isValid=true;
                            parent->isSecondClick=true;
                            parent->ultimo=this;
                            parent->isInput=isInput;
                            this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                            parent->color=this->color;
                            parent->isBus=false;
                            parent->bitNumber=0;
                        }
                    }
                }
            }
        }
    }
    else{////Primer Click
        if(cantidadBits>1){//Es un bus
            parent->ultimo=this;
            parent->isInput=isInput;
            this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
            parent->color=this->color;
            parent->isValid=true;
            parent->isSecondClick=true;
            parent->isBus=true;
            parent->bitNumber=cantidadBits;
            this->paintTemp =true;
        }
        else{///Es un bit, no un bus
            if(event->modifiers()==Qt::ControlModifier){///Click especial
                if(isConnected[0]&&(!isInput)){///Si ya se encuentra conetado, y es una salida.
                    ///>Solo se alamacenan los valores al parent.
                    parent->ultimo=this;
                    parent->isInput=isInput;
                    parent->color=this->color;
                    parent->isValid=true;
                    parent->isSecondClick=true;
                    parent->isBus=false;
                    parent->bitNumber=0;
                }
                else{///Equivalente a un click sencillo.
                    QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                    for(int i=0;i<borrar.size();++i){
                        borrar.at(i).conexion->eraseConnection(this,0,borrar.at(i).bit);///Se borran las conexiones.
                    }
                    this->asociada.remove(0);///Se limpia la lista de conexiones.
                    ///>Se asignan los valores del cuadrado y de conexión tanto al padre como a *this.
                    isConnected[0]=true;
                    parent->isValid=true;
                    parent->isSecondClick=true;
                    parent->ultimo=this;
                    parent->bitNumber=0;
                    parent->isBus=0;
                    parent->isInput=isInput;
                    this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                    parent->color=this->color;
                }
            }
            else{///Click Sencillo
                QList<connection> borrar = asociada.values(0);///Se obtienen todas las lineas asociadas.
                for(int i=0;i<borrar.size();++i){
                    borrar.at(i).conexion->eraseConnection(this,borrar.at(i).bit,0);///Se borran las conexiones.
                }
                this->asociada.remove(0);///Se limpia la lista de conexiones.
                ///>Se asignan los valores del cuadrado y de conexión tanto al padre como a *this.
                isConnected[0]=true;
                parent->isValid=true;
                parent->isSecondClick=true;
                parent->ultimo=this;
                parent->isInput=isInput;
                this->color=QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8);
                parent->color=this->color;
                parent->isBus=false;
                parent->bitNumber=0;
            }
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
