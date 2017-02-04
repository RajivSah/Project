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

    this->showMaximized();
    phaseTracerText = new QCPItemText(ui->customPlot);
    phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    phaseTracerText->setPositionAlignment(Qt::AlignCenter|Qt::AlignTop);
    phaseTracerText->position->setCoords(0.5, 0.02); // lower right corner of axis rect
    phaseTracerText->setTextAlignment(Qt::AlignLeft);
    phaseTracerText->setText("");
    phaseTracerText->setFont(QFont(font().family(), 12));
    phaseTracerText->setBrush(QBrush(QColor(231,231,231,100)));
    phaseTracerText->setPadding(QMargins(5,5,5,5));

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QRegExp exp("[0-9]{0,4}");
    ui->yearLineEdit->setValidator(new QRegExpValidator(exp));


    initializeGraph();


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
    phaseTracerText->setText("");
    move=0;
    time=50;
    if(ui->comboBox->currentIndex()==0)
    {
        setInitials();
        initializeGraph();
        drawGraph();
    }
    else if(ui->comboBox->currentIndex()==1)
    {

    setInitials_Yearly();
    initializeGraph_Yearly();
    drawGraph_Yearly();

    }
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
    bar->setPen(QPen(QColor(0, 0, 0).lighter(130)));
    QColor color;

   /* switch(rand()%4)
    *
    {
    case 0:
        color.setRgb(255, 155, 73);
        break;
    case 1:
        color.setRgb(255, 155, 73);
        break;
    case 2:
        color.setRgb(73, 173, 255);
        break;
    case 3:
        color.setRgb(241, 142, 255);
        break;

    }*/

    color.setRgb(rand()%255+1,rand()%255+1,rand()%255+1);

    bar->setBrush(QBrush(color));
    bar->setAntialiased(false);

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
    ui->customPlot->xAxis->setLabelColor(Qt::gray);
    ui->customPlot->xAxis->setLabelFont(QFont("calibri",14,2));
    ui->customPlot->xAxis->setTickLabelFont(QFont("calibri",14,2));
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
    ui->customPlot->yAxis->setLabelColor(Qt::gray);
    ui->customPlot->yAxis->setLabelFont(QFont("calibri",18,2));
    ui->customPlot->yAxis->setTickLabelFont(QFont("calibri",14,2));
    ui->customPlot->replot();

    }
void Analysis::drawGraph()
{

    if(move<1)
{
        move=move+0.04;
        if(move>1)
        {
            move=1;
            return;
        }
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
    else if(move==1)
    {
        move++;
        timer->stop();
        Data.clear();
        Data<<month[0]<<month[1]<<month[2]<<month[3]<<month[4]<<month[5]<<month[6]<<month[7]<<month[8]<<month[9]<<month[10]<<month[11];
        qDebug()<<Data;
        bar->setData(ticks, Data);
        phaseTracerText->setText(QString("January=%1    February=%2    March=%3    April=%4    May=%5    June=%6    July=%7    August=%8    September=%9    October=%10    November=%11    December=%12").arg(month[0]).arg(month[1]).arg(month[2]).arg(month[3]).arg(month[4]).arg(month[5]).arg(month[6]).arg(month[7]).arg(month[8]).arg(month[9]).arg(month[10]).arg(month[11]));

        ui->customPlot->replot();


    }

}

void Analysis::setInitials_Yearly()
{
tempYear=ui->yearLineEdit->text().toInt();//year to store starting value of lineedit
if(!connector.db.open())
{
    return;
}

for(int i=0;i<10;i++)
{
    year[i]=0;
}


QSqlQuery *query=new QSqlQuery(connector.db);
query->prepare("SELECT EXTRACT(YEAR FROM soldDate) FROM tbl_customer WHERE EXTRACT(YEAR FROM soldDate)>=?");
query->addBindValue(tempYear);
query->exec();

for(int i=0;i<query->size();i++)
{
    query->next();
    int value=query->value(0).toInt();
   if( value==tempYear)
        year[0]++;

    else if(value== tempYear+1)
        year[1]++;

     else if (value==tempYear+2)
        year[2]++;

   else if (value==tempYear+3)
        year[3]++;

   else if (value==tempYear+4)
        year[4]++;

   else if(value==tempYear+5)
        year[5]++;

   else if(value==tempYear+6)
        year[6]++;

   else if (value==tempYear+7)
        year[7]++;

   else if(value==tempYear+8)
        year[8]++;

   else if(value==tempYear+9)
        year[9]++;

}
Data.clear();
Data<<year[0]<<year[1]<<year[2]<<year[3]<<year[4]<<year[5]<<year[6]<<year[7]<<year[8]<<year[9];
connector.db.close();
}

void Analysis::initializeGraph_Yearly()
{
    ui->customPlot->clearPlottables();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


    QColor color;
    color.setRgb(rand()%255+1,rand()%255+1,rand()%255+1);
    graph=new QCPGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    graph->setPen(QPen(color));
    // prepare x axis with country labels:


    labels.clear();
    ticks.clear();
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<<8<<9<<10;
    labels << QString().setNum(tempYear)<< QString().setNum(tempYear+1)<< QString().setNum(tempYear+2)<< QString().setNum(tempYear+3)<<QString().setNum( tempYear+4)<< QString().setNum(tempYear+5)<< QString().setNum(tempYear+6)<< QString().setNum(tempYear+7)<<QString().setNum( tempYear+8)<< QString().setNum(tempYear+9);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setRange(0, 13);
    ui->customPlot->xAxis->setLabelColor(Qt::gray);
    ui->customPlot->xAxis->setLabelFont(QFont("calibri",14,2));
    ui->customPlot->xAxis->setTickLabelFont(QFont("calibri",14,2));
    int maxSaleYearValue=0;
    for (int i=0; i<10; i++)
    {
    if (year[i] > maxSaleYearValue)
    maxSaleYearValue = year[i];
    }
    qDebug()<<maxSaleYearValue;

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, maxSaleYearValue+20);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Total Sale");
    ui->customPlot->yAxis->setLabelColor(Qt::gray);
    ui->customPlot->yAxis->setLabelFont(QFont("calibri",18,2));
    ui->customPlot->yAxis->setTickLabelFont(QFont("calibri",14,2));
    ui->customPlot->replot();


}

void Analysis::drawGraph_Yearly()
{
    x_Axis.clear();
    y_Axis.clear();


        for(int i=0;i<10;i++)
        {
            x_Axis.push_back(ticks.at(0));
            y_Axis.push_back(Data.at(0));
            ticks.pop_front();
            Data.pop_front();

            graph->addData(x_Axis,y_Axis);
            ui->customPlot->replot();
            this->thread()->msleep(50);
        }
        phaseTracerText->setText(QString(QString().setNum(tempYear)+"=%1   "+ QString().setNum(tempYear+1)+"=%2   "+ QString().setNum(tempYear+2)+"=%3   "+ QString().setNum(tempYear+3)+"=%4   "+QString().setNum( tempYear+4)+"=%5   "+ QString().setNum(tempYear+5)+"=%6   "+ QString().setNum(tempYear+6)+"=%7   "+ QString().setNum(tempYear+7) +"=%8   "+ QString().setNum( tempYear+8)+"=%9   "+ QString().setNum(tempYear+9)+"=%10").arg(year[0]).arg(year[1]).arg(year[2]).arg(year[3]).arg(year[4]).arg(year[5]).arg(year[6]).arg(year[7]).arg(year[8]).arg(year[9]));
        ui->customPlot->replot();


}

void Analysis::on_comboBox_currentIndexChanged(int index)
{
    if(index==0)
    {
        phaseTracerText->setText("");
        this->setInitials();
        this->initializeGraph();
    }
    if(index == 1)
    {
        phaseTracerText->setText("");
        this->setInitials_Yearly();
        this->initializeGraph_Yearly();
    }
}
