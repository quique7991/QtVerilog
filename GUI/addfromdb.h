#ifndef ADDFROMDB_H
#define ADDFROMDB_H

#include <QDialog>
#include<QtSql>
namespace Ui {
class AddFromDB;
}

class AddFromDB : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddFromDB(QWidget *parent = 0);
    ~AddFromDB();
    int Location4;
    
private slots:
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::AddFromDB *ui;
};

#endif // ADDFROMDB_H
