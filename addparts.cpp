#include "addparts.h"
#include "ui_addparts.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

addParts::addParts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addParts)
{
    ui->setupUi(this);
}

addParts::~addParts()
{
    delete ui;
}

void addParts::on_addPushButton_clicked()
{

   if(!connector.db.open())
    {
        QMessageBox msg;
        msg.setText("data cannot be added");
        msg.exec();
        qDebug()<<connector.db.lastError();
        return;
    }
    else
    {
    QSqlQuery *query=new QSqlQuery(connector.db);
    query->prepare("INSERT INTO partstore (Name,ID,SellingPrice) VALUES(?,?,?)");
    query->addBindValue(ui->nameLineEdit->text());
    query->addBindValue(ui->IDLineEdit->text());
    query->addBindValue(ui->spLineEdit->text());
    if(!query->exec())

    {
        QMessageBox msg;
        msg.setText("data cannot be added");
        return;
    }
    else
    {
        qDebug()<<"data added sucessfully";
    }
    }


    }
