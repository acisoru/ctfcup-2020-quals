#ifndef SPRINT_H
#define SPRINT_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>

#include "productbacklog.h"

class Sprint
{
public:
    Sprint(int i);
    void addTask(QString task);
    void deleteTask(QString task);
    void moveTask(QString task, int sprint);
    QStringList getTasks();
    void writeChanges();
private:
    QStringList tasks;
    int index;
};

#endif // SPRINT_H
