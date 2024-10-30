/********************************************************************************
** Form generated from reading UI file 'calculadora.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULADORA_H
#define UI_CALCULADORA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calculadora
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QPushButton *Boton_3;
    QPushButton *Boton_0;
    QPushButton *Boton_7;
    QPushButton *Boton_division;
    QPushButton *Boton_6;
    QPushButton *Boton_punto;
    QPushButton *Boton_5;
    QPushButton *Boton_suma;
    QPushButton *Boton_menos;
    QPushButton *Boton_8;
    QPushButton *Boton_4;
    QPushButton *Boton_igual;
    QPushButton *Boton_borrar;
    QPushButton *Boton_1;
    QPushButton *Boton_porcentaje;
    QPushButton *Boton_multiplicacion;
    QPushButton *Boton_resta;
    QPushButton *Boton_parentesis;
    QPushButton *Boton_2;
    QPushButton *Boton_9;

    void setupUi(QWidget *calculadora)
    {
        if (calculadora->objectName().isEmpty())
            calculadora->setObjectName("calculadora");
        calculadora->resize(360, 301);
        horizontalLayout = new QHBoxLayout(calculadora);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(calculadora);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        Boton_3 = new QPushButton(calculadora);
        Boton_3->setObjectName("Boton_3");

        gridLayout->addWidget(Boton_3, 4, 2, 1, 1);

        Boton_0 = new QPushButton(calculadora);
        Boton_0->setObjectName("Boton_0");

        gridLayout->addWidget(Boton_0, 5, 1, 1, 1);

        Boton_7 = new QPushButton(calculadora);
        Boton_7->setObjectName("Boton_7");

        gridLayout->addWidget(Boton_7, 1, 0, 1, 1);

        Boton_division = new QPushButton(calculadora);
        Boton_division->setObjectName("Boton_division");

        gridLayout->addWidget(Boton_division, 0, 3, 1, 1);

        Boton_6 = new QPushButton(calculadora);
        Boton_6->setObjectName("Boton_6");

        gridLayout->addWidget(Boton_6, 2, 2, 1, 1);

        Boton_punto = new QPushButton(calculadora);
        Boton_punto->setObjectName("Boton_punto");

        gridLayout->addWidget(Boton_punto, 5, 2, 1, 1);

        Boton_5 = new QPushButton(calculadora);
        Boton_5->setObjectName("Boton_5");

        gridLayout->addWidget(Boton_5, 2, 1, 1, 1);

        Boton_suma = new QPushButton(calculadora);
        Boton_suma->setObjectName("Boton_suma");

        gridLayout->addWidget(Boton_suma, 4, 3, 1, 1);

        Boton_menos = new QPushButton(calculadora);
        Boton_menos->setObjectName("Boton_menos");

        gridLayout->addWidget(Boton_menos, 5, 0, 1, 1);

        Boton_8 = new QPushButton(calculadora);
        Boton_8->setObjectName("Boton_8");

        gridLayout->addWidget(Boton_8, 1, 1, 1, 1);

        Boton_4 = new QPushButton(calculadora);
        Boton_4->setObjectName("Boton_4");

        gridLayout->addWidget(Boton_4, 2, 0, 1, 1);

        Boton_igual = new QPushButton(calculadora);
        Boton_igual->setObjectName("Boton_igual");

        gridLayout->addWidget(Boton_igual, 5, 3, 1, 1);

        Boton_borrar = new QPushButton(calculadora);
        Boton_borrar->setObjectName("Boton_borrar");

        gridLayout->addWidget(Boton_borrar, 0, 0, 1, 1);

        Boton_1 = new QPushButton(calculadora);
        Boton_1->setObjectName("Boton_1");

        gridLayout->addWidget(Boton_1, 4, 0, 1, 1);

        Boton_porcentaje = new QPushButton(calculadora);
        Boton_porcentaje->setObjectName("Boton_porcentaje");

        gridLayout->addWidget(Boton_porcentaje, 0, 2, 1, 1);

        Boton_multiplicacion = new QPushButton(calculadora);
        Boton_multiplicacion->setObjectName("Boton_multiplicacion");

        gridLayout->addWidget(Boton_multiplicacion, 1, 3, 1, 1);

        Boton_resta = new QPushButton(calculadora);
        Boton_resta->setObjectName("Boton_resta");

        gridLayout->addWidget(Boton_resta, 2, 3, 1, 1);

        Boton_parentesis = new QPushButton(calculadora);
        Boton_parentesis->setObjectName("Boton_parentesis");

        gridLayout->addWidget(Boton_parentesis, 0, 1, 1, 1);

        Boton_2 = new QPushButton(calculadora);
        Boton_2->setObjectName("Boton_2");

        gridLayout->addWidget(Boton_2, 4, 1, 1, 1);

        Boton_9 = new QPushButton(calculadora);
        Boton_9->setObjectName("Boton_9");

        gridLayout->addWidget(Boton_9, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(calculadora);

        QMetaObject::connectSlotsByName(calculadora);
    } // setupUi

    void retranslateUi(QWidget *calculadora)
    {
        calculadora->setWindowTitle(QCoreApplication::translate("calculadora", "calculadora", nullptr));
        label->setText(QString());
        Boton_3->setText(QCoreApplication::translate("calculadora", "3", nullptr));
        Boton_0->setText(QCoreApplication::translate("calculadora", "0", nullptr));
        Boton_7->setText(QCoreApplication::translate("calculadora", "7", nullptr));
        Boton_division->setText(QCoreApplication::translate("calculadora", "/", nullptr));
        Boton_6->setText(QCoreApplication::translate("calculadora", "6", nullptr));
        Boton_punto->setText(QCoreApplication::translate("calculadora", ".", nullptr));
        Boton_5->setText(QCoreApplication::translate("calculadora", "5", nullptr));
        Boton_suma->setText(QCoreApplication::translate("calculadora", "+", nullptr));
        Boton_menos->setText(QCoreApplication::translate("calculadora", "+/-", nullptr));
        Boton_8->setText(QCoreApplication::translate("calculadora", "8", nullptr));
        Boton_4->setText(QCoreApplication::translate("calculadora", "4", nullptr));
        Boton_igual->setText(QCoreApplication::translate("calculadora", "=", nullptr));
        Boton_borrar->setText(QCoreApplication::translate("calculadora", "C", nullptr));
        Boton_1->setText(QCoreApplication::translate("calculadora", "1", nullptr));
        Boton_porcentaje->setText(QCoreApplication::translate("calculadora", "%", nullptr));
        Boton_multiplicacion->setText(QCoreApplication::translate("calculadora", "*", nullptr));
        Boton_resta->setText(QCoreApplication::translate("calculadora", "-", nullptr));
        Boton_parentesis->setText(QCoreApplication::translate("calculadora", "( )", nullptr));
        Boton_2->setText(QCoreApplication::translate("calculadora", "2", nullptr));
        Boton_9->setText(QCoreApplication::translate("calculadora", "9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class calculadora: public Ui_calculadora {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULADORA_H
