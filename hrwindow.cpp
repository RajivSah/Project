#include "hrwindow.h"
#include "ui_hrwindow.h"
#include <QDebug>
#include "dbconnection.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QCalendarWidget>
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDesktopWidget>
#include <QStringList>

DBCONNECTION connector;
hrwindow::hrwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hrwindow)
{
    //
    ui->setupUi(this);

    setInitails();
    setInputValidator();



/*    if(connector.connect())
    {
        qDebug() << "Database Connected";
    }
    else
        qDebug() << "Database Error";
*/
//    connect(ui->searchButton, SIGNAL(textChanged(QString)), this, SLOT(searchFunction(QString)));
//    connect(ui->searchButton_2, SIGNAL(textChanged(QString)), this, SLOT(searchFunction(QString)));
//    connect(ui->searchButton_3, SIGNAL(textChanged(QString)), this, SLOT(searchFunction(QString)));





}
void hrwindow::setInitails()
{
    setSizes();
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    setCentralWidget(ui->tabWidget);


    QButtonGroup *statRadio=new QButtonGroup();
    statRadio->addButton(ui->activeRadio);
    statRadio->addButton(ui->inactiveRadio);



    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setBlurRadius(5);
    effect->setOffset(0,0);
    effect->setColor(Qt::gray);
    ui->groupBox->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect2= new QGraphicsDropShadowEffect();

    effect2->setBlurRadius(5);
    effect2->setOffset(0,0);
    effect2->setColor(Qt::gray);

    ui->groupBox_2->setGraphicsEffect(effect2);

    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect();

    effect3->setBlurRadius(5);
    effect3->setOffset(0,0);
    effect3->setColor(Qt::gray);

    ui->groupBox_3->setGraphicsEffect(effect3);

    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect();

    effect4->setBlurRadius(5);
    effect4->setOffset(0,0);
    effect4->setColor(Qt::gray);

    ui->groupBox_4->setGraphicsEffect(effect4);

    QGraphicsDropShadowEffect *effect5 = new QGraphicsDropShadowEffect();

    effect5->setBlurRadius(5);
    effect5->setOffset(0,0);
    effect5->setColor(Qt::gray);

    ui->tableView->setGraphicsEffect(effect5);

    QGraphicsDropShadowEffect *effect6 = new QGraphicsDropShadowEffect();

    effect6->setBlurRadius(5);
    effect6->setOffset(00);
    effect6->setColor(Qt::gray);

    ui->tableView_2->setGraphicsEffect(effect6);

    QGraphicsDropShadowEffect *effect7 = new QGraphicsDropShadowEffect();

    effect7->setBlurRadius(5);
    effect7->setOffset(0,0);
    effect7->setColor(Qt::gray);

    ui->tableView_3->setGraphicsEffect(effect7);



}
void hrwindow::setSizes()
{
    QRect screenSize =QApplication::desktop()->availableGeometry();

    qDebug()<<screenSize;



}

hrwindow::~hrwindow()
{
    delete ui;
}

//Select Add Tab
void hrwindow::search_user_Tab_select()
{
        // Dashboard to Search
        ui->tabWidget->setCurrentIndex(0);
}
void hrwindow::add_user_Tab_select()
{

        // Dashboard to Add
        ui->tabWidget->setCurrentIndex(1);
}
void hrwindow::edit_user_Tab_select()
{
        // Dashboard to Edit
        ui->tabWidget->setCurrentIndex(2);
}
void hrwindow::remove_user_Tab_select()
{
        // Dashboard to remove
        ui->tabWidget->setCurrentIndex(3);
}

void hrwindow::on_ClearButton_clicked()
{
    //Add Employee Clear Button
        ui->firstName->clear();
        ui->lastName->clear();
        ui->contact->clear();
        ui->maleRadio->setChecked(false);
        ui->femaleRadio->setChecked(false);
        ui->address1Edit->clear();
        ui->address2Edit->clear();
		ui->address3Edit->clear();
		ui->salaryEdit->clear();
		ui->qualificationInput->clear();
		ui->DOBEdit->clear();
        ui->activeRadio->setChecked(false);
        ui->inactiveRadio->setChecked(false);
        ui->ClearButton->clearFocus();
	
}






void hrwindow::on_AddButton_clicked()
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connect";
                  return;
    }
    QSqlQuery *insertQuery=new QSqlQuery();
    insertQuery->prepare("INSERT INTO employeetable (`name` ,`contact`, `gender`, `addressArea` ,`addressCity`, `addressDistrict`, `salary` ,`post`, `dob` ,`status`, `quallification` )" "VALUES ( ?, ?, ?, ?, ?,?, ?, ?, ?, ?, ?"
                         ")");
    insertQuery->addBindValue(ui->firstName->text()+" "+ui->lastName->text());

    insertQuery->addBindValue(ui->contact->text());
    qDebug()<<ui->contact->text();
    int gen;
    if(ui->maleRadio->isChecked())
        gen= 1;

    else
        gen=0;

    insertQuery->addBindValue(gen);
    insertQuery->addBindValue(ui->address1Edit->text());
    insertQuery->addBindValue(ui->address2Edit->text());
    insertQuery->addBindValue(ui->address3Edit->text());
    insertQuery->addBindValue(ui->salaryEdit->text().toInt());
    insertQuery->addBindValue(ui->comboBox->currentText());
    insertQuery->addBindValue(ui->DOBEdit->text());
    int status;
    if(ui->activeRadio->isChecked())
        status=1;

    else
       status =0;

    insertQuery->addBindValue(status);
    insertQuery->addBindValue(ui->qualificationInput->toPlainText());

    if(insertQuery->exec())
    {
        qDebug() << "Sucessfully Added to Database. ";
        ui->statusbar->showMessage("The Data has been added Successfully. ", 4000);
        connector.db.close();
        on_ClearButton_clicked();

    }

    else
       { qDebug() << "Error"<<connector.db.lastError();

    }

}



void hrwindow::on_searchButton_textChanged(const QString &arg1)
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {

    model->setQuery("SELECT id,Name,post,addressCity FROM employeetable WHERE Name LIKE '%"+arg1+"%' OR addressCity LIKE '%"+arg1+"%' OR post LIKE '%"+arg1+"%' OR addressArea LIKE '%"+arg1+"%'" );
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->setColumnWidth(1,ui->tableView->width()/3);
    ui->tableView->setColumnWidth(2,ui->tableView->width()/3);
    ui->tableView->setColumnWidth(3,ui->tableView->width()/3);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connector.db.close();
    }
  }

void hrwindow::on_tableView_clicked(const QModelIndex &index)
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {
        QModelIndex index1 = model->index(index.row(),0);
        int searchKey= index1.data().toInt();
        qDebug()<<searchKey;
        detailSearchResult(searchKey);


        connector.db.close();
    }



}
void hrwindow::detailSearchResult(int searchKey)
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM employeetable WHERE ID= ?");
        query.addBindValue(searchKey);
        if(query.exec())
        {

            query.next();
            QStringList list = query.value(1).toString().split(QRegExp("\\s+"), QString::SkipEmptyParts);
            ui->firstNameSearch->setText(list.at(0));

            ui->lastNameSearch->setText(list.at(1));
            ui->contactSearch->setText(query.value(2).toString());


            if(query.value(3).toBool())
            {   qDebug()<<query.value(3).toBool();
                ui->genderLineEdit->setText("Male");}
            else
                ui->genderLineEdit->setText("Female");

            ui->addressAreaSearch->setText(query.value(4).toString());
            ui->addresscitySearch->setText(query.value(5).toString());
            ui->addressDistrictSearch->setText(query.value(6).toString());
            ui->salaryEdit->setText(query.value(7).toString());
            ui->postSearch->setCurrentText(query.value(8).toString());

            if(query.value(9).toBool()==1)
                ui->activeRadioSearch->setChecked(1);
            else
                ui->inactiveRadioSearch->setChecked(1);

            ui->qualificationSeach->setText(query.value(10).toString());
            ui->DOBeditSearch->setText(query.value(11).toString());

            ui->statusbar->showMessage("seach sucessfull");
        }
        else
        {
            qDebug()<<"did not execute query";
        }

        connector.db.close();
    }
}

void hrwindow::setInputValidator()
{
    QRegExp regexp("[0-9]{0,10}");
    ui->contact->setValidator(new QRegExpValidator(regexp));
    QRegExp regexp1("[a-z A-Z]{0,30}");
    ui->firstName->setValidator(new QRegExpValidator(regexp1));
    ui->lastName->setValidator(new QRegExpValidator(regexp1));
    ui->address2Edit->setValidator(new QRegExpValidator(regexp1));
    ui->address3Edit->setValidator(new QRegExpValidator(regexp1));
    ui->salaryEdit->setValidator(new QRegExpValidator(regexp));


}

void hrwindow::on_searchButton_2_textChanged(const QString &arg1)
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {

    model->setQuery("SELECT id,Name,post,addressCity FROM employeetable WHERE Name LIKE '%"+arg1+"%' OR addressCity LIKE '%"+arg1+"%' OR post LIKE '%"+arg1+"%' OR addressArea LIKE '%"+arg1+"%'" );
    ui->tableView_2->setModel(model);
    ui->tableView_2->hideColumn(0);
    ui->tableView_2->setColumnWidth(1,ui->tableView->width()/3);
    ui->tableView_2->setColumnWidth(2,ui->tableView->width()/3);
    ui->tableView_2->setColumnWidth(3,ui->tableView->width()/3);
    ui->tableView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    connector.db.close();
    }
}

void hrwindow::on_tableView_2_clicked(const QModelIndex &index)
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connet "<<connector.db.lastError();
        return;
    }
    else
    {
        QModelIndex index1 = model->index(index.row(),0);
        int searchKey= index1.data().toInt();
        qDebug()<<searchKey;


        QSqlQuery query;
        query.prepare("SELECT * FROM employeetable WHERE ID= ?");
        query.addBindValue(searchKey);
        if(query.exec())
        {

            query.next();
            QStringList list = query.value(1).toString().split(QRegExp("\\s+"), QString::SkipEmptyParts);
            ui->firstNameEdit->setText(list.at(0));

            ui->lastNameEdit->setText(list.at(1));
            ui->contactEdit->setText(query.value(2).toString());


            if(query.value(3).toBool())
            {   qDebug()<<query.value(3).toBool();
                ui->maleRadioEdit->setChecked(1);}
            else
                ui->femaleRadioEdit->setChecked(1);

            ui->addressAreaEdit->setText(query.value(4).toString());
            ui->addressCityedit->setText(query.value(5).toString());
            ui->addressDistrictEdit->setText(query.value(6).toString());
            ui->salaryEdit->setText(query.value(7).toString());
            ui->postEdit->setCurrentText(query.value(8).toString());

            if(query.value(9).toBool()==1)
                ui->activeRadioEdit->setChecked(1);
            else
                ui->inactiveRadioEdit->setChecked(1);

            ui->qualificationInputEdit->setText(query.value(10).toString());
            ui->DOBEdit_Edit->setText(query.value(11).toString());
        }
        else
        {
            qDebug()<<"did not execute query";
        }


        connector.db.close();
    }


}
