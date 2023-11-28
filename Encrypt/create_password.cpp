#include "create_password.h"
#include "ui_create_password.h"

create_password::create_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_password)
{
    ui->setupUi(this);
}

create_password::~create_password()
{
    delete ui;
}

void create_password::on_horizontalSlider_actionTriggered(int action)
{
    int length = ui->horizontalSlider->sliderPosition();
    ui->label_length->setNum(length);
}

void create_password::on_pushButton_ok_clicked()
{
    this->isLower = ui->checkBox_lower->isChecked();
    this->isUpper = ui->checkBox_upper->isChecked();
    this->isNumber = ui->checkBox_numbers->isChecked();
    this->isSymbol = ui->checkBox_symbols->isChecked();
    this->isCopy = ui->checkBox_copy->isChecked();
    this->length = ui->horizontalSlider->sliderPosition();
    hide();
}

