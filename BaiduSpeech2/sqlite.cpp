#include "sqlite.h"
#include <QDebug>
#include <QSqlError>

sqlite::sqlite(QWidget *parent)
    : QWidget{parent}
{
    if (!openDatabase()) {
        qDebug() << "Failed to open database";
    }
    if (!createTable()) {
        qDebug() << "Failed to create table";
    }
}

bool sqlite::openDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("speech_results.db");
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
        return false;
    }
    return true;
}

bool sqlite::createTable()
{
    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS SpeechResults ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "result TEXT)";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Error creating table:" << query.lastError().text();
        return false;
    }
    return true;
}

bool sqlite::insertResult(const QString& result)
{
    QSqlQuery query;
    query.prepare("INSERT INTO SpeechResults (result) VALUES (:result)");
    query.bindValue(":result", result);
    if (!query.exec()) {
        qDebug() << "Error inserting result:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<QString> sqlite::getAllResults()
{
    QList<QString> results;
    QSqlQuery query("SELECT result FROM SpeechResults");
    while (query.next()) {
        results.append(query.value(0).toString());
    }
    return results;
}

// bool sqlite::deleteAllResults()
// {
//     QSqlQuery query;
//     if (!query.exec("DELETE FROM SpeechResults")) {
//         qDebug() << "Error deleting results:" << query.lastError().text();
//         return false;
//     }
//     return true;
// }

bool sqlite::deleteSingleResult(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SpeechResults WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error deleting single result:" << query.lastError().text();
        return false;
    }
    return true;
}
