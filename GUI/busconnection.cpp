#include "busconnection.h"
#include "ui_busconnection.h"

busConnection::busConnection(QWidget *parent, line *last, Main* const Ventana) :
    QTabWidget(parent),
    ui(new Ui::busConnection)
{
    ui->setupUi(this);
    this->last=last;
    this->ventana=Ventana;
    if((ventana->ultimo->getCantidadBits()==1)||(last->getCantidadBits()==1)){
        this->removeTab(2);
        this->removeTab(1);
    }
    else{
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

    ui->verticalLayout_4->addWidget(new QSpinBox(0));
}
