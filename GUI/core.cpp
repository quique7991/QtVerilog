#include "core.h"
#include <QtGui>
#include <QPainter>
#include <QMenu>

Core::Core(int index, int left,int top,  QString direccionImagen,QColor color,int cantidadEntradas,int cantidadSalidas,Main *parent,bool force,int width,int height){
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
    if(force){
        minHeight=height;
        minWidth=width;
    }
    z = qrand()%256;
    minWidth=100;///Luego es necsario comparar la altura contra la imágen que va adentro.
    this->left=left;
    this->top=top;
    this->direccionImagen=direccionImagen;
    this->color = color;
    this->parent=parent;
    this->index=index;
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

int Core::getIndex(){
    return this->index;
}

QRectF Core::boundingRect() const{
    return QRectF(left,top,minWidth,minHeight);
}

QPainterPath Core::shape() const{
    QPainterPath path;
    path.addRect(left,top,minWidth,minHeight);
    return path;
}

void Core::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);
    Q_UNUSED(item);
    //painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush( QColor(z,z,z) );
    painter->setPen( QPen(color) );
    //painter->drawLine(QPointF(1,1),QPointF(2,2));
    //painter->drawRect(QRectF(left,top,minWidth,minHeight));
    QPixmap *pix = new QPixmap(direccionImagen);
    painter->drawPixmap(left,top,minWidth,minHeight,*pix);
}

void Core::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    if(event->button()==Qt::RightButton){
       QMenu* contextMenu = new QMenu ();
        Q_CHECK_PTR ( contextMenu );
        parent->setActualItem(this);
        contextMenu->addAction ( "Analyse" , parent , SLOT (downHierarchie() ));
        contextMenu->addAction ( "Erase" , parent , SLOT (erase() ));
        contextMenu->popup( QCursor::pos() );
        contextMenu->exec ();
        delete contextMenu;
        contextMenu = 0;
    }
}

void Core::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event);
}

void Core::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
