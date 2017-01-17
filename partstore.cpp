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
//    qDebug()<<"SELECT * FROM partstore WHERE ID LIKE '%"+arg1+"%' OR Name LIKE '%"+arg1+"%'";

    if(!connector.db.open())
    {
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
        qDebug()<<connector.db.lastError();

    connector.db.close();
    }
}

void partstore::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_ID->setText(index.sibling(index.row(),0).data().toString());
    ui->lineEdit_Name->setText(index.sibling(index.row(),1).data().toString());
    ui->lineEdit_SP->setText(index.sibling(index.row(),2).data().toString());
    ui->lineEdit_Quantity->setText(index.sibling(index.row(),3).data().toString());
    ui->groupBox->setEnabled(1);
    ID=index.sibling(index.row(),0).data().toString();
    update_tableView_Detail();

}

void partstore::on_pushButton_Edit_clicked()
{
    ui->lineEdit_Name->setEnabled(1);
    ui->lineEdit_ID->setEnabled(1);
    ui->lineEdit_Quantity->setEnabled(1);
    ui->lineEdit_SP->setEnabled(1);
    prevID=ui->lineEdit_ID->text();
    ui->pushButton_Update->setEnabled(1);
}

void partstore::on_pushButton_Update_clicked()
{

    if(!connector.db.open())
    {
        qDebug()<<"cannot connect "<<connector.db.lastError();
        return;
    }
    else
    {
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
        query2->exec();

        if(!query->exec() )
        {
            QMessageBox msg;
            msg.setText("update failed");
            msg.exec();
        }
        else
        {
            ui->lineEdit_ID->setDisabled(1);
            ui->lineEdit_Name->setDisabled(1);
            ui->lineEdit_Quantity->setDisabled(1);
            ui->lineEdit_SP->setDisabled(1);
            ui->pushButton_Update->setDisabled(1);
            on_searchButton_textChanged(ui->searchButton->text());
            ID=ui->lineEdit_ID->text();
            connector.db.close();
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
}

void partstore::on_pushButton_add_clicked()
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connect "<<connector.db.lastError();
        return;
    }
    else
    {
        QSqlQuery *query=new QSqlQuery(connector.db);
        query->prepare("INSERT INTO partstock (ID,DateAdded,Quantity) VALUES (?,?,?)");
        query->addBindValue(ID);
        query->addBindValue(ui->lineEdit_date->text());
        query->addBindValue(ui->lineEdit_newQuantity->text());

        if(!query->exec())
        {
            QMessageBox msg;
            msg.setText("ADD Failed");
            msg.exec();
        }
        else
        {
            ui->lineEdit_date->setEnabled(0);
            ui->lineEdit_date->clear();
            ui->lineEdit_newQuantity->clear();
            ui->lineEdit_newQuantity->setEnabled(0);
            ui->pushButton_add->setEnabled(0);
            ui->pushButton_newEdit->setEnabled(1);
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
    model->setFilter("ID='"+ID+"'");
    model->select();
    qDebug()<<model->lastError().text();
    ui->tableView_Detail->setModel(model);
}
