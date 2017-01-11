#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QSql>
#include <QSqlDatabase>

class DBCONNECTION
{
public:

    bool connect()
    {
        QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
        db.setDatabaseName("mitsubishi");
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("");

        if(db.open())
        {
            return true;

        }
        else
            return false;
    }


};


#endif // DBCONNECTION_H
