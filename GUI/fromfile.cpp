#include "fromfile.h"
#include "ui_fromfile.h"
#include "parser.h"

FromFile::FromFile(QWidget *parent, Parser *pars) :
    QDialog(parent),
    ui(new Ui::FromFile),
    parser(pars)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(pars->ModulesIF.size());
    ui->tableWidget->setColumnCount(3);
    for(int i = 0; i < pars->ModulesIF.size(); ++i){
        QTableWidgetItem *Name = new QTableWidgetItem(pars->ModulesIF[i].Name);
        QTableWidgetItem *NumInputs = new QTableWidgetItem(QString::number(pars->ModulesIF[i].InputsTotal));
        QTableWidgetItem *NumOutputs = new QTableWidgetItem(QString::number(pars->ModulesIF[i].OutputsTotal));
        ui->tableWidget-> setItem(i,0,Name);
        ui->tableWidget-> setItem(i,1,NumInputs);
        ui->tableWidget->setItem(i,2,NumOutputs);
    }
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(QString("Name;Num Inputs;Num Outputs").split(";"));
}

FromFile::~FromFile()
{
    delete ui;
}

void FromFile::on_tableWidget_itemSelectionChanged()
{
    Location = ui->tableWidget->currentRow();
    ui->lineEdit->setText(parser->ModulesIF[Location].Name);
}
