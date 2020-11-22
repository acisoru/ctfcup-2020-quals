#ifndef PBACKLOGWINDOW_H
#define PBACKLOGWINDOW_H

#include <QWidget>
#include <QInputDialog>
#include <QTextEdit>

#include "productbacklog.h"

namespace Ui {
class PBacklogWindow;
}

class PBacklogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PBacklogWindow(QWidget *parent = nullptr);
    ~PBacklogWindow();
    productbacklog *pb;

private slots:
    void on_add_clicked();

    void on_delete_2_clicked();

    void on_edit_clicked();

private:
    Ui::PBacklogWindow *ui;
};

#endif // PBACKLOGWINDOW_H
