#include "sales.h"
#include "ui_sales.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QAbstractItemModel>
#include "databasestructure.h"

int customerID;

sales::sales(bool adminMode, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sales)
{
    ui->setupUi(this);
    //This is for loading sales related users / staffs recorded in the database

    this->showMaximized();
    setValidator();

        ui->customerTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        if(adminMode==1)
        {
            adminView();
        }


        if(connector.db.open())
        {
            QSqlQuery *qryForCombo=new QSqlQuery(connector.db);
            qryForCombo->exec("select name from employeetable where status=1 ");
            //ui->soldByCombo->setCurrentText("Others");
            ui->soldByCombo->addItem("Others");
            while (qryForCombo->next())
            {
                ui->soldByCombo->addItem(qryForCombo->value(0).toString());

            }
            //ui->soldByCombo->addItem("None");

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

    if(ui->customerName->text()!="" && ui->vrn->text()!="" && ui->model->text()!="")
    {
        ui->addUserErrorMsg->setText("");
        if(connector.db.open())
        {
            QSqlQuery *qryToInsert=new QSqlQuery(connector.db);

            qryToInsert->prepare("INSERT INTO tbl_customer(VRN,model,VIN,customerName,contactNumber,driverContact,soldBy,soldDate,LoC,deliveryDate) VALUES(:vrn,:model,:vin,:customerName,:contactNo,:driver,:soldBy,:date,:loc,:delivery)");
            qryToInsert->bindValue(":vrn",ui->vrn->text());
            qryToInsert->bindValue(":vin",ui->vin->text());
            qryToInsert->bindValue(":model",ui->model->text());
            qryToInsert->bindValue(":customerName",ui->customerName->text());
            qryToInsert->bindValue(":contactNo",ui->contactNo->text());
            qryToInsert->bindValue(":driver",ui->driverNameContact->text());
            qryToInsert->bindValue(":soldBy",ui->soldByCombo->currentText());
            qryToInsert->bindValue(":date",ui->dateOfSale->text());
            qryToInsert->bindValue(":loc",ui->Loc->text());
            qryToInsert->bindValue(":delivery",ui->deliveryDate->text());
                if(qryToInsert->exec())
                    qDebug()<<"Data Inserted successfully";
                else
                    qDebug()<<qryToInsert->lastError();

            connector.db.close();
            connector.db.removeDatabase("QMYSQL");
            on_ClearButton_clicked();
            ui->statusbar->showMessage("Added Successfully");
        }

        else
            qDebug()<<connector.db.lastError();
    }
    else
    {
        qDebug()<<"Customer Name and VRN is must!";
        ui->addUserErrorMsg->setText("Customer name, VRN and Model are required ");
    }

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
    ui->deliveryDate->clear();
    ui->Loc->clear();

}






void sales::on_SearchButton_textChanged(const QString &arg1)
{

    if(connector.db.open())
    {
        qDebug()<<"Connected";
        QSqlQueryModel *model=new QSqlQueryModel();

        model->setQuery("SELECT customerID,VRN,model,customerName FROM tbl_customer WHERE VRN LIKE '%"+arg1+"%' OR model LIKE '%"+arg1+"%' OR customerName LIKE '%"+arg1+"%'",connector.db);
        ui->customerTableView->setModel(model);
        ui->customerTableView->hideColumn(0);
        for (int c = 0; c < ui->customerTableView->horizontalHeader()->count(); ++c)
        {
            ui->customerTableView->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }

    }
}


void sales::on_customerTableView_clicked(const QModelIndex &index)
{
    if(!connector.db.open())
    {
        qDebug()<<"Cannot connect to database";
        return;
    }

    QSqlQuery *query=new QSqlQuery(connector.db);
    query->prepare("SELECT * FROM tbl_customer WHERE customerID=:id");
    query->bindValue(":id",index.sibling(index.row(),0).data().toString());
    if(query->exec())
    {
        query->next(); //This is to set the pointer to the selected row
        customerID=index.sibling(index.row(),0).data().toInt();
        ui->vrnSearched->setText(query->value("VRN").toString());
        ui->modelSearched->setText(query->value("model").toString());
        ui->vinSearched->setText(query->value("VIN").toString());
        ui->customerNameSearched->setText(query->value("customerName").toString());

        ui->contactNoSearched->setText(query->value("contactNumber").toString());
        ui->driverNameContactSearched->setText(query->value("driverContact").toString());

        QString soldBy=query->value("soldBy").toString();
        ui->soldByComboSearched->clear();
        QSqlQuery *qryForCombo=new QSqlQuery(connector.db);
        qryForCombo->exec("select name from employeetable where status=1 ");
        ui->soldByComboSearched->addItem("Others");
        while (qryForCombo->next())
        {
            ui->soldByComboSearched->addItem(qryForCombo->value(0).toString());

        }
        ui->soldByComboSearched->setCurrentText(soldBy);
        ui->dateOfSaleSearched->setText(query->value("soldDate").toString());
        ui->LoCSearched->setText(query->value("LoC").toString());
        ui->deliveryDateSearched->setText(query->value("deliveryDate").toString());

        connector.db.close();
    }





}

void sales::on_updateBtn_clicked()
{
    if(!connector.db.open())
    {
        qDebug("failed to open database");
        return;
    }
    QSqlQuery *updateQuery=new QSqlQuery(connector.db);
    updateQuery->prepare("UPDATE tbl_customer SET VRN=:vrn, model=:model,VIN=:vin, customerName=:customerName,contactNumber=:contact,driverContact=:driver,soldDate=:date ,soldBy=:soldBy ,LoC=:loc, deliveryDate=:delivery WHERE customerID=:id");
    updateQuery->bindValue(":vrn",ui->vrnSearched->text());
    updateQuery->bindValue(":model",ui->modelSearched->text());
    updateQuery->bindValue(":vin",ui->vinSearched->text());
    updateQuery->bindValue(":customerName",ui->customerNameSearched->text());
    updateQuery->bindValue(":contact",ui->contactNoSearched->text());
    updateQuery->bindValue(":driver",ui->driverNameContactSearched->text());
    updateQuery->bindValue(":id",customerID);
    updateQuery->bindValue(":date",ui->dateOfSaleSearched->text());
    updateQuery->bindValue(":soldBy",ui->soldByComboSearched->currentText());
    updateQuery->bindValue(":loc",ui->LoCSearched->text());
    updateQuery->bindValue(":delivery",ui->deliveryDateSearched->text());
    if(updateQuery->exec())
    {
        qDebug()<<"Updated";
        ui->statusbar->showMessage("Updated Successfully");
        on_SearchButton_textChanged(ui->SearchButton->text());
    }
    else
    {
        ui->statusbar->showMessage("Update Failed");
        qDebug()<<"Error "<<updateQuery->lastError();
    }
    connector.db.close();


}

void sales::on_removeBtn_clicked()
{
    if(!connector.db.open())
    {
        qDebug("failed to open database");
        return;
    }
    QSqlQuery *removeQuery=new QSqlQuery(connector.db);
    removeQuery->prepare("DELETE FROM tbl_customer WHERE customerID=:id");

    removeQuery->bindValue(":id",customerID);

    if(removeQuery->exec())
    {
        qDebug()<<"Removed";
        on_SearchButton_textChanged(ui->SearchButton->text());
        ui->statusbar->showMessage("Removed Successfully");
        on_SearchButton_textChanged(ui->SearchButton->text());
        clearSearch();
    }else
    {   ui->statusbar->showMessage("Failed to Removed Data");
        qDebug()<<removeQuery->lastError();
    }
    connector.db.close();
}
void sales::adminView()
{
    ui->tabWidget->removeTab(0);
    ui->removeBtn->setDisabled(1);
    ui->updateBtn->setEnabled(0);
}

void sales::setValidator()
{
    QRegExp exp("[0-9]{5,10}");//number
    QRegExp name("[a-z A-Z]{0,30}");//text only
    QRegExp exp4("[0-9]{4}-[0-9]{2}-[0-9]{2}");//date yyyy-mm-dd
    QRegExp varchar("[a-z A-Z 0-9]{0,30}");//varchar
    ui->dateOfSale->setValidator(new QRegExpValidator(exp4));
    ui->dateOfSaleSearched->setValidator(new QRegExpValidator(exp4));
    ui->deliveryDate->setValidator(new QRegExpValidator(exp4));
    ui->deliveryDateSearched->setValidator(new QRegExpValidator(exp4));

    ui->contactNo->setValidator(new QRegExpValidator(exp));
    ui->contactNoSearched->setValidator(new QRegExpValidator(exp));

    ui->customerName->setValidator(new QRegExpValidator(name));
    ui->customerNameSearched->setValidator(new QRegExpValidator(name));

    ui->driverNameContact->setValidator(new QRegExpValidator(varchar));
    ui->driverNameContactSearched->setValidator(new QRegExpValidator(varchar));
    ui->vin->setValidator(new QRegExpValidator(varchar));
    ui->vinSearched->setValidator(new QRegExpValidator(varchar));
    ui->vrn->setValidator(new QRegExpValidator(varchar));
    ui->vrnSearched->setValidator(new QRegExpValidator(varchar));
    ui->Loc->setValidator(new QRegExpValidator(varchar));
    ui->LoCSearched->setValidator(new QRegExpValidator(varchar));


}

void sales::clearSearch()
{
    ui->customerNameSearched->clear();
    ui->contactNoSearched->clear();
    ui->vrnSearched->clear();
    ui->vinSearched->clear();
    ui->driverNameContactSearched->clear();
    ui->modelSearched->clear();
    ui->soldByComboSearched->clear();
    ui->dateOfSaleSearched->clear();
    ui->LoCSearched->clear();
    ui->deliveryDateSearched->clear();
}


void sales::on_addModel_clicked()
{
    if(ui->newModelName->text()!=""){
        if(connector.db.open()){
            QSqlQuery *addModelQuery=new QSqlQuery(connector.db);
            addModelQuery->prepare("insert into carmodel(model) VALUES (:model)");
            addModelQuery->bindValue(":model",ui->newModelName->text());
            if(!addModelQuery->exec()){
                ui->statusbar->showMessage("Cannot add to the database");

            }
            else
            {
                ui->newModelName->clear();
            }

        }


    }

}

void sales::on_searchButton_textChanged(const QString &arg1)
{
    if(connector.db.open())
    {
        qDebug()<<"Connected";
        QSqlQueryModel *model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM carmodel WHERE model LIKE '%"+arg1+"%'",connector.db);
        ui->tableViewModel->setModel(model);
        ui->tableViewModel->hideColumn(0);
        ui->tableViewModel->setSelectionBehavior(QAbstractItemView::SelectRows);
        for (int c = 0; c < ui->tableViewModel->horizontalHeader()->count(); ++c)
        {
            ui->tableViewModel->horizontalHeader()->setSectionResizeMode(
                c, QHeaderView::Stretch);
        }

    }

}

void sales::on_tableViewModel_clicked(const QModelIndex &index)
{
    if(!connector.db.open())
    {
        qDebug()<<"Cannot connect to database";
        return;
    }
        ui->modelName->setText(index.sibling(index.row(),1).data().toString());
        ui->totalQuantity->setText(index.sibling(index.row(),2).data().toString());



}
