#include "analysis.h"
#include "ui_analysis.h"
#include <QSqlQuery>
#include <QTimer>
Analysis::Analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analysis)
{
    ui->setupUi(this);
/*
    connector.db.open();
    QSqlQuery *q=new QSqlQuery(connector.db);
    q->exec("Select * from tbl_customer");
    QSqlQuery *query=new QSqlQuery(connector.db);
    int year,month,day;
    QString date;
    for(int i=0;i<q->size();i++)
    {
        year=qrand()%3;
        month=qrand()%12;
        day=qrand()%30;
        if(month==2 && day==29)
        {
            day=28;
        }
        if(year==0)
        {
            year=2014;
        }
        else if(year==1)
        {
            year=2015;
        }
        else
        {
            year=2016;
        }
        month++;
        day++;

//        qDebug()<<year<<month<<day;
        date=QString().setNum(year)+"-"+QString().setNum(month)+"-"+QString().setNum(day);
//        qDebug()<<date;
        query->prepare("UPDATE tbl_customer SET SoldDate =? WHERE customerID=?");
        query->addBindValue(date);
        query->addBindValue(i+1);
        qDebug()<<query->exec();
    }
*/



}

Analysis::~Analysis()
{
    delete ui;
}


void Analysis::setInitials()
{
    int year=ui->yearLineEdit->text().toInt();
    if(!connector.db.open())
    {
        return;
    }

    for(int i=0;i<12;i++)
    {
        month[i]=0;
    }


    QSqlQuery *query=new QSqlQuery(connector.db);
    query->prepare("SELECT EXTRACT(YEAR FROM soldDate), EXTRACT(MONTH FROM soldDate) FROM tbl_customer WHERE EXTRACT(YEAR FROM soldDate)=?");
    query->addBindValue(year);
    query->exec();
    for(int i=0;i<query->size();i++)
    {
        query->next();
//        qDebug()<<query->value(0).toInt()<<query->value(1).toInt();
        switch(query->value(1).toInt())
        {
        case 1:
            month[0]++;
            break;
        case 2:
            month[1]++;
            break;
        case 3:
            month[2]++;
            break;
        case 4:
            month[3]++;
            break;
        case 5:
            month[4]++;
            break;
        case 6:
            month[5]++;
            break;
        case 7:
            month[6]++;
            break;
        case 8:
            month[7]++;
            break;
        case 9:
            month[8]++;
            break;
        case 10:
            month[9]++;
            break;
        case 11:
            month[10]++;
            break;
        case 12:
            month[11]++;
            break;
        }

    }

    connector.db.close();
}

void Analysis::on_drawButton_clicked()
{
    move=0;
    time=50;
    setInitials();
    initializeGraph();
    drawGraph();
//    this->resize(this->width()-1,this->height()-1);
}
void Analysis::initializeGraph()
{
    ui->customPlot->clearPlottables();
    QBrush gray(Qt::white);
    qDebug()<<month[0]<<month[1]<<month[2]<<month[3]<<month[4]<<month[5]<<month[6]<<month[7]<<month[8]<<month[9]<<month[10]<<month[11];
    ui->customPlot->setBackground(gray);
    // create empty bar chart objects:
    bar= new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    bar->setName("barerative");
    bar->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    bar->setBrush(QColor(0, 168, 140));

    // prepare x axis with country labels:

    QVector<QString> labels;
    labels.clear();
    ticks.clear();
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<<8<<9<<10<<11<<12;
    labels << "January" << "February" << "March" << "April" << "May" << "June" << "July"<<"August"<<"September"<<"October"<<"November"<<"December";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setRange(0, 13);
    int maxSaleMonthValue=0;
    for (int i=0; i<12; i++)
    {
    if (month[i] > maxSaleMonthValue)
    maxSaleMonthValue = month[i];
    }
    qDebug()<<maxSaleMonthValue;

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, maxSaleMonthValue+2);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Total Sale");


    }
void Analysis::drawGraph()
{


    if((int)move<1)
{
        move=move+0.02;
        Data.clear();
        Data<<move*month[0]<<move*month[1]<<move*month[2]<<move*month[3]<<move*month[4]<<move*month[5]<<move*month[6]<<move*month[7]<<move*month[8]<<move*month[9]<<move*month[10]<<move*month[11];
        qDebug()<<Data;
        bar->setData(ticks, Data);
        ui->customPlot->replot();
    qDebug()<<"move="<<move;
    connect(timer, SIGNAL(timeout()), this, SLOT(drawGraph()));
    timer->start(time);
    if(time > 40)
    {
    time=time-2;
    }
    }
    else
    {

        timer->stop();
    }

}
