#ifndef SELECTTASKSDIALOG_H
#define SELECTTASKSDIALOG_H

#include <QDialog>

namespace Ui {
class SelectTasksDialog;
}

class SelectTasksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTasksDialog(QWidget *parent = nullptr);
    ~SelectTasksDialog();

private:
    Ui::SelectTasksDialog *ui;
};

#endif // SELECTTASKSDIALOG_H
