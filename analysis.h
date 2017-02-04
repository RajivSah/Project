#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QWidget>
#include "dbconnection.h"
#include "qcustomplot.h"

namespace Ui {
class Analysis;
}

class Analysis : public QWidget
{
    Q_OBJECT

public:
    explicit Analysis(QWidget *parent = 0);
    ~Analysis();
    DBCONNECTION connector{"analysis"};
    void initializeGraph();
    void setInitials();


private slots:
    void on_drawButton_clicked();
    void drawGraph();

private:
    Ui::Analysis *ui;

    int month[12]={0};
    QVector<double> Data;
    QCPBars *bar;
    QVector<double> ticks;
    QTimer *timer = new QTimer(this);
    float move;
    float time;
};

#endif // ANALYSIS_H
