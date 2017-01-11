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

DBCONNECTION connector;
hrwindow::hrwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hrwindow)
{
    //
    ui->setupUi(this);

    setInitails();




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
    ui->tableView->setAlternatingRowColors(true);

    setCentralWidget(ui->tabWidget);
     setFixedSize(1024, 640);
    // Makes Tab Transparent
    ui->tabWidget->setDocumentMode(true);
    //Used in Add New Employee
    ui->groupBox->setFixedSize(905, 470);
    //
    QButtonGroup *statRadio=new QButtonGroup();
    statRadio->addButton(ui->radioButton_3);
    statRadio->addButton(ui->radioButton_4);



    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setBlurRadius(5);
    effect->setOffset(5,5);
    effect->setColor(Qt::gray);
    ui->groupBox->setGraphicsEffect(effect);
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect();

    effect2->setBlurRadius(5);
    effect2->setOffset(5,5);
    effect2->setColor(Qt::gray);

    ui->groupBox_2->setGraphicsEffect(effect2);



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
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);
        ui->address1Edit->clear();
        ui->address2Edit->clear();
		ui->address3Edit->clear();
		ui->salaryEdit->clear();
		ui->qualificationInput->clear();
		ui->DOBEdit->clear();
        ui->radioButton_3->setChecked(false);
        ui->radioButton_4->setChecked(false);
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
    QString name=ui->firstName->text();
    QString gender;

    name.append(" ");
    name.append(ui->lastName->text());
    QSqlQuery *insertQuery=new QSqlQuery();
    insertQuery->prepare("INSERT INTO EMPLOYEE_TABLE (`Name`, `Contact`, `Gender`, `Address`, `Salary`, `Post`, `Qualification`, `DOB`, `Status`)" "VALUES (:name , :contact, :gender, :address, :salary, :post, :qualification, :dob, :status)");

    if(ui->radioButton->isChecked())
        gender=ui->radioButton->text();

    else
        gender=ui->radioButton_2->text();



    insertQuery->bindValue(":name", name);
    insertQuery->bindValue(":contact", ui->contact->text());

    if(ui->radioButton->isChecked())
        insertQuery->bindValue(":gender",ui->radioButton->text());

    else
        insertQuery->bindValue(":gender", ui->radioButton_2->text());

    QString address=ui->address1Edit->text();
    address.append(", ");
    address.append(ui->address2Edit->text());
    address.append(", ");
    address.append(ui->address3Edit->text());
    insertQuery->bindValue(":address", address);

    insertQuery->bindValue(":salary", ui->salaryEdit->text());
    insertQuery->bindValue(":post", ui->comboBox->currentText());
    insertQuery->bindValue(":qualification", ui->qualificationInput->toPlainText());
    insertQuery->bindValue(":dob", ui->DOBEdit->text());

    if(ui->radioButton->isChecked())
        insertQuery->bindValue(":status",ui->radioButton_3->text());

    else
        insertQuery->bindValue(":status", ui->radioButton_4->text());

    if(insertQuery->exec())
    {
        qDebug() << "Sucessfully Added to Database. ";
        ui->statusbar->showMessage("The Data has been added Successfully. ", 4000);

    }

    else
        qDebug() << "Error";















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
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee_table WHERE Username LIKE '%"+arg1+"%'");
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connector.db.close();
    }
  }

void hrwindow::on_tableView_clicked(const QModelIndex &index)
{

}
