#include "busconnection.h"
#include "ui_busconnection.h"

busConnection::busConnection(QWidget *parent, line *last, Main* const Ventana) :
    QTabWidget(parent),
    ui(new Ui::busConnection)
{
    ui->setupUi(this);
    this->last=last;
    this->oneOneCounter=1; //Es el siguiente valor adonde se van a almacenar los checkbox, y spinbox del one to one.
    this->ventana=Ventana;
    this->blockCounter=1;
    checkboxOneOne.append(ui->checkBox);
    QSpinBoxOneOneLeft.append(ui->spinBox_5);
    QSpinBoxOneOneRight.append(ui->spinBox_6);
    checkBoxBlock.append(ui->checkBox_2);
    QSpinBoxBlockInLeft.append(ui->spinBox);
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
    QSpinBoxBlockInRight.append(ui->spinBox_2);
    connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
    QSpinBoxBlockOutLeft.append(ui->spinBox_3);
    connect(ui->spinBox_3,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
    QSpinBoxBlockOutRight.append(ui->spinBox_4);
    connect(ui->spinBox_4,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
    if((ventana->ultimo->getCantidadBits()==1)||(last->getCantidadBits()==1)){
        this->removeTab(2);
        this->removeTab(1);
        if(ventana->ultimo->getCantidadBits()==1){
            ui->label_8->setAlignment(Qt::AlignCenter);
            ui->label_8->setTextFormat(Qt::RichText);
            ui->label_8->setText("<b>"+ventana->ultimo->getNombre()+"</b>");
            ui->label_4->setAlignment(Qt::AlignCenter);
            ui->label_4->setTextFormat(Qt::RichText);
            ui->label_4->setText("<b>"+last->getNombre()+"</b>");
            ui->spinBox_7->setMaximum(last->getCantidadBits()-1);
        }
        else{
            ui->label_8->setAlignment(Qt::AlignCenter);
            ui->label_8->setTextFormat(Qt::RichText);
            ui->label_8->setText("<b>"+last->getNombre()+"<\b>");
            ui->label_4->setAlignment(Qt::AlignCenter);
            ui->label_4->setTextFormat(Qt::RichText);
            ui->label_4->setText("<b>"+ventana->ultimo->getNombre()+"</b>");
            ui->spinBox_7->setMaximum(ventana->ultimo->getCantidadBits()-1);
        }
    }
    else{
        ui->label_5->setAlignment(Qt::AlignCenter);
        ui->label_2->setAlignment(Qt::AlignCenter);
        ui->label_5->setTextFormat(Qt::RichText);
        ui->label_2->setTextFormat(Qt::RichText);
        ui->label_5->setText("<b>"+ventana->ultimo->getNombre()+"</b>");
        ui->label_2->setText("<b>"+ventana->ultimo->getNombre()+"</b>");
        ui->spinBox_5->setMaximum(ventana->ultimo->getCantidadBits()-1);
        ui->spinBox->setMaximum(ventana->ultimo->getCantidadBits()-1);
        ui->spinBox_2->setMaximum(ventana->ultimo->getCantidadBits()-1);
        ui->label_3->setAlignment(Qt::AlignCenter);
        ui->label_3->setTextFormat(Qt::RichText);
        ui->label_6->setAlignment(Qt::AlignCenter);
        ui->label_6->setTextFormat(Qt::RichText);
        ui->label_3->setText("<b>"+last->getNombre()+"</b>");
        ui->label_6->setText("<b>"+last->getNombre()+"</b>");
        ui->spinBox_6->setMaximum(last->getCantidadBits()-1);
        ui->spinBox_3->setMaximum(last->getCantidadBits()-1);
        ui->spinBox_4->setMaximum(last->getCantidadBits()-1);
        this->removeTab(3);
    }
    if(ventana->ultimo->getCantidadBits()!=last->getCantidadBits()){
        this->removeTab(0);
    }
}

busConnection::~busConnection()
{
    delete ui;
}

void busConnection::on_pushButton_3_clicked()
{
    bool boolean = true;
    bool *in= new bool[ventana->ultimo->getCantidadBits()];
    for(int i=0; i<ventana->ultimo->getCantidadBits();++i){
        in[i]=false;
    }
    bool *out= new bool[last->getCantidadBits()];
    for(int i=0; i<last->getCantidadBits();++i){
        out[i]=false;
    }

    for(int i=0;i < blockCounter;++i){
        int izquierdaIn = QSpinBoxBlockInLeft.at(i)->value();
        int derechaIn = QSpinBoxBlockInRight.at(i)->value();
        int izquierdaOut = QSpinBoxBlockOutLeft.at(i)->value();
        int derechaOut = QSpinBoxBlockOutRight.at(i)->value();
        if(checkBoxBlock.at(i)->isChecked()){
            if((QSpinBoxBlockInLeft.at(i)->value() <= QSpinBoxBlockInRight.at(i)->value())&&(QSpinBoxBlockOutLeft.at(i)->value()<=QSpinBoxBlockOutRight.at(i)->value())){
                for(int j=QSpinBoxBlockInLeft.at(i)->value();j<=QSpinBoxBlockInRight.at(i)->value();++j){
                    if(in[j]){
                    ///Se abre una ventana de warning en caso de que un bit se repita
                        QMessageBox msgBox;
                        msgBox.setIcon(QMessageBox::Warning);
                        msgBox.setText("El bit "+QString::number(j)+" de la columna de la izquierda se repite en varias lineas");
                        msgBox.setInformativeText("Esta seguro que quiere continuar?");
                        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                        msgBox.setDefaultButton(QMessageBox::Yes);
                        int ret = msgBox.exec();
                        switch (ret) {
                            case QMessageBox::Yes:
                                msgBox.close();
                                break;
                            case QMessageBox::No:
                                //Es necesario borrar la conexi[on inicada con anterioridad.
                                boolean=false;
                                msgBox.close();
                                break;
                            default:
                                ///Es necesario borrar la conexión iniciada con anterioridad.
                                this->close();
                                break;
                        }

                    }
                    else{
                        in[j]=true;
                    }
                }
                for(int j=QSpinBoxBlockOutLeft.at(i)->value();j<=QSpinBoxBlockOutRight.at(i)->value();++j){///Se hacen warning en caso de que un bit salga conectado varias veces.
                    if(out[j]){
                        //Se abre una ventana de warning
                        QMessageBox msgBox;
                        msgBox.setIcon(QMessageBox::Warning);
                        msgBox.setText("El bit "+QString::number(j)+" de la columna de la derecha se repite en varias lineas");
                        msgBox.setInformativeText("Esta seguro que quiere continuar?");
                        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                        msgBox.setDefaultButton(QMessageBox::Yes);
                        int ret = msgBox.exec();
                        switch (ret) {
                            case QMessageBox::Yes:
                                msgBox.close();
                                break;
                            case QMessageBox::No:
                                //Es necesario borrar la conexi[on inicada con anterioridad.
                                msgBox.close();
                                boolean=false;
                                break;
                            default:
                                ///Es necesario borrar la conexión iniciada con anterioridad.
                                this->close();
                                break;
                        }
                    }
                    else{
                        out[j]=true;
                    }
                }
            }
            else{///Se abre un error cuando la cantidad de bits de una columna no coordinan con la otra.
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText("Los rangos en la linea "+QString::number(i)+" tienen un error.");
                msgBox.exec();
                boolean = false;
            }
        }
        if((derechaIn-izquierdaIn)!=(derechaOut-izquierdaOut)){
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("La cantidad de bits en la columna de la izquierda en la fila "+QString::number(i)+" no concuerda con la columna de la derecha.");
            msgBox.exec();
            boolean = false;
        }
    }
    if(boolean){
        for(int i=0;i < blockCounter;++i){
            int izquierdaIn = QSpinBoxBlockInLeft.at(i)->value();
            int derechaIn = QSpinBoxBlockInRight.at(i)->value();
            int izquierdaOut = QSpinBoxBlockOutLeft.at(i)->value();
            if(checkBoxBlock.at(i)->isChecked()){
                if(ventana->ultimo->getIsInput()){
                    ventana->ultimo->setColor(last->getColor());
                }
                else{
                    last->setColor(ventana->ultimo->getColor());
                }
                int diff=derechaIn-izquierdaIn;
                for(int i=0;i<=diff;++i){
                    ventana->ultimo->addConnection(last,izquierdaIn+i,izquierdaOut+i);
                    last->addConnection(ventana->ultimo,izquierdaOut+i,izquierdaIn+i);
                }
            }
        }
    }
    if(boolean){
    this->close();
    ventana->ultimo=0;
    ventana->isSecondClick=false;
    ventana->isValid=false;
    }
}

void busConnection::on_conectarTodos_clicked()
{
    for(int i=0; i < last->getCantidadBits();++i){
        ventana->ultimo->setColor(last->getColor());
        ventana->ultimo->addConnection(last,i,i);
        last->addConnection(ventana->ultimo,i,i);
    }
    this->close();
    ventana->ultimo=0;
    ventana->isSecondClick=false;
    ventana->isValid=false;
}

void busConnection::on_pushButton_clicked()
{
    if(ventana->ultimo->getCantidadBits()==1){
        ventana->ultimo->setColor(last->getColor());
        ventana->ultimo->addConnection(last,0,ui->spinBox_7->value());
        last->addConnection(ventana->ultimo,ui->spinBox_7->value(),0);
    }
    else{
        last->setColor(ventana->ultimo->getColor());
        ventana->ultimo->addConnection(last,ui->spinBox_7->value(),0);
        last->addConnection(ventana->ultimo,0,ui->spinBox_7->value());
    }
    this->close();
    ventana->ultimo=0;
    ventana->isSecondClick=false;
    ventana->isValid=false;
}

void busConnection::on_spinBox_5_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(!(ui->checkBox->isChecked())){
        QHBoxLayout *bla = new QHBoxLayout;
        ui->verticalLayout->addLayout(bla);
        QCheckBox *intento = new QCheckBox;
        intento->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        QSpinBox *left = new QSpinBox(0);
        left->setMaximum(ventana->ultimo->getCantidadBits()-1);
        QSpinBox *right = new QSpinBox(0);
        right->setMaximum(last->getCantidadBits()-1);
        checkboxOneOne.append(intento);
        QSpinBoxOneOneLeft.append(left);
        QSpinBoxOneOneRight.append(right);
        connect(left,SIGNAL(valueChanged(int)),this,SLOT(newOneOneLine(int)));
        connect(right,SIGNAL(valueChanged(int)),this,SLOT(newOneOneLine(int)));
        ++oneOneCounter;
        bla->addWidget(intento);
        bla->addWidget(left);
        bla->addWidget(right);
    }
    ui->checkBox->setChecked(true);
}

void busConnection::newOneOneLine(int bla){
    Q_UNUSED(bla);
    int index;
    if(QSpinBoxOneOneLeft.contains((QSpinBox*) this->sender())){
        index = QSpinBoxOneOneLeft.indexOf((QSpinBox*) this->sender());
    }
    else{
        index = QSpinBoxOneOneRight.indexOf((QSpinBox*) this->sender());
    }
    int min = (last->getCantidadBits() > ventana->ultimo->getCantidadBits())?(ventana->ultimo->getCantidadBits()):(last->getCantidadBits());
    if((!checkboxOneOne.at(index)->isChecked())&&(oneOneCounter<min)){
        QHBoxLayout *bla = new QHBoxLayout;
        ui->verticalLayout->addLayout(bla);
        QCheckBox *intento = new QCheckBox;
        intento->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        QSpinBox *left = new QSpinBox(0);
        left->setMaximum(ventana->ultimo->getCantidadBits()-1);
        QSpinBox *right = new QSpinBox(0);
        right->setMaximum(last->getCantidadBits()-1);
        checkboxOneOne.append(intento);
        QSpinBoxOneOneLeft.append(left);
        QSpinBoxOneOneRight.append(right);
        connect(left,SIGNAL(valueChanged(int)),this,SLOT(newOneOneLine(int)));
        connect(right,SIGNAL(valueChanged(int)),this,SLOT(newOneOneLine(int)));
        ++oneOneCounter;
        bla->addWidget(intento);
        bla->addWidget(left);
        bla->addWidget(right);
    }
    checkboxOneOne.at(index)->setChecked(true);
}

void busConnection::on_spinBox_6_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(!(ui->checkBox->isChecked())){
        QHBoxLayout *bla = new QHBoxLayout;
        ui->verticalLayout->addLayout(bla);
        QCheckBox *intento = new QCheckBox;
        intento->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        QSpinBox *left = new QSpinBox(0);
        left->setMaximum(ventana->ultimo->getCantidadBits()-1);
        QSpinBox *right = new QSpinBox(0);
        right->setMaximum(last->getCantidadBits()-1);
        checkboxOneOne.append(intento);
        QSpinBoxOneOneLeft.append(left);
        QSpinBoxOneOneRight.append(right);
        connect(left,SIGNAL(valueChanged(int)),this,SLOT(newOneOneLine(int)));
        connect(right,SIGNAL(valueChanged(int)),this,SLOT(newOneOneLine(int)));
        ++oneOneCounter;
        bla->addWidget(intento);
        bla->addWidget(left);
        bla->addWidget(right);
    }
    ui->checkBox->setChecked(true);
}

void busConnection::on_pushButton_2_clicked()
{
    ///left es ventana->ultimo;
    ///right es last;
    for(int i=0;i<oneOneCounter;++i){
        if(checkboxOneOne.at(i)->isChecked()){
            if(ventana->ultimo->getIsInput()){
                ventana->ultimo->setColor(last->getColor());
            }
            else{
                last->setColor(ventana->ultimo->getColor());
            }
            last->addConnection(ventana->ultimo,QSpinBoxOneOneRight.at(i)->value(),QSpinBoxOneOneLeft.at(i)->value());
            ventana->ultimo->addConnection(last,QSpinBoxOneOneLeft.at(i)->value(),QSpinBoxOneOneRight.at(i)->value());
        }
    }
    this->close();
    ventana->ultimo=0;
    ventana->isSecondClick=false;
    ventana->isValid=false;
}

void busConnection::newBlockLine(int k){
    Q_UNUSED(k);
    int index;
    if(QSpinBoxBlockInLeft.contains((QSpinBox*) this->sender())){
        index = QSpinBoxBlockInLeft.indexOf((QSpinBox*) this->sender());
    }
    else if(QSpinBoxBlockInRight.contains((QSpinBox*) this->sender())){
        index = QSpinBoxBlockInRight.indexOf((QSpinBox*) this->sender());
    }
    else if(QSpinBoxBlockOutRight.contains((QSpinBox*) this->sender())){
        index = QSpinBoxBlockOutRight.indexOf((QSpinBox*) this->sender());
    }
    else{
        index = QSpinBoxBlockOutLeft.indexOf((QSpinBox*) this->sender());
    }
    if((!checkBoxBlock.at(index)->isChecked())&&(blockCounter<(last->getCantidadBits()))){
        QHBoxLayout *bla = new QHBoxLayout;
        ui->verticalLayout_4->addLayout(bla);
        QCheckBox *intento = new QCheckBox;
        intento->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        QSpinBox *leftIn = new QSpinBox(0);
        leftIn->setMaximum(last->getCantidadBits()-1);
        QSpinBox *rightIn = new QSpinBox(0);
        rightIn->setMaximum(last->getCantidadBits()-1);
        QSpinBox *leftOut = new QSpinBox(0);
        leftOut->setMaximum(ventana->ultimo->getCantidadBits()-1);
        QSpinBox *rightOut = new QSpinBox(0);
        rightOut->setMaximum(ventana->ultimo->getCantidadBits()-1);
        checkBoxBlock.append(intento);
        QSpinBoxBlockInLeft.append(leftIn);
        QSpinBoxBlockInRight.append(rightIn);
        QSpinBoxBlockOutLeft.append(leftOut);
        QSpinBoxBlockOutRight.append(rightOut);
        connect(leftIn,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
        connect(rightIn,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
        connect(leftOut,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
        connect(rightOut,SIGNAL(valueChanged(int)),this,SLOT(newBlockLine(int)));
        ++blockCounter;
        bla->addWidget(intento);
        bla->addWidget(leftIn);
        bla->addWidget(rightIn);
        bla->addWidget(leftOut);
        bla->addWidget(rightOut);
    }
    checkBoxBlock.at(index)->setChecked(true);
}

void busConnection::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);
    if(!(ventana->ultimo->getTrulyConnected())){
        if(ventana->ultimo->getCantidadBits()>1){
            ventana->ultimo->setPaintTemp(false);
        }else{
            ventana->ultimo->setConnected(false,0);
        }
    }
    else{
        if(ventana->ultimo->getCantidadBits()>1){
            ventana->ultimo->setPaintTemp(false);
        }
    }
}
