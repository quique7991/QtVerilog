#include "hierarchidialog.h"
#include "ui_hierarchidialog.h"
#include<QDebug>
HierarchiDialog::HierarchiDialog(QWidget *parent, QHash<QString, int> *ModInDesign_arg) :
    QDialog(parent),
    ModInDesign(ModInDesign_arg),
    ui(new Ui::HierarchiDialog)
{
    ui->setupUi(this);
    QList<QString> Keys = ModInDesign->keys();
    int RowQuant = ModInDesign->keys().size();
    ui->tableWidget->setRowCount(RowQuant);
    ui->tableWidget->setColumnCount(1);
    for(int i = 0; i < Keys.size();++i){
        ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(Keys[i]));
    }
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
}

HierarchiDialog::~HierarchiDialog()
{
    delete ui;
}

void HierarchiDialog::on_tableWidget_itemSelectionChanged()
{
    Selection = ui->tableWidget->currentItem()->text();
}
