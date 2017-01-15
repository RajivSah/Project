#include "mainwindow.h"
#include <QApplication>
#include "sales.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   //w.show();
   sales s;
   s.show();



    return a.exec();
}
