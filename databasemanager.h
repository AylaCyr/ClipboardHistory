#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QStringList>

class DatabaseManager
{
public:
    DatabaseManager();

    bool openDatabase();
    bool createTable();
    bool addHistory(const QString& content);
    QStringList loadHistory();
    bool deleteHistory(const QString& content);
    bool clearHistory();

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
