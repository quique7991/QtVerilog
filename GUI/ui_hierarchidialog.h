/********************************************************************************
** Form generated from reading UI file 'hierarchidialog.ui'
**
** Created: Wed Oct 2 22:19:40 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIERARCHIDIALOG_H
#define UI_HIERARCHIDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HierarchiDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *HierarchiDialog)
    {
        if (HierarchiDialog->objectName().isEmpty())
            HierarchiDialog->setObjectName(QString::fromUtf8("HierarchiDialog"));
        HierarchiDialog->resize(194, 162);
        verticalLayout = new QVBoxLayout(HierarchiDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(HierarchiDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        buttonBox = new QDialogButtonBox(HierarchiDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(HierarchiDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), HierarchiDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), HierarchiDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(HierarchiDialog);
    } // setupUi

    void retranslateUi(QDialog *HierarchiDialog)
    {
        HierarchiDialog->setWindowTitle(QApplication::translate("HierarchiDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HierarchiDialog: public Ui_HierarchiDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIERARCHIDIALOG_H
