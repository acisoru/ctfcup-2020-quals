/********************************************************************************
** Form generated from reading UI file 'listdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTDIALOG_H
#define UI_LISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_ListDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *list;

    void setupUi(QDialog *ListDialog)
    {
        if (ListDialog->objectName().isEmpty())
            ListDialog->setObjectName(QString::fromUtf8("ListDialog"));
        ListDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ListDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 250, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        list = new QListWidget(ListDialog);
        list->setObjectName(QString::fromUtf8("list"));
        list->setGeometry(QRect(30, 20, 341, 211));

        retranslateUi(ListDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ListDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ListDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ListDialog);
    } // setupUi

    void retranslateUi(QDialog *ListDialog)
    {
        ListDialog->setWindowTitle(QCoreApplication::translate("ListDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListDialog: public Ui_ListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTDIALOG_H
