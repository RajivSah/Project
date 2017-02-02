#include "analysis.h"
#include "ui_analysis.h"

Analysis::Analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analysis)
{
    ui->setupUi(this);

}

Analysis::~Analysis()
{
    delete ui;
}
