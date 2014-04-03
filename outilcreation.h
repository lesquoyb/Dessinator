#ifndef OUTILCREATION_H
#define OUTILCREATION_H

#include <QDialog>

namespace Ui {
class outilCreation;
}

class outilCreation : public QDialog
{
    Q_OBJECT

public:
    explicit outilCreation(QWidget *parent = 0);
    ~outilCreation();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::outilCreation *ui;
};

#endif // OUTILCREATION_H
