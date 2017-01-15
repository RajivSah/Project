#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QMainWindow>
#include <QtCore/QCoreApplication>
#include <QtGui>
#include <QtSql>
#include<QtDebug>
#include<QTableView>
#include<QModelIndex>
#include<QAbstractItemView>
#include<QTableWidgetItem>
#include <QSqlError>
#include<QDateTime>
#include<QSqlQuery>

namespace Ui {
class workshop;
}

class workshop : public QMainWindow
{
    Q_OBJECT


public:
    QSqlQueryModel * model;
    QSqlQuery *query;
    QString  searchItem,VRN, Model , VIN, CuNo, MoNo, DrCo, Date1, Jorder, Jdone;
    explicit workshop(QWidget *parent = 0);
    ~workshop();

    void setInitials();
    void setSizes();
    void getData();

private slots:
     void on_Search_lineEdit_textChanged(const QString &arg1);
     void on_tableView_clicked(const QModelIndex &index);
     void on_Add_clicked();
     void on_updatepush_clicked();



private:
    Ui::workshop *ui;
};

#endif // WORKSHOP_H
