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
    void setInitials_Yearly();
    void initializeGraph_Yearly();



private slots:
    void on_drawButton_clicked();
    void drawGraph();
    void drawGraph_Yearly();
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Analysis *ui;
    QVector<QString> labels;
    double month[12]={0};
    QVector<double> Data;
    QCPBars *bar;
    QCPGraph *graph;
    QVector<double> ticks;

    QVector<double> x_Axis,y_Axis;
    QTimer *timer = new QTimer(this);
    float move;
    float time;
    QCPItemText *phaseTracerText;
    double year[10]={0};
    int tempYear;//year to store starting value of lineedit
};

#endif // ANALYSIS_H
