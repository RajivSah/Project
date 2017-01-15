#include "workshop.h"
#include "ui_workshop.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <dbconnection.h>
DBCONNECTION d;

workshop::workshop(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workshop)
{
    ui->setupUi(this);

    setInitials();
}

workshop::~workshop()
{
    delete ui;
}


void workshop::setSizes()
{
    QRect screenSize =QApplication::desktop()->availableGeometry();

    qDebug()<<screenSize;
    this->setFixedSize(screenSize.width()+10,screenSize.height()*0.96);


}

void workshop::setInitials()
{
    qDebug() << "Hello World";
    setSizes();

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setBlurRadius(5);
    effect->setOffset(5,5);
    effect->setColor(Qt::gray);

    ui->groupBox->setGraphicsEffect(effect);


    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect();

    effect1->setBlurRadius(5);
    effect1->setOffset(5,5);
    effect1->setColor(Qt::gray);


    ui->Search_lineEdit->setGraphicsEffect(effect1);

    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect();

    effect2->setBlurRadius(5);
    effect2->setOffset(5,5);
    effect2->setColor(Qt::gray);


   // ui->tableView->setGraphicsEffect(effect2);

    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);



}

void workshop::on_Search_lineEdit_textChanged(const QString &arg1)
{
    qDebug() << "Text Changed" ;

    searchItem = ui->Search_lineEdit->text();


bool check = d.db.open();
    if(!check)
    {
        qDebug() <<"cannot connect";
                  return;
    }

    else
        qDebug() <<"Database opened";


    model = new QSqlQueryModel();
   query = new QSqlQuery();
    if(searchItem.length()>0 )

    query->prepare("select * from tbl_name where VRN like '%"+searchItem+"%' or Model like '%"+searchItem+"%' or CustomerName like '%"+searchItem+"%' ");
   else
    query->prepare("select * from tbl_name   ");


    query->exec();


    model->setQuery(*query);
    ui->tableView->setModel(model);
    qDebug()<< ( model->rowCount());
    d.db.close();

}

void workshop::on_tableView_clicked(const QModelIndex &index)
{







 QString VRN = (index.sibling( index.row(), 0).data().toString() );
 QString Model = (index.sibling( index.row(), 1).data().toString() );
 QString VIN = (index.sibling( index.row(), 2).data().toString() );
QString CuNo = (index.sibling( index.row(), 3).data().toString() );
 QString MoNo= (index.sibling( index.row(), 4).data().toString() );

 QString DrCo = (index.sibling( index.row(), 5).data().toString() );
 QDate Date = (index.sibling( index.row(), 6).data().toDate() );
 QString Date1 = Date.toString();
 QString Jorder = (index.sibling( index.row(), 7).data().toString() );
 QString Jdone = (index.sibling( index.row(), 8).data().toString() );

ui->VRN_lineEdit->setText( VRN );
ui->Model_lineEdit->setText( Model );
ui->VIN_lineEdit->setText( VIN );
ui->CustomerName_lineEdit->setText( CuNo );
ui->CMobileno_lineEdit->setText( MoNo );

ui->drivercontact_lineEdit->setText( DrCo );
ui->templineEdit->setText( Date1 );
//ui->dateCombobox->setItemText( 0,Date1 );
ui->Joborder_lineEdit->setText( Jorder );
ui->Jobdone_textEdit_2->insertPlainText(Jdone );



}

void workshop::getData()
{
    VRN = ui->VRN_lineEdit->text();
    Model = ui->Model_lineEdit->text();
    VIN = ui->VIN_lineEdit->text();
    CuNo = ui->CustomerName_lineEdit->text();
    MoNo = ui->CMobileno_lineEdit->text();
    DrCo= ui->drivercontact_lineEdit->text(  );
    Date1= ui->templineEdit->text();
    //ui->dateCombobox->setItemText( 0,Date1 );
    Jorder=ui->Joborder_lineEdit->toPlainText();
    Jdone= ui->Jobdone_textEdit_2->toPlainText();
}

void workshop::on_Add_clicked()
{
   getData();

    qDebug()<<(VRN);

      if( ( VRN != "") && (Date1 != "") )
     {

          if(!d.db.open())
          {
              qDebug()<<"cannot connect";
                        return;
          }

      query = new QSqlQuery(d.db);//
      query->prepare("INSERT INTO tbl_name ( VRN, Model , VIN , CustomerName, MobileNo,DriverContact, Date, Joborder, JobDone ) VALUES ( :VRN, :Model , :VIN , :CustomerName, :MobileNo, :DriverContact, :Date, :Joborder, :JobDone)");

      query->addBindValue(  VRN );
       query->addBindValue( Model );
        query->addBindValue(VIN );
        query->addBindValue( CuNo );
        query->addBindValue( MoNo );
        query->addBindValue( DrCo );
        query->addBindValue( Date1 );
        query->addBindValue(Jorder );
        query->addBindValue( Jdone );

      query->exec();
      qDebug() << (VRN)<<query->lastError();
      d.db.close();
      }
      else

       qDebug() <<"Error data not added";
}



void workshop::on_updatepush_clicked()
{
getData();
}

