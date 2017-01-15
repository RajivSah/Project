#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QSql>
#include <QSqlDatabase>

class DBCONNECTION
{
public:
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    DBCONNECTION()
    {
        db.setDatabaseName("mitsubishi");
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("");

    }

    bool connect()
    {
        if(db.open())
            return true;
        else
            return false;
    }
    void close()
    {
        db.close();
    }


};


#endif // DBCONNECTION_H
