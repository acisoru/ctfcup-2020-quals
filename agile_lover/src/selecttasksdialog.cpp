#include "selecttasksdialog.h"
#include "ui_selecttasksdialog.h"

SelectTasksDialog::SelectTasksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectTasksDialog)
{
    ui->setupUi(this);
}

SelectTasksDialog::~SelectTasksDialog()
{
    delete ui;
}
