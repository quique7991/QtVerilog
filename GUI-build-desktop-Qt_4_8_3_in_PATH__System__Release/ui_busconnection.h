/********************************************************************************
** Form generated from reading UI file 'busconnection.ui'
**
** Created: Tue Oct 1 10:01:31 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUSCONNECTION_H
#define UI_BUSCONNECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_busConnection
{
public:
    QWidget *allToAll;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *conectarTodos;
    QSpacerItem *horizontalSpacer;
    QWidget *porBloques;
    QVBoxLayout *verticalLayout_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_8;
    QWidget *oneByOne;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_6;
    QWidget *bitToBus;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_4;
    QSpinBox *spinBox_7;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QTabWidget *busConnection)
    {
        if (busConnection->objectName().isEmpty())
            busConnection->setObjectName(QString::fromUtf8("busConnection"));
        busConnection->resize(402, 319);
        allToAll = new QWidget();
        allToAll->setObjectName(QString::fromUtf8("allToAll"));
        verticalLayout_5 = new QVBoxLayout(allToAll);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(allToAll);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout_5->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        conectarTodos = new QPushButton(allToAll);
        conectarTodos->setObjectName(QString::fromUtf8("conectarTodos"));

        horizontalLayout->addWidget(conectarTodos);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout);

        busConnection->addTab(allToAll, QString());
        porBloques = new QWidget();
        porBloques->setObjectName(QString::fromUtf8("porBloques"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(porBloques->sizePolicy().hasHeightForWidth());
        porBloques->setSizePolicy(sizePolicy);
        porBloques->setAutoFillBackground(true);
        verticalLayout_8 = new QVBoxLayout(porBloques);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        scrollArea = new QScrollArea(porBloques);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 378, 266));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_9 = new QSpacerItem(20, 2, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setWordWrap(true);

        horizontalLayout_4->addWidget(label_5);

        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setWordWrap(true);

        horizontalLayout_4->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);

        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(label_10);

        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(label_11);

        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(label_12);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(label_9);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox_2 = new QCheckBox(scrollAreaWidgetContents);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(checkBox_2);

        spinBox = new QSpinBox(scrollAreaWidgetContents);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_6->addWidget(spinBox);

        spinBox_2 = new QSpinBox(scrollAreaWidgetContents);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        horizontalLayout_6->addWidget(spinBox_2);

        spinBox_3 = new QSpinBox(scrollAreaWidgetContents);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        horizontalLayout_6->addWidget(spinBox_3);

        spinBox_4 = new QSpinBox(scrollAreaWidgetContents);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

        horizontalLayout_6->addWidget(spinBox_4);


        verticalLayout_4->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);

        pushButton_3 = new QPushButton(scrollAreaWidgetContents);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_12->addWidget(pushButton_3);

        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_12);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_10->addLayout(horizontalLayout_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_8->addWidget(scrollArea);

        busConnection->addTab(porBloques, QString());
        oneByOne = new QWidget();
        oneByOne->setObjectName(QString::fromUtf8("oneByOne"));
        verticalLayout_7 = new QVBoxLayout(oneByOne);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(oneByOne);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(oneByOne);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox = new QCheckBox(oneByOne);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        sizePolicy2.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(checkBox);

        spinBox_5 = new QSpinBox(oneByOne);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));

        horizontalLayout_3->addWidget(spinBox_5);

        spinBox_6 = new QSpinBox(oneByOne);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));

        horizontalLayout_3->addWidget(spinBox_6);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_7->addLayout(verticalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);

        pushButton_2 = new QPushButton(oneByOne);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_10->addWidget(pushButton_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);


        verticalLayout_7->addLayout(horizontalLayout_10);

        busConnection->addTab(oneByOne, QString());
        bitToBus = new QWidget();
        bitToBus->setObjectName(QString::fromUtf8("bitToBus"));
        verticalLayout_6 = new QVBoxLayout(bitToBus);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_7 = new QLabel(bitToBus);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setWordWrap(true);

        verticalLayout_3->addWidget(label_7);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(bitToBus);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_4 = new QLabel(bitToBus);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_11->addWidget(label_4);

        spinBox_7 = new QSpinBox(bitToBus);
        spinBox_7->setObjectName(QString::fromUtf8("spinBox_7"));

        verticalLayout_11->addWidget(spinBox_7);


        horizontalLayout_7->addLayout(verticalLayout_11);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(bitToBus);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_9->addWidget(pushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_6->addLayout(verticalLayout_3);

        busConnection->addTab(bitToBus, QString());

        retranslateUi(busConnection);

        busConnection->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(busConnection);
    } // setupUi

    void retranslateUi(QTabWidget *busConnection)
    {
        busConnection->setWindowTitle(QApplication::translate("busConnection", "TabWidget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Para conectar los bits de ambos buses en orden ascendente (bit 0 a bit 0, bit 1 a bit 1 y as\303\255 sucesivamente</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        conectarTodos->setText(QApplication::translate("busConnection", "Conectar todos", 0, QApplication::UnicodeUTF8));
        busConnection->setTabText(busConnection->indexOf(allToAll), QApplication::translate("busConnection", "Conectar todos", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("busConnection", "<html><head/><body><p><span style=\" font-weight:600;\">Nombre del segundo bus</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("busConnection", "<html><head/><body><p><span style=\" font-weight:600;\">Nombre del primer bus</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Desde</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Hasta</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Desde </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Hasta</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QString());
        pushButton_3->setText(QApplication::translate("busConnection", "Conectar", 0, QApplication::UnicodeUTF8));
        busConnection->setTabText(busConnection->indexOf(porBloques), QApplication::translate("busConnection", "Por bloques", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Primer Click Nombre</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Segundo Click Nombre</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QString());
        pushButton_2->setText(QApplication::translate("busConnection", "Conectar", 0, QApplication::UnicodeUTF8));
        busConnection->setTabText(busConnection->indexOf(oneByOne), QApplication::translate("busConnection", "Uno a uno", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("busConnection", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">A continuaci\303\263n elija el bit del bus al que quiere conectar:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">TextLabel</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("busConnection", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">TextLabel</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("busConnection", "Conectar", 0, QApplication::UnicodeUTF8));
        busConnection->setTabText(busConnection->indexOf(bitToBus), QApplication::translate("busConnection", "bit a Bus", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class busConnection: public Ui_busConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUSCONNECTION_H
