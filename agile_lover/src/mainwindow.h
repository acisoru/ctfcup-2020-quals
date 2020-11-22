#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDirIterator>
#include <QListWidgetItem>
#include <QDebug>

#include "pbacklogwindow.h"
#include "productbacklog.h"
#include "sprintwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_pbacklog();
    void init_sprints_list();
    productbacklog *pbacklog;
    SprintWindow *sw;

private slots:
    void on_pbacklog_clicked();

    void on_sprint_settings_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
