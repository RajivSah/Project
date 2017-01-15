#ifndef HRWINDOW_H
#define HRWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

namespace Ui {
class hrwindow;
}

class hrwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit hrwindow(QWidget *parent = 0);
    ~hrwindow();

    //Variables




    //Functions
     void search_user_Tab_select();
     void add_user_Tab_select();
     void edit_user_Tab_select();
     void remove_user_Tab_select();
     void setInitails();
     void setInputValidator();
     void setSizes();
private slots:
     void on_ClearButton_clicked();
     void searchFunction(QString);

     void on_AddButton_clicked();


     void on_searchButton_textChanged(const QString &arg1);

     void on_tableView_clicked(const QModelIndex &index);
     void detailSearchResult(int);


    // void on_searchButton_2_textChanged(const QString &arg1);

private:
    Ui::hrwindow *ui;
    QSqlQueryModel *model=new QSqlQueryModel();
};



#endif // HRWINDOW_H
