/********************************************************************************
** Form generated from reading UI file 'sprintwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRINTWINDOW_H
#define UI_SPRINTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SprintWindow
{
public:
    QPushButton *delete_2;
    QLabel *label_2;
    QPushButton *add;
    QLabel *label;
    QListWidget *tasks;
    QPushButton *move;
    QLabel *snumber;

    void setupUi(QWidget *SprintWindow)
    {
        if (SprintWindow->objectName().isEmpty())
            SprintWindow->setObjectName(QString::fromUtf8("SprintWindow"));
        SprintWindow->resize(478, 300);
        delete_2 = new QPushButton(SprintWindow);
        delete_2->setObjectName(QString::fromUtf8("delete_2"));
        delete_2->setGeometry(QRect(300, 154, 161, 31));
        label_2 = new QLabel(SprintWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 224, 101, 31));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel {color : green; }"));
        label_2->setTextFormat(Qt::PlainText);
        add = new QPushButton(SprintWindow);
        add->setObjectName(QString::fromUtf8("add"));
        add->setGeometry(QRect(300, 54, 161, 31));
        label = new QLabel(SprintWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 24, 91, 21));
        label->setFont(font);
        tasks = new QListWidget(SprintWindow);
        tasks->setObjectName(QString::fromUtf8("tasks"));
        tasks->setGeometry(QRect(20, 54, 251, 201));
        move = new QPushButton(SprintWindow);
        move->setObjectName(QString::fromUtf8("move"));
        move->setGeometry(QRect(300, 104, 161, 31));
        snumber = new QLabel(SprintWindow);
        snumber->setObjectName(QString::fromUtf8("snumber"));
        snumber->setGeometry(QRect(410, 230, 61, 20));
        snumber->setFont(font);

        retranslateUi(SprintWindow);

        QMetaObject::connectSlotsByName(SprintWindow);
    } // setupUi

    void retranslateUi(QWidget *SprintWindow)
    {
        SprintWindow->setWindowTitle(QCoreApplication::translate("SprintWindow", "Sprint settings", nullptr));
        delete_2->setText(QCoreApplication::translate("SprintWindow", "Delete", nullptr));
        label_2->setText(QCoreApplication::translate("SprintWindow", "Sprint number:", nullptr));
        add->setText(QCoreApplication::translate("SprintWindow", "Add from sprint backlog", nullptr));
        label->setText(QCoreApplication::translate("SprintWindow", "Sprint tasks", nullptr));
        move->setText(QCoreApplication::translate("SprintWindow", "Move to another sprint", nullptr));
        snumber->setText(QCoreApplication::translate("SprintWindow", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SprintWindow: public Ui_SprintWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRINTWINDOW_H
