#include "outilcreation.h"
#include "ui_outilcreation.h"
#include "dessinTechnique.h"
#include "quadrangle.h"

outilCreation::outilCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outilCreation)
{
    ui->setupUi(this);
}

outilCreation::~outilCreation()
{
    delete ui;
}

void outilCreation::on_buttonBox_accepted()
{
    QWidget* current = ui->tabWidget->currentWidget();
    if (current->objectName().compare("QuadrangleCreator")){
        //quadrangle* q = new quadrangle
    }
}
