#ifndef SALES_H
#define SALES_H

#include <QMainWindow>
#include <QtSql>


namespace Ui {
class sales;
}

class sales : public QMainWindow
{
    Q_OBJECT

public:
    explicit sales(QWidget *parent = 0);
    ~sales();

private slots:
    void on_AddButton_clicked();

    void on_ClearButton_clicked();

    void on_searchButton_textChanged(const QString &arg1);

    void on_customerSearchButton_textChanged(const QString &arg1);

    void on_SearchButton_textChanged(const QString &arg1);

    void on_SearchButton_textEdited(const QString &arg1);

private:
    Ui::sales *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
};

#endif // SALES_H
