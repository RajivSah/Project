#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>

class DBCONNECTION
{
public:
    QSqlDatabase db;
    DBCONNECTION( QString conName)
    {
        db = QSqlDatabase::addDatabase("QMYSQL", conName);
        db.setDatabaseName("mitsubishi");
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("");
        qDebug()<<db.connectionName()<<conName;

    }



};


#endif // DBCONNECTION_H
