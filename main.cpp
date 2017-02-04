#include "mainwindow.h"
#include <QApplication>
#include "partstore.h"
#include "workshop.h"
#include "sales.h"
#include "analysis.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow m;
//    m.show();
    Analysis ana;
    ana.show();

    return a.exec();
}
