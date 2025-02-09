#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QDialog>
#include <QFontDatabase>

namespace Ui {
class LanguageDialog;
}

class LanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageDialog(QWidget *parent = nullptr);
    ~LanguageDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::LanguageDialog *ui;

    int choosing_lang_value = 0;
};

#endif // LANGUAGEDIALOG_H
