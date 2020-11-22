#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>

namespace Ui {
class ListDialog;
}

class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget *parent = nullptr);
    ~ListDialog();
    void setList(QStringList list);
    void enableMultiselect();
    QStringList getSelected();

private:
    Ui::ListDialog *ui;
};

#endif // LISTDIALOG_H
