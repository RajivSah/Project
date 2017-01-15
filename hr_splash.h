#ifndef HR_SPLASH_H
#define HR_SPLASH_H

#include <QMainWindow>
#include "hrwindow.h"

namespace Ui {
class hr_splash;
}

class hr_splash : public QMainWindow
{
    Q_OBJECT

public:
    explicit hr_splash(QWidget *parent = 0);
    ~hr_splash();

private slots:
    void on_searchUser_clicked();

    void on_addUser_clicked();

    void on_editUser_clicked();

    void on_removeUser_clicked();



private:
    Ui::hr_splash *ui;
};

#endif // HR_SPLASH_H
