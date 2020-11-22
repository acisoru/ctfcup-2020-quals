#include "sprintwindow.h"
#include "ui_sprintwindow.h"

SprintWindow::SprintWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SprintWindow)
{
    ui->setupUi(this);
    pb = new productbacklog();
}

SprintWindow::~SprintWindow()
{
    delete ui;
}

void SprintWindow::initSprint(int index){
    s = new Sprint(index);
    ui->tasks->addItems(s->getTasks());
    ui->snumber->setText(QString::number(index));
}

void SprintWindow::on_add_clicked()
{
    ListDialog *ld = new ListDialog(this);
    ld->setWindowTitle("Add tasks");
    ld->setList(pb->getItems());
    ld->enableMultiselect();
    if (ld->exec() == QDialog::Accepted && ld->getSelected().length() > 0){
        QStringList list = ld->getSelected();
        for (int i = 0; i < list.length(); i++){
            s->addTask(list[i]);
            ui->tasks->addItem(list[i]);
        }
    }
}

void SprintWindow::on_move_clicked()
{
    ListDialog *ld = new ListDialog(this);
    ld->setWindowTitle("Move task");
    QDir d(".");
    QStringList sprints = d.entryList(QStringList() << "sprint*", QDir::Files);
    sprints.removeAll("sprint"+ui->snumber->text());
    ld->setList(sprints);
    if (ld->exec() == QDialog::Accepted && ld->getSelected().length() > 0 && ui->tasks->currentItem()->isSelected()){
        int sprint = ld->getSelected()[0].mid(6).toInt();
        QString item = ui->tasks->currentItem()->text();
        s->moveTask(item, sprint);
        delete ui->tasks->takeItem(ui->tasks->row(ui->tasks->currentItem()));
    }
}

void SprintWindow::on_delete_2_clicked()
{
    QList<QListWidgetItem*> items = ui->tasks->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        s->deleteTask(item->text());
        delete ui->tasks->takeItem(ui->tasks->row(item));
    }
}
