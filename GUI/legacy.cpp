///Hugo aca voy a poner codigo legacy, en caso de que yo lo vuelva a necesitar. No sirve por ahora de nada en el código.

/*void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
*/
/*
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

*/
