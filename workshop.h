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
#include "dbconnection.h"

namespace Ui {
class workshop;
}

class workshop : public QMainWindow
{
    Q_OBJECT


public:
    // Variables
    QSqlQueryModel * model;
    QSqlQuery *query;
    QString  searchItem,VRN, Model , VIN, VName,VBrand,MfdYear,OdoReading,Distance,CuNo, MoNo, DrCo, Date1, Jorder, Jdone;
    int Rid;
    DBCONNECTION d {"workshow"};


    explicit workshop(bool adminMode=0,QWidget *parent = 0);
    ~workshop();

    void setInitials();
    void setSizes();
    void getData();
    void adminView();

private slots:
     void on_Search_lineEdit_textChanged(const QString &arg1);
     void on_tableView_clicked(const QModelIndex &index);
     void on_Add_clicked();
     void on_updatepush_clicked();
     void on_clearPush_clicked();
     void hideColumns();
     void changeBoxItems();
    void on_pushButton_clicked();


     void on_pushButton_2_clicked();
      void on_dateCombobox_currentIndexChanged(int index);
      void on_deletePush_clicked();
      void refreshTable();
      void refresh();




private:
    Ui::workshop *ui;
};

#endif // WORKSHOP_H
