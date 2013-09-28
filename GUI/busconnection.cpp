#include "busconnection.h"
#include "ui_busconnection.h"

busConnection::busConnection(QWidget *parent, line *last, Main* const Ventana) :
    QTabWidget(parent),
    ui(new Ui::busConnection)
{
    ui->setupUi(this);
    this->last=last;
    this->oneOneCounter=0; //Es el siguiente valor adonde se van a almacenar los checkbox, y spinbox del one to one.
    this->ventana=Ventana;
    checkboxOneOne.append(ui->checkBox);
    QSpinBoxOneOneLeft.append(ui->spinBox_5);
    QSpinBoxOneOneRight.append(ui->spinBox_6);
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
        ui->label_2->setAlignment(Qt::AlignCenter);
        ui->label_2->setTextFormat(Qt::RichText);
        ui->label_2->setText("<b>"+ventana->ultimo->getNombre()+"</b>");
        ui->spinBox_5->setMaximum(ventana->ultimo->getCantidadBits()-1);
        ui->label_3->setAlignment(Qt::AlignCenter);
        ui->label_3->setTextFormat(Qt::RichText);
        ui->label_3->setText("<b>"+last->getNombre()+"</b>");
        ui->spinBox_6->setMaximum(last->getCantidadBits()-1);
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
}

void busConnection::on_conectarTodos_clicked()
{
    for(int i=0; i < last->getCantidadBits();++i){
        ventana->ultimo->setColor(last->getColor());
        ventana->ultimo->addConnection(last,i);
        last->addConnection(ventana->ultimo,i);
    }
    this->close();
}

void busConnection::on_pushButton_clicked()
{
    if(ventana->ultimo->getCantidadBits()==1){
        ventana->ultimo->setColor(last->getColor());
        ventana->ultimo->addConnection(last,ui->spinBox_7->value());
        last->addConnection(ventana->ultimo,0);
    }
    else{
        last->setColor(ventana->ultimo->getColor());
        ventana->ultimo->addConnection(last,0);
        last->addConnection(ventana->ultimo,ui->spinBox_7->value());
    }
    this->close();
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
        left->setMaximum(last->getCantidadBits()-1);
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
    if((!checkboxOneOne.at(index)->isChecked())&&(oneOneCounter<(last->getCantidadBits()-1))){
        QHBoxLayout *bla = new QHBoxLayout;
        ui->verticalLayout->addLayout(bla);
        QCheckBox *intento = new QCheckBox;
        intento->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        QSpinBox *left = new QSpinBox(0);
        left->setMaximum(last->getCantidadBits()-1);
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
        left->setMaximum(last->getCantidadBits()-1);
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
