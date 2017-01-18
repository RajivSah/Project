#include "partstore.h"
#include "ui_partstore.h"
#include "addparts.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>
#include <QDate>
#include <QSqlTableModel>

partstore::partstore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::partstore)
{
    ui->setupUi(this);
}

partstore::~partstore()
{
    delete ui;
}

void partstore::on_pushButton_clicked()
{
    addParts p;
    p.exec();
}

void partstore::on_searchButton_textChanged(const QString &arg1)
{

    if(!connector.db.open())
    {
        displayMessage("Cannot connect: Try again Later ");
        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM partstore WHERE ID LIKE '%"+arg1+"%' OR Name LIKE '%"+arg1+"%'",connector.db);
        ui->tableView->setModel(model);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->hideColumn(3);
//      qDebug()<<connector.db.lastError();

    connector.db.close();
    }
}

void partstore::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_ID->setText(index.sibling(index.row(),0).data().toString());
    ui->lineEdit_Name->setText(index.sibling(index.row(),1).data().toString());
    ui->lineEdit_SP->setText(index.sibling(index.row(),2).data().toString());
    ui->lineEdit_Quantity->setText(index.sibling(index.row(),3).data().toString());

    enable_GroupBox(1);

    prevID=index.sibling(index.row(),0).data().toString();//set prevID to the id of clicked row

    update_tableView_Detail();//refresh tableview_Detail

}

void partstore::on_pushButton_Edit_clicked()
{
    ui->lineEdit_Name->setEnabled(1);
    ui->lineEdit_ID->setEnabled(1);
    ui->lineEdit_Quantity->setEnabled(1);
    ui->lineEdit_SP->setEnabled(1);
    ui->pushButton_Update->setEnabled(1);
    ui->pushButton_Edit->setEnabled(0);

}

void partstore::on_pushButton_Update_clicked()
{

    if(!connector.db.open())
    {
        displayMessage("cannot connect :Try again later");
        qDebug()<<"cannot connect "<<connector.db.lastError();
        return;
    }
    else
    {
        try
        {
            connector.db.transaction();
            QSqlQuery *query=new QSqlQuery(connector.db);
                    query->prepare("UPDATE partstore SET Name =? ,ID=?,SellingPrice=?, Quantity=? WHERE ID=?");
                    query->addBindValue(ui->lineEdit_Name->text());
                    query->addBindValue(ui->lineEdit_ID->text());
                    query->addBindValue(ui->lineEdit_SP->text());
                    query->addBindValue(ui->lineEdit_Quantity->text());
                    query->addBindValue(prevID);

                    QSqlQuery *query2=new QSqlQuery(connector.db);
                    query2->prepare("UPDATE partstock SET ID=? WHERE ID=?");
                    query2->addBindValue(ui->lineEdit_ID->text());
                    query2->addBindValue(prevID);
            if(!query->exec())
            {
                throw 1;
            }
            if(!query2->exec())
            {
                throw 1;
            }
             connector.db.commit();

             ui->lineEdit_Name->setEnabled(0);
             ui->lineEdit_ID->setEnabled(0);
             ui->lineEdit_Quantity->setEnabled(0);
             ui->lineEdit_SP->setEnabled(0);
             ui->pushButton_Update->setEnabled(0);
             ui->pushButton_Edit->setEnabled(1);

             ui->statusbar->showMessage("Update Successfull");

             prevID=ui->lineEdit_ID->text();

             on_searchButton_textChanged(ui->searchButton->text());
             update_tableView_Detail();

             connector.db.close();

        }
        catch (int)
        {
           displayMessage("cannot connect :Try again later");
           ui->statusbar->showMessage("Update Failed");
           qDebug() <<connector.db.rollback();
        }


    }

}

void partstore::on_pushButton_2_clicked()
{
    ui->lineEdit_date->setText(QDate::currentDate().toString("dd/MM/yyyy"));
}

void partstore::on_pushButton_newEdit_clicked()
{
    ui->lineEdit_date->setEnabled(1);
    ui->lineEdit_newQuantity->setEnabled(1);
    ui->pushButton_add->setEnabled(1);
    ui->pushButton_2->setEnabled(1);
    ui->pushButton_newEdit->setDisabled(1);

    ui->lineEdit_date->clear();
    ui->lineEdit_newQuantity->clear();
}

void partstore::on_pushButton_add_clicked()
{
    if(!connector.db.open())
    {
        displayMessage("cannot connect :Try again later");
        qDebug()<<"cannot connect "<<connector.db.lastError();
        return;
    }
    else
    {
        QSqlQuery *query=new QSqlQuery(connector.db);
        query->prepare("INSERT INTO partstock (ID,DateAdded,Quantity) VALUES (?,?,?)");
        query->addBindValue(prevID);
        query->addBindValue(ui->lineEdit_date->text());
        query->addBindValue(ui->lineEdit_newQuantity->text());

        if(!query->exec())
        {
            displayMessage("cannot ADD :Try again later");
        }
        else
        {

            ui->lineEdit_date->setEnabled(0);
            ui->lineEdit_newQuantity->setEnabled(0);
            ui->pushButton_add->setEnabled(0);
            ui->pushButton_2->setEnabled(0);
            ui->pushButton_newEdit->setEnabled(1);

            ui->lineEdit_date->clear();
            ui->lineEdit_newQuantity->clear();

            ui->statusbar->showMessage("New Stock addded");
            update_tableView_Detail();
            connector.db.close();
        }
    }
}
void partstore::update_tableView_Detail()
{
/*
    QSqlQuery *query=new QSqlQuery(connector.db);
    query->prepare("SELECT * FROM WHERE ID =?");
    query->addBindValue(ID);*/
    connector.db.open();
    QSqlTableModel *model=new QSqlTableModel(nullptr,connector.db);
    model->setTable("partstock");
    model->setFilter("ID='"+prevID+"'");
    model->select();
//    qDebug()<<model->lastError().text();
    ui->tableView_Detail->setModel(model);
}
void partstore::displayMessage(QString msg)
{
    message.setText(msg);
    message.exec();
}
void partstore::enable_GroupBox(bool x)
{
    ui->groupBox->setEnabled(x);
    ui->groupBox_partStore->setEnabled(x);
    ui->pushButton_Edit->setEnabled(x);
    ui->pushButton_newEdit->setEnabled(x);
    ui->pushButton_2->setEnabled(x);
}


