#ifndef PARTSTORE_H
#define PARTSTORE_H

#include <QMainWindow>
#include "dbconnection.h"
#include <QMessageBox>
#include "partspro.h"

namespace Ui {
class partstore;
}

class partstore : public QMainWindow
{
    Q_OBJECT

public:
    explicit partstore(bool adminMode=0,QWidget *parent = 0);
    ~partstore();
    DBCONNECTION connector{"partstore"};
    QString prevID;
//    QString ID;
    void update_tableView_Detail();
    void enable_GroupBox(bool x);
    void setValidator();
    void setInitials();
    void addGraphicsEffect();
    void adminView();

private slots:
    void on_pushButton_clicked();

    void on_searchButton_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_Edit_clicked();

    void on_pushButton_Update_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_newEdit_clicked();

    void on_pushButton_add_clicked();


    void on_showallpushButton_3_clicked();

    void on_removerecordspushButton_5_clicked();

    void on_removeentrypushButton_4_clicked();

    void on_tableView_Detail_clicked(const QModelIndex &index);

    void on_seepartspropushButton_3_clicked();

    void on_sendentrypushButton_4_clicked();

    void on_lineEdit_date_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::partstore *ui;
    QMessageBox message;
    void displayMessage(QString);
    int pid;
    bool aM;
};

#endif // PARTSTORE_H
