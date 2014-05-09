/********************************************************************************
** Form generated from reading UI file 'diagramm.ui'
**
** Created: Sun 11. Apr 16:26:05 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGRAMM_H
#define UI_DIAGRAMM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_diagram
{
public:

    void setupUi(QWidget *diagram)
    {
        if (diagram->objectName().isEmpty())
            diagram->setObjectName(QString::fromUtf8("diagram"));
        diagram->resize(400, 300);

        retranslateUi(diagram);

        QMetaObject::connectSlotsByName(diagram);
    } // setupUi

    void retranslateUi(QWidget *diagram)
    {
        diagram->setWindowTitle(QApplication::translate("diagram", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class diagram: public Ui_diagram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMM_H
