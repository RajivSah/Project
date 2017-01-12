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
    effect->setOffset(5,5);
    effect->setColor(Qt::gray);
    ui->groupBox->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect2= new QGraphicsDropShadowEffect();

    effect2->setBlurRadius(5);
    effect2->setOffset(5,5);
    effect2->setColor(Qt::gray);

    ui->groupBox_2->setGraphicsEffect(effect2);

    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect();

    effect3->setBlurRadius(5);
    effect3->setOffset(5,5);
    effect3->setColor(Qt::gray);

    ui->groupBox_3->setGraphicsEffect(effect3);

    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect();

    effect4->setBlurRadius(5);
    effect4->setOffset(5,5);
    effect4->setColor(Qt::gray);

    ui->groupBox_4->setGraphicsEffect(effect4);

    QGraphicsDropShadowEffect *effect5 = new QGraphicsDropShadowEffect();

    effect5->setBlurRadius(5);
    effect5->setOffset(5,5);
    effect5->setColor(Qt::gray);

    ui->tableView->setGraphicsEffect(effect5);

    QGraphicsDropShadowEffect *effect6 = new QGraphicsDropShadowEffect();

    effect6->setBlurRadius(5);
    effect6->setOffset(5,5);
    effect6->setColor(Qt::gray);

    ui->tableView_2->setGraphicsEffect(effect6);

    QGraphicsDropShadowEffect *effect7 = new QGraphicsDropShadowEffect();

    effect7->setBlurRadius(5);
    effect7->setOffset(5,5);
    effect7->setColor(Qt::gray);

    ui->tableView_3->setGraphicsEffect(effect7);



}
void hrwindow::setSizes()
{
    QRect screenSize =QApplication::desktop()->availableGeometry();

    qDebug()<<screenSize;
    this->setFixedSize(screenSize.width()+10,screenSize.height()*0.96);


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

void hrwindow::searchFunction(QString keyword)
{
    qDebug() << keyword;
    QSqlQueryModel *qmodel=new QSqlQueryModel();


    qmodel->setQuery("SELECT *from employee_table where NAME like '%"+keyword+"%'");
    ui->tableView->setModel(qmodel);










}




void hrwindow::on_AddButton_clicked()
{
    if(!connector.db.open())
    {
        qDebug()<<"cannot connect";
                  return;
    }
    QSqlQuery *insertQuery=new QSqlQuery();
    insertQuery->prepare("INSERT INTO employeetable (`firstName`,`lastName` ,`contact`, `gender`, `addressArea` ,`addressCity`, `addressDistrict`, `salary` ,`post`, `dob` ,`status`, `quallification` )" "VALUES (?, ?, ?, ?, ?, ?,?, ?, ?, ?, ?, ?"
                         ")");
    insertQuery->addBindValue(ui->firstName->text());
    insertQuery->addBindValue(ui->lastName->text());
    insertQuery->addBindValue(ui->contact->text().toInt());
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

    model->setQuery("SELECT id,firstname,lastname,post FROM employeetable WHERE firstname LIKE '%"+arg1+"%'");
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
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
        QModelIndex index1=model->index(index.row(),0);
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
//            ui->firstNameSearch->setText(query.value(1).toString());

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

}
