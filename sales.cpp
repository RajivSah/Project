#include "sales.h"
#include "ui_sales.h"
#include "dbconnection.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>


sales::sales(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sales)
{
    ui->setupUi(this);
    //This is for loading sales related users / staffs recorded in the database

        DBCONNECTION connector;
        if(connector.db.open())
        {
            QSqlQuery qryForCombo;
            qryForCombo.exec("select username from login where userType='sales'");
            while (qryForCombo.next())
            {
                ui->soldByCombo->addItem(qryForCombo.value(0).toString());

            }
            connector.db.close();

         }
        else
            qDebug()<<connector.db.lastError();
//********************************************************************************************

//**********Loading current date in the "Sold date" field*******************
QDate date=QDate::currentDate();
ui->dateOfSale->setText(date.toString("yyyy-MM-dd"));

//**********************************************************************************************


}

sales::~sales()
{
    delete ui;
}

void sales::on_AddButton_clicked()
{
    DBCONNECTION connector;
    if(ui->customerName->text()!="" && ui->vrn->text()!="" && ui->model->text()!="")
    {
        if(connector.db.open())
        {
            QSqlQuery qryToInsert;

             qryToInsert.prepare("INSERT INTO tbl_customer(VRN,model,VIN,customerName,contactNumber,driverContact,soldBy,soldDate) VALUES(:vrn,:model,:vin,:customerName,:contact,:driver,soldBy,:date)");
            qryToInsert.bindValue("vrn",ui->vrn->text());
            qryToInsert.bindValue(":vin",ui->vin->text());
            qryToInsert.bindValue(":model",ui->model->text());
            qryToInsert.bindValue(":customerName",ui->customerName->text());
            qryToInsert.bindValue(":contact",ui->contactNo->text());
            qryToInsert.bindValue(":driver",ui->driverNameContact->text());
            qryToInsert.bindValue(":soldBy",ui->soldByCombo->currentText());
            qryToInsert.bindValue(":date",ui->dateOfSale->text());
                if(qryToInsert.exec())
                    qDebug()<<"Data Inserted successfully";
                else
                    qDebug()<<qryToInsert.lastError();

            connector.db.close();
            connector.db.removeDatabase("QMYSQL");

        }

        else
            qDebug()<<connector.db.lastError();
    }
    else
        qDebug()<<"Customer Name and VRN is must!";
}

void sales::on_ClearButton_clicked()
{
    ui->customerName->clear();
    ui->contactNo->clear();
    ui->vrn->clear();
    ui->vin->clear();
    ui->model->clear();
    ui->driverNameContact->clear();
    ui->dateOfSale->setText(QDate::currentDate().toString("yyyy-MM-dd"));

}






void sales::on_SearchButton_textChanged(const QString &arg1)
{
    DBCONNECTION connector;
    if(connector.db.open())
    {
        qDebug()<<"Connected";
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT VRN,model,customerName FROM tbl_customer WHERE VRN LIKE '%"+arg1+"%' OR model LIKE '%"+arg1+"%' OR customerName LIKE '%"+arg1+"%'");
        ui->customerTableView->setModel(model);

    }
}

