#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_sprints_list();
    init_pbacklog();
}

void MainWindow::init_sprints_list(){
    ui->sprints->addItem("New sprint");
    QDir d(".");
    QStringList sprints = d.entryList(QStringList() << "sprint*", QDir::Files);
    foreach(QString filename, sprints){
        ui->sprints->addItem(filename);
    }
}

void MainWindow::init_pbacklog(){
    pbacklog = new productbacklog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbacklog_clicked()
{
    PBacklogWindow *pb = new PBacklogWindow;
    pb->show();
}

void MainWindow::on_sprint_settings_clicked()
{
    QString sprint = ui->sprints->currentText();
    int index;
    if (sprint == "New sprint"){
        index = 1;
        for (int i = 0; i < ui->sprints->count(); i++){
            if (ui->sprints->itemText(i) == "New sprint")
                continue;
            int tmp = ui->sprints->itemText(i).mid(6).toInt();
            if (tmp >= index){
                index = tmp + 1;
            }
        }
        ui->sprints->addItem("sprint"+QString::number(index));
    } else {
        index = sprint.mid(6).toInt();
    }

    sw = new SprintWindow();
    sw->initSprint(index);
    sw->show();
}
