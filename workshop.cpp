#include "workshop.h"
#include "ui_workshop.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <dbconnection.h>
#include <QMessageBox>

workshop::workshop(bool adminMode, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workshop)
{
    this->showMaximized();
    ui->setupUi(this);
    if(adminMode == 1)
    {
        adminView();
    }
    setInitials();
}

workshop::~workshop()
{
    delete ui;
}


void workshop::setSizes()
{


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

void workshop::on_pushButton_clicked()
{

    refresh();
}


void workshop::refresh()
{
    model = new QSqlQueryModel();
    d.db.open();
    query = new QSqlQuery( d.db );
    query->prepare("select * from tbl_name order by Date desc ");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);
  //ui-> tableView->columnMoved(11, 11, 1);
    hideColumns();

    d.db.close();
    qDebug()<<( model->rowCount());
}

void workshop::refreshTable()
{
    searchItem = ui->Search_lineEdit->text();


model = new QSqlQueryModel();
    d.db.open();

   query = new QSqlQuery( d.db );
   if(searchItem.length()>0 )

    query->prepare("select * from tbl_name where VRN like '%"+searchItem+"%' or Model like '%"+searchItem+"%' or CustomerName like '%"+searchItem+"%' ORDER BY Date desc");
   else
    query->prepare("select * from tbl_name ORDER BY Date desc  ");

    query->exec();

    model->setQuery(*query);
    ui->tableView->setModel(model);
    hideColumns();

    qDebug()<<( model->rowCount());
    d.db.close();

}

void workshop::on_Search_lineEdit_textChanged(const QString &arg1)
{
    refreshTable();

}
void workshop::hideColumns()
{
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);



    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    ui->tableView->hideColumn(10);
    ui->tableView->hideColumn(11);
    ui->tableView->hideColumn(13);
    ui->tableView->hideColumn(14);

    ui->tableView->setColumnWidth(9, 200);
    ui->tableView->setColumnWidth(2, 150);

}


void workshop::on_tableView_clicked(const QModelIndex &index)
{

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::NoUpdate);

             Rid = (index.sibling( index.row(), 0).data().toInt() );
     QString VRN = (index.sibling( index.row(), 1).data().toString() );

     QString Model = (index.sibling( index.row(), 2).data().toString() );
     QString VIN = (index.sibling( index.row(), 3).data().toString() );
    QString VName = (index.sibling( index.row(), 4).data().toString() );
    QString VBrand = (index.sibling( index.row(), 5).data().toString() );
       QString MfdYear = (index.sibling( index.row(), 6).data().toString() );
     QString OdoReading = (index.sibling( index.row(), 7).data().toString() );
     QString Distance = (index.sibling( index.row(), 8).data().toString() );
       QString CuNo = (index.sibling( index.row(), 9).data().toString() );
     QString MoNo= (index.sibling( index.row(), 10).data().toString() );

     QString DrCo = (index.sibling( index.row(), 11).data().toString() );
     QString Date1 = (index.sibling( index.row(), 12).data().toString() );

     QString Jorder = (index.sibling( index.row(), 13).data().toString() );
     QString Jdone = (index.sibling( index.row(), 14).data().toString() );



    ui->VRN_lineEdit->setText( VRN );
    ui->Model_lineEdit->setText( Model );
    ui->VIN_lineEdit->setText( VIN );
    ui->VNamelineEdit->setText( VName );
    ui->MfdyrlineEdit->setText( MfdYear ) ;
    ui->OReadLineEdit->setText( OdoReading );

    ui->CustomerName_lineEdit->setText( CuNo );
    ui->CMobileno_lineEdit->setText( MoNo );
    ui->drivercontact_lineEdit->setText( DrCo );

    ui->templineEdit->setText( Date1 );

    ui->Joborder_lineEdit->setText(Jorder );
    ui->Jobdone_textEdit_2->setText(Jdone );

    //ui->Jobdone_textEdit_2->setText( );

    //search for those records with same VRN to get different dates
    d.db.open();
    QSqlQuery *query1 = new QSqlQuery(d.db);



    query1 -> prepare("SELECT *FROM tbl_name WHERE VRN = :VRN ORDER BY DATE desc");
    query1 ->addBindValue(VRN);
    query1 -> exec();

    QSqlQueryModel *model1= new QSqlQueryModel();

    model1 ->setQuery( *query1 );
    ui->tableView->setModel( model1 );
    //QModelIndex index1 = ui->tableView->currentIndex();

    //ui->tableView->selectionModel()->select( newIndex, QItemSelectionModel::Select);
    //
    //ui->tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::NoUpdate);


    changeBoxItems();

    ui->dateCombobox->setCurrentText(Date1);
    ui->VBrandCombobox->clear();
    ui->VBrandCombobox->addItem("Mitsubishi");
    ui->VBrandCombobox->addItem("Others");
    ui->VBrandCombobox->setCurrentText( VBrand );
    //
    ui->distancecomboBox->clear();
    ui->distancecomboBox->addItem("KM");
    ui->distancecomboBox->addItem("Miles");
    ui->distancecomboBox->setCurrentText( Distance );


}

void workshop::changeBoxItems()
{
    QModelIndex newIndex = ui->tableView->model()->index(0,12);
    //ui->tableView->setCurrentIndex(newIndex);

    QString Date2 = (newIndex.sibling( newIndex.row(), 12).data().toString() );


    int row = 0;
    ui->dateCombobox->clear();

    do{



    ui->dateCombobox->addItem(Date2);
    row++;
    newIndex = ui->tableView->model()->index(row,12);
    Date2 = (newIndex.sibling( newIndex.row(), 12).data().toString() );

    }while( Date2 != "");

}

void workshop::on_clearPush_clicked()
{

    ui->VRN_lineEdit->setText( "" );
    ui->Model_lineEdit->setText( "" );
    ui->VIN_lineEdit->setText( "" );
    ui->CustomerName_lineEdit->setText( "" );
    ui->CMobileno_lineEdit->setText( "" );
    ui->VNamelineEdit->setText( "" );
    ui->MfdyrlineEdit->setText( "") ;
    ui->OReadLineEdit->setText( "" );

    ui->drivercontact_lineEdit->setText( "" );
    ui->templineEdit->setText( "" );
    //ui->dateCombobox->setItemText( 0,Date1 );
    ui->Joborder_lineEdit->setText( "" );
    ui->Jobdone_textEdit_2->setText( "" );
}

void workshop::getData()
{
    VRN = ui->VRN_lineEdit->text();
       Model = ui->Model_lineEdit->text();
       VIN = ui->VIN_lineEdit->text();
       VName = ui->VNamelineEdit->text();

       VBrand = ui->VBrandCombobox->currentText();

       MfdYear = ui->MfdyrlineEdit->text();
       OdoReading = ui->OReadLineEdit->text();
       CuNo = ui->CustomerName_lineEdit->text();
       MoNo = ui->CMobileno_lineEdit->text();
       DrCo= ui->drivercontact_lineEdit->text(  );
       Date1= ui->templineEdit->text(  );
       Distance = ui->distancecomboBox->currentText();
       //ui->dateCombobox->setItemText( 0,Date1 );
       Jorder=ui->Joborder_lineEdit->toPlainText(  );
       Jdone= ui->Jobdone_textEdit_2->toPlainText();
}

void workshop::on_Add_clicked()
{
    QMessageBox::StandardButton reply;
              reply = QMessageBox::question(this, "Confirm", "Are you sure?",
                                            QMessageBox::Yes|QMessageBox::No);
              if( reply == QMessageBox::Yes )
              {
    getData();

     qDebug()<<(VRN);
       if( ( VRN != "") && (Date1 != "") )
      {
           d.db.open();
       query = new QSqlQuery(d.db);//
       query->prepare("INSERT INTO tbl_name ( VRN, Model , VIN, VehicleName, VehicleBrand ,MfdYear, OdometerReading,Distance, CustomerName, MobileNo,DriverContact, Date, Joborder, JobDone ) VALUES ( :VRN, :Model , :VIN , :VehicleName, :VehicleBrand ,:MfdYear, :OdometerReading , :Distance,:CustomerName, :MobileNo, :DriverContact, :Date, :Joborder, :JobDone)");

       query->addBindValue(  VRN );
        query->addBindValue( Model );
         query->addBindValue( VIN );
         query->addBindValue( VName );
         query->addBindValue( VBrand );
         query->addBindValue( MfdYear );
         query->addBindValue( OdoReading );
         query->addBindValue( Distance );
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
       ui->Search_lineEdit->setText( "" );

        ui->Search_lineEdit->setText( VRN );

 changeBoxItems();
}


}
void workshop::on_updatepush_clicked()
{
    QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Confirm", "Are you sure?",
                                       QMessageBox::Yes|QMessageBox::No);
         if( reply == QMessageBox::Yes )
         {
    getData();
    if( ( VRN != "") && (Date1 != "") )
    {




    d.db.open();
          query = new QSqlQuery(d.db);
          query->prepare("UPDATE tbl_name SET VRN=?, Model=? , VIN=? ,VehicleName =?, VehicleBrand=? ,MfdYear=?, OdometerReading=?, Distance=?, CustomerName=?, MobileNo=?,DriverContact=?,Date=?, Joborder=?, JobDone=? "
                       " WHERE RId = :Rid" );

          query->addBindValue(  VRN );
          query->addBindValue( Model );
          query->addBindValue(VIN );
          query->addBindValue( VName );
          query->addBindValue( VBrand );
          query->addBindValue( MfdYear );
          query->addBindValue( OdoReading );
          query->addBindValue( Distance );
          query->addBindValue( CuNo );
          query->addBindValue( MoNo );
          query->addBindValue( DrCo );
          query->addBindValue( Date1 );
          query->addBindValue(Jorder );
          query->addBindValue( Jdone );

          query->addBindValue( Rid );

        query->exec();
        qDebug() << (VRN)<<query->lastError();





    d.db.close();
    }

    d.db.open();
          query = new QSqlQuery(d.db);
          query->prepare("UPDATE tbl_name SET  Model=? , VIN=? ,VehicleName =?, VehicleBrand=? ,MfdYear=?, OdometerReading=?, Distance=?, CustomerName=?, MobileNo=?,DriverContact=? "
                       " WHERE VRN = :VRN" );


          query->addBindValue( Model );
          query->addBindValue(VIN );
          query->addBindValue( VName );
          query->addBindValue( VBrand );
          query->addBindValue( MfdYear );
          query->addBindValue( OdoReading );
          query->addBindValue( Distance );
          query->addBindValue( CuNo );
          query->addBindValue( MoNo );
          query->addBindValue( DrCo );


          query->addBindValue( VRN );

        query->exec();
        qDebug() << (VRN)<<query->lastError();





    d.db.close();
    ui->Search_lineEdit->setText( "" );
    ui->Search_lineEdit->setText( VRN );




    changeBoxItems();
         }
}

void workshop::on_deletePush_clicked()
{QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Are you sure?",
                                  QMessageBox::Yes|QMessageBox::No);
    if( reply == QMessageBox::Yes )
    {
    getData();
    d.db.open();

query = new QSqlQuery( d.db);
query->prepare( "delete from tbl_name where RId = :Rid ");
query->addBindValue(Rid);
query->exec();
qDebug() << (VRN)<<query->lastError();
d.db.close();
changeBoxItems();
ui->Search_lineEdit->setText( "" );
ui->Search_lineEdit->setText( VRN );
changeBoxItems();
    }
}




void workshop::on_dateCombobox_currentIndexChanged(int index)
{
    Date1 = ui->dateCombobox->currentText();\
    ui->templineEdit->setText( Date1 );

    int row = 0;
  QString Date3, Jorder1, Jdone1;

    do{





     QModelIndex newIndex1 = ui->tableView->model()->index(row,12);
    Date3 = (newIndex1.sibling( newIndex1.row(), 12).data().toString() );
    if ( Date3 == Date1)
    {
        Rid = newIndex1.sibling(newIndex1.row(), 0).data().toInt();
        Jorder1 = newIndex1.sibling( newIndex1.row(), 13).data().toString() ;
        Jdone1 = newIndex1.sibling( newIndex1.row(), 14).data().toString() ;
        if( Jorder1 != "")
        ui->Joborder_lineEdit->setText( Jorder1 );
        else
             ui->Joborder_lineEdit->clear();

        if( Jdone1 != "")
        ui->Jobdone_textEdit_2->setText( Jdone1 );
        else
            ui->Jobdone_textEdit_2->clear();
    }
    row++;
    }while( Date3 != "");




}



void workshop::on_pushButton_2_clicked()
{
    QDate d1;


   QString today = d1.currentDate().toString("yyyy-MM-dd");

   ui->templineEdit->setText( today );
}
void workshop::adminView()
{
    ui->Add->setDisabled(1);
    ui->pushButton_2->setDisabled(1);
    ui->clearPush->setDisabled(1);
    ui->deletePush->setDisabled(1);
    ui->updatepush->setDisabled(1);
}
