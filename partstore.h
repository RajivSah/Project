#ifndef PARTSTORE_H
#define PARTSTORE_H

#include <QMainWindow>
#include "dbconnection.h"
#include <QMessageBox>

namespace Ui {
class partstore;
}

class partstore : public QMainWindow
{
    Q_OBJECT

public:
    explicit partstore(QWidget *parent = 0);
    ~partstore();
    DBCONNECTION connector{"partstore"};
    QString prevID;
//    QString ID;
    void update_tableView_Detail();
    void enable_GroupBox(bool x);

private slots:
    void on_pushButton_clicked();

    void on_searchButton_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_Edit_clicked();

    void on_pushButton_Update_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_newEdit_clicked();

    void on_pushButton_add_clicked();


private:
    Ui::partstore *ui;
    QMessageBox message;
    void displayMessage(QString);
};

#endif // PARTSTORE_H
