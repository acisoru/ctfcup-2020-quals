/********************************************************************************
** Form generated from reading UI file 'pbacklogwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PBACKLOGWINDOW_H
#define UI_PBACKLOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PBacklogWindow
{
public:
    QListWidget *tasks;
    QLabel *label;
    QPushButton *add;
    QPushButton *delete_2;
    QPushButton *edit;

    void setupUi(QWidget *PBacklogWindow)
    {
        if (PBacklogWindow->objectName().isEmpty())
            PBacklogWindow->setObjectName(QString::fromUtf8("PBacklogWindow"));
        PBacklogWindow->resize(400, 300);
        tasks = new QListWidget(PBacklogWindow);
        tasks->setObjectName(QString::fromUtf8("tasks"));
        tasks->setGeometry(QRect(10, 40, 256, 231));
        label = new QLabel(PBacklogWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 51, 21));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        add = new QPushButton(PBacklogWindow);
        add->setObjectName(QString::fromUtf8("add"));
        add->setGeometry(QRect(300, 40, 75, 23));
        delete_2 = new QPushButton(PBacklogWindow);
        delete_2->setObjectName(QString::fromUtf8("delete_2"));
        delete_2->setGeometry(QRect(300, 80, 75, 23));
        edit = new QPushButton(PBacklogWindow);
        edit->setObjectName(QString::fromUtf8("edit"));
        edit->setGeometry(QRect(300, 120, 75, 23));

        retranslateUi(PBacklogWindow);

        QMetaObject::connectSlotsByName(PBacklogWindow);
    } // setupUi

    void retranslateUi(QWidget *PBacklogWindow)
    {
        PBacklogWindow->setWindowTitle(QCoreApplication::translate("PBacklogWindow", "Product Backlog", nullptr));
        label->setText(QCoreApplication::translate("PBacklogWindow", "Tasks", nullptr));
        add->setText(QCoreApplication::translate("PBacklogWindow", "Add task", nullptr));
        delete_2->setText(QCoreApplication::translate("PBacklogWindow", "Delete task", nullptr));
        edit->setText(QCoreApplication::translate("PBacklogWindow", "Edit task", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PBacklogWindow: public Ui_PBacklogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PBACKLOGWINDOW_H
