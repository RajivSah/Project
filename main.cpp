#include "mainwindow.h"
#include <QApplication>
#include "partstore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//   w.show();
//    addParts p;
//    p.show();
    partstore ps;
    ps.show();
    return a.exec();
}
