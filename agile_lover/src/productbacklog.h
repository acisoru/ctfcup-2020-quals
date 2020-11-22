#ifndef PRODUCTBACKLOG_H
#define PRODUCTBACKLOG_H

#include <QFile>
#include <QTextStream>
#include <vector>
#include <QDebug>

using namespace std;

class productbacklog
{
public:
    productbacklog();
    void addItem(QString item);
    void removeItem(QString item);
    void editItem(QString item, QString newtext);
    QStringList getItems();
    void write(QString secret);
private:
    QStringList tasks;
    void writeChanges();
};

#endif // PRODUCTBACKLOG_H
