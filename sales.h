#ifndef SALES_H
#define SALES_H

#include <QMainWindow>
#include <QtSql>
#include "dbconnection.h"


namespace Ui {
class sales;
}

class sales : public QMainWindow
{
    Q_OBJECT

public:
    explicit sales(bool adminMode=0,QWidget *parent = 0);
    ~sales();
    DBCONNECTION connector{"salesQt"};

    void adminView();
    void setValidator();
private slots:
    void on_AddButton_clicked();

    void on_ClearButton_clicked();





    void on_SearchButton_textChanged(const QString &arg1);



    void on_customerTableView_clicked(const QModelIndex &index);

    void on_updateBtn_clicked();

    void on_removeBtn_clicked();


private:
    Ui::sales *ui;

};

#endif // SALES_H
