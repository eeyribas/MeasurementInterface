#ifndef YESNODIALOG_H
#define YESNODIALOG_H

#include <QDialog>
#include <QFontDatabase>

namespace Ui {
class YesNoDialog;
}

class YesNoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YesNoDialog(QWidget *parent = nullptr);
    ~YesNoDialog();

signals:
    void atYesNoDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::YesNoDialog *ui;
};

#endif // YESNODIALOG_H
