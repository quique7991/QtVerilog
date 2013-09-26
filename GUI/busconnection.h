#ifndef BUSCONNECTION_H
#define BUSCONNECTION_H

#include <QTabWidget>
#include <QList>
#include "line.h"
#include "canvas.h"

namespace Ui {
class busConnection;
}

class line;
class Main;

class busConnection : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit busConnection(QWidget *parent = 0, line* last=0, Main* const ventana=0);
    ~busConnection();
    
private slots:

    void on_pushButton_3_clicked();

private:
    Ui::busConnection *ui;
    line *last;
    Main* ventana;
};

#endif // BUSCONNECTION_H
