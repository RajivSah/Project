#ifndef HRWINDOW_H
#define HRWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include"dbconnection.h"

namespace Ui {
class hrwindow;
}

class hrwindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit hrwindow(bool adminMode=0,QWidget *parent = 0);

    ~hrwindow();

    //Variables
    DBCONNECTION connector {"hrwindow"};



    //Functions
     void search_user_Tab_select();
     void add_user_Tab_select();
     void edit_user_Tab_select();
     void remove_user_Tab_select();
     void setInitails();
     void setInputValidator();
     void setSizes();
     void adminView();

private slots:
     void on_ClearButton_clicked();


     void on_AddButton_clicked();


     void on_searchButton_2_textChanged(const QString &arg1);

     void on_tableView_2_clicked(const QModelIndex &index);

     void on_AddButton_5_clicked();
     void on_remove_Button_clicked();
     void clearAfterRemove();

private:
    Ui::hrwindow *ui;
    QSqlQueryModel *model1=new QSqlQueryModel();
    QSqlQueryModel *model2=new QSqlQueryModel();
    QSqlQueryModel *model3=new QSqlQueryModel();
    int searchKey1;
    int searchKey2;


};



#endif // HRWINDOW_H
