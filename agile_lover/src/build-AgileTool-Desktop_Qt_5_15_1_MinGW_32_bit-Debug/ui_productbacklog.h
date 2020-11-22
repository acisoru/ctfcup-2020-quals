/********************************************************************************
** Form generated from reading UI file 'productbacklog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTBACKLOG_H
#define UI_PRODUCTBACKLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductBacklog
{
public:

    void setupUi(QWidget *ProductBacklog)
    {
        if (ProductBacklog->objectName().isEmpty())
            ProductBacklog->setObjectName(QString::fromUtf8("ProductBacklog"));
        ProductBacklog->resize(400, 300);

        retranslateUi(ProductBacklog);

        QMetaObject::connectSlotsByName(ProductBacklog);
    } // setupUi

    void retranslateUi(QWidget *ProductBacklog)
    {
        ProductBacklog->setWindowTitle(QCoreApplication::translate("ProductBacklog", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductBacklog: public Ui_ProductBacklog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTBACKLOG_H
