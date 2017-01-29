#include "admin.h"
#include "ui_admin.h"
#include <QSqlTableModel>
#include <QSqlQuery>


Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);


}

Admin::~Admin()
{
    delete ui;
}
void Admin::chooseDepartment()
{
    QString Department =ui->comboBox->currentText();
    qDebug()<<Department;
    if(Department=="Human Resources")
    {
        hrwindow *hr=new hrwindow(1);
        hr->show();

    }
    else if(Department=="Sales")
    {

    }
    else if (Department=="Workshop")
    {
        workshop *work=new workshop(1);
        work->show();
     }
    else if (Department=="Parts Store")
    {
        partstore *parts=new partstore(1);
        parts->show();
    }
    else if(Department=="Parts Processing")
    {
        partspro *pro=new partspro(1);
        pro->show();
    }
    else
    {
        qDebug()<<"nowhere";
    }


}


void Admin::on_okPushButton_clicked()
{

    chooseDepartment();

}

void Admin::on_tabWidget_tabBarClicked(int index)
{
    if(!connector.db.open())
    {
        return;
    }
    QSqlTableModel *model=new QSqlTableModel(nullptr,connector.db);
    model->setTable("login");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(2);

    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void Admin::on_addPushButton_clicked()
{
    if(!connector.db.open())
    {
        displayMessage("Cannot Add");
        return;
    }
    else
    {
        qDebug()<<"Inside query";
        if(!(ui->nameLineEdit->text()=="" || ui->passLineEdit->text()==""))
        {
        QSqlQuery *query=new QSqlQuery(connector.db);
        query->prepare("INSERT INTO login (Username,Password,Role) VALUES(?,?,?) ");
        query->addBindValue(ui->nameLineEdit->text());
        query->addBindValue(ui->passLineEdit->text());
        query->addBindValue(ui->roleComboBox->currentText());
        query->exec();

        connector.db.close();
        }
        else
        {
            displayMessage("Username or Password cannot be Empty");
        }
    }
}
void Admin::displayMessage(QString msg)
{
    message.setText(msg);
    message.exec();
}

void Admin::on_removePushButton_clicked()
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
        query->prepare("DELETE FROM login where id = :Pid");
        query->addBindValue(pid);
        if(!query->exec())
        {

        }
        else
        {
            on_tabWidget_tabBarClicked(1);
            displayMessage("User successfully removed" );
            connector.db.close();
        }

    }
}

void Admin::on_tableView_clicked(const QModelIndex &index)
{
    pid=index.sibling(index.row(),2).data().toInt();
}
