#include "core.h"
#include <QtGui>
#include <QPainter>
#include <QMenu>

Core::Core(int left,int top,  QString direccionImagen,QColor color,int cantidadEntradas,int cantidadSalidas,QGraphicsScene *canvas){
   minHeight = 150;
    if(cantidadEntradas>cantidadSalidas){
        minHeight = cantidadEntradas*10+8;
    }
    else{
        minHeight = cantidadSalidas*10+8;
    }
    if(minHeight<50){
        minHeight=50;
    }
    z = qrand()%256;
    minWidth=100;///Luego es necsario comparar la altura contra la imágen que va adentro.
    this->left=left;
    this->top=top;
    this->direccionImagen=direccionImagen;
    this->color = color;
    this->canvas=canvas;
    this->setFlag(QGraphicsItem::ItemIsMovable);
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
    painter->drawLine(QPointF(1,1),QPointF(2,2));
    painter->drawRect(QRectF(left,top,minWidth,minHeight));
}

void Core::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        QMenu* contextMenu = new QMenu ();
        Q_CHECK_PTR ( contextMenu );

        contextMenu->addAction ( "Analyse" , this , SLOT (downHierarchie()) );
        contextMenu->addAction ( "Erase" , this , SLOT (erase()) );
        contextMenu->popup( QCursor::pos() );
        contextMenu->exec ();
        delete contextMenu;
        contextMenu = 0;
    }
}

void Core::mouseMoveEvent(QMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event);
}

void Core::mouseReleaseEvent(QMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void Core::downHierarchie(){
    qDebug()<<"Down Hierarchie";
}

void Core::erase(){
    qDebug()<<"Erase";
}
