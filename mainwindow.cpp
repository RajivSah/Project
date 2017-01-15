
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   ui->setupUi(this);
    setInitials();
    setConnection();//connect with database


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setInitials()
{
    this->setFixedSize(640, 480);
    ui->userName->setFixedSize(200, 38);
    ui->passWord->setFixedSize(200, 38);
    ui->LoginButton->setFixedSize(200, 38);
    ui->dateLabel->setText(QDate::currentDate().toString("dd, MMMM yyyy "));
    ui->dateLabel->setAlignment(Qt::AlignCenter);
    ui->loginNotificationLabel->setText("");
    ui->loginNotificationLabel->setAlignment(Qt::AlignCenter);
}
void MainWindow::setConnection()
{
    db.setHostName("localhost");
    db.setDatabaseName("mitsubishi");
    db.setUserName("root");
    db.setPassword("");
}

void MainWindow::on_LoginButton_clicked()
{
     QMessageBox msgBox;

    if(!db.open())
    {

        msgBox.setText("Cannot Connecct to the Database");
        msgBox.setWindowTitle("ERROR");
        msgBox.exec();
        return;
    }
    else
    {
        qDebug("Connected");
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM login WHERE Username= ? AND Password= ?");
    query.addBindValue(ui->userName->text());
    query.addBindValue(ui->passWord->text());
    query.exec();

    if(query.size()==1)
    {
    ui->loginNotificationLabel->setText("");
        /*msgBox.setText("Loged In");
        msgBox.setWindowTitle("WELCOME");
        msgBox.exec();
        db.close();*/
    hr_splash *hrSplash=new hr_splash();
    this->close();

    hrSplash->show();
        return;


    }
    else
    {
      ui->loginNotificationLabel->setText("Incorrecet Username or Password");
      db.close();
    }


}

void MainWindow::on_userName_textChanged(const QString &arg1)
{
    ui->loginNotificationLabel->setText("");
}

void MainWindow::on_passWord_textChanged(const QString &arg1)
{
    ui->loginNotificationLabel->setText("");
}
