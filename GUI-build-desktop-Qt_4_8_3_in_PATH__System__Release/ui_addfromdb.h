/********************************************************************************
** Form generated from reading UI file 'addfromdb.ui'
**
** Created: Tue Oct 1 10:01:31 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFROMDB_H
#define UI_ADDFROMDB_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddFromDB
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddFromDB)
    {
        if (AddFromDB->objectName().isEmpty())
            AddFromDB->setObjectName(QString::fromUtf8("AddFromDB"));
        AddFromDB->resize(400, 300);
        verticalLayout = new QVBoxLayout(AddFromDB);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(AddFromDB);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AddFromDB);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(AddFromDB);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(AddFromDB);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AddFromDB);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddFromDB, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddFromDB, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddFromDB);
    } // setupUi

    void retranslateUi(QDialog *AddFromDB)
    {
        AddFromDB->setWindowTitle(QApplication::translate("AddFromDB", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddFromDB", "Module:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddFromDB: public Ui_AddFromDB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFROMDB_H
