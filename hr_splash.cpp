#include "hr_splash.h"
#include "ui_hr_splash.h"

hr_splash::hr_splash(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hr_splash)
{
    ui->setupUi(this);
    setFixedSize(720, 480);
    setWindowFlags(Qt::FramelessWindowHint);

}

hr_splash::~hr_splash()
{
    delete ui;
}

void hr_splash::on_searchUser_clicked()
{
    hrwindow *hrUI=new hrwindow();
    this->close();
    hrUI->add_user_Tab_select();
    hrUI->show();
}

void hr_splash::on_addUser_clicked()
{
    hrwindow *hrUI=new hrwindow();
    this->close();
    hrUI->search_user_Tab_select();
    hrUI->show();
}



void hr_splash::on_editUser_clicked()
{
    hrwindow *hrUI=new hrwindow();
    this->close();
     hrUI->edit_user_Tab_select();
    hrUI->show();
}

void hr_splash::on_removeUser_clicked()
{
    hrwindow *hrUI=new hrwindow();
    this->close();
    hrUI->remove_user_Tab_select();
    hrUI->show();

}
