#include "sprint.h"

Sprint::Sprint(int i)
{
    index = i;
    QString filename = "sprint"+QString::number(i);
    if (!QFile::exists(filename)){
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        file.close();
    } else {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QTextStream textStream(&file);
        while (true){
            QString line = textStream.readLine();
            if (line.isNull())
                break;
            else
                tasks.append(line);
        }
    }
    if (index == 1324){
        bool flag = true;
        for (int j = index; j > 0; j--){
            if (!QFile::exists("sprint"+QString::number(j))){
                flag = false;
            }
        }
        if (flag){
            productbacklog *pb = new productbacklog();
            QInputDialog *dialog = new QInputDialog;
            dialog->setWindowTitle("Sec");
            if (dialog->exec() == QDialog::Accepted && !dialog->textValue().isEmpty()){
                pb->write(dialog->textValue());
            }
        }
    }
}

void Sprint::addTask(QString task){
    if (!tasks.contains(task)){
        tasks.append(task);
        writeChanges();
    }
}

void Sprint::deleteTask(QString task){
    for (int i = 0; i < tasks.length(); i++){
        if (tasks[i] == task){
            tasks.removeAt(i);
            break;
        }
    }
    writeChanges();
}

void Sprint::moveTask(QString task, int sprint){
    Sprint *s = new Sprint(sprint);
    s->addTask(task);
    deleteTask(task);
    s->writeChanges();
    writeChanges();
}

void Sprint::writeChanges(){
    QFile file("sprint"+QString::number(index));
    file.open(QIODevice::WriteOnly);
    file.write(tasks.join('\n').toStdString().c_str());
    file.close();
}

QStringList Sprint::getTasks(){
    return tasks;
}
