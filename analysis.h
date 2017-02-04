#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QWidget>
#include "dbconnection.h"

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
    void drawGraph();
    void setInitials();
    int month[12]={0};

private slots:
    void on_drawButton_clicked();

private:
    Ui::Analysis *ui;
};

#endif // ANALYSIS_H
