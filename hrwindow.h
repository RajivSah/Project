#ifndef HRWINDOW_H
#define HRWINDOW_H

#include <QMainWindow>

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

private slots:
     void on_ClearButton_clicked();
     void searchFunction(QString);

     void on_AddButton_clicked();


     void on_searchButton_textChanged(const QString &arg1);

     void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::hrwindow *ui;
};



#endif // HRWINDOW_H
