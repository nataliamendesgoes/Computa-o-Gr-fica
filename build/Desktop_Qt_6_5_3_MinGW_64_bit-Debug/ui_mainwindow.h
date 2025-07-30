/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *areaContainer;
    QSpinBox *anguloRotacaospinBox;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *camera;
    QRadioButton *pokemon1;
    QRadioButton *pokemon2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *escala;
    QRadioButton *rotacao;
    QRadioButton *translacao;
    QVBoxLayout *verticalLayout_4;
    QScrollBar *XScrollBar;
    QScrollBar *YScrollBar;
    QScrollBar *ZScrollBar;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_10;
    QRadioButton *xRotacao;
    QRadioButton *yRotacao;
    QRadioButton *zRotacao;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1038, 602);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        areaContainer = new QFrame(centralwidget);
        areaContainer->setObjectName("areaContainer");
        areaContainer->setGeometry(QRect(50, 20, 501, 501));
        areaContainer->setFrameShape(QFrame::StyledPanel);
        areaContainer->setFrameShadow(QFrame::Raised);
        anguloRotacaospinBox = new QSpinBox(centralwidget);
        anguloRotacaospinBox->setObjectName("anguloRotacaospinBox");
        anguloRotacaospinBox->setGeometry(QRect(870, 480, 44, 29));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(630, 480, 221, 31));
        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(630, 520, 131, 31));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(600, 70, 411, 80));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        camera = new QRadioButton(horizontalLayoutWidget);
        camera->setObjectName("camera");

        horizontalLayout_8->addWidget(camera);

        pokemon1 = new QRadioButton(horizontalLayoutWidget);
        pokemon1->setObjectName("pokemon1");

        horizontalLayout_8->addWidget(pokemon1);

        pokemon2 = new QRadioButton(horizontalLayoutWidget);
        pokemon2->setObjectName("pokemon2");

        horizontalLayout_8->addWidget(pokemon2);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(590, 230, 311, 181));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        escala = new QRadioButton(horizontalLayoutWidget_2);
        escala->setObjectName("escala");

        verticalLayout_2->addWidget(escala);

        rotacao = new QRadioButton(horizontalLayoutWidget_2);
        rotacao->setObjectName("rotacao");

        verticalLayout_2->addWidget(rotacao);

        translacao = new QRadioButton(horizontalLayoutWidget_2);
        translacao->setObjectName("translacao");

        verticalLayout_2->addWidget(translacao);


        horizontalLayout_9->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        XScrollBar = new QScrollBar(horizontalLayoutWidget_2);
        XScrollBar->setObjectName("XScrollBar");
        XScrollBar->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(XScrollBar);

        YScrollBar = new QScrollBar(horizontalLayoutWidget_2);
        YScrollBar->setObjectName("YScrollBar");
        YScrollBar->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(YScrollBar);

        ZScrollBar = new QScrollBar(horizontalLayoutWidget_2);
        ZScrollBar->setObjectName("ZScrollBar");
        ZScrollBar->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(ZScrollBar);


        horizontalLayout_9->addLayout(verticalLayout_4);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(910, 230, 71, 181));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout_3->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout_3->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_4->setObjectName("lineEdit_4");

        verticalLayout_3->addWidget(lineEdit_4);

        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(780, 520, 160, 41));
        horizontalLayout_10 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        xRotacao = new QRadioButton(horizontalLayoutWidget_3);
        xRotacao->setObjectName("xRotacao");

        horizontalLayout_10->addWidget(xRotacao);

        yRotacao = new QRadioButton(horizontalLayoutWidget_3);
        yRotacao->setObjectName("yRotacao");

        horizontalLayout_10->addWidget(yRotacao);

        zRotacao = new QRadioButton(horizontalLayoutWidget_3);
        zRotacao->setObjectName("zRotacao");

        horizontalLayout_10->addWidget(zRotacao);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1038, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "Angulo para Rotacao", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "Eixo para rotacao", nullptr));
        camera->setText(QCoreApplication::translate("MainWindow", "C\303\242mera", nullptr));
        pokemon1->setText(QCoreApplication::translate("MainWindow", "Pokemon 1", nullptr));
        pokemon2->setText(QCoreApplication::translate("MainWindow", "Pokemon 2", nullptr));
        escala->setText(QCoreApplication::translate("MainWindow", "Escala", nullptr));
        rotacao->setText(QCoreApplication::translate("MainWindow", "Rotacao", nullptr));
        translacao->setText(QCoreApplication::translate("MainWindow", "Translacao", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        xRotacao->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        yRotacao->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        zRotacao->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
