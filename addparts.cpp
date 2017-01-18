#include "addparts.h"
#include "ui_addparts.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


addParts::addParts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addParts)
{
    ui->setupUi(this);
    setValidator();
}

addParts::~addParts()
{
    delete ui;
}

void addParts::on_addPushButton_clicked()
{

   if(!connector.db.open())
    {
        displayMessage("Data Cannot be Added");
        qDebug()<<connector.db.lastError();
        return;
    }
    else
    {
       if(ui->IDLineEdit->text()==NULL)
       {
           displayMessage("ID cannot be empty");
           return;
       }
    QSqlQuery *query=new QSqlQuery(connector.db);
    query->prepare("INSERT INTO partstore (Name,ID,SellingPrice) VALUES(?,?,?)");
    query->addBindValue(ui->nameLineEdit->text());
    query->addBindValue(ui->IDLineEdit->text());
    query->addBindValue(ui->spLineEdit->text());
    if(!query->exec())

    {
        displayMessage("Execution Failed");
        return;
    }
    else
    {
        qDebug()<<"data added sucessfully";
        this->close();
    }
    }


    }
void addParts::displayMessage(QString msg)
{
    message.setText(msg);
    message.exec();
}
void addParts::setValidator()
{
    QRegExp exp("[0-9]{0,9}");
    ui->spLineEdit->setValidator(new QRegExpValidator(exp));
    QRegExp exp1("[a-z A-z 0-9]{0,20}");
    ui->nameLineEdit->setValidator(new QRegExpValidator(exp1));
    ui->IDLineEdit->setValidator(new QRegExpValidator(exp1));

}
