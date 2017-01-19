#include "partstore.h"
#include "ui_partstore.h"
#include "addparts.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>
#include <QDate>
#include <QSqlTableModel>
#include <QGraphicsDropShadowEffect>
partstore::partstore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::partstore)
{
    ui->setupUi(this);
    setValidator();
    setInitials();
    addGraphicsEffect();
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
        for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
        {
            ui->tableView->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }
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
    ui->lineEdit_date->setText(QDate::currentDate().toString("yyyy/MM/dd"));
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

    if(!connector.db.open())
    {
        displayMessage("Cannot connect");
        return;
    }
    QSqlTableModel *model=new QSqlTableModel(nullptr,connector.db);
    model->setTable("partstock");
    model->setFilter("ID='"+prevID+"'");
    model->select();
    model->setSort(1,Qt::DescendingOrder);

    ui->tableView_Detail->setModel(model);
    ui->tableView_Detail->hideColumn(0);
    ui->tableView_Detail->hideColumn(3);
    for (int c = 0; c < ui->tableView_Detail->horizontalHeader()->count(); ++c)
    {
        ui->tableView_Detail->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
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
    ui->pushButton_add->setEnabled(!x);
    ui->pushButton_Update->setEnabled(!x);
    ui->lineEdit_Name->setEnabled(0);
    ui->lineEdit_ID->setEnabled(0);
    ui->lineEdit_Quantity->setEnabled(0);
    ui->lineEdit_SP->setEnabled(0);
    ui->pushButton_Update->setEnabled(0);
    ui->lineEdit_date->setEnabled(0);
    ui->lineEdit_newQuantity->setEnabled(0);
    ui->pushButton_add->setEnabled(0);
    ui->pushButton_2->setEnabled(0);


}
void partstore::setValidator()
{
    QRegExp exp("[a-z A-Z 0,9]{0,20}");
    QRegExp exp2("[a-z A-Z]{0,20}");
    QRegExp exp3("[0-9]{0,9}");

    ui->searchButton->setValidator(new QRegExpValidator(exp));
    ui->lineEdit_ID->setValidator(new QRegExpValidator(exp));
    ui->lineEdit_Quantity->setValidator(new QRegExpValidator(exp3));
    ui->lineEdit_newQuantity->setValidator(new QRegExpValidator(exp3));
    ui->lineEdit_SP->setValidator(new QRegExpValidator(exp3));
    ui->lineEdit_Name->setValidator(new QRegExpValidator(exp));
    ui->lineEdit_ID->setValidator(new QRegExpValidator(exp));
}

void partstore::setInitials()
{
    ui->tableView->setAlternatingRowColors(1);

}
void partstore::addGraphicsEffect()
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setBlurRadius(5);
    effect->setOffset(0,0);
    effect->setColor(Qt::gray);
    ui->groupBox_2->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect();

    effect2->setBlurRadius(5);
    effect2->setOffset(0,0);
    effect2->setColor(Qt::gray);
    ui->tableView->setGraphicsEffect(effect2);

    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect();

    effect3->setBlurRadius(5);
    effect3->setOffset(0,0);
    effect3->setColor(Qt::gray);
    ui->searchButton->setGraphicsEffect(effect3);
}

void partstore::on_showallpushButton_3_clicked()
{
    if(!connector.db.open())
    {
        displayMessage("Cannot connect: Try again Later ");
//        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM partstore ",connector.db);
        ui->tableView->setModel(model);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->hideColumn(3);
        for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
        {
            ui->tableView->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }
//      qDebug()<<connector.db.lastError();

    connector.db.close();
    }
}

void partstore::on_removerecordspushButton_5_clicked()
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
            query->prepare("DELETE FROM partstore where ID = :PrevID");
            query->addBindValue( prevID );
            if( !query->exec() )
            {
                throw 1;
            }
            QSqlQuery *query2=new QSqlQuery(connector.db);
            query2->prepare("DELETE FROM partstock where ID = :PrevID");
            query2->addBindValue(prevID);
            if(!query2->exec())
            {
                throw 1;
            }

             if(!connector.db.commit())
             {
                 displayMessage("Deletion Failed");
             }
             ui->statusbar->showMessage("Deletion Successfull");
             update_tableView_Detail();
        }
        catch (int)
        {
           displayMessage("cannot connect :Try again later");
           ui->statusbar->showMessage("Update Failed");
           connector.db.rollback();
        }

        connector.db.close();
    }
    on_showallpushButton_3_clicked();

}

void partstore::on_removeentrypushButton_4_clicked()
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
        query->prepare("DELETE FROM partstock where pid = :Pid");
        query->addBindValue(pid);
        if(!query->exec())
        {

        }
        else
        {
            update_tableView_Detail();
            displayMessage("Stock successfully removed" );
        }

    }
}

void partstore::on_tableView_Detail_clicked(const QModelIndex &index)
{
     pid = index.sibling(index.row(),3).data().toInt();

}
