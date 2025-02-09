#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QFontDatabase::addApplicationFont(":/fonts/fonts/Roboto-Bold.ttf");

    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString read_pass_text = ui->lineEdit->text();
    if (read_pass_text == "pass1" || read_pass_text == "pass2" || read_pass_text == "pass3" ||
        read_pass_text == "pass4" || read_pass_text == "pass5") {
        ui->label_3->setText("You have entered the correct password.");
        close();

        emit atLoginDialog(read_pass_text);
    } else {
        ui->label_3->setText("You have entered the incorrect password. Please enter the password again.");
    }
}

void LoginDialog::on_pushButton_2_clicked()
{
    close();
}
