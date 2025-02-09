#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QPainter>
#include <QGraphicsScene>
#include <QSignalMapper>
#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <staticparameters.h>
#include <processthread.h>
#include <linechartparameters.h>
#include <mousemovefunction.h>
#include <logindialog.h>
#include <yesnodialog.h>
#include <languagedialog.h>
#include <linechartthread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onProcessValueChanged();
    void onLineChartValueChanged();
    void onSignalMapperFunction(int);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_34_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_39_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_41_clicked();
    void on_pushButton_42_clicked();
    void on_pushButton_43_clicked();
    void on_pushButton_44_clicked();
    void on_pushButton_45_clicked();
    void on_pushButton_46_clicked();
    void on_pushButton_47_clicked();
    void on_pushButton_48_clicked();
    void on_pushButton_49_clicked();
    void on_pushButton_50_clicked();
    void on_pushButton_51_clicked();
    void on_pushButton_52_clicked();
    void on_pushButton_53_clicked();
    void on_pushButton_54_clicked();
    void on_pushButton_55_clicked();
    void on_pushButton_56_clicked();
    void on_pushButton_57_clicked();
    void on_pushButton_58_clicked();
    void on_pushButton_59_clicked();
    void on_pushButton_60_clicked();
    void on_pushButton_61_clicked();
    void on_pushButton_62_clicked();
    void on_pushButton_63_clicked();
    void on_pushButton_64_clicked();
    void on_pushButton_65_clicked();
    void on_pushButton_66_clicked();
    void on_pushButton_67_clicked();
    void on_pushButton_68_clicked();
    void on_pushButton_69_clicked();
    void on_pushButton_70_clicked();
    void on_pushButton_71_clicked();
    void on_pushButton_72_clicked();
    void on_pushButton_73_clicked();
    void on_pushButton_74_clicked();
    void on_pushButton_75_clicked();

    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_5_currentIndexChanged(int index);
    void on_comboBox_7_currentIndexChanged(int index);
    void on_listView_2_clicked(const QModelIndex &index);

    void onLoginDialog(QString password);
    void onSliderValue();

    void onMousePressedFunction1();
    void onMouseMovedFunction1();
    void onMouseReleasedFunction1();
    void onMousePressedFunction2();
    void onMouseMovedFunction2();
    void onMouseReleasedFunction2();
    void onMousePressedFunction3();
    void onMouseMovedFunction3();
    void onMouseReleasedFunction3();

private:
    void LineChartConfig1();
    void LineChartConfig2();
    void LineChartInit1(QChartView *tmp_chart_view, QChart *tmp_chart, QLineSeries *tmp_line_series_1, QLineSeries *tmp_line_series_2, QLineSeries *tmp_line_series_3,
                        QValueAxis *tmp_value_axis_1, QValueAxis *tmp_value_axis_2, double value_1, double value_2, double value_3, double value_4, double value_5,
                        double value_6, QColor color_1, QColor color_2, int value_7, int value_8, QColor color_3, int value_9, QColor color_4, int value_10, QColor color_5);
    void LineChartInit2(QChartView *tmp_chart_view, QChart *tmp_chart, QLineSeries *line_series_1, QLineSeries *line_series_2, QLineSeries *line_series_3, QLineSeries *line_series_4,
                        QLineSeries *line_series_5, QLineSeries *line_series_6, QLineSeries *line_series_7, QLineSeries *line_series_8, QLineSeries *line_series_9, QValueAxis *x_axis,
                        QValueAxis *y_axis, QColor color_1, QColor color_2, QColor color_3, QColor color_4, QColor color_5, QColor color_6, QColor color_7, QColor color_8, QColor color_9);
    void LineChartInit3(QChartView *tmp_chart_view, QChart *tmp_chart, QLineSeries *line_series, QValueAxis *x_value_axis, QValueAxis *y_value_axis, QColor color);
    void ClearLineCharts1();
    void ClearLineCharts2();

    void DrawShape1(QList<int> array, int x, int width, int height, int array_length);
    void DrawShape2(QGraphicsView *tmp_graph_view, QGraphicsScene *tmp_graph_scene, QPixmap *tmp_pixmap, QPainter *tmp_painter,
                    QPen tmp_pen, QList<int> array, int x, int width, int height, int array_length);
    void DrawGraphicsFunction(double zoom_count);
    void DrawPoint1(QLineSeries *line_series_1, QLineSeries *line_series_2, QLineSeries *line_series_3, QValueAxis *x_value_axis, QValueAxis *y_value_axis,
                    double value_1, double value_2, double value_3, double value_4, double value_5, double value_6, double value_7, double value_8);
    void DrawPoint2(QLineSeries *line_series, QValueAxis *x_value_axis, QValueAxis *y_value_axis, double min_x_value, double max_y_value, double x_value, double y_value);
    void DrawPoint3(QLineSeries *line_series, QValueAxis *x_value_axis, QValueAxis *y_value_axis, double max_y_value, double x_value, double y_value);
    void DrawText1(QList<int> array, int x, int y_limit, int sum, int array_length);
    void DrawText2(QGraphicsView *tmp_graph_view, QGraphicsScene *tmp_graph_scene, QPixmap *tmp_pixmap, QPainter *tmp_painter, QPen tmp_pen,
                   QList<int> array, int x, int y_limit, int sum, int array_length);

    void MouseReleasedFunction(QGraphicsView *tmp_graph_view, QLabel *label, QList<int> first_array, QList<int> second_array, QList<int> third_array,
                               QList<int> meter_array, int y_first_value, int y_last_value);
    void MousePressedFunction(QLabel *label, int x_press, int y_press);
    void MouseMovedFunction(QLabel *label, int x_first, int y_first, int y_move);

    void SchematicsMousePressedFunction(int x_value, int y_value, double value_1, double value_2, double value_3);
    double RandomFunction(double min, double max);
    double RoundFunction(double number, int pow_factor);

    ProcessThread *process_thread;
    LineChartThread *line_chart_thread;
    int line_chart_thread_value;
    int x_line_chart_axis_value;
    double y_line_chart_axis_value;

    StaticParameters static_parameters;
    LineChartParameters line_chart_params;
    QGraphicsScene *graphics_scene;
    QPixmap *pixmap;
    QPainter *painter;
    QPen pen;

    QPushButton *rec_buttons[10];
    bool rec_buttons_state[10];
    QSignalMapper *signal_mapper;
    QStringListModel *string_list_model;
    QStandardItemModel *standard_item_model;

    Ui::MainWindow *ui;
    LoginDialog *login_dialog;
    YesNoDialog *yes_no_dialog;
    LanguageDialog *language_dialog;
};

#endif // MAINWINDOW_H
