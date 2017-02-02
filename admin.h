#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "hrwindow.h"
#include "hr_splash.h"
#include "addparts.h"
#include "admin.h"
#include "partstore.h"
#include "workshop.h"
#include "dbconnection.h"
#include "QMessageBox"
#include "sales.h"
#include "analysis.h"
namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin( QWidget *parent = 0);
    void chooseDepartment();
    QMessageBox message;
    void displayMessage(QString);


    ~Admin();

private slots:
    void on_okPushButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_addPushButton_clicked();

    void on_removePushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Admin *ui;
    DBCONNECTION connector{"admin"};
    int pid;
};

#endif // ADMIN_H
