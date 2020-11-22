/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pbacklog;
    QLabel *label;
    QLabel *label_2;
    QComboBox *sprints;
    QPushButton *sprint_settings;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(624, 289);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pbacklog = new QPushButton(centralwidget);
        pbacklog->setObjectName(QString::fromUtf8("pbacklog"));
        pbacklog->setGeometry(QRect(120, 90, 151, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 40, 61, 31));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(420, 50, 51, 21));
        label_2->setFont(font);
        sprints = new QComboBox(centralwidget);
        sprints->setObjectName(QString::fromUtf8("sprints"));
        sprints->setGeometry(QRect(360, 90, 161, 31));
        sprint_settings = new QPushButton(centralwidget);
        sprint_settings->setObjectName(QString::fromUtf8("sprint_settings"));
        sprint_settings->setGeometry(QRect(390, 150, 111, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 624, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AgileTool", nullptr));
        pbacklog->setText(QCoreApplication::translate("MainWindow", "Product backlog", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Product", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Sprints", nullptr));
        sprint_settings->setText(QCoreApplication::translate("MainWindow", "Sprint settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
