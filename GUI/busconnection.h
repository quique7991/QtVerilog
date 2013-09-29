#ifndef BUSCONNECTION_H
#define BUSCONNECTION_H

#include <QTabWidget>
#include <QList>
#include <QCheckBox>
#include <QSpinBox>
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

public slots:
    void newOneOneLine(int);
    void newBlockLine(int);
    
private slots:

    void on_pushButton_3_clicked();

    void on_conectarTodos_clicked();

    void on_pushButton_clicked();

    void on_spinBox_5_valueChanged(int arg1);

    void on_spinBox_6_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    void closeEvent(QCloseEvent *);
    Ui::busConnection *ui;
    line *last;
    Main* ventana;
    int oneOneCounter;
    QList<QCheckBox*> checkboxOneOne;
    QList<QSpinBox*> QSpinBoxOneOneLeft;
    QList<QSpinBox*> QSpinBoxOneOneRight;
    int blockCounter;
    QList<QCheckBox*> checkBoxBlock;
    QList<QSpinBox*> QSpinBoxBlockInLeft;
    QList<QSpinBox*> QSpinBoxBlockInRight;
    QList<QSpinBox*> QSpinBoxBlockOutLeft;
    QList<QSpinBox*> QSpinBoxBlockOutRight;
};

#endif // BUSCONNECTION_H

