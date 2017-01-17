#include "partstore.h"
#include "ui_partstore.h"
#include "addparts.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>

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

}

void partstore::on_pushButton_Edit_clicked()
{
    ui->lineEdit_Name->setEnabled(1);
    ui->lineEdit_ID->setEnabled(1);
    ui->lineEdit_Quantity->setEnabled(1);
    ui->lineEdit_SP->setEnabled(1);
    prevID=ui->lineEdit_ID->text();
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

        if(!query->exec())
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
            on_searchButton_textChanged(ui->searchButton->text());
            connector.db.close();
        }
    }

}
