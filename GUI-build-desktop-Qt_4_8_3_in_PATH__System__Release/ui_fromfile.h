/********************************************************************************
** Form generated from reading UI file 'fromfile.ui'
**
** Created: Tue Oct 1 10:01:31 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FROMFILE_H
#define UI_FROMFILE_H

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

class Ui_FromFile
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FromFile)
    {
        if (FromFile->objectName().isEmpty())
            FromFile->setObjectName(QString::fromUtf8("FromFile"));
        FromFile->resize(403, 301);
        verticalLayout = new QVBoxLayout(FromFile);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(FromFile);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FromFile);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(FromFile);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(FromFile);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FromFile);
        QObject::connect(buttonBox, SIGNAL(accepted()), FromFile, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FromFile, SLOT(reject()));

        QMetaObject::connectSlotsByName(FromFile);
    } // setupUi

    void retranslateUi(QDialog *FromFile)
    {
        FromFile->setWindowTitle(QApplication::translate("FromFile", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FromFile", "Module:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FromFile: public Ui_FromFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FROMFILE_H
