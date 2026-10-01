#include "databasemanager.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager::DatabaseManager()
{
}

bool DatabaseManager::openDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("clipboard.db");

    if (!database.open())
    {
        qDebug() << "数据库打开失败：" << database.lastError().text();
        return false;
    }

    return createTable();
}

bool DatabaseManager::createTable()
{
    QSqlQuery query;

    QString sql =
        "CREATE TABLE IF NOT EXISTS history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "content TEXT NOT NULL UNIQUE"
        ")";

    if (!query.exec(sql))
    {
        qDebug() << "数据表创建失败：" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addHistory(const QString& content)
{
    QSqlQuery query;

    query.prepare("INSERT OR IGNORE INTO history (content) VALUES (:content)");
    query.bindValue(":content", content);

    if (!query.exec())
    {
        qDebug() << "历史记录保存失败：" << query.lastError().text();
        return false;
    }

    return true;
}

QStringList DatabaseManager::loadHistory()
{
    QStringList history;
    QSqlQuery query("SELECT content FROM history ORDER BY id DESC");

    while (query.next())
    {
        history.append(query.value(0).toString());
    }

    return history;
}

bool DatabaseManager::deleteHistory(const QString& content)
{
    QSqlQuery query;

    query.prepare("DELETE FROM history WHERE content = :content");
    query.bindValue(":content", content);

    if (!query.exec())
    {
        qDebug() << "历史记录删除失败：" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::clearHistory()
{
    QSqlQuery query;

    if (!query.exec("DELETE FROM history"))
    {
        qDebug() << "历史记录清空失败：" << query.lastError().text();
        return false;
    }

    return true;
}
