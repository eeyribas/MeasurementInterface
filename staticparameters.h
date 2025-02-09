#ifndef STATICPARAMETERS_H
#define STATICPARAMETERS_H

#include <QList>

class StaticParameters
{
public:
    QList<QString> record_list_0 = {"52.25", "17.32", "-24.25", "0.8", "1.2", "3.2", "-2.54", "2.59", "-1.02", "2.97", "-2"};
    QList<QString> record_list_1 = {"13.21", "12.14", "-12.45", "0.7", "1.3", "3.15", "-2.76", "2.45", "-2.54", "2.93", "-2.46"};
    QList<QString> record_list_2 = {"12.45", "0.21", "-8.43", "0.6", "1.4", "2.76", "-2.95", "1.12", "-2.12", "2.12", "-2.12"};
    QList<QString> record_list_3 = {"61.13", "-12.54", "1.23", "0.9", "1.5", "2.98", "-2.43", "1.56", "-2.67", "2.41", "-2.87"};
    QList<QString> record_list_4 = {"62.3", "-23.21", "52.12", "0.87", "1.6", "2.56", "-2.12", "1.08", "-2.33", "2.18", "-1.23"};
    QList<QString> record_list_5 = {"33.44", "30.21", "13.42", "0.69", "1.42", "2.10", "-2.02", "1.78", "-2.48", "1.77", "-1.78"};
    QList<QString> record_list_6 = {"41.87", "28.45", "-21.12", "0.34", "1.28", "3.13", "-3.65", "1.24", "-1.67", "1.08", "-1.93"};
    QList<QString> record_list_7 = {"43.09", "45.19", "24.23", "0.29", "1.32", "3.25", "-1.78", "2.78", "-0.9", "1.89", "-2.68"};
    QList<QString> record_list_8 = {"24.52", "-12.32", "36.45", "0.89", "1.25", "3.9", "-3.41", "2.4", "-0.78", "2.32", "-0.59"};
    QList<QString> record_list_9 = {"11.21", "39.03", "31.31", "0.81", "1.12", "2.2", "-3.53", "2.76", "-1.84", "2.81", "-2.71"};
    QList<int> meter_array = {99900, 1800, 1700, 1600, 1500, 1400, 1300, 1200, 1100, 1000, 900, 800, 700, 600, 500, 400, 300, 200, 100, 0};

    QList<double> meter_list_1;
    QList<double> meter_list_2;
    QList<double> meter_list_3;
    QList<double> meter_list_4;
    QList<double> meter_list_5;
    QList<double> meter_list_6;
    QList<double> meter_list_7;
    QList<double> meter_list_8;
    QList<double> meter_list_9;

    QList<int> value_list_1;
    QList<int> value_list_2;
    QList<int> value_list_3;
    QList<int> value_list_4;
    QList<int> value_list_5;
    QList<int> value_list_6;
    QList<int> value_list_7;
    QList<int> value_list_8;
    QList<int> value_list_9;

    QList<int> color_value_list_1;
    QList<int> color_value_list_2;
    QList<int> color_value_list_3;

    QList<int> graphic_value_list_1;
    QList<int> graphic_value_list_2;
    QList<int> graphic_value_list_3;
    QList<int> graphic_meter_list;

    QList<QString> record_value_list_1;
    QList<QString> record_value_list_2;
    QList<QString> record_value_list_3;
    QList<QString> record_value_list_4;
    QList<QString> record_value_list_5;
    QList<QString> record_value_list_6;

    QList<int> button_counter_list;

    double value_1 = 0;
    double value_2 = 0;
    double value_3 = 0;
    double value_4 = 0;
    double value_5 = 0;
    double value_6 = 0;
    double value_7 = 0;
    double value_8 = 0;
    double value_9 = 0;
    double value_10 = 0;
    double value_11 = 0;
    double value_12 = 0;
    double value_13 = 0;
    double value_14 = 0;
    double value_15 = 0;
    double value_16 = 0;
    double value_17 = 0;
    double current_meter = 0.0;
    int last_meter = 0;
    double speed = 0.0;

    QString record_value_1 = ": -";
    QString record_value_2 = ": -";
    QString record_value_3 = ": -";
    QString record_value_4 = ": -";
    QString record_value_5 = ": -";
    QString record_value_6 = ": -";
    QString record_value_7 = ": -";
    QString record_value_8 = ": -";

    int choose_sch_push_button_1 = 1;
    int choose_sch_push_button_2 = 0;
    int x_move_widget_value = 1082;
    int change_zoom_count = 1;
    int zoom_state = 0;
    int color_array_length = 20;

    bool button_state_1 = true;
    bool button_state_2 = true;
    bool chart_or_graphic_state = false;
    bool released_state = false;
    bool moving_state = true;
};

#endif // STATICPARAMETERS_H
