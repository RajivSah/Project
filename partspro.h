#ifndef PARTSPRO_H
#define PARTSPRO_H

#include <QMainWindow>
#include <QtCore/QCoreApplication>
#include <QtGui>
#include <QtSql>
#include<QtDebug>
#include<QTableView>
#include <QSqlTableModel>
#include<QModelIndex>
#include<QAbstractItemView>
#include<QTableWidgetItem>
#include <QSqlError>
#include<QDateTime>
#include<QMessageBox>
#include<QPalette>
#include "dbconnection.h"
namespace Ui {
class partspro;
}

class partspro : public QMainWindow
{
    Q_OBJECT

public:
QSqlDatabase db;
DBCONNECTION d{"partspro"};
    explicit partspro(QWidget *parent = 0);



    ~partspro();



private slots:
    void on_showRecordspushButton_clicked();
    void hidecolumns();

    void on_tableView_clicked(const QModelIndex &index);


    void getData();
    void showtable();
    void on_DeleterpushButton_7_clicked();

    void on_ClearpushButton_3_clicked();

    void on_EditpushButton_2_clicked();

    void on_seeinventorypushButton_4_clicked();

    void finditemtable();
    void on_searchlineEdit_5_textChanged(const QString &arg1);

    void initialconditions(bool);

    void on_todaypushButton_clicked();

private:
    Ui::partspro *ui;
    QSqlQuery *query ;
    QSqlQueryModel *model = new QSqlQueryModel();
int Prid;
QString POrder,PNo, PName, EntryDate , OutDate, VRN,CustomerName,RFNo,quantity;
};

#endif // PARTSPRO_H
