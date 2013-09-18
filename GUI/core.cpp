#include "core.h"
#include <QtGui>
#include <QPainter>
#include <QMenu>

/*
    Constructor
*/
Core::Core(int index, int left,int top,  QString direccionImagen,QColor color,int cantidadEntradas,int cantidadSalidas,Main *parent,bool force,int width,int height){
    ///Se define los tamaños del anocho y el largo, a partir de la cantidad de netradas y salidas.
    minHeight = 150;
    if(cantidadEntradas>cantidadSalidas){
        minHeight = cantidadEntradas*10+8;
    }
    else{
        minHeight = cantidadSalidas*10+8;
    }
    if(minHeight<100){
        minHeight=100;
    }
    minWidth=100;///Luego es necsario comparar la altura contra la imágen que va adentro.
    if(force){///Si se envia force se asignan directamente estas variables
        minHeight=height;
        minWidth=width;
    }
    z = qrand()%256;
    ///Se asignan los valores a los parámetros
    this->left=left;
    this->top=top;
    this->direccionImagen=direccionImagen;
    this->color = color;
    this->parent=parent;
    this->index=index;
    ///Se asigna la variable que permite mover al objeto.
    this->setFlag(QGraphicsItem::ItemIsMovable);
}



/*
  Función que devuelve el índice del objeto.
*/
int Core::getIndex(){
    return this->index;
}


/*
  Funciones de forma del objeto.
*/
QRectF Core::boundingRect() const{
    return QRectF(left,top,minWidth,minHeight);
}

QPainterPath Core::shape() const{
    QPainterPath path;
    path.addRect(left,top,minWidth,minHeight);
    return path;
}

/*
  Función que se encarga de dibujar la imagen.
*/
void Core::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    //Se indica que los inputs no son utilizados.
    Q_UNUSED(widget);
    Q_UNUSED(item);
    //painter->setRenderHint(QPainter::Antialiasing);
    ///Se asigna el color del Brusy y el pen.
    painter->setBrush( QColor(z,z,z) );
    painter->setPen( QPen(color) );
    ///En caso de que se quiera sustituir la imagen por un rectangulo
    //painter->drawLine(QPointF(1,1),QPointF(2,2));
    //painter->drawRect(QRectF(left,top,minWidth,minHeight));
    ///Se indica la figura que se va a dibujar y se imprime en la ventana
    QPixmap *pix = new QPixmap(direccionImagen);
    painter->drawPixmap(left,top,minWidth,minHeight,*pix);
}

/*
    Función que permite hacer click derecho sobre la imagen para borrarla o hacer un análisis jerárquico.
*/
void Core::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    if(event->button()==Qt::RightButton){///Se verifica si es un click derecho.
       QMenu* contextMenu = new QMenu ();///Se crea un menu de contexto.
        Q_CHECK_PTR ( contextMenu );
        parent->setActualItem(this);///Se el puntero a este objeto en el objeto padre en caso de que se quiera borrar..
        contextMenu->addAction ( "Analyse" , parent , SLOT (downHierarchie() ));//Se agrega la opción de analizar la jerarquía.
        contextMenu->addAction ( "Erase" , parent , SLOT (erase() ));///Se borra el objeto.
        contextMenu->popup( QCursor::pos() );
        contextMenu->exec ();
        delete contextMenu;
        contextMenu = 0;
    }
}

///Funciones no utilizadas que manejan los eventos del mouse

void Core::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event);
}

void Core::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
