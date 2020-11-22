#include "listdialog.h"
#include "ui_listdialog.h"

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog)
{
    ui->setupUi(this);
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::setList(QStringList list){
    foreach(QString item, list){
        ui->list->addItem(item);
    }
}

void ListDialog::enableMultiselect(){
    ui->list->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

QStringList ListDialog::getSelected(){
    QStringList data;
    QList<QListWidgetItem*> items = ui->list->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        data.append(item->text());
    }
    return data;
}
