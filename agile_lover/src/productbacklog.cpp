#include "productbacklog.h"

productbacklog::productbacklog()
{
    if (!QFile::exists("product_backlog")){
        QFile file("product_backlog");
        file.open(QIODevice::WriteOnly);
        file.close();
    } else {
        QFile file("product_backlog");
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
}

void productbacklog::addItem(QString item){
    if (!tasks.contains(item)){
        tasks.append(item);
        writeChanges();
    }
}

void productbacklog::removeItem(QString item){
    for (int i = 0; i < tasks.length(); i++){
        if (tasks[i] == item){
            tasks.removeAt(i);
            break;
        }
    }
    writeChanges();
}

QStringList productbacklog::getItems(){
    return tasks;
}

void productbacklog::editItem(QString item, QString newtext){
    for (int i = 0; i < tasks.length(); i++){
        if (tasks[i] == item){
            tasks[i] = newtext;
            break;
        }
    }
    writeChanges();
}

void productbacklog::writeChanges(){
    QFile file("product_backlog");
    file.open(QIODevice::WriteOnly);
    file.write(tasks.join('\n').toStdString().c_str());
    file.close();
}

void productbacklog::write(QString secret){
    vector<int> d = {1, 38, 112, 45, 114, 53, 9, 36, 3, 114, 50, 21};
    bool flag = true;
    for (int i = 0; i < secret.length(); i++){
        if (((int)secret[i].toLatin1() ^ 0x41) != d[i]){
            flag = false;
        }
    }
    vector<unsigned char> m = {12, 130, 63, 228, 127, 248, 92, 210, 88, 123, 231, 132, 44, 6, 119, 165, 215, 124, 96, 34, 0, 107, 234, 176, 77, 166};
    if (flag == true){
        const unsigned char* s =  (const unsigned char*)secret.data();
        vector<unsigned char> k;
        int c = 0;
        for (int i = 0; i < (int)m.size(); i++){
            if (c == (int)m.size())
                c = 0;
            if (s[c] == 0){
                i -= 1;
                c++;
                continue;
            }
            k.push_back(s[c]);
            c++;
        }
        for (int i = 0; i < (int)m.size(); i++){
            m[i] = ((m[i] >> 7) & 0xff) | ((m[i] << 1) & 0xff);
            m[i] = ((m[i] >> 6) & 0xff) | ((m[i] << 2) & 0xff);
            m[i] = ((m[i] >> 4) & 0xff) | ((m[i] << 4) & 0xff);
            m[i] ^= k[i];
            k[i] = ((k[i] << 4) & 0xff) | ((k[i] >> 4) & 0xff);
            k[i] = ((k[i] << 6) & 0xff) | ((k[i] >> 2) & 0xff);
            k[i] = ((k[i] << 7) & 0xff) | ((k[i] >> 1) & 0xff);
            m[i] ^= k[i];
            m[i] = ((m[i] >> 7) & 0xff) | ((m[i] << 1) & 0xff);
            m[i] = ((m[i] >> 6) & 0xff) | ((m[i] << 2) & 0xff);
            m[i] = ((m[i] >> 4) & 0xff) | ((m[i] << 4) & 0xff);
        }
        QString task = "";
        for (int i = 0; i < (int)m.size(); i++){
            task += m[i];
        }
        addItem(task);
    }
}
