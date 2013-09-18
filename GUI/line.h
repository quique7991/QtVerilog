#ifndef LINE_H
#define LINE_H

#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include "canvas.h"

class Main;

class line : public QGraphicsItem
{
public:
    line(Main* const parent,const QColor &color, int x1,int x2, int y,bool isInput,QGraphicsItem *padre, QGraphicsScene *canvas,QString nombre);///Constructor.
    QRectF boundingRect() const;//Rectangulo envolvente.
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);///Función de dibujo de la clase.
    int setConnected(bool con);///Asigna un estado de conectado..
    int eraseConnection(line *conexion);///Se borra la conexión.
    int addConnection(line *conexion);//Se agrega una conexipon.
    int setColor(QColor color);///Se asigna el color del cuadrado.
    QList<line*>& getAsociado();///Se obtienen todos los inouts conectados a este.
    QString getNombre();///Devuelve el nombre.
    bool getConnected();///Devuelve si algun nodo conectado.
    bool getVarConnected();///devuelve si la variable esta asociada un conectado.

protected:
    ///Eventos de mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool event(QEvent *event);

private:
    int x1,x2, y;//posicion
    bool isInput,isConnected;//isInput indica si es entrada (o salida), isConnected indica si la linea se encuentra en estado de conectado.
    ///padre es elemento que contienen a esta linea. (la imagen Core.)
    QGraphicsItem *padre;
    ///Es el largo de la linea.
    int width;
    ///Es el parent real que contiene a todas las figuras de la escena y al canvas en si.
    Main *parent;
    //El color del cuadrado que se dibuja cuando se encuentra conectado.
    QColor color;
    //Lista de nodos conectados a est.
    QList<line*> asociada;
    ///Nombre del in/out
    QString nombre;
    QList<QPointF> stuff;
    //Rectangulo de conexión
    QGraphicsRectItem *rectangle;
    //La linea en si.
    QLine *line1;
    //Canvas que contiene a los objetos
    QGraphicsScene *canvas;
};

#endif //LINE_H
