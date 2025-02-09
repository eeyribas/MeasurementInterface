#include "languagedialog.h"
#include "ui_languagedialog.h"

LanguageDialog::LanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LanguageDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QFontDatabase::addApplicationFont(":/fonts/fonts/Roboto-Bold.ttf");

    choosing_lang_value = rand() % 4;
    if (choosing_lang_value == 0) {
        ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
        ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
        ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
        ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
        ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
    } else if(choosing_lang_value == 1) {
        ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                      "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
        ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
        ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
        ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
        ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
    } else if(choosing_lang_value == 2) {
        ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                      "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
        ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
        ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
        ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
        ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
    } else if(choosing_lang_value == 3) {
        ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                      "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
        ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
        ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
        ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
        ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
    } else if(choosing_lang_value == 4) {
        ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                      "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
        ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
        ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
        ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                        "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
        ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
    }
}

LanguageDialog::~LanguageDialog()
{
    delete ui;
}

void LanguageDialog::on_pushButton_clicked()
{
    ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
    ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
    ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
}

void LanguageDialog::on_pushButton_2_clicked()
{
    ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                  "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
    ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
    ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
}

void LanguageDialog::on_pushButton_3_clicked()
{
    ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                  "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
    ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
    ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
}

void LanguageDialog::on_pushButton_4_clicked()
{
    ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                  "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
    ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
    ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
}

void LanguageDialog::on_pushButton_5_clicked()
{
    ui->pushButton->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/turkeyPassiveImage.png); }"
                                  "QPushButton:hover { border: 0px; image: url(:/images/images/turkeyActiveImage.png); }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/USAPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/USAActiveImage.png); }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/brasilPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/brasilActiveImage.png); }");
    ui->pushButton_4->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/thailandPassiveImage.png); }"
                                    "QPushButton:hover { border: 0px; image: url(:/images/images/thailandActiveImage.png); }");
    ui->pushButton_5->setStyleSheet("QPushButton { border: 0px; image: url(:/images/images/indonesiaActiveImage.png); }");
}

void LanguageDialog::on_pushButton_6_clicked()
{
    close();
}
