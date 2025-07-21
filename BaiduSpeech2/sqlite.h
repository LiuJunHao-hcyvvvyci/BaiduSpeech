#ifndef SQLITE_H
#define SQLITE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

class sqlite : public QWidget
{
    Q_OBJECT
public:
    explicit sqlite(QWidget *parent = nullptr);
    bool openDatabase();
    bool createTable();
    bool insertResult(const QString& result);
    QList<QString> getAllResults();
    //bool deleteAllResults(); // 添加删除所有记录的方法
    bool deleteSingleResult(int id); // 添加删除单条记录的方法

signals:

private:
    QSqlDatabase db;
};

#endif // SQLITE_H
