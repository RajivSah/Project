#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QWidget>

namespace Ui {
class Analysis;
}

class Analysis : public QWidget
{
    Q_OBJECT

public:
    explicit Analysis(QWidget *parent = 0);
    ~Analysis();

private:
    Ui::Analysis *ui;
};

#endif // ANALYSIS_H
