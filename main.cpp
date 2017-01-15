#include "mainwindow.h"
#include <QApplication>
#include "workshop.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //MainWindow w;
  //w.show();
   hrwindow h;
    h.show();

    workshop w;
    w.show();

    return a.exec();
}
