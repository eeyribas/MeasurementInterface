#include "yesnodialog.h"
#include "ui_yesnodialog.h"

YesNoDialog::YesNoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YesNoDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QFontDatabase::addApplicationFont(":/fonts/fonts/Roboto-Bold.ttf");
}

YesNoDialog::~YesNoDialog()
{
    delete ui;
}

void YesNoDialog::on_pushButton_clicked()
{
    emit atYesNoDialog();
    close();
}

void YesNoDialog::on_pushButton_2_clicked()
{
    close();
}
