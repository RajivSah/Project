#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include "hrwindow.h"
#include "hr_splash.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setInitials();
    void setConnection();

private slots:

    void on_LoginButton_clicked();

    void on_userName_textChanged(const QString &arg1);

    void on_passWord_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
};

#endif // MAINWINDOW_H
