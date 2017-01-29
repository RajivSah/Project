#include "partspro.h"
#include "partstore.h"
#include "ui_partspro.h"
#include "dbconnection.h"
#include<QDesktopWidget>
#include <QGraphicsDropShadowEffect>


partspro::partspro(bool adminMode, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::partspro)
{


    ui->setupUi(this);
    aM=adminMode;
    if(adminMode == 1)
    {
        adminView();
    }
    setSizes();
initialconditions( 0 );
}

void partspro::setSizes()
{


}


partspro::~partspro()
{
    delete ui;
}

void partspro:: hidecolumns()
{
    ui->tableView->hideColumn( 0 );
}
void partspro:: showtable()
{
    d.db.open();

query = new QSqlQuery(d.db);
    query->prepare( "select * from partsprocessing ");
    query->exec();
   d.db.close();
    model->setQuery( *query );

    ui->tableView->setModel( model);
 hidecolumns();
}
void partspro::on_showRecordspushButton_clicked()
{

showtable();
}
void partspro::initialconditions( bool x )
{
    ui->EditpushButton_2->setEnabled(x);
    ui->ClearpushButton_3->setEnabled(x);
    ui->DeleterpushButton_7->setEnabled(x);
    ui->todaypushButton->setEnabled(x);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setBlurRadius(5);
    effect->setOffset(5,5);
    effect->setColor(Qt::gray);

    ui->maingroupbox->setGraphicsEffect(effect);


    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect();

    effect1->setBlurRadius(5);
    effect1->setOffset(5,5);
    effect1->setColor(Qt::gray);


    ui->searchlineEdit_5->setGraphicsEffect(effect1);

}
void partspro::on_tableView_clicked(const QModelIndex &index)
{ ui->tableView->setAlternatingRowColors(1);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    Prid = (index.sibling( index.row(), 0).data().toInt() );
QString POrder = (index.sibling( index.row(), 1).data().toString() );
QString EntryDate = (index.sibling( index.row(), 2).data().toString() );
QString OutDate = (index.sibling( index.row(), 3).data().toString() );
QString PNo = (index.sibling( index.row(), 4).data().toString() );
QString PName = (index.sibling( index.row(), 5).data().toString() );

QString VRN = (index.sibling( index.row(), 6).data().toString() );
QString CustomerName = (index.sibling( index.row(), 7).data().toString() );
QString RFNo = (index.sibling( index.row(), 8).data().toString() );
QString quantity = (index.sibling( index.row(), 9).data().toString() );
ui->porderlineEdit_2->setText( POrder );
ui->pnolineEdit->setText( PNo);
ui->PNametextEdit->setPlainText( PName );
ui->EdatelineEdit_3->setText( EntryDate );
ui->OdatelineEdit_4->setText( OutDate );
ui->VRNdatelineEdit_5->setText( VRN );
ui->CNameineEdit_6->setText( CustomerName );
ui->RFNdatelineEdit_7->setText( RFNo );
ui->quantitylineEdit_2->setText( quantity );

if(aM==0){
initialconditions(1);
}
else
{
    initialconditions(0);
}
}
void partspro:: getData()
{
   POrder = ui->porderlineEdit_2->text();
   PNo= ui->pnolineEdit->text();
   PName = ui->PNametextEdit->toPlainText();
   EntryDate = ui->EdatelineEdit_3->text();
   OutDate = ui -> OdatelineEdit_4->text();
   VRN = ui->VRNdatelineEdit_5->text();
   CustomerName = ui->CNameineEdit_6->text();
   RFNo = ui->RFNdatelineEdit_7->text();
quantity = ui->quantitylineEdit_2->text();
}

/*void partspro::on_addentrypush_clicked()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm", "Are you sure?",
                                      QMessageBox::Yes|QMessageBox::No);
        if( reply == QMessageBox::Yes )
        {
    getData();
d.db.open();
query = new QSqlQuery(d.db.db);
query -> prepare( "INSERT INTO partsprocessing ( PurchaseOrder, EntryDate , OutDate ,PartNo , PartName, VRN,CustomerName,RequisitionFormNo,Quantity  ) VALUES ( :POrder,:EntryDate,:OutDate,:PNo,:PName,:VRN,:CustomerName,:RFNo,:quantity )");
        query->addBindValue( POrder );
        query->addBindValue( EntryDate );
        query->addBindValue( OutDate );
        query->addBindValue( PNo );
        query->addBindValue( PName );

        query->addBindValue( VRN );
        query->addBindValue( CustomerName );
        query->addBindValue( RFNo );
        query->addBindValue( quantity );

query->exec();
qDebug()<<query->lastError();
d.db.close();

showtable();
        }
}
*/
void partspro::on_DeleterpushButton_7_clicked()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm", "Are you sure?",
                                      QMessageBox::Yes|QMessageBox::No);
        if( reply == QMessageBox::Yes )
        {
    d.db.open();
    query = new QSqlQuery(d.db);
    query-> prepare( "delete from partsprocessing where PrId = :Prid");
    query->addBindValue( Prid);
    query->exec();
    qDebug()<<query->lastError();

    d.db.close();
    showtable();
 }
}

void partspro::on_ClearpushButton_3_clicked()
{
     ui->porderlineEdit_2->clear();
     ui->pnolineEdit->clear();
     ui->PNametextEdit->clear();
     ui->EdatelineEdit_3->clear();
     ui -> OdatelineEdit_4->clear();
     ui->VRNdatelineEdit_5->clear();
     ui->CNameineEdit_6->clear();
     ui->RFNdatelineEdit_7->clear();
     ui->quantitylineEdit_2->clear();
    // initialconditions(0);
}

void partspro::on_EditpushButton_2_clicked()
{getData();
    if( PNo != "" && PName != "" && EntryDate !="" ){
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm", "Are you sure?",
                                      QMessageBox::Yes|QMessageBox::No);
        if( reply == QMessageBox::Yes )
        {

d.db.open();
query = new QSqlQuery(d.db);
query -> prepare( "UPDATE partsprocessing SET PurchaseOrder=?, EntryDate=? , OutDate=? ,PartNo=? , PartName=?, VRN=?,CustomerName=?,RequisitionFormNo=? ,Quantity=? where Prid = ?");
        query->addBindValue( POrder );
        query->addBindValue( EntryDate );
        query->addBindValue( OutDate );
        query->addBindValue( PNo );
        query->addBindValue( PName );

        query->addBindValue( VRN );
        query->addBindValue( CustomerName );
        query->addBindValue( RFNo );
        query->addBindValue( quantity );
        query->addBindValue( Prid);



query->exec();
qDebug()<<query->lastError();
d.db.close();

showtable();
        }
    }
}

void partspro::finditemtable()
{
    QString searchItem = ui->searchlineEdit_5->text();
     d.db.open();

 query = new QSqlQuery(d.db);
     query->prepare( "select * from partsprocessing where PartNo like '%"+searchItem+"%' or PartName like '%"+searchItem+"%' or RequisitionFormNo like '%"+searchItem+"%' or VRN like '%"+searchItem+"%' or CustomerName like '%"+searchItem+"%' or PurchaseOrder like '%"+searchItem+"%' or EntryDate like '%"+searchItem+"%' or OutDate like '%"+searchItem+"%'");
     query->exec();
    d.db.close();
     model->setQuery( *query );

     ui->tableView->setModel( model);
  hidecolumns();
  qDebug()<<ui->tableView->model()->rowCount();
}
void partspro::on_seeinventorypushButton_4_clicked()
{
this->close();
partstore* ps = new partstore(aM);
ps->show();
}


void partspro::on_searchlineEdit_5_textChanged(const QString &arg1)
{
   finditemtable();
}



void partspro::on_todaypushButton_clicked()
{
    QDate d1;


   QString today = d1.currentDate().toString("yyyy/MM/dd");

   ui->OdatelineEdit_4->setText( today );

}
void partspro::adminView()
{
  ui->ClearpushButton_3->setDisabled(1);
  ui->EditpushButton_2->setDisabled(1);
  ui->DeleterpushButton_7->setDisabled(1);
}
