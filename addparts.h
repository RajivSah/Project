#ifndef ADDPARTS_H
#define ADDPARTS_H

#include <QDialog>
#include "dbconnection.h"

namespace Ui {
class addParts;
}

class addParts : public QDialog
{
    Q_OBJECT

public:
    explicit addParts(QWidget *parent = 0);
    ~addParts();
    DBCONNECTION connector{"addparts"};

private slots:
    void on_addPushButton_clicked();

private:
    Ui::addParts *ui;
};

#endif // ADDPARTS_H
