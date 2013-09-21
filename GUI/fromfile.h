#ifndef FROMFILE_H
#define FROMFILE_H

#include <QDialog>
#include "parser.h"
namespace Ui {
class FromFile;
}

class FromFile : public QDialog
{
    Q_OBJECT
    
public:
    explicit FromFile(QWidget *parent = 0, Parser *pars = 0);
    ~FromFile();
    int Location;
private slots:
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::FromFile *ui;
    Parser *parser;
};

#endif // FROMFILE_H
