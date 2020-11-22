#ifndef SPRINTWINDOW_H
#define SPRINTWINDOW_H

#include <QWidget>
#include <QDir>

#include "sprint.h"
#include "listdialog.h"
#include "productbacklog.h"

namespace Ui {
class SprintWindow;
}

class SprintWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SprintWindow(QWidget *parent = nullptr);
    ~SprintWindow();
    void initSprint(int index);
    Sprint *s;
    productbacklog *pb;

private slots:
    void on_add_clicked();

    void on_move_clicked();

    void on_delete_2_clicked();

private:
    Ui::SprintWindow *ui;
};

#endif // SPRINTWINDOW_H
