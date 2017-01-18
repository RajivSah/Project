#ifndef ADDPARTS_H
#define ADDPARTS_H

#include <QDialog>
#include "dbconnection.h"
#include <QMessageBox>

namespace Ui {
class addParts;
}

class addParts : public QDialog
{
    Q_OBJECT

public:
    explicit addParts(QWidget *parent = 0);
    void setValidator();
    ~addParts();


private slots:
    void on_addPushButton_clicked();

private:
    Ui::addParts *ui;
    DBCONNECTION connector{"addparts"};
    QMessageBox message;
    void displayMessage(QString);
};

#endif // ADDPARTS_H
