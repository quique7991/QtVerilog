#include "addfromdb.h"
#include "ui_addfromdb.h"

AddFromDB::AddFromDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFromDB)
{
    ui->setupUi(this);
    QSqlQuery Query("Select * from Modules");
    int sizeQuer = Query.size();
    ui->tableWidget->setRowCount(sizeQuer);
    ui->tableWidget->setColumnCount(3);
    int RowCount = 0;
    while(Query.next()){
        ui->tableWidget->setItem(RowCount,0,new QTableWidgetItem(Query.value(1).toString()));
        ui->tableWidget->setItem(RowCount,1,new QTableWidgetItem(Query.value(2).toString()));
        ui->tableWidget->setItem(RowCount,2,new QTableWidgetItem(Query.value(3).toString()));
        RowCount++;
    }
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(QString("Name;Num Inputs;Num Outputs").split(";"));
}

AddFromDB::~AddFromDB()
{
    delete ui;
}
#include <iostream>
void AddFromDB::on_tableWidget_itemSelectionChanged()
{
    Location4 = ui->tableWidget->currentRow();
    ui->lineEdit->setText(ui->tableWidget->itemAt(Location4,0)->text());
}
