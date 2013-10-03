#ifndef HIERARCHIDIALOG_H
#define HIERARCHIDIALOG_H

#include <QDialog>

namespace Ui {
class HierarchiDialog;
}

class HierarchiDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit HierarchiDialog(QWidget *parent = 0, QHash<QString,int> *ModInDesign_arg = 0);
    ~HierarchiDialog();
    QHash<QString,int> *ModInDesign;
    QString Selection;
private slots:
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::HierarchiDialog *ui;
};

#endif // HIERARCHIDIALOG_H
