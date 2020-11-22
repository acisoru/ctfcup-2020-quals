/********************************************************************************
** Form generated from reading UI file 'selecttasksdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTASKSDIALOG_H
#define UI_SELECTTASKSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectTasksDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;

    void setupUi(QDialog *SelectTasksDialog)
    {
        if (SelectTasksDialog->objectName().isEmpty())
            SelectTasksDialog->setObjectName(QString::fromUtf8("SelectTasksDialog"));
        SelectTasksDialog->resize(327, 300);
        buttonBox = new QDialogButtonBox(SelectTasksDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(120, 240, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listWidget = new QListWidget(SelectTasksDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(30, 20, 256, 192));

        retranslateUi(SelectTasksDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SelectTasksDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SelectTasksDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectTasksDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectTasksDialog)
    {
        SelectTasksDialog->setWindowTitle(QCoreApplication::translate("SelectTasksDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectTasksDialog: public Ui_SelectTasksDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTASKSDIALOG_H
