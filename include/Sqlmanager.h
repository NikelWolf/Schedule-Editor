#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QtSql>

class SqlManager
{
public:
    SqlManager();
    void createAllTables();
private:
    QSqlDatabase db;
    QString db_path = "test_db";
};

#endif // SQLMANAGER_H