#include "pbacklogwindow.h"
#include "ui_pbacklogwindow.h"

PBacklogWindow::PBacklogWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PBacklogWindow)
{
    ui->setupUi(this);
    pb = new productbacklog();
    ui->tasks->addItems(pb->getItems());
}

PBacklogWindow::~PBacklogWindow()
{
    delete ui;
}

void PBacklogWindow::on_add_clicked()
{
    QInputDialog *dialog = new QInputDialog;
    dialog->setWindowTitle("Add task");
    dialog->setOption(QInputDialog::UsePlainTextEditForTextInput);
    dialog->setLabelText("Task description:");
    if (dialog->exec() == QDialog::Accepted && !dialog->textValue().isEmpty()){
        pb->addItem(dialog->textValue());
        ui->tasks->addItem(dialog->textValue());
    }
}

void PBacklogWindow::on_delete_2_clicked()
{
    QList<QListWidgetItem*> items = ui->tasks->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        pb->removeItem(item->text());
        delete ui->tasks->takeItem(ui->tasks->row(item));
    }
}

void PBacklogWindow::on_edit_clicked()
{
    QListWidgetItem* item = ui->tasks->selectedItems()[0];
    QInputDialog *dialog = new QInputDialog;
    dialog->setWindowTitle("Edit task");
    dialog->setOption(QInputDialog::UsePlainTextEditForTextInput);
    dialog->setLabelText("Task description:");
    dialog->setTextValue(item->text());
    if (dialog->exec() == QDialog::Accepted && !dialog->textValue().isEmpty()){
        pb->editItem(item->text(), dialog->textValue());
        item->setText(dialog->textValue());
    }
}
