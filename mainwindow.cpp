#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    setWindowIcon(QIcon(":/images/images/iconImage.ico"));
    QFontDatabase::addApplicationFont(":/fonts/fonts/Roboto-Bold.ttf");

    line_chart_thread_value = 0;
    x_line_chart_axis_value = 0;
    y_line_chart_axis_value = 0;

    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->comboBox_5->setCurrentIndex(-1);
    ui->comboBox_6->setCurrentIndex(-1);
    ui->comboBox_7->setCurrentIndex(-1);

    graphics_scene = new QGraphicsScene(this);
    pixmap = new QPixmap(210, 680);
    pixmap->fill(QColor(94, 94, 94));
    painter = new QPainter(pixmap);

    QGraphicsScene *tmp_graph_scene = new QGraphicsScene(this);
    QPixmap *tmp_pixmap = new QPixmap(120, 588);
    tmp_pixmap->fill(QColor(94, 94, 94));
    QPainter *tmp_painter = new QPainter(tmp_pixmap);
    QPen tmp_pen;

    static_parameters.color_value_list_1.clear();
    static_parameters.color_value_list_2.clear();
    static_parameters.color_value_list_3.clear();
    static_parameters.graphic_value_list_1.clear();
    static_parameters.graphic_value_list_2.clear();
    static_parameters.graphic_value_list_3.clear();
    for (int i = 0; i < static_parameters.color_array_length; i++) {
        static_parameters.color_value_list_1.append(0);
        static_parameters.color_value_list_2.append(0);
        static_parameters.color_value_list_3.append(0);
        static_parameters.graphic_value_list_1.append(1);
        static_parameters.graphic_value_list_2.append(1);
        static_parameters.graphic_value_list_3.append(1);
    }
    static_parameters.graphic_meter_list.append(0);

    DrawShape1(static_parameters.color_value_list_1, 0, 53, 34, static_parameters.color_array_length);
    DrawShape1(static_parameters.color_value_list_2, 57, 53, 34, static_parameters.color_array_length);
    DrawShape1(static_parameters.color_value_list_3, 114, 53, 34, static_parameters.color_array_length);

    DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.color_value_list_1,
               10, 30, 29, static_parameters.color_array_length);
    DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.color_value_list_2,
               44, 30, 29, static_parameters.color_array_length);
    DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.color_value_list_3,
               78, 30, 29, static_parameters.color_array_length);
    ui->label_119->setStyleSheet("background-color: rgb(118, 118, 118); border: 0px;");
    ui->label_119->setGeometry(109, 300, 29, 10);

    LineChartConfig1();

    static_parameters.meter_list_1.clear();
    static_parameters.meter_list_2.clear();
    static_parameters.meter_list_3.clear();
    static_parameters.meter_list_4.clear();
    static_parameters.meter_list_5.clear();
    static_parameters.meter_list_6.clear();
    static_parameters.meter_list_7.clear();
    static_parameters.meter_list_8.clear();
    static_parameters.meter_list_9.clear();

    signal_mapper = new QSignalMapper(this);
    QWidget *tmp_widget = new QWidget();
    tmp_widget->setStyleSheet("QWidget { background-color: rgb(94, 94, 94); }");
    ui->scrollArea->setWidget(tmp_widget);
    QFormLayout *tmp_form_layout = new QFormLayout();
    tmp_widget->setLayout(tmp_form_layout);

    static_parameters.record_value_list_1.clear();
    static_parameters.record_value_list_2.clear();
    static_parameters.record_value_list_3.clear();
    static_parameters.record_value_list_4.clear();
    static_parameters.record_value_list_5.clear();
    static_parameters.record_value_list_6.clear();
    static_parameters.record_value_list_1 << "Still - 1" << "Still - 2" << "Still - 3" << "Still - 4" << "Still - 5" << "Still - 6" << "Still - 7" << "Still - 8" << "Still - 9" << "Still - 10";
    static_parameters.record_value_list_2 << "2450 m" << "1345 m" << "580 m" << "3345 m" << "1320 m" << "870 m" << "5400 m" << "200 m" << "980 m" << "3210 m";
    static_parameters.record_value_list_3 << "16.04.2020" << "15.04.2020" << "14.04.2020" << "11.04.2020" << "08.04.2020" << "04.04.2020" << "02.04.2020" << "26.03.2020" << "22.03.2020" << "16.03.2020";
    static_parameters.record_value_list_4 << "18.45" << "15.20" << "11.45" << "10.13" << "19.45" << "17.30" << "14.50" << "13.20" << "08.55" << "14.20";
    static_parameters.record_value_list_5 << "Repo 1" << "Repo 1" << "Repo 2" << "Repo 1" << "Repo 3" << "Repo 3" << "Repo 2" << "Repo 1" << "Repo 4" << "Repo 2";
    static_parameters.record_value_list_6 << "Very Good" << "Good" << "Middle" << "Bad" << "Middle" << "Good" << "Good" << "Very Good" << "Bad" << "Middle";

    for (int i = 0; i < 10; i++) {
        rec_buttons[i] = new QPushButton(this);
        rec_buttons[i]->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); border: 1px solid black; border-radius: 5px; width: 45px; height: 45px; } QPushButton:hover { "
                                      "background-image: url(:/images/images/okStockImage.png); }");
        rec_buttons_state[i] = false;
        connect(rec_buttons[i], SIGNAL(clicked()),
                signal_mapper, SLOT(map()));
         signal_mapper->setMapping(rec_buttons[i], i);

        QLabel *label_1 = new QLabel();
        label_1->setFixedWidth(150);
        label_1->setStyleSheet("QLabel { border: 0px; font-size: 14px; color: rgb(240, 240, 240); }");
        label_1->setText(static_parameters.record_value_list_1[i]);

        QLabel *label_2 = new QLabel();
        label_2->setFixedWidth(65);
        label_2->setStyleSheet("QLabel { border: 0px; font-size: 14px; color: rgb(240, 240, 240); }");
        label_2->setText(static_parameters.record_value_list_2[i]);

        QLabel *label_3 = new QLabel();
        label_3->setFixedWidth(90);
        label_3->setStyleSheet("QLabel { border: 0px; font-size: 14px; color: rgb(240, 240, 240); }");
        label_3->setText(static_parameters.record_value_list_3[i]);

        QLabel *label_4 = new QLabel();
        label_4->setFixedWidth(60);
        label_4->setStyleSheet("QLabel { border: 0px; font-size: 14px; color: rgb(240, 240, 240); }");
        label_4->setText(static_parameters.record_value_list_4[i]);

        QLabel *label_5 = new QLabel();
        label_5->setFixedWidth(65);
        label_5->setStyleSheet("QLabel { border: 0px; font-size: 14px; color: rgb(240, 240, 240); }");
        label_5->setText(static_parameters.record_value_list_5[i]);

        QLabel *label_6 = new QLabel();
        label_6->setFixedWidth(55);
        label_6->setStyleSheet("QLabel { border: 0px; font-size: 14px; color: rgb(240, 240, 240); }");
        label_6->setText(static_parameters.record_value_list_6[i]);

        QLabel *label_7 = new QLabel();
        label_7->setFixedWidth(25);
        label_7->setStyleSheet("QLabel { image: url(:/images/images/recordsImage.png); border: 0px; }");

        QWidget *tmp_widget = new QWidget();
        QHBoxLayout *tmp_hbox_layout = new QHBoxLayout();
        tmp_hbox_layout->addWidget(label_1);
        tmp_hbox_layout->addWidget(label_2);
        tmp_hbox_layout->addWidget(label_3);
        tmp_hbox_layout->addWidget(label_4);
        tmp_hbox_layout->addWidget(label_5);
        tmp_hbox_layout->addWidget(label_6);
        tmp_hbox_layout->addWidget(label_7);
        tmp_widget->setLayout(tmp_hbox_layout);
        tmp_widget->setStyleSheet("QWidget { border: 0px; } QWidget:hover { border: 2px solid white; }");

        tmp_form_layout->addRow(rec_buttons[i], tmp_widget);
    }

    LineChartConfig2();

    connect(signal_mapper, SIGNAL(mappedInt(int)),
            this, SLOT(onSignalMapperFunction(int)));

    connect(ui->mouseMoveFunction, SIGNAL(mousePressedSignal()),
            this, SLOT(onMousePressedFunction1()));
    connect(ui->mouseMoveFunction, SIGNAL(mouseMovedSignal()),
            this, SLOT(onMouseMovedFunction1()));
    connect(ui->mouseMoveFunction, SIGNAL(mouseReleasedSignal()),
            this, SLOT(onMouseReleasedFunction1()));

    connect(ui->mouseMoveFunction_2, SIGNAL(mousePressedSignal()),
            this, SLOT(onMousePressedFunction2()));
    connect(ui->mouseMoveFunction_2, SIGNAL(mouseMovedSignal()),
            this, SLOT(onMouseMovedFunction2()));
    connect(ui->mouseMoveFunction_2, SIGNAL(mouseReleasedSignal()),
            this, SLOT(onMouseReleasedFunction2()));

    connect(ui->mouseMoveFunction_3, SIGNAL(mousePressedSignal()),
            this, SLOT(onMousePressedFunction3()));
    connect(ui->mouseMoveFunction_3, SIGNAL(mouseMovedSignal()),
            this, SLOT(onMouseMovedFunction3()));
    connect(ui->mouseMoveFunction_3, SIGNAL(mouseReleasedSignal()),
            this, SLOT(onMouseReleasedFunction3()));

    connect(ui->pushButton_6, SIGNAL(clicked()),
            SLOT(showMinimized()));
}

MainWindow::~MainWindow()
{
    if (process_thread)
        delete process_thread;

    if (line_chart_thread)
        delete line_chart_thread;

    if (graphics_scene)
        delete graphics_scene;

    if (pixmap)
        delete pixmap;

    if (painter)
        delete painter;

    if (signal_mapper)
        delete signal_mapper;

    if (string_list_model)
        delete string_list_model;

    if (standard_item_model)
        delete standard_item_model;

    if (login_dialog)
        delete login_dialog;

    if (yes_no_dialog)
        delete yes_no_dialog;

    if (language_dialog)
        delete language_dialog;

    delete ui;
}

void MainWindow::onProcessValueChanged()
{
    ui->pushButton_14->setStyleSheet("QPushButton { background-color: rgb(38, 201, 84); color: rgb(94, 94, 94); border: 0px; "
                                   "border-radius: 5px; text-align: center; }");
    ui->pushButton_15->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; "
                                  "border-radius: 5px; text-align: center; } QPushButton::hover { background-color: rgb(194, 194, 194); "
                                  "color: rgb(94, 94, 94); border: 0px; border-radius: 5px; text-align: center; }");

    static_parameters.speed = 10;
    static_parameters.current_meter = static_parameters.current_meter + 0.1;
    ui->label_99->setText(QString::number(static_parameters.speed) + " m/min");
    ui->label_97->setText(QString::number(static_parameters.current_meter) + " m");

    double random = 0;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double left_a_test = 10;//random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double left_b_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double left_c_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double middle_a_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double middle_b_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double middle_c_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double right_a_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double right_b_test = random;
    random = RandomFunction(0, 10);
    random = RoundFunction(random, 2);
    double right_c_test = random;

    double left_delta_a_test = left_a_test - static_parameters.value_9;
    double left_delta_b_test = left_b_test - static_parameters.value_10;
    double left_delta_c_test = left_c_test - static_parameters.value_11;
    double middle_delta_a_test = middle_a_test - static_parameters.value_12;
    double middle_delta_b_test = middle_b_test - static_parameters.value_13;
    double middle_delta_c_test = middle_c_test - static_parameters.value_14;
    double right_delta_a_test = right_a_test - static_parameters.value_15;
    double right_delta_b_test = right_b_test - static_parameters.value_16;
    double right_delta_c_test = right_c_test - static_parameters.value_17;
    static_parameters.meter_list_1.append(left_delta_a_test);
    static_parameters.meter_list_2.append(left_delta_b_test);
    static_parameters.meter_list_3.append(left_delta_c_test);
    static_parameters.meter_list_4.append(middle_delta_a_test);
    static_parameters.meter_list_5.append(middle_delta_b_test);
    static_parameters.meter_list_6.append(middle_delta_c_test);
    static_parameters.meter_list_7.append(right_delta_a_test);
    static_parameters.meter_list_8.append(right_delta_b_test);
    static_parameters.meter_list_9.append(right_delta_c_test);

    double left_delta_a_test_ave = 0;
    double left_delta_b_test_ave = 0;
    double left_delta_c_test_ave = 0;
    double middle_delta_a_test_ave = 0;
    double middle_delta_b_test_ave = 0;
    double middle_delta_c_test_ave = 0;
    double right_delta_a_test_ave = 0;
    double right_delta_b_test_ave = 0;
    double right_delta_c_test_ave = 0;
    for (int i = 0; i < static_parameters.meter_list_1.length(); i++) {
        left_delta_a_test_ave = left_delta_a_test_ave + static_parameters.meter_list_1[i];
        left_delta_b_test_ave = left_delta_b_test_ave + static_parameters.meter_list_2[i];
        left_delta_c_test_ave = left_delta_c_test_ave + static_parameters.meter_list_3[i];
        middle_delta_a_test_ave = middle_delta_a_test_ave + static_parameters.meter_list_4[i];
        middle_delta_b_test_ave = middle_delta_b_test_ave + static_parameters.meter_list_5[i];
        middle_delta_c_test_ave = middle_delta_c_test_ave + static_parameters.meter_list_6[i];
        right_delta_a_test_ave = right_delta_a_test_ave + static_parameters.meter_list_7[i];
        right_delta_b_test_ave = right_delta_b_test_ave + static_parameters.meter_list_8[i];
        right_delta_c_test_ave = right_delta_c_test_ave + static_parameters.meter_list_9[i];
    }
    left_delta_a_test_ave = RoundFunction(left_delta_a_test_ave / static_parameters.meter_list_1.length(), 2);
    left_delta_b_test_ave = RoundFunction(left_delta_b_test_ave / static_parameters.meter_list_2.length(), 2);
    left_delta_c_test_ave = RoundFunction(left_delta_c_test_ave / static_parameters.meter_list_3.length(), 2);
    middle_delta_a_test_ave = RoundFunction(middle_delta_a_test_ave / static_parameters.meter_list_4.length(), 2);
    middle_delta_b_test_ave = RoundFunction(middle_delta_b_test_ave / static_parameters.meter_list_5.length(), 2);
    middle_delta_c_test_ave = RoundFunction(middle_delta_c_test_ave / static_parameters.meter_list_6.length(), 2);
    right_delta_a_test_ave = RoundFunction(right_delta_a_test_ave / static_parameters.meter_list_7.length(), 2);
    right_delta_b_test_ave = RoundFunction(right_delta_b_test_ave / static_parameters.meter_list_8.length(), 2);
    right_delta_c_test_ave = RoundFunction(right_delta_c_test_ave / static_parameters.meter_list_9.length(), 2);

    double left_delta_e_test = pow(left_delta_a_test, 2) + pow(left_delta_b_test, 2) + pow(left_delta_c_test, 2);
    left_delta_e_test = sqrt(left_delta_e_test);
    left_delta_e_test = RoundFunction(left_delta_e_test, 2);
    double middle_delta_e_test = pow(middle_delta_a_test, 2) + pow(middle_delta_b_test, 2) + pow(middle_delta_c_test, 2);
    middle_delta_e_test = sqrt(middle_delta_e_test);
    middle_delta_e_test = RoundFunction(middle_delta_e_test, 2);
    double right_delta_e_test = pow(right_delta_a_test, 2) + pow(right_delta_b_test, 2) + pow(right_delta_c_test, 2);
    right_delta_e_test = sqrt(right_delta_e_test);
    right_delta_e_test = RoundFunction(right_delta_e_test, 2);
    double left_middle_delta_e_test = pow((left_a_test - middle_a_test), 2) + pow((left_b_test - middle_b_test), 2) + pow((left_c_test - middle_c_test), 2);
    left_middle_delta_e_test = sqrt(left_middle_delta_e_test);
    left_middle_delta_e_test = RoundFunction(left_middle_delta_e_test, 2);
    double left_right_delta_e_test = pow((left_a_test - right_a_test), 2) + pow((left_b_test - right_b_test), 2) + pow((left_c_test - right_c_test), 2);
    left_right_delta_e_test = sqrt(left_right_delta_e_test);
    left_right_delta_e_test = RoundFunction(left_right_delta_e_test, 2);
    double middle_right_delta_e_test = pow((middle_a_test - right_a_test), 2) + pow((middle_b_test - right_b_test), 2) + pow((middle_c_test - right_c_test), 2);
    middle_right_delta_e_test = sqrt(middle_right_delta_e_test);
    middle_right_delta_e_test = RoundFunction(middle_right_delta_e_test, 2);

    if (static_parameters.choose_sch_push_button_2 == 0) {
        if (static_parameters.choose_sch_push_button_1 == 0) {

            if (left_delta_a_test > static_parameters.value_4 && left_delta_a_test < static_parameters.value_3) {
                ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(left_delta_a_test));
            } else {
                ui->label_58->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(left_delta_a_test));
            }

            if (left_delta_b_test > static_parameters.value_6 && left_delta_b_test < static_parameters.value_5) {
                ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(left_delta_b_test));
            } else {
                ui->label_60->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(left_delta_b_test));
            }

            if (left_delta_c_test > static_parameters.value_8 && left_delta_c_test < static_parameters.value_7) {
                ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(left_delta_c_test));
            } else {
                ui->label_62->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(left_delta_c_test));
            }

            double delta_a_sch_double = 140 - ((left_delta_a_test / 4) * 80);
            int delta_a_sch_int = (int)delta_a_sch_double;
            if (delta_a_sch_int < 50)
                delta_a_sch_int = 50;
            else if (delta_a_sch_int > 222)
                delta_a_sch_int = 222;
            ui->label_75->setGeometry(10, delta_a_sch_int, 34, 4);

            double delta_b_sch_double = 170 + ((left_delta_b_test / 3) * 90);
            int delta_b_sch_int = (int)delta_b_sch_double;
            if (delta_b_sch_int < 80)
                delta_b_sch_int = 80;
            else if (delta_b_sch_int > 250)
                delta_b_sch_int = 250;
            double delta_c_sch_double = 140 - ((left_delta_c_test / 3) * 90);
            int delta_c_sch_int = (int)delta_c_sch_double;
            if (delta_c_sch_int < 50)
                delta_c_sch_int = 50;
            else if (delta_c_sch_int > 220)
                delta_c_sch_int = 220;
            ui->label_78->setGeometry(delta_b_sch_int, delta_c_sch_int, 10, 10);

            ui->label_101->setText(QString::number(RoundFunction(left_a_test, 2)));
            ui->label_103->setText(QString::number(RoundFunction(left_b_test, 2)));
            ui->label_105->setText(QString::number(RoundFunction(left_c_test, 2)));
            ui->label_107->setText(QString::number(RoundFunction(left_delta_e_test, 2)));
            ui->label_110->setText(QString::number(static_parameters.value_1));
            ui->label_113->setText(QString::number(static_parameters.value_2));

        } else if (static_parameters.choose_sch_push_button_1 == 1) {
            if (middle_delta_a_test > static_parameters.value_4 && middle_delta_a_test < static_parameters.value_3) {
                ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(middle_delta_a_test));
            } else {
                ui->label_58->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(middle_delta_a_test));
            }

            if (middle_delta_b_test > static_parameters.value_6 && middle_delta_b_test < static_parameters.value_5) {
                ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(middle_delta_b_test));
            } else {
                ui->label_60->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(middle_delta_b_test));
            }

            if (middle_delta_c_test > static_parameters.value_8 && middle_delta_c_test < static_parameters.value_7) {
                ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(middle_delta_c_test));
            } else {
                ui->label_62->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(middle_delta_c_test));
            }

            double delta_a_sch_double = 140 - ((middle_delta_a_test / 4) * 80);
            int delta_a_sch_int = (int)delta_a_sch_double;
            if (delta_a_sch_int < 50)
                delta_a_sch_int = 50;
            else if (delta_a_sch_int > 222)
                delta_a_sch_int = 222;
            ui->label_75->setGeometry(10, delta_a_sch_int, 34, 4);

            double delta_b_sch_double = 170 + ((middle_delta_c_test / 3) * 90);
            int delta_b_sch_int = (int)delta_b_sch_double;
            if (delta_b_sch_int < 80)
                delta_b_sch_int = 80;
            else if (delta_b_sch_int > 250)
                delta_b_sch_int = 250;
            double delta_c_sch_double = 140 - ((middle_delta_c_test / 3) * 90);
            int delta_c_sch_int = (int)delta_c_sch_double;
            if (delta_c_sch_int < 50)
                delta_c_sch_int = 50;
            else if (delta_c_sch_int > 220)
                delta_c_sch_int = 220;
            ui->label_78->setGeometry(delta_b_sch_int, delta_c_sch_int, 10, 10);

            ui->label_101->setText(QString::number(RoundFunction(middle_a_test, 2)));
            ui->label_103->setText(QString::number(RoundFunction(middle_b_test, 2)));
            ui->label_105->setText(QString::number(RoundFunction(middle_c_test, 2)));
            ui->label_107->setText(QString::number(RoundFunction(middle_delta_e_test, 2)));
            ui->label_110->setText(QString::number(static_parameters.value_1));
            ui->label_113->setText(QString::number(static_parameters.value_2));

        } else if (static_parameters.choose_sch_push_button_1 == 2) {
            if (right_delta_a_test > static_parameters.value_4 && right_delta_a_test < static_parameters.value_3) {
                ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(right_delta_a_test));
            } else {
                ui->label_58->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(right_delta_a_test));
            }

            if (right_delta_b_test > static_parameters.value_6 && right_delta_b_test < static_parameters.value_5) {
                ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(right_delta_b_test));
            } else {
                ui->label_60->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(right_delta_b_test));
            }

            if (right_delta_c_test > static_parameters.value_8 && right_delta_c_test < static_parameters.value_7) {
                ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(right_delta_c_test));
            } else {
                ui->label_62->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(right_delta_c_test));
            }

            double delta_a_sch_double = 140 - ((right_delta_a_test / 4) * 80);
            int delta_a_sch_int = (int)delta_a_sch_double;
            if (delta_a_sch_int < 50)
                delta_a_sch_int = 50;
            else if (delta_a_sch_int > 222)
                delta_a_sch_int = 222;
            ui->label_75->setGeometry(10, delta_a_sch_int, 34, 4);

            double delta_b_sch_double = 170 + ((right_delta_b_test / 3) * 90);
            int delta_b_sch_int = (int)delta_b_sch_double;
            if (delta_b_sch_int < 80)
                delta_b_sch_int = 80;
            else if (delta_b_sch_int > 250)
                delta_b_sch_int = 250;
            double delta_c_sch_double = 140 - ((right_delta_c_test / 3) * 90);
            int delta_c_sch_int = (int)delta_c_sch_double;
            if (delta_c_sch_int < 50)
                delta_c_sch_int = 50;
            else if (delta_c_sch_int > 220)
                delta_c_sch_int = 220;
            ui->label_78->setGeometry(delta_b_sch_int, delta_c_sch_int, 10, 10);

            ui->label_101->setText(QString::number(RoundFunction(right_a_test, 2)));
            ui->label_103->setText(QString::number(RoundFunction(right_b_test, 2)));
            ui->label_105->setText(QString::number(RoundFunction(right_c_test, 2)));
            ui->label_107->setText(QString::number(RoundFunction(right_delta_e_test, 2)));
            ui->label_110->setText(QString::number(static_parameters.value_1));
            ui->label_113->setText(QString::number(static_parameters.value_2));
        }
    } else if (static_parameters.choose_sch_push_button_2 == 1) {
        if (static_parameters.choose_sch_push_button_1 == 0) {
            if (left_delta_a_test_ave > static_parameters.value_4 && left_delta_a_test_ave < static_parameters.value_3) {
                ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(left_delta_a_test_ave));
            } else {
                ui->label_58->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(left_delta_a_test_ave));
            }

            if (left_delta_b_test_ave > static_parameters.value_6 && left_delta_b_test_ave < static_parameters.value_5) {
                ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(left_delta_b_test_ave));
            } else {
                ui->label_60->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(left_delta_b_test_ave));
            }

            if (left_delta_c_test_ave > static_parameters.value_8 && left_delta_c_test_ave < static_parameters.value_7) {
                ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(left_delta_c_test_ave));
            } else {
                ui->label_62->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(left_delta_c_test_ave));
            }

            double delta_a_sch_double = 140 - ((left_delta_a_test_ave / 4) * 80);
            int delta_a_sch_int = (int)delta_a_sch_double;
            if (delta_a_sch_int < 50)
                delta_a_sch_int = 50;
            else if (delta_a_sch_int > 222)
                delta_a_sch_int = 222;
            ui->label_75->setGeometry(10, delta_a_sch_int, 34, 4);

            double delta_b_sch_double = 170 + ((left_delta_b_test_ave / 3) * 90);
            int delta_b_sch_int = (int)delta_b_sch_double;
            if (delta_b_sch_int < 80)
                delta_b_sch_int = 80;
            else if (delta_b_sch_int > 250)
                delta_b_sch_int = 250;
            double delta_c_sch_double = 140 - ((left_delta_c_test_ave/ 3) * 90);
            int delta_c_sch_int = (int)delta_c_sch_double;
            if (delta_c_sch_int < 50)
                delta_c_sch_int = 50;
            else if (delta_c_sch_int > 220)
                delta_c_sch_int = 220;
            ui->label_78->setGeometry(delta_b_sch_int, delta_c_sch_int, 10, 10);

            ui->label_101->setText(QString::number(RoundFunction(left_a_test, 2)));
            ui->label_103->setText(QString::number(RoundFunction(left_b_test, 2)));
            ui->label_105->setText(QString::number(RoundFunction(left_c_test, 2)));
            ui->label_107->setText(QString::number(RoundFunction(left_delta_e_test, 2)));
            ui->label_110->setText(QString::number(static_parameters.value_1));
            ui->label_113->setText(QString::number(static_parameters.value_2));

        } else if (static_parameters.choose_sch_push_button_1 == 1) {
            if (middle_delta_a_test_ave > static_parameters.value_4 && middle_delta_a_test_ave < static_parameters.value_3) {
                ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(middle_delta_a_test_ave));
            } else {
                ui->label_58->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(middle_delta_a_test_ave));
            }

            if (middle_delta_b_test_ave > static_parameters.value_6 && middle_delta_b_test_ave < static_parameters.value_5) {
                ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(middle_delta_b_test_ave));
            } else {
                ui->label_60->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(middle_delta_b_test_ave));
            }

            if (middle_delta_c_test_ave > static_parameters.value_8 && middle_delta_c_test_ave < static_parameters.value_7) {
                ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(middle_delta_c_test_ave));
            } else {
                ui->label_62->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(middle_delta_c_test_ave));
            }

            double delta_a_sch_double = 140 - ((middle_delta_a_test_ave / 4) * 80);
            int delta_a_sch_int = (int)delta_a_sch_double;
            if (delta_a_sch_int < 50)
                delta_a_sch_int = 50;
            else if (delta_a_sch_int > 222)
                delta_a_sch_int = 222;
            ui->label_75->setGeometry(10, delta_a_sch_int, 34, 4);

            double delta_b_sch_double = 170 + ((middle_delta_b_test_ave / 3) * 90);
            int delta_b_sch_int = (int)delta_b_sch_double;
            if (delta_b_sch_int < 80)
                delta_b_sch_int = 80;
            else if (delta_b_sch_int > 250)
                delta_b_sch_int = 250;
            double delta_c_sch_double = 140 - ((middle_delta_c_test_ave / 3) * 90);
            int delta_c_sch_int = (int)delta_c_sch_double;
            if (delta_c_sch_int < 50)
                delta_c_sch_int = 50;
            else if (delta_c_sch_int > 220)
                delta_c_sch_int = 220;
            ui->label_78->setGeometry(delta_b_sch_int, delta_c_sch_int, 10, 10);

            ui->label_101->setText(QString::number(RoundFunction(middle_a_test, 2)));
            ui->label_103->setText(QString::number(RoundFunction(middle_b_test, 2)));
            ui->label_105->setText(QString::number(RoundFunction(middle_c_test, 2)));
            ui->label_107->setText(QString::number(RoundFunction(middle_delta_e_test, 2)));
            ui->label_110->setText(QString::number(static_parameters.value_1));
            ui->label_113->setText(QString::number(static_parameters.value_2));

        } else if (static_parameters.choose_sch_push_button_1 == 2) {
            if (right_delta_a_test_ave > static_parameters.value_4 && right_delta_a_test_ave < static_parameters.value_3) {
                ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(right_delta_a_test_ave));
            } else {
                ui->label_58->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_58->setText(QString::number(right_delta_a_test_ave));
            }

            if (right_delta_b_test_ave > static_parameters.value_6 && right_delta_b_test_ave < static_parameters.value_5) {
                ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(right_delta_b_test_ave));
            } else {
                ui->label_60->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_60->setText(QString::number(right_delta_b_test_ave));
            }

            if (right_delta_c_test_ave > static_parameters.value_8 && right_delta_c_test_ave < static_parameters.value_7) {
                ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(right_delta_c_test_ave));
            } else {
                ui->label_62->setStyleSheet("background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
                ui->label_62->setText(QString::number(right_delta_c_test_ave));
            }

            double delta_a_sch_double = 140 - ((right_delta_a_test_ave / 4) * 80);
            int delta_a_sch_int = (int)delta_a_sch_double;
            if (delta_a_sch_int < 50)
                delta_a_sch_int = 50;
            else if (delta_a_sch_int > 222)
                delta_a_sch_int = 222;
            ui->label_75->setGeometry(10, delta_a_sch_int, 34, 4);

            double delta_b_sch_double = 170 + ((right_delta_b_test_ave / 3) * 90);
            int delta_b_sch_int = (int)delta_b_sch_double;
            if (delta_b_sch_int < 80)
                delta_b_sch_int = 80;
            else if (delta_b_sch_int > 250)
                delta_b_sch_int = 250;
            double delta_c_sch_double = 140 - ((right_delta_c_test_ave / 3) * 90);
            int delta_c_sch_int = (int)delta_c_sch_double;
            if (delta_c_sch_int < 50)
                delta_c_sch_int = 50;
            else if (delta_c_sch_int > 220)
                delta_c_sch_int = 220;
            ui->label_78->setGeometry(delta_b_sch_int, delta_c_sch_int, 10, 10);

            ui->label_101->setText(QString::number(RoundFunction(right_a_test, 2)));
            ui->label_103->setText(QString::number(RoundFunction(right_b_test, 2)));
            ui->label_105->setText(QString::number(RoundFunction(right_c_test, 2)));
            ui->label_107->setText(QString::number(RoundFunction(right_delta_e_test, 2)));
            ui->label_110->setText(QString::number(static_parameters.value_1));
            ui->label_113->setText(QString::number(static_parameters.value_2));
        }
    }


    ui->label_19->setText("a " + QString::number(left_a_test));
    ui->label_16->setText("b " + QString::number(left_b_test));
    ui->label_17->setText("c " + QString::number(left_c_test));
    ui->label_18->setText("E " + QString::number(left_delta_e_test));
    if (left_delta_e_test < 2) {
        ui->label_28->setStyleSheet("image: url(:/images/images/whiteLeftRectangleImage.png);");
        ui->label_18->setStyleSheet("background-color: rgb(194, 194, 194); font: 34px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_19->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_16->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_17->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
    } else if (left_delta_e_test >= 2 && left_delta_e_test < 5) {
        ui->label_28->setStyleSheet("image: url(:/images/images/blueLeftRectangleImage.png);");
        ui->label_18->setStyleSheet("background-color: rgb(52, 154, 211); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_19->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_16->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_17->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    } else if (left_delta_e_test >= 5 && left_delta_e_test < 9) {
        ui->label_28->setStyleSheet("image: url(:/images/images/brownLeftRectangleImage.png);");
        ui->label_18->setStyleSheet("background-color: rgb(150, 117, 0); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_19->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_16->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_17->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    } else {
        ui->label_28->setStyleSheet("image: url(:/images/images/redLeftRectangleImage.png);");
        ui->label_18->setStyleSheet("background-color: rgb(181, 0, 0); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_19->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_16->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_17->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    }

    ui->label_20->setText("a " + QString::number(middle_a_test));
    ui->label_21->setText("b " + QString::number(middle_b_test));
    ui->label_22->setText("c " + QString::number(middle_c_test));
    ui->label_23->setText("E " + QString::number(middle_delta_e_test));
    if (middle_delta_e_test < 2) {
        ui->label_29->setStyleSheet("image: url(:/images/images/whiteMiddleRectangleImage.png);");
        ui->label_23->setStyleSheet("background-color: rgb(194, 194, 194); font: 34px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_20->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_21->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_22->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
    } else if (middle_delta_e_test >= 2 && middle_delta_e_test < 5) {
        ui->label_29->setStyleSheet("image: url(:/images/images/blueMiddleRectangleImage.png);");
        ui->label_23->setStyleSheet("background-color: rgb(52, 154, 211); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_20->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_21->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_22->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    } else if (middle_delta_e_test >= 5 && middle_delta_e_test < 9) {
        ui->label_29->setStyleSheet("image: url(:/images/images/brownMiddleRectangleImage.png);");
        ui->label_23->setStyleSheet("background-color: rgb(150, 117, 0); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_20->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_21->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_22->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    } else {
        ui->label_29->setStyleSheet("image: url(:/images/images/redMiddleRectangleImage.png);");
        ui->label_23->setStyleSheet("background-color: rgb(181, 0, 0); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_20->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_21->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_22->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    }

    ui->label_24->setText("a " + QString::number(right_a_test));
    ui->label_25->setText("b " + QString::number(right_b_test));
    ui->label_26->setText("c " + QString::number(right_c_test));
    ui->label_27->setText("E " + QString::number(right_delta_e_test));
    if (right_delta_e_test < 2) {
        ui->label_30->setStyleSheet("image: url(:/images/images/whiteRightRectangleImage.png);");
        ui->label_27->setStyleSheet("background-color: rgb(194, 194, 194); font: 34px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_24->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_25->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
        ui->label_26->setStyleSheet("background-color: rgb(194, 194, 194); font: 14px 'Roboto'; color: rgb(92, 92, 92); border: 0px;");
    } else if (right_delta_e_test >= 2 && right_delta_e_test < 5) {
        ui->label_30->setStyleSheet("image: url(:/images/images/blueRightRectangleImage.png);");
        ui->label_27->setStyleSheet("background-color: rgb(52, 154, 211); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_24->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_25->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_26->setStyleSheet("background-color: rgb(52, 154, 211); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    } else if (right_delta_e_test >= 5 && right_delta_e_test < 9) {
        ui->label_30->setStyleSheet("image: url(:/images/images/brownRightRectangleImage.png);");
        ui->label_27->setStyleSheet("background-color: rgb(150, 117, 0); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_24->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_25->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_26->setStyleSheet("background-color: rgb(150, 117, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    } else {
        ui->label_30->setStyleSheet("image: url(:/images/images/redRightRectangleImage.png);");
        ui->label_27->setStyleSheet("background-color: rgb(181, 0, 0); font: 34px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_24->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_25->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
        ui->label_26->setStyleSheet("background-color: rgb(181, 0, 0); font: 14px 'Roboto'; color: rgb(194, 194, 194); border: 0px;");
    }

    ui->label_31->setText(QString::number(left_middle_delta_e_test));
    if (left_middle_delta_e_test < 2)
        ui->label_31->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 2px solid rgb(94, 94, 94);");
    else if (left_middle_delta_e_test >= 2 && left_middle_delta_e_test < 5)
        ui->label_31->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");
    else if (left_middle_delta_e_test >= 5 && left_middle_delta_e_test < 9)
        ui->label_31->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(150, 117, 0); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");
    else
        ui->label_31->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(181, 0, 0); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");

    ui->label_32->setText(QString::number(left_right_delta_e_test));
    if (left_right_delta_e_test < 2)
        ui->label_32->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 2px solid rgb(94, 94, 94);");
    else if (left_right_delta_e_test >= 2 && left_right_delta_e_test < 5)
        ui->label_32->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");
    else if (left_right_delta_e_test >= 5 && left_right_delta_e_test < 9)
        ui->label_32->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(150, 117, 0); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");
    else
        ui->label_32->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(181, 0, 0); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");

    ui->label_33->setText(QString::number(middle_right_delta_e_test));
    if (middle_right_delta_e_test < 2)
        ui->label_33->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 2px solid rgb(94, 94, 94);");
    else if (middle_right_delta_e_test >= 2 && middle_right_delta_e_test < 5)
        ui->label_33->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(52, 154, 211); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");
    else if (middle_right_delta_e_test >= 5 && middle_right_delta_e_test < 9)
        ui->label_33->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(150, 117, 0); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");
    else
        ui->label_33->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(181, 0, 0); color: rgb(194, 194, 194); border: 2px solid rgb(94, 94, 94);");

    if (left_delta_e_test < 2)
        static_parameters.graphic_value_list_1.prepend(2);
    else if (left_delta_e_test >= 2 && left_delta_e_test < 5)
        static_parameters.graphic_value_list_1.prepend(3);
    else if (left_delta_e_test >= 5 && left_delta_e_test < 9)
        static_parameters.graphic_value_list_1.prepend(4);
    else
        static_parameters.graphic_value_list_1.prepend(5);
    static_parameters.graphic_value_list_1.removeLast();

    if (middle_delta_e_test < 2)
        static_parameters.graphic_value_list_2.prepend(2);
    else if (middle_delta_e_test >= 2 && middle_delta_e_test < 5)
        static_parameters.graphic_value_list_2.prepend(3);
    else if (middle_delta_e_test >= 5 && middle_delta_e_test < 9)
        static_parameters.graphic_value_list_2.prepend(4);
    else
        static_parameters.graphic_value_list_2.prepend(5);
    static_parameters.graphic_value_list_2.removeLast();

    if (right_delta_e_test < 2)
        static_parameters.graphic_value_list_3.prepend(2);
    else if (right_delta_e_test >= 2 && right_delta_e_test < 5)
        static_parameters.graphic_value_list_3.prepend(3);
    else if (right_delta_e_test >= 5 && right_delta_e_test < 9)
        static_parameters.graphic_value_list_3.prepend(4);
    else
        static_parameters.graphic_value_list_3.prepend(5);
    static_parameters.graphic_value_list_3.removeLast();

    pixmap->fill(QColor(94, 94, 94));
    DrawShape1(static_parameters.graphic_value_list_1, 0, 53, 34, static_parameters.color_array_length);
    DrawShape1(static_parameters.graphic_value_list_2, 57, 53, 34, static_parameters.color_array_length);
    DrawShape1(static_parameters.graphic_value_list_3, 114, 53, 34, static_parameters.color_array_length);

    static_parameters.last_meter = static_parameters.last_meter + 1;
    if (static_parameters.graphic_meter_list.length() < static_parameters.color_array_length) {
        static_parameters.graphic_meter_list.append(static_parameters.last_meter);
    } else {
        static_parameters.graphic_meter_list.removeAt(0);
        static_parameters.graphic_meter_list.append(static_parameters.last_meter);
    }
    DrawText1(static_parameters.graphic_meter_list, 170, 35, 15, static_parameters.graphic_meter_list.length());

    line_chart_params.x_axis_value_1 = line_chart_params.x_axis_value_1 + 1;
    DrawPoint1(line_chart_params.line_chart_1_series_1, line_chart_params.line_chart_1_series_2, line_chart_params.line_chart_1_series_3,
               line_chart_params.line_chart_1_value_axis_2, line_chart_params.line_chart_1_value_axis_1, line_chart_params.x_axis_value_1,
               left_middle_delta_e_test, 1, 0, 0, line_chart_params.x_axis_value_1, 0, 20);
    DrawPoint1(line_chart_params.line_chart_2_series_1, line_chart_params.line_chart_2_series_2, line_chart_params.line_chart_2_series_3,
               line_chart_params.line_chart_2_value_axis_2, line_chart_params.line_chart_2_value_axis_1, line_chart_params.x_axis_value_1,
               middle_right_delta_e_test, 1, 0, 0, line_chart_params.x_axis_value_1, 0, 20);
    DrawPoint1(line_chart_params.line_chart_3_series_1, line_chart_params.line_chart_3_series_2, line_chart_params.line_chart_3_series_3,
               line_chart_params.line_chart_3_value_axis_2, line_chart_params.line_chart_3_value_axis_1, line_chart_params.x_axis_value_1,
               left_right_delta_e_test, 1, 0, 0, line_chart_params.x_axis_value_1, 0, 20);

    DrawPoint1(line_chart_params.line_chart_4_series_1, line_chart_params.line_chart_4_series_2, line_chart_params.line_chart_4_series_3,
               line_chart_params.line_chart_4_value_axis_2, line_chart_params.line_chart_4_value_axis_1, line_chart_params.x_axis_value_1,
               left_delta_e_test, 1, 0, 0, line_chart_params.x_axis_value_1, 0, 20);
    DrawPoint1(line_chart_params.line_chart_5_series_1, line_chart_params.line_chart_5_series_2, line_chart_params.line_chart_5_series_3,
               line_chart_params.line_chart_5_value_axis_2, line_chart_params.line_chart_5_value_axis_1, line_chart_params.x_axis_value_1,
               left_a_test, static_parameters.value_3, static_parameters.value_4, 0, line_chart_params.x_axis_value_1, -10, 20);
    DrawPoint1(line_chart_params.line_chart_6_series_1, line_chart_params.line_chart_6_series_2, line_chart_params.line_chart_6_series_3,
               line_chart_params.line_chart_6_value_axis_2, line_chart_params.line_chart_6_value_axis_1, line_chart_params.x_axis_value_1,
               left_b_test, static_parameters.value_5, static_parameters.value_6, 0, line_chart_params.x_axis_value_1, -10, 20);
    DrawPoint1(line_chart_params.line_chart_7_series_1, line_chart_params.line_chart_7_series_2, line_chart_params.line_chart_7_series_3,
               line_chart_params.line_chart_7_value_axis_2, line_chart_params.line_chart_7_value_axis_1, line_chart_params.x_axis_value_1,
               left_c_test, static_parameters.value_7, static_parameters.value_8, 0, line_chart_params.x_axis_value_1, -10, 20);

    DrawPoint1(line_chart_params.line_chart_8_series_1, line_chart_params.line_chart_8_series_2, line_chart_params.line_chart_8_series_3,
               line_chart_params.line_chart_8_value_axis_2, line_chart_params.line_chart_8_value_axis_1, line_chart_params.x_axis_value_1,
               middle_delta_e_test, 1, 0, 0, line_chart_params.x_axis_value_1, 0, 20);
    DrawPoint1(line_chart_params.line_chart_9_series_1, line_chart_params.line_chart_9_series_2, line_chart_params.line_chart_9_series_3,
               line_chart_params.line_chart_9_value_axis_2, line_chart_params.line_chart_9_value_axis_1, line_chart_params.x_axis_value_1,
               middle_a_test, static_parameters.value_3, static_parameters.value_4, 0, line_chart_params.x_axis_value_1, -10, 20);
    DrawPoint1(line_chart_params.line_chart_10_series_1, line_chart_params.line_chart_10_series_2, line_chart_params.line_chart_10_series_3,
               line_chart_params.line_chart_10_value_axis_2, line_chart_params.line_chart_10_value_axis_1, line_chart_params.x_axis_value_1,
               middle_b_test, static_parameters.value_5, static_parameters.value_6, 0, line_chart_params.x_axis_value_1, -10, 20);
    DrawPoint1(line_chart_params.line_chart_11_series_1, line_chart_params.line_chart_11_series_2, line_chart_params.line_chart_11_series_3,
               line_chart_params.line_chart_11_value_axis_2, line_chart_params.line_chart_11_value_axis_1, line_chart_params.x_axis_value_1,
               middle_c_test, static_parameters.value_7, static_parameters.value_8, 0, line_chart_params.x_axis_value_1, -10, 20);

    DrawPoint1(line_chart_params.line_chart_12_series_1, line_chart_params.line_chart_12_series_2, line_chart_params.line_chart_12_series_3,
               line_chart_params.line_chart_12_value_axis_2, line_chart_params.line_chart_12_value_axis_1, line_chart_params.x_axis_value_1,
               right_delta_e_test, 1, 0, 0, line_chart_params.x_axis_value_1, 0, 20);
    DrawPoint1(line_chart_params.line_chart_13_series_1, line_chart_params.line_chart_13_series_2, line_chart_params.line_chart_13_series_3,
               line_chart_params.line_chart_13_value_axis_2, line_chart_params.line_chart_13_value_axis_1, line_chart_params.x_axis_value_1,
               right_a_test, static_parameters.value_3, static_parameters.value_4, 0, line_chart_params.x_axis_value_1, -10, 20);
    DrawPoint1(line_chart_params.line_chart_14_series_1, line_chart_params.line_chart_14_series_2, line_chart_params.line_chart_14_series_3,
               line_chart_params.line_chart_14_value_axis_2, line_chart_params.line_chart_14_value_axis_1, line_chart_params.x_axis_value_1,
               right_b_test, static_parameters.value_5, static_parameters.value_6, 0, line_chart_params.x_axis_value_1, -10, 20);
    DrawPoint1(line_chart_params.line_chart_15_series_1, line_chart_params.line_chart_15_series_2, line_chart_params.line_chart_15_series_3,
               line_chart_params.line_chart_15_value_axis_2, line_chart_params.line_chart_15_value_axis_1, line_chart_params.x_axis_value_1,
               right_c_test, static_parameters.value_7, static_parameters.value_8, 0, line_chart_params.x_axis_value_1, -10, 20);

    ui->label_54->setText("✎     Left E = " + QString::number(left_delta_e_test) + " Middle E = " + QString::number(middle_delta_e_test) +
                          " Right E = " + QString::number(right_delta_e_test));
    ui->label_55->setText("✎     Left-Middle E = " + QString::number(left_middle_delta_e_test) + " Middle-Right E = " + QString::number(middle_right_delta_e_test) +
                          " Left-Right E = " + QString::number(left_right_delta_e_test));
    ui->label_56->setText("✎     Left a = " + QString::number(left_a_test) + " Middle a = " + QString::number(middle_a_test) + " Right a = " +
                          QString::number(right_a_test));
}

void MainWindow::onLineChartValueChanged()
{
    if (line_chart_thread_value == 0) {
        int random_int = rand() % 20;
        double random = (double)random_int;
        if (y_line_chart_axis_value < random_int)
            y_line_chart_axis_value = random_int;

        DrawPoint3(line_chart_params.line_chart_32_series, line_chart_params.line_chart_32_value_axis_1, line_chart_params.line_chart_32_value_axis_2,
                   y_line_chart_axis_value, x_line_chart_axis_value, random);
        ui->label_315->setText(QString::number(random_int));
        x_line_chart_axis_value = x_line_chart_axis_value + 1;

    } else if (line_chart_thread_value == 1) {
        int random_int = rand() % 20;
        double random = (double)random_int;
        if (y_line_chart_axis_value < random_int)
            y_line_chart_axis_value = random_int;

        DrawPoint3(line_chart_params.line_chart_33_series, line_chart_params.line_chart_33_value_axis_1, line_chart_params.line_chart_33_value_axis_2,
                   y_line_chart_axis_value, x_line_chart_axis_value, random);
        ui->label_317->setText(QString::number(random_int));
        x_line_chart_axis_value = x_line_chart_axis_value + 1;

    } else if (line_chart_thread_value == 2) {
        int random_int = rand() % 20;
        double random = (double)random_int;
        if(y_line_chart_axis_value < random_int)
            y_line_chart_axis_value = random_int;

        DrawPoint3(line_chart_params.line_chart_34_series, line_chart_params.line_chart_34_value_axis_1, line_chart_params.line_chart_34_value_axis_2,
                   y_line_chart_axis_value, x_line_chart_axis_value, random);
        ui->label_319->setText(QString::number(random_int));
        x_line_chart_axis_value = x_line_chart_axis_value + 1;
    }
}

void MainWindow::onSignalMapperFunction(int counter)
{
    if (rec_buttons_state[counter] == false) {
        for (int i = 0; i < 10; i++) {
            rec_buttons[i]->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); border: 1px solid black; border-radius: 5px; width: 45px; "
                                          "height: 45px; } QPushButton:hover { background-image: url(:/images/images/okStockImage.png); }");
            rec_buttons_state[i] = false;
        }
        static_parameters.button_counter_list.clear();

        rec_buttons[counter]->setStyleSheet("QPushButton { background-image: url(:/images/images/okStockImage.png); border: 1px solid black; "
                                            "border-radius: 5px; width: 45px; height: 45px; }");
        rec_buttons_state[counter] = true;
        static_parameters.button_counter_list.append(counter);
    }

    if (static_parameters.button_state_2 == true) {

        QList<QString> recordValueList;
        if (static_parameters.button_counter_list[0] == 0) {
            for (int i = 0; i < static_parameters.record_list_0.length(); i++)
                recordValueList.append(static_parameters.record_list_0[i]);
        } else if (static_parameters.button_counter_list[0] == 1) {
            for (int i = 0; i < static_parameters.record_list_1.length(); i++)
                recordValueList.append(static_parameters.record_list_1[i]);
        } else if (static_parameters.button_counter_list[0] == 2) {
            for (int i = 0; i < static_parameters.record_list_2.length(); i++)
                recordValueList.append(static_parameters.record_list_2[i]);
        } else if (static_parameters.button_counter_list[0] == 3) {
            for (int i = 0; i < static_parameters.record_list_3.length(); i++)
                recordValueList.append(static_parameters.record_list_3[i]);
        } else if (static_parameters.button_counter_list[0] == 4) {
            for (int i = 0; i < static_parameters.record_list_4.length(); i++)
                recordValueList.append(static_parameters.record_list_4[i]);
        } else if (static_parameters.button_counter_list[0] == 5) {
            for (int i = 0; i < static_parameters.record_list_5.length(); i++)
                recordValueList.append(static_parameters.record_list_5[i]);
        } else if (static_parameters.button_counter_list[0] == 6) {
            for (int i = 0; i < static_parameters.record_list_6.length(); i++)
                recordValueList.append(static_parameters.record_list_6[i]);
        } else if (static_parameters.button_counter_list[0] == 7) {
            for (int i = 0; i < static_parameters.record_list_7.length(); i++)
                recordValueList.append(static_parameters.record_list_7[i]);
        } else if (static_parameters.button_counter_list[0] == 8) {
            for (int i = 0; i < static_parameters.record_list_8.length(); i++)
                recordValueList.append(static_parameters.record_list_8[i]);
        } else if (static_parameters.button_counter_list[0] == 9) {
            for (int i = 0; i < static_parameters.record_list_9.length(); i++)
                recordValueList.append(static_parameters.record_list_9[i]);
        } else {
            for (int i = 0; i < static_parameters.record_list_9.length(); i++)
                recordValueList.append("0.00");
        }

        ui->label_172->setText(recordValueList[0]);
        ui->label_174->setText(recordValueList[1]);
        ui->label_176->setText(recordValueList[2]);
        ui->label_181->setText(recordValueList[3]);
        ui->label_182->setText(recordValueList[4]);
        ui->label_186->setText(QString::number(RoundFunction(static_parameters.value_3, 2)));
        ui->label_149->setText(recordValueList[0]);
        ui->label_151->setText(recordValueList[1]);
        ui->label_153->setText(recordValueList[2]);

        double max_a_value_sch_double = (120 - 2) - ((recordValueList[5].toDouble() / 4) * 80);
        int max_a_value_sch_int = (int) max_a_value_sch_double;
        if (max_a_value_sch_int < 30)
            max_a_value_sch_int = 30;
        ui->label_167->setGeometry(10, max_a_value_sch_int, 34, 4);
        double min_a_value_sch_double = (120 + 2) - ((recordValueList[6].toDouble() / 4) * 80);
        int min_a_value_sch_int = (int) min_a_value_sch_double;
        if (min_a_value_sch_int > 210)
            min_a_value_sch_int = 210;
        ui->label_168->setGeometry(10, min_a_value_sch_int, 34, 4);

        double min_b_value_sch_double = (170 + 1) + ((recordValueList[8].toDouble() / 3) * 90);
        int min_b_value_sch_int = (int) min_b_value_sch_double;
        if (min_b_value_sch_int < 80)
            min_b_value_sch_int = 79;
        double max_b_value_sch_double = (recordValueList[7].toDouble() - recordValueList[8].toDouble()) * 30;
        int max_b_value_sch_int = (int) max_b_value_sch_double;
        if (max_b_value_sch_int > 180)
            max_b_value_sch_int = 181;
        double min_c_value_sch_double = (recordValueList[9].toDouble() - recordValueList[10].toDouble()) * 30;
        int min_c_value_sch_int = (int) min_c_value_sch_double;
        if (min_c_value_sch_int > 150)
            min_c_value_sch_int = 151;
        double max_c_value_sch_double = (120 - 1) - ((recordValueList[9].toDouble() / 3) * 90);
        int max_c_value_sch_int = (int) max_c_value_sch_double;
        if (max_c_value_sch_int < 30)
            max_c_value_sch_int = 29;
        ui->label_170->setGeometry(min_b_value_sch_int, max_c_value_sch_int, max_b_value_sch_int, min_c_value_sch_int);
    }

    DrawGraphicsFunction(1);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    ui->pushButton->setStyleSheet("color: rgb(94, 94, 94); border: 1px solid black; text-align: left; font: 22px 'Roboto'; padding-left: 65px; "
                                  "background-image: url(:/images/images/stockOpenImage.png); background-repeat: no-repeat;");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/parametersCloseImage.png); background-repeat: no-repeat; }"
                                    "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/parametersOpenImage.png);"
                                    "background-repeat: no-repeat; }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; padding-left: 65px; "
                                    "background-image: url(:/images/images/systemCloseImage.png); background-repeat: no-repeat; } QPushButton::hover { color: rgb(94, 94, 94); "
                                    "background-image: url(:/images/images/systemOpenImage.png); background-repeat: no-repeat; }");

    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    ui->lineEdit_6->setDisabled(true);
    ui->lineEdit_7->setDisabled(true);
    ui->lineEdit_8->setDisabled(true);
    ui->lineEdit_9->setDisabled(true);
    ui->lineEdit_10->setDisabled(true);
    ui->lineEdit_11->setDisabled(true);

    ui->pushButton_28->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okStockImage.png); "
                                     "background-repeat: no-repeat; }");
    ui->pushButton_28->setEnabled(false);
    static_parameters.button_state_2 = true;
    static_parameters.button_counter_list.clear();
    ui->pushButton_23->setEnabled(false);

    static_parameters.chart_or_graphic_state = false;
    static_parameters.change_zoom_count = 0;
    ui->pushButton_22->setEnabled(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->pushButton->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; padding-left: 65px; "
                                  "background-image: url(:/images/images/stockCloseImage.png); background-repeat: no-repeat; } QPushButton::hover { "
                                  "color: rgb(94, 94, 94); background-image: url(:/images/images/stockOpenImage.png); background-repeat: no-repeat; }");
    ui->pushButton_2->setStyleSheet("color: rgb(94, 94, 94); border: 1px solid black; text-align: left; font: 22px 'Roboto'; padding-left: 65px; "
                                    "background-image: url(:/images/images/parametersOpenImage.png); background-repeat: no-repeat;");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; padding-left: 65px; "
                                    "background-image: url(:/images/images/systemCloseImage.png); background-repeat: no-repeat; } QPushButton::hover { "
                                    "color: rgb(94, 94, 94); background-image: url(:/images/images/systemOpenImage.png); background-repeat: no-repeat; }");
}

void MainWindow::on_pushButton_3_clicked()
{
    login_dialog = new LoginDialog(this);
    login_dialog->show();
    connect(login_dialog, SIGNAL(atLoginDialog(QString)),
            this, SLOT(onLoginDialog(QString)));
}

void MainWindow::on_pushButton_4_clicked()
{
    yes_no_dialog = new YesNoDialog(this);
    yes_no_dialog->show();
    connect(yes_no_dialog, SIGNAL(atYesNoDialog()),
            this, SLOT(close()));
}

void MainWindow::on_pushButton_5_clicked()
{
    language_dialog = new LanguageDialog(this);
    language_dialog->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->label_34->setText("Left Section Values");
    static_parameters.choose_sch_push_button_1 = 0;

    ui->label_58->setText(QString::number(static_parameters.value_9));
    ui->label_60->setText(QString::number(static_parameters.value_10));
    ui->label_62->setText(QString::number(static_parameters.value_11));
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; }");
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->label_34->setText("Middle Section Values");
    static_parameters.choose_sch_push_button_1 = 1;

    ui->label_58->setText(QString::number(static_parameters.value_12));
    ui->label_60->setText(QString::number(static_parameters.value_13));
    ui->label_62->setText(QString::number(static_parameters.value_14));
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; }");
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->label_34->setText("Right Section Values");
    static_parameters.choose_sch_push_button_1 = 2;

    ui->label_58->setText(QString::number(static_parameters.value_15));
    ui->label_60->setText(QString::number(static_parameters.value_16));
    ui->label_62->setText(QString::number(static_parameters.value_17));
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; }");
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->pushButton_10->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid black; text-align: center; "
                                     "font: 14px 'Roboto'; }");
    ui->pushButton_11->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid black; text-align: center; "
                                     "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                     "border: 1px solid black; text-align: center; font: 15px 'Roboto'; }");

    static_parameters.choose_sch_push_button_2 = 1;
    ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_58->setText("0.00");
    ui->label_60->setText("0.00");
    ui->label_62->setText("0.00");

    static_parameters.meter_list_1.clear();
    static_parameters.meter_list_2.clear();
    static_parameters.meter_list_3.clear();
    static_parameters.meter_list_4.clear();
    static_parameters.meter_list_5.clear();
    static_parameters.meter_list_6.clear();
    static_parameters.meter_list_7.clear();
    static_parameters.meter_list_8.clear();
    static_parameters.meter_list_9.clear();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->pushButton_11->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid black; text-align: center; "
                                     "font: 14px 'Roboto'; }");
    ui->pushButton_10->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid black; text-align: center; "
                                     "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                     "border: 1px solid black; text-align: center; font: 15px 'Roboto'; }");

    static_parameters.choose_sch_push_button_2 = 0;
    ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_58->setText("0.00");
    ui->label_60->setText("0.00");
    ui->label_62->setText("0.00");
}

void MainWindow::on_pushButton_12_clicked()
{
    if (static_parameters.x_move_widget_value == 1082)
        static_parameters.x_move_widget_value = 482;
    else if (static_parameters.x_move_widget_value == 482)
        static_parameters.x_move_widget_value = 1082;
    ui->widget_5->move(static_parameters.x_move_widget_value, 88);
}

void MainWindow::on_pushButton_13_clicked()
{
    static_parameters.current_meter = 0;
    ui->label_97->setText("0000 m");
}

void MainWindow::on_pushButton_14_clicked()
{
    process_thread = new ProcessThread();
    connect(process_thread, SIGNAL(atProcessValueChanged()),
            this, SLOT(onProcessValueChanged()));
    process_thread->start();
}

void MainWindow::on_pushButton_15_clicked()
{
    process_thread->stop = true;
    ui->pushButton_14->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; border-radius: 5px; "
                                     "text-align: center; } QPushButton::hover { background-color: rgb(38, 201, 84); color: rgb(94, 94, 94); border: 0px; "
                                     "border-radius: 5px; text-align: center; }");
    ui->pushButton_15->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; border-radius: 5px; "
                                     "text-align: center; }");

    static_parameters.speed = 0;
    ui->label_99->setText("00 m/min");
    ui->label_97->setText("0000 m");

    static_parameters.meter_list_1.clear();
    static_parameters.meter_list_2.clear();
    static_parameters.meter_list_3.clear();
    static_parameters.meter_list_4.clear();
    static_parameters.meter_list_5.clear();
    static_parameters.meter_list_6.clear();
    static_parameters.meter_list_7.clear();
    static_parameters.meter_list_8.clear();
    static_parameters.meter_list_9.clear();

    ui->label_75->setGeometry(10, 138, 34, 8);
    ui->label_78->setGeometry(165, 135, 10, 10);
    ui->label_58->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_60->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_62->setStyleSheet("background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 0px; text-align: left; font: 15px 'Roboto';");
    ui->label_58->setText("0.00");
    ui->label_60->setText("0.00");
    ui->label_62->setText("0.00");

    ui->label_101->setText("0.00");
    ui->label_103->setText("0.00");
    ui->label_105->setText("0.00");
    ui->label_107->setText("0.00");
    ui->label_110->setText("0.00");
    ui->label_113->setText("0.00");

    ui->label_19->setText("");
    ui->label_16->setText("");
    ui->label_17->setText("");
    ui->label_18->setText("E 0.00");
    ui->label_20->setText("");
    ui->label_21->setText("");
    ui->label_22->setText("");
    ui->label_23->setText("E 0.00");
    ui->label_24->setText("");
    ui->label_25->setText("");
    ui->label_26->setText("");
    ui->label_27->setText("E 0.00");

    ui->label_28->setStyleSheet("image: url(:/images/images/grayLeftRectangleImage.png);");
    ui->label_18->setStyleSheet("font: 34px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_19->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_16->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_17->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");

    ui->label_29->setStyleSheet("image: url(:/images/images/grayMiddleRectangleImage.png);");
    ui->label_23->setStyleSheet("font: 34px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_20->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_21->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_22->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");

    ui->label_30->setStyleSheet("image: url(:/images/images/grayRightRectangleImage.png);");
    ui->label_27->setStyleSheet("font: 34px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_24->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_25->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");
    ui->label_26->setStyleSheet("font: 14px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(92, 92, 92); border: 0px;");

    ui->label_31->setText("0.00");
    ui->label_31->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(94, 94, 94); border: 2px solid rgb(94, 94, 94);");
    ui->label_32->setText("0.00");
    ui->label_32->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(94, 94, 94); border: 2px solid rgb(94, 94, 94);");
    ui->label_33->setText("0.00");
    ui->label_33->setStyleSheet("font: 32px 'Roboto'; background-color: rgb(118, 118, 118); color: rgb(94, 94, 94); border: 2px solid rgb(94, 94, 94);");

    static_parameters.color_value_list_1.clear();
    static_parameters.color_value_list_2.clear();
    static_parameters.color_value_list_3.clear();
    static_parameters.graphic_value_list_1.clear();
    static_parameters.graphic_value_list_2.clear();
    static_parameters.graphic_value_list_3.clear();
    for (int i = 0; i < static_parameters.color_array_length; i++) {
        static_parameters.color_value_list_1.append(0);
        static_parameters.color_value_list_2.append(0);
        static_parameters.color_value_list_3.append(0);
        static_parameters.graphic_value_list_1.append(1);
        static_parameters.graphic_value_list_2.append(1);
        static_parameters.graphic_value_list_3.append(1);
    }

    pixmap->fill(QColor(94, 94, 94));
    DrawShape1(static_parameters.color_value_list_1, 0, 53, 34, static_parameters.color_array_length);
    DrawShape1(static_parameters.color_value_list_2, 57, 53, 34, static_parameters.color_array_length);
    DrawShape1(static_parameters.color_value_list_3, 114, 53, 34, static_parameters.color_array_length);

    static_parameters.graphic_meter_list.clear();
    DrawText1(static_parameters.graphic_meter_list, 170, 35, 15, static_parameters.graphic_meter_list.length());
    static_parameters.graphic_meter_list.append(0);
    static_parameters.last_meter = 0;

    ClearLineCharts1();

    ui->label_54->setText("-");
    ui->label_55->setText("-");
    ui->label_56->setText("-");
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->pushButton_16->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); font: 14px 'Roboto'; }");
    ui->pushButton_19->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_20->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_21->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_23->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");

    DrawGraphicsFunction(1);
    ui->pushButton_16->setEnabled(false);
    ui->pushButton_19->setEnabled(true);
    ui->pushButton_20->setEnabled(true);
    ui->pushButton_21->setEnabled(true);
    ui->pushButton_23->setEnabled(true);
}

void MainWindow::on_pushButton_17_clicked()
{
    if (static_parameters.chart_or_graphic_state == false) {
        ui->stackedWidget_3->setCurrentIndex(1);
        ui->groupBox_20->setStyleSheet("border: 4px solid rgb(151, 151, 151);");
        static_parameters.chart_or_graphic_state = true;
        line_chart_params.x_axis_value_2 = 0;

        double random = 0;
        double max_a_random = RandomFunction(0, 20);
        max_a_random = RoundFunction(max_a_random, 2);
        double min_a_random = RandomFunction(0, 20);
        min_a_random = RoundFunction(min_a_random, 2);
        double max_b_random = RandomFunction(-10, 20);
        max_b_random = RoundFunction(max_b_random, 2);
        double min_b_random = RandomFunction(-10, 20);
        min_b_random = RoundFunction(min_b_random, 2);
        double max_c_random = RandomFunction(-10, 20);
        max_c_random = RoundFunction(max_c_random, 2);
        double min_c_random = RandomFunction(-10, 20);
        min_c_random = RoundFunction(min_c_random, 2);

        ClearLineCharts2();

        for (int i = 0; i < 29; i++) {
            random = RandomFunction(0, 2);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_16_series_1, line_chart_params.line_chart_16_series_2, line_chart_params.line_chart_16_series_3,
                       line_chart_params.line_chart_16_value_axis_2, line_chart_params.line_chart_16_value_axis_1, line_chart_params.x_axis_value_2,
                       random, 1, 0, 0, line_chart_params.x_axis_value_2, 0, 2);
            random = RandomFunction(0, 2);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_17_series_1, line_chart_params.line_chart_17_series_2, line_chart_params.line_chart_17_series_3,
                       line_chart_params.line_chart_17_value_axis_2, line_chart_params.line_chart_17_value_axis_1, line_chart_params.x_axis_value_2,
                       random, 1, 0, 0, line_chart_params.x_axis_value_2, 0, 2);
            random = RandomFunction(0, 2);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_18_series_1, line_chart_params.line_chart_18_series_2, line_chart_params.line_chart_18_series_3,
                       line_chart_params.line_chart_18_value_axis_2, line_chart_params.line_chart_18_value_axis_1, line_chart_params.x_axis_value_2,
                       random, 1, 0, 0, line_chart_params.x_axis_value_2, 0, 2);

            random = RandomFunction(0, 10);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_19_series_1, line_chart_params.line_chart_19_series_2, line_chart_params.line_chart_19_series_3,
                       line_chart_params.line_chart_19_value_axis_2, line_chart_params.line_chart_19_value_axis_1, line_chart_params.x_axis_value_2,
                       random, 1, 0, 0, line_chart_params.x_axis_value_2, 0, 10);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_20_series_1, line_chart_params.line_chart_20_series_2, line_chart_params.line_chart_20_series_3,
                       line_chart_params.line_chart_20_value_axis_2, line_chart_params.line_chart_20_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_a_random, min_a_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_21_series_1, line_chart_params.line_chart_21_series_2, line_chart_params.line_chart_21_series_3,
                       line_chart_params.line_chart_21_value_axis_2, line_chart_params.line_chart_21_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_b_random, min_b_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_22_series_1, line_chart_params.line_chart_22_series_2, line_chart_params.line_chart_22_series_3,
                       line_chart_params.line_chart_22_value_axis_2, line_chart_params.line_chart_22_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_c_random, min_c_random, 0, line_chart_params.x_axis_value_2, -10, 20);

            random = RandomFunction(0, 10);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_23_series_1, line_chart_params.line_chart_23_series_2, line_chart_params.line_chart_23_series_3,
                       line_chart_params.line_chart_23_value_axis_2, line_chart_params.line_chart_23_value_axis_1, line_chart_params.x_axis_value_2,
                       random, 1, 0, 0, line_chart_params.x_axis_value_2, 0, 10);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_24_series_1, line_chart_params.line_chart_24_series_2, line_chart_params.line_chart_24_series_3,
                       line_chart_params.line_chart_24_value_axis_2, line_chart_params.line_chart_24_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_a_random, min_a_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_25_series_1, line_chart_params.line_chart_25_series_2, line_chart_params.line_chart_25_series_3,
                       line_chart_params.line_chart_25_value_axis_2, line_chart_params.line_chart_25_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_b_random, min_b_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_26_series_1, line_chart_params.line_chart_26_series_2, line_chart_params.line_chart_26_series_3,
                       line_chart_params.line_chart_26_value_axis_2, line_chart_params.line_chart_26_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_c_random, min_c_random, 0, line_chart_params.x_axis_value_2, -10, 20);

            random = RandomFunction(0, 10);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_27_series_1, line_chart_params.line_chart_27_series_2, line_chart_params.line_chart_27_series_3,
                       line_chart_params.line_chart_27_value_axis_2, line_chart_params.line_chart_27_value_axis_1, line_chart_params.x_axis_value_2,
                       random, 1, 0, 0, line_chart_params.x_axis_value_2, 0, 10);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_28_series_1, line_chart_params.line_chart_28_series_2, line_chart_params.line_chart_28_series_3,
                       line_chart_params.line_chart_28_value_axis_2, line_chart_params.line_chart_28_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_a_random, min_a_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_29_series_1, line_chart_params.line_chart_29_series_2, line_chart_params.line_chart_29_series_3,
                       line_chart_params.line_chart_29_value_axis_2, line_chart_params.line_chart_29_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_b_random, min_b_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            random = RandomFunction(-10, 20);
            random = RoundFunction(random, 2);
            DrawPoint1(line_chart_params.line_chart_30_series_1, line_chart_params.line_chart_30_series_2, line_chart_params.line_chart_30_series_3,
                       line_chart_params.line_chart_30_value_axis_2, line_chart_params.line_chart_30_value_axis_1, line_chart_params.x_axis_value_2,
                       random, max_c_random, min_c_random, 0, line_chart_params.x_axis_value_2, -10, 20);
            line_chart_params.x_axis_value_2 = line_chart_params.x_axis_value_2 + 50;
        }
    } else if (static_parameters.chart_or_graphic_state == true) {
        ui->stackedWidget_3->setCurrentIndex(0);
        ui->groupBox_20->setStyleSheet("border: 2px solid rgb(151, 151, 151);");
        static_parameters.chart_or_graphic_state = false;
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                  "padding-left: 65px; background-image: url(:/images/images/stockCloseImage.png); background-repeat: no-repeat; } "
                                  "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/stockOpenImage.png); "
                                  "background-repeat: no-repeat; }");
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->pushButton_16->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_19->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); font: 14px 'Roboto'; }");
    ui->pushButton_20->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_21->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_23->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");

    DrawGraphicsFunction(1);
    ui->pushButton_16->setEnabled(true);
    ui->pushButton_19->setEnabled(false);
    ui->pushButton_20->setEnabled(true);
    ui->pushButton_21->setEnabled(true);
    ui->pushButton_23->setEnabled(true);
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->pushButton_16->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_19->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_20->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); font: 14px 'Roboto'; }");
    ui->pushButton_21->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_23->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");

    DrawGraphicsFunction(1);
    ui->pushButton_16->setEnabled(true);
    ui->pushButton_19->setEnabled(true);
    ui->pushButton_20->setEnabled(false);
    ui->pushButton_21->setEnabled(true);
    ui->pushButton_23->setEnabled(true);
}

void MainWindow::on_pushButton_21_clicked()
{
    ui->pushButton_16->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_19->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_20->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_21->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); font: 14px 'Roboto'; }");
    ui->pushButton_23->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");

    DrawGraphicsFunction(1);
    ui->pushButton_16->setEnabled(true);
    ui->pushButton_19->setEnabled(true);
    ui->pushButton_20->setEnabled(true);
    ui->pushButton_21->setEnabled(false);
    ui->pushButton_23->setEnabled(true);
}

void MainWindow::on_pushButton_22_clicked()
{
    ui->pushButton_22->setEnabled(false);
    ui->pushButton_22->setStyleSheet("");
    ui->label_116->setText("");

    DrawGraphicsFunction(1);
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->pushButton_16->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_19->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_20->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_21->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); font: 14px 'Roboto'; }"
                                     "QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); }");
    ui->pushButton_23->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); font: 14px 'Roboto'; }");

    DrawGraphicsFunction(1);
    ui->pushButton_16->setEnabled(true);
    ui->pushButton_19->setEnabled(true);
    ui->pushButton_20->setEnabled(true);
    ui->pushButton_21->setEnabled(true);
    ui->pushButton_23->setEnabled(false);
}

void MainWindow::on_pushButton_24_clicked()
{
    if (static_parameters.change_zoom_count >= 0 && static_parameters.change_zoom_count < 2)
        static_parameters.change_zoom_count = static_parameters.change_zoom_count + 1;

    if (static_parameters.change_zoom_count == 0) {
        static_parameters.zoom_state = 0;
        DrawGraphicsFunction(1);
    } else if (static_parameters.change_zoom_count == 1) {
        static_parameters.zoom_state = 1;
        DrawGraphicsFunction(2);
    } else if (static_parameters.change_zoom_count == 2) {
        static_parameters.zoom_state = 1;
        DrawGraphicsFunction(4);
    }
}

void MainWindow::on_pushButton_25_clicked()
{
    if (static_parameters.change_zoom_count > 0) {
        static_parameters.change_zoom_count = static_parameters.change_zoom_count - 1;
        if (static_parameters.change_zoom_count == 2) {
            static_parameters.zoom_state = 1;
            DrawGraphicsFunction(4);
        } else if (static_parameters.change_zoom_count == 1) {
            static_parameters.zoom_state = 1;
            DrawGraphicsFunction(2);
        } else if (static_parameters.change_zoom_count == 0) {
            static_parameters.zoom_state = 0;
            DrawGraphicsFunction(1);
        }
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->lineEdit->setText("0.00");
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_2->setText("0.00");
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_2->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_3->setText("0.00");
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_3->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_4->setText("0.00");
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_4->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_5->setText("0.00");
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_5->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_6->setText("0.00");
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_6->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_7->setText("0.00");
    ui->lineEdit_7->setEnabled(false);
    ui->lineEdit_7->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_8->setText("0.00");
    ui->lineEdit_8->setEnabled(false);
    ui->lineEdit_8->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_9->setText("0.00");
    ui->lineEdit_9->setEnabled(false);
    ui->lineEdit_9->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_10->setText("0.00");
    ui->lineEdit_10->setEnabled(false);
    ui->lineEdit_10->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_11->setText("0.00");
    ui->lineEdit_11->setEnabled(false);
    ui->lineEdit_11->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");

    static_parameters.button_state_2 = true;
    ui->pushButton_28->setEnabled(false);
    ui->pushButton_28->setStyleSheet("border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okStockImage.png); background-repeat: no-repeat;");
    ui->pushButton_29->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayCloseStockImage.png); "
                                     "background-repeat: no-repeat; } QPushButton:hover { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayOpenStockImage.png); "
                                     "background-repeat: no-repeat; } ");
    ui->pushButton_30->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayCloseStockImage.png); "
                                     "background-repeat: no-repeat; } QPushButton:hover { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayOpenStockImage.png); "
                                     "background-repeat: no-repeat; } ");

    if (static_parameters.button_state_2 == true) {

        QList<QString> recordValueList;
        if (static_parameters.button_counter_list[0] == 0) {
            for (int i = 0; i < static_parameters.record_list_0.length(); i++)
                recordValueList.append(static_parameters.record_list_0[i]);
        } else if(static_parameters.button_counter_list[0] == 1) {
            for (int i = 0; i < static_parameters.record_list_1.length(); i++)
                recordValueList.append(static_parameters.record_list_1[i]);
        } else if (static_parameters.button_counter_list[0] == 2) {
            for (int i = 0; i < static_parameters.record_list_2.length(); i++)
                recordValueList.append(static_parameters.record_list_2[i]);
        } else if (static_parameters.button_counter_list[0] == 3) {
            for (int i = 0; i < static_parameters.record_list_3.length(); i++)
                recordValueList.append(static_parameters.record_list_3[i]);
        } else if (static_parameters.button_counter_list[0] == 4) {
            for (int i = 0; i < static_parameters.record_list_4.length(); i++)
                recordValueList.append(static_parameters.record_list_4[i]);
        } else if (static_parameters.button_counter_list[0] == 5) {
            for (int i = 0; i < static_parameters.record_list_5.length(); i++)
                recordValueList.append(static_parameters.record_list_5[i]);
        } else if (static_parameters.button_counter_list[0] == 6) {
            for (int i = 0; i < static_parameters.record_list_6.length(); i++)
                recordValueList.append(static_parameters.record_list_6[i]);
        } else if (static_parameters.button_counter_list[0] == 7) {
            for (int i = 0; i < static_parameters.record_list_7.length(); i++)
                recordValueList.append(static_parameters.record_list_7[i]);
        } else if (static_parameters.button_counter_list[0] == 8) {
            for (int i = 0; i < static_parameters.record_list_8.length(); i++)
                recordValueList.append(static_parameters.record_list_8[i]);
        } else if (static_parameters.button_counter_list[0] == 9) {
            for (int i = 0; i < static_parameters.record_list_9.length(); i++)
                recordValueList.append(static_parameters.record_list_9[i]);
        } else {
            for (int i = 0; i < static_parameters.record_list_9.length(); i++)
                recordValueList.append("0.00");
        }

        ui->label_172->setText(recordValueList[0]);
        ui->label_174->setText(recordValueList[1]);
        ui->label_176->setText(recordValueList[2]);
        ui->label_181->setText(recordValueList[3]);
        ui->label_182->setText(recordValueList[4]);
        ui->label_186->setText(QString::number(RoundFunction(static_parameters.value_3, 2)));
        ui->label_149->setText(recordValueList[0]);
        ui->label_151->setText(recordValueList[1]);
        ui->label_153->setText(recordValueList[2]);

        double max_a_sch_double = (120 - 2) - ((recordValueList[5].toDouble() / 4) * 80);
        int max_a_sch_int = (int)max_a_sch_double;
        if (max_a_sch_int < 30)
            max_a_sch_int = 30;
        ui->label_167->setGeometry(10, max_a_sch_int, 34, 4);

        double min_a_sch_double = (120 + 2) - ((recordValueList[6].toDouble() / 4) * 80);
        int min_a_sch_int = (int)min_a_sch_double;
        if (min_a_sch_int > 210)
            min_a_sch_int = 210;
        ui->label_168->setGeometry(10, min_a_sch_int, 34, 4);

        double min_b_sch_double = (170 + 1) + ((recordValueList[8].toDouble() / 3) * 90);
        int min_b_sch_int = (int)min_b_sch_double;
        if (min_b_sch_int < 80)
            min_b_sch_int = 79;
        double max_b_sch_double = (recordValueList[7].toDouble() - recordValueList[8].toDouble()) * 30;
        int max_b_sch_int = (int)max_b_sch_double;
        if (max_b_sch_int > 180)
            max_b_sch_int = 181;
        double min_c_sch_double = (recordValueList[9].toDouble() - recordValueList[10].toDouble()) * 30;
        int min_c_sch_int = (int)min_c_sch_double;
        if (min_c_sch_int > 150)
            min_c_sch_int = 151;
        double max_c_sch_double = (120 - 1) - ((recordValueList[9].toDouble() / 3) * 90);
        int max_c_sch_int = (int)max_c_sch_double;
        if (max_c_sch_int < 30)
            max_c_sch_int = 29;
        ui->label_170->setGeometry(min_b_sch_int, max_c_sch_int, max_b_sch_int, min_c_sch_int);
    }

    DrawGraphicsFunction(1);
}

void MainWindow::on_pushButton_29_clicked()
{
    ui->label_172->setText(ui->lineEdit_7->text());
    ui->label_174->setText(ui->lineEdit_8->text());
    ui->label_176->setText(ui->lineEdit_9->text());
    ui->label_181->setText(ui->lineEdit_10->text());
    ui->label_182->setText(ui->lineEdit_11->text());
    ui->label_186->setText(QString::number(RoundFunction(static_parameters.value_3, 2)));
    ui->label_149->setText(ui->lineEdit_7->text());
    ui->label_151->setText(ui->lineEdit_8->text());
    ui->label_153->setText(ui->lineEdit_9->text());

    double max_a_sch_double = (120 - 2) - ((ui->lineEdit->text().toDouble() / 4) * 80);
    int max_a_sch_int = (int)max_a_sch_double;
    if (max_a_sch_int < 30)
        max_a_sch_int = 30;
    ui->label_167->setGeometry(10, max_a_sch_int, 34, 4);

    double min_a_sch_double = (120 + 2) - ((ui->lineEdit_2->text().toDouble() / 4) * 80);
    int min_a_sch_int = (int)min_a_sch_double;
    if (min_a_sch_int > 210)
        min_a_sch_int = 210;
    ui->label_168->setGeometry(10, min_a_sch_int, 34, 4);

    double min_b_sch_double = (170 + 1) + ((ui->lineEdit_4->text().toDouble() / 3) * 90);
    int min_b_sch_int = (int)min_b_sch_double;
    if (min_b_sch_int < 80)
        min_b_sch_int = 79;
    double max_b_sch_double = (ui->lineEdit_3->text().toDouble() - ui->lineEdit_4->text().toDouble()) * 30;
    int max_b_sch_int = (int)max_b_sch_double;
    if (max_b_sch_int > 180)
        max_b_sch_int = 181;
    double min_c_sch_double = (ui->lineEdit_5->text().toDouble() - ui->lineEdit_6->text().toDouble()) * 30;
    int min_c_sch_int = (int)min_c_sch_double;
    if (min_c_sch_int > 150)
        min_c_sch_int = 151;
    double max_c_sch_double = (120 - 1) - ((ui->lineEdit_5->text().toDouble() / 3) * 90);
    int max_c_sch_int = (int)max_c_sch_double;
    if (max_c_sch_int < 30)
        max_c_sch_int = 29;
    ui->label_170->setGeometry(min_b_sch_int, max_c_sch_int, max_b_sch_int, min_c_sch_int);

    ui->lineEdit->setText("0.00");
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_2->setText("0.00");
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_2->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_3->setText("0.00");
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_3->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_4->setText("0.00");
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_4->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_5->setText("0.00");
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_5->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_6->setText("0.00");
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_6->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_7->setText("0.00");
    ui->lineEdit_7->setEnabled(false);
    ui->lineEdit_7->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_8->setText("0.00");
    ui->lineEdit_8->setEnabled(false);
    ui->lineEdit_8->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_9->setText("0.00");
    ui->lineEdit_9->setEnabled(false);
    ui->lineEdit_9->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_10->setText("0.00");
    ui->lineEdit_10->setEnabled(false);
    ui->lineEdit_10->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");
    ui->lineEdit_11->setText("0.00");
    ui->lineEdit_11->setEnabled(false);
    ui->lineEdit_11->setStyleSheet("background-color: rgb(75, 73, 73); color: rgb(118, 118, 118); border: 1px solid rgb(118, 118, 118); font: 20px 'Roboto';");

    static_parameters.button_state_2 = false;
    ui->pushButton_28->setEnabled(true);
    ui->pushButton_28->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayCloseStockImage.png); "
                                     "background-repeat: no-repeat; } QPushButton:hover { border: 1px solid black; border-radius: 5px; background-image: "
                                     "url(:/images/images/okayOpenStockImage.png); background-repeat: no-repeat; } ");
    ui->pushButton_29->setStyleSheet("border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okStockImage.png); background-repeat: "
                                     "no-repeat;");
    ui->pushButton_30->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayCloseStockImage.png); "
                                     "background-repeat: no-repeat; } QPushButton:hover { border: 1px solid black; border-radius: 5px; background-image: "
                                     "url(:/images/images/okayOpenStockImage.png); background-repeat: no-repeat; } ");

    DrawGraphicsFunction(1);
}

void MainWindow::on_pushButton_30_clicked()
{
    ui->label_172->setText("0.00");
    ui->label_174->setText("0.00");
    ui->label_176->setText("0.00");
    ui->label_181->setText("0.00");
    ui->label_182->setText("0.00");
    ui->label_186->setText("0.00");
    ui->label_149->setText("0.00");
    ui->label_151->setText("0.00");
    ui->label_153->setText("0.00");
    ui->label_167->setGeometry(10, 98, 34, 4);
    ui->label_168->setGeometry(10, 142, 34, 4);
    ui->label_170->setGeometry(129, 90, 80, 60);

    ui->lineEdit->setEnabled(true);
    ui->lineEdit->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_2->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_3->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_4->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_5->setEnabled(true);
    ui->lineEdit_5->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_6->setEnabled(true);
    ui->lineEdit_6->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_7->setEnabled(true);
    ui->lineEdit_7->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_8->setEnabled(true);
    ui->lineEdit_8->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_9->setEnabled(true);
    ui->lineEdit_9->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_10->setEnabled(true);
    ui->lineEdit_10->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");
    ui->lineEdit_11->setEnabled(true);
    ui->lineEdit_11->setStyleSheet("background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 0px; font: 20px 'Roboto';");

    static_parameters.button_state_2 = false;
    ui->pushButton_28->setEnabled(false);
    ui->pushButton_28->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayCloseStockImage.png); "
                                     "background-repeat: no-repeat; } QPushButton:hover { border: 1px solid black; border-radius: 5px; background-image: "
                                     "url(:/images/images/okayOpenStockImage.png); background-repeat: no-repeat; } ");
    ui->pushButton_29->setStyleSheet("QPushButton { border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okayCloseStockImage.png); "
                                     "background-repeat: no-repeat; } QPushButton:hover { border: 1px solid black; border-radius: 5px; background-image: "
                                     "url(:/images/images/okayOpenStockImage.png); background-repeat: no-repeat; } ");
    ui->pushButton_30->setStyleSheet("border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/okStockImage.png); background-repeat: "
                                     "no-repeat;");
}

void MainWindow::on_pushButton_31_clicked()
{
    if (static_parameters.button_state_1 == true) {
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->lineEdit_30->setEnabled(false);
        ui->lineEdit_29->setEnabled(false);
        ui->comboBox_3->setCurrentIndex(-1);
        ui->comboBox_4->setCurrentIndex(-1);
        static_parameters.button_state_1 = false;
    } else if (static_parameters.button_state_1 == false) {
        ui->comboBox_3->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->lineEdit_30->setEnabled(true);
        ui->lineEdit_29->setEnabled(true);
        static_parameters.button_state_1 = true;
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    ui->comboBox_5->setCurrentIndex(-1);
    ui->lineEdit_12->setText("0.00");
    ui->lineEdit_15->setText("0.00");
    ui->lineEdit_18->setText("0.00");
    ui->lineEdit_13->setText("0.00");
    ui->lineEdit_16->setText("0.00");
    ui->lineEdit_19->setText("0.00");
    ui->lineEdit_14->setText("0.00");
    ui->lineEdit_17->setText("0.00");
    ui->lineEdit_20->setText("0.00");

    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->lineEdit_30->clear();
    ui->lineEdit_29->clear();
    ui->lineEdit_23->setText("0.00");
    ui->lineEdit_24->setText("0.00");
    ui->lineEdit_25->setText("0.00");
    ui->lineEdit_26->setText("0.00");
    ui->lineEdit_27->setText("0.00");
    ui->lineEdit_28->setText("0.00");
    ui->lineEdit_21->setText("0.00");
    ui->lineEdit_22->setText("0.00");
}

void MainWindow::on_pushButton_33_clicked()
{
    ui->label_266->setText("");
    ui->label_237->setText("0.00");
    ui->label_243->setText("0.00");
    ui->label_249->setText("0.00");
    ui->label_239->setText("0.00");
    ui->label_245->setText("0.00");
    ui->label_251->setText("0.00");
    ui->label_241->setText("0.00");
    ui->label_247->setText("0.00");
    ui->label_253->setText("0.00");
    ui->comboBox_6->setCurrentIndex(-1);
    ui->comboBox_7->setCurrentIndex(-1);

    ui->label_271->setText("0.00");
    ui->label_274->setText("0.00");
    ui->label_277->setText("0.00");
    ui->label_280->setText("0.00");
    ui->label_283->setText("0.00");
    ui->label_286->setText("0.00");
    ui->label_256->setText("0.00");
    ui->label_259->setText("0.00");
    ui->stackedWidget_5->setCurrentIndex(0);
}

void MainWindow::on_pushButton_34_clicked()
{
    ui->comboBox_5->setCurrentIndex(-1);
    ui->lineEdit_12->setText("0.00");
    ui->lineEdit_15->setText("0.00");
    ui->lineEdit_18->setText("0.00");
    ui->lineEdit_13->setText("0.00");
    ui->lineEdit_16->setText("0.00");
    ui->lineEdit_19->setText("0.00");
    ui->lineEdit_14->setText("0.00");
    ui->lineEdit_17->setText("0.00");
    ui->lineEdit_20->setText("0.00");

    ui->comboBox_3->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->lineEdit_30->clear();
    ui->lineEdit_29->clear();
    ui->lineEdit_23->setText("0.00");
    ui->lineEdit_24->setText("0.00");
    ui->lineEdit_25->setText("0.00");
    ui->lineEdit_26->setText("0.00");
    ui->lineEdit_27->setText("0.00");
    ui->lineEdit_28->setText("0.00");
    ui->lineEdit_21->setText("0.00");
    ui->lineEdit_22->setText("0.00");
}

void MainWindow::on_pushButton_35_clicked()
{
    ui->comboBox_5->setCurrentIndex(-1);
    ui->lineEdit_12->setText("0.00");
    ui->lineEdit_12->setEnabled(false);
    ui->lineEdit_15->setText("0.00");
    ui->lineEdit_15->setEnabled(false);
    ui->lineEdit_18->setText("0.00");
    ui->lineEdit_18->setEnabled(false);
    ui->lineEdit_13->setText("0.00");
    ui->lineEdit_13->setEnabled(false);
    ui->lineEdit_16->setText("0.00");
    ui->lineEdit_16->setEnabled(false);
    ui->lineEdit_19->setText("0.00");
    ui->lineEdit_19->setEnabled(false);
    ui->lineEdit_14->setText("0.00");
    ui->lineEdit_14->setEnabled(false);
    ui->lineEdit_17->setText("0.00");
    ui->lineEdit_17->setEnabled(false);
    ui->lineEdit_20->setText("0.00");
    ui->lineEdit_20->setEnabled(false);

    ui->comboBox_3->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->lineEdit_23->setText("0.00");
    ui->lineEdit_23->setEnabled(false);
    ui->lineEdit_24->setText("0.00");
    ui->lineEdit_24->setEnabled(false);
    ui->lineEdit_25->setText("0.00");
    ui->lineEdit_25->setEnabled(false);
    ui->lineEdit_26->setText("0.00");
    ui->lineEdit_26->setEnabled(false);
    ui->lineEdit_27->setText("0.00");
    ui->lineEdit_27->setEnabled(false);
    ui->lineEdit_28->setText("0.00");
    ui->lineEdit_28->setEnabled(false);
    ui->lineEdit_21->setText("0.00");
    ui->lineEdit_21->setEnabled(false);
    ui->lineEdit_22->setText("0.00");
    ui->lineEdit_22->setEnabled(false);

    login_dialog = new LoginDialog(this);
    login_dialog->show();
    connect(login_dialog, SIGNAL(atLoginDialog(QString)),
            this, SLOT(onLoginDialog(QString)));
}

void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/parametersCloseImage.png); background-repeat: "
                                    "no-repeat; } QPushButton::hover { color: rgb(94, 94, 94); background-image: "
                                    "url(:/images/images/parametersOpenImage.png); background-repeat: no-repeat; }");

    static_parameters.value_9 = ui->label_237->text().toDouble();
    static_parameters.value_10 = ui->label_243->text().toDouble();
    static_parameters.value_11 = ui->label_249->text().toDouble();
    static_parameters.value_12 = ui->label_239->text().toDouble();
    static_parameters.value_13 = ui->label_245->text().toDouble();
    static_parameters.value_14 = ui->label_251->text().toDouble();
    static_parameters.value_15 = ui->label_241->text().toDouble();
    static_parameters.value_16 = ui->label_247->text().toDouble();
    static_parameters.value_17 = ui->label_253->text().toDouble();

    static_parameters.value_1 = ui->label_256->text().toDouble();
    static_parameters.value_2 = ui->label_259->text().toDouble();
    static_parameters.value_3 = ui->label_271->text().toDouble();
    static_parameters.value_4 = ui->label_274->text().toDouble();
    static_parameters.value_5 = ui->label_277->text().toDouble();
    static_parameters.value_6 = ui->label_280->text().toDouble();
    static_parameters.value_7 = ui->label_283->text().toDouble();
    static_parameters.value_8 = ui->label_286->text().toDouble();

    ui->label_39->setText(": " + static_parameters.record_value_1);
    ui->label_37->setText(": " + static_parameters.record_value_2);
    ui->label_47->setText(": " + static_parameters.record_value_3);
    ui->label_41->setText(": " + static_parameters.record_value_4);
    ui->label_43->setText(": " + static_parameters.record_value_5);
    ui->label_49->setText(": " + static_parameters.record_value_6);
    ui->label_51->setText(": " + static_parameters.record_value_7);
    ui->label_45->setText(": " + static_parameters.record_value_8);

    double max_a_sch_double = (140 - 2) - ((static_parameters.value_3 / 4) * 80);
    int max_a_sch_int = (int)max_a_sch_double;
    if (max_a_sch_int < 50)
        max_a_sch_int = 50;
    ui->label_76->setGeometry(10, max_a_sch_int, 34, 4);

    double min_a_sch_double = (140 + 2) - ((static_parameters.value_4 / 4) * 80);
    int min_a_sch_int = (int)min_a_sch_double;
    if (min_a_sch_int > 230)
        min_a_sch_int = 230;
    ui->label_77->setGeometry(10, min_a_sch_int, 34, 4);

    double min_b_sch_double = (170 + 1) + ((static_parameters.value_6 / 3) * 90);
    int min_b_sch_int = (int)min_b_sch_double;
    if (min_b_sch_int < 80)
        min_b_sch_int = 79;
    double max_b_sch_double = (static_parameters.value_5 - static_parameters.value_6) * 30;
    int max_b_sch_int = (int)max_b_sch_double;
    if (max_b_sch_int > 180)
        max_b_sch_int = 181;
    double min_c_sch_double = (static_parameters.value_7 - static_parameters.value_8) * 30;
    int min_c_sch_int = (int)min_c_sch_double;
    if (min_c_sch_int > 180)
        min_c_sch_int = 181;
    double max_c_sch_double = (140 - 1) - ((static_parameters.value_7 / 3) * 90);
    int max_c_sch_int = (int)max_c_sch_double;
    if (max_c_sch_int < 50)
        max_c_sch_int = 49;
    ui->label_79->setGeometry(min_b_sch_int, max_c_sch_int, max_b_sch_int, min_c_sch_int);

    ui->label_58->setText(QString::number(static_parameters.value_12));
    ui->label_60->setText(QString::number(static_parameters.value_13));
    ui->label_62->setText(QString::number(static_parameters.value_14));
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194);  font: 15px 'Roboto';}");
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; }");
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");

    ClearLineCharts1();
}

void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/parametersCloseImage.png); background-repeat: no-repeat; }"
                                    "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/parametersOpenImage.png);"
                                    "background-repeat: no-repeat; }");

    static_parameters.value_1 = ui->label_256->text().toDouble();
    static_parameters.value_2 = ui->label_259->text().toDouble();
    static_parameters.value_3 = ui->label_271->text().toDouble();
    static_parameters.value_4 = ui->label_274->text().toDouble();
    static_parameters.value_5 = ui->label_277->text().toDouble();
    static_parameters.value_6 = ui->label_280->text().toDouble();
    static_parameters.value_7 = ui->label_283->text().toDouble();
    static_parameters.value_8 = ui->label_286->text().toDouble();
    static_parameters.value_9 = ui->label_237->text().toDouble();
    static_parameters.value_10 = ui->label_243->text().toDouble();
    static_parameters.value_11 = ui->label_249->text().toDouble();
    static_parameters.value_12 = ui->label_239->text().toDouble();
    static_parameters.value_13 = ui->label_245->text().toDouble();
    static_parameters.value_14 = ui->label_251->text().toDouble();
    static_parameters.value_15 = ui->label_241->text().toDouble();
    static_parameters.value_16 = ui->label_247->text().toDouble();
    static_parameters.value_17 = ui->label_253->text().toDouble();

    ui->label_39->setText(": " + static_parameters.record_value_1);
    ui->label_37->setText(": " + static_parameters.record_value_2);
    ui->label_47->setText(": " + static_parameters.record_value_3);
    ui->label_41->setText(": " + static_parameters.record_value_4);
    ui->label_43->setText(": " + static_parameters.record_value_5);
    ui->label_49->setText(": " + static_parameters.record_value_6);
    ui->label_51->setText(": " + static_parameters.record_value_7);
    ui->label_45->setText(": " + static_parameters.record_value_8);

    double max_a_sch_double = (140 - 2) - ((static_parameters.value_3 / 4) * 80);
    int max_a_sch_int = (int)max_a_sch_double;
    if (max_a_sch_int < 50)
        max_a_sch_int = 50;
    ui->label_76->setGeometry(10, max_a_sch_int, 34, 4);

    double min_a_sch_double = (140 + 2) - ((static_parameters.value_4 / 4) * 80);
    int min_a_sch_int = (int)min_a_sch_double;
    if (min_a_sch_int > 230)
        min_a_sch_int = 230;
    ui->label_77->setGeometry(10, min_a_sch_int, 34, 4);

    double min_b_sch_double = (170 + 1) + ((static_parameters.value_6 / 3) * 90);
    int min_b_sch_int = (int)min_b_sch_double;
    if (min_b_sch_int < 80)
        min_b_sch_int = 79;
    double max_b_sch_double = (static_parameters.value_5 - static_parameters.value_6) * 30;
    int max_b_sch_int = (int)max_b_sch_double;
    if (max_b_sch_int > 180)
        max_b_sch_int = 181;
    double min_c_sch_double = (static_parameters.value_7 - static_parameters.value_8) * 30;
    int min_c_sch_int = (int)min_c_sch_double;
    if (min_c_sch_int > 180)
        min_c_sch_int = 181;
    double max_c_sch_double = (140 - 1) - ((static_parameters.value_7 / 3) * 90);
    int max_c_sch_int = (int)max_c_sch_double;
    if (max_c_sch_int < 50)
        max_c_sch_int = 49;
    ui->label_79->setGeometry(min_b_sch_int, max_c_sch_int, max_b_sch_int, min_c_sch_int);

    ui->label_58->setText(QString::number(static_parameters.value_12));
    ui->label_60->setText(QString::number(static_parameters.value_13));
    ui->label_62->setText(QString::number(static_parameters.value_14));
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; }");
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: rgb(94, 94, 94); color: rgb(194, 194, 194); border: 1px solid rgb(194, 194, 194); "
                                    "font: 15px 'Roboto'; } QPushButton::hover { background-color: rgb(194, 194, 194); color: rgb(94, 94, 94); "
                                    "border: 1px solid rgb(194, 194, 194); font: 15px 'Roboto';}");

    ClearLineCharts1();
}

void MainWindow::on_pushButton_38_clicked()
{
    ui->pushButton_38->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(21, 21, 21); color: rgb(211, 211, 211); "
                                     "font: 12px 'Roboto'; } ");
    ui->pushButton_39->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(211, 211, 211); color: rgb(21, 21, 21); "
                                     "font: 12px 'Roboto'; } QPushButton::hover { background-color: rgb(21, 21, 21); color: rgb(211, 211, 211); }");
    ui->label_288->setText("Koyu");
}

void MainWindow::on_pushButton_39_clicked()
{
    ui->pushButton_39->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(21, 21, 21); color: rgb(211, 211, 211); font: 12px 'Roboto'; } ");
    ui->pushButton_38->setStyleSheet("QPushButton { border: 1px solid black; background-color: rgb(211, 211, 211); color: rgb(21, 21, 21); font: 12px 'Roboto'; } "
                                     "QPushButton::hover { background-color: rgb(21, 21, 21); color: rgb(211, 211, 211); }");
    ui->label_288->setText("Open");
}

void MainWindow::on_pushButton_40_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_3->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/systemCloseImage.png); background-repeat: no-repeat; }"
                                    "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/systemOpenImage.png);"
                                    "background-repeat: no-repeat; }");
}

void MainWindow::on_pushButton_41_clicked()
{
    ui->label_310->setText("Default");
    ui->label_312->setText("Default");
    ui->label_311->setText("Default");

    ui->lineEdit_31->setEnabled(true);
    ui->lineEdit_31->clear();
    ui->lineEdit_32->clear();
    ui->comboBox_8->setCurrentIndex(-1);

    line_chart_params.line_chart_31_series_1->clear();
    line_chart_params.line_chart_31_series_2->clear();
    line_chart_params.line_chart_31_series_3->clear();
    line_chart_params.line_chart_31_series_4->clear();
    line_chart_params.line_chart_31_series_5->clear();
    line_chart_params.line_chart_31_series_6->clear();
    line_chart_params.line_chart_31_series_7->clear();
    line_chart_params.line_chart_31_series_8->clear();
    line_chart_params.line_chart_31_series_9->clear();
}

void MainWindow::on_pushButton_42_clicked()
{
    line_chart_params.line_chart_31 = new QChart();
    line_chart_params.line_chart_31_series_1 = new QLineSeries();
    line_chart_params.line_chart_31_series_2 = new QLineSeries();
    line_chart_params.line_chart_31_series_3 = new QLineSeries();
    line_chart_params.line_chart_31_series_4 = new QLineSeries();
    line_chart_params.line_chart_31_series_5 = new QLineSeries();
    line_chart_params.line_chart_31_series_6 = new QLineSeries();
    line_chart_params.line_chart_31_series_7 = new QLineSeries();
    line_chart_params.line_chart_31_series_8 = new QLineSeries();
    line_chart_params.line_chart_31_series_9 = new QLineSeries();
    line_chart_params.line_chart_31_value_axis_1 = new QValueAxis();
    line_chart_params.line_chart_31_value_axis_2 = new QValueAxis();

    LineChartInit2(ui->chartView_31, line_chart_params.line_chart_31, line_chart_params.line_chart_31_series_1, line_chart_params.line_chart_31_series_2,
                   line_chart_params.line_chart_31_series_3, line_chart_params.line_chart_31_series_4, line_chart_params.line_chart_31_series_5,
                   line_chart_params.line_chart_31_series_6, line_chart_params.line_chart_31_series_7, line_chart_params.line_chart_31_series_8,
                   line_chart_params.line_chart_31_series_9, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   QColor(255, 0, 0), QColor(206, 85, 4), QColor(202, 207, 3), QColor(0, 255, 0), QColor(0, 128, 0), QColor(2, 103, 253), QColor(50, 7, 248),
                   QColor(164, 6, 249), QColor(250, 5, 238));

    ui->label_310->setText("Pass");
    ui->lineEdit_31->setEnabled(false);
    ui->lineEdit_32->setEnabled(false);
    ui->comboBox_8->setEnabled(false);

    line_chart_params.line_chart_31_series_1->clear();
    line_chart_params.line_chart_31_series_2->clear();
    line_chart_params.line_chart_31_series_3->clear();
    line_chart_params.line_chart_31_series_4->clear();
    line_chart_params.line_chart_31_series_5->clear();
    line_chart_params.line_chart_31_series_6->clear();
    line_chart_params.line_chart_31_series_7->clear();
    line_chart_params.line_chart_31_series_8->clear();
    line_chart_params.line_chart_31_series_9->clear();

    QList<double> tmp_left_values = { 0, 1000, 1200, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000,
                                      20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000,
                                      10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000};
    QList<double> tmp_middle_values = { 1200, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000,
                                        10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000,
                                        20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 30000, 1000};
    QList<double> tmp_right_values = { 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000,
                                       7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000,
                                       40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 0, 1000, 1200, 3000, 3700};
    double count = 400;
    double max_left_value = 0;
    for (int i = 0; i < 61; i++) {
        if (max_left_value < tmp_left_values[i])
            max_left_value = tmp_left_values[i];
    }

    for (int i = 0; i < 61; i++) {
        DrawPoint2(line_chart_params.line_chart_31_series_1, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_left_values[i]);
        DrawPoint2(line_chart_params.line_chart_31_series_2, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_middle_values[i]);
        DrawPoint2(line_chart_params.line_chart_31_series_3, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_right_values[i]);
        count = count + 5;
    }
}

void MainWindow::on_pushButton_43_clicked()
{
    ui->label_312->setText("Pass");
    line_chart_params.line_chart_31_series_4->clear();
    line_chart_params.line_chart_31_series_5->clear();
    line_chart_params.line_chart_31_series_6->clear();
    line_chart_params.line_chart_31_series_7->clear();
    line_chart_params.line_chart_31_series_8->clear();
    line_chart_params.line_chart_31_series_9->clear();

    QList<double> tmp_left_values = { 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000,
                                      5500, 5200, 5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000,
                                      40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 0, 1000, 1200, 3000, 3700, 4000, 5000};
    QList<double> tmp_middle_values = { 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200,
                                        5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000,
                                        20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 30000, 1000, 1200, 3000, 3700, 4000, 5000, 5200};
    QList<double> tmp_right_values = { 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000,
                                       3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000,
                                       10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 0, 1000, 1200, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000};
    double count = 400;
    double max_left_value = 0;
    for (int i = 0; i < 61; i++) {
        if (max_left_value < tmp_left_values[i])
            max_left_value = tmp_left_values[i];
    }

    for (int i = 0; i < 61; i++) {
        DrawPoint2(line_chart_params.line_chart_31_series_4, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_left_values[i]);
        DrawPoint2(line_chart_params.line_chart_31_series_5, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_middle_values[i]);
        DrawPoint2(line_chart_params.line_chart_31_series_6, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_right_values[i]);
        count = count + 5;
    }
}

void MainWindow::on_pushButton_44_clicked()
{
    ui->label_311->setText("Start-Left");
    line_chart_params.line_chart_31_series_7->clear();

    QList<double> tmp_left_values = { 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000,
                                      3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000,
                                      7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 0, 1000, 1200, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000};
    double count = 400;
    double max_left_value = 0;
    for (int i = 0; i < 61; i++) {
        if (max_left_value < tmp_left_values[i])
            max_left_value = tmp_left_values[i];
    }

    for (int i = 0; i < 61; i++) {
        DrawPoint2(line_chart_params.line_chart_31_series_7, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_left_value, count, tmp_left_values[i]);
        count = count + 5;
    }
}

void MainWindow::on_pushButton_45_clicked()
{
    ui->label_311->setText("Stop-Left");
}

void MainWindow::on_pushButton_46_clicked()
{
    ui->label_311->setText("Start-Middle");
    line_chart_params.line_chart_31_series_8->clear();

    QList<double> tmp_middle_values = { 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000,
                                        8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000,
                                        3700, 3000, 0, 1000, 1200, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000};
    double count = 400;
    double max_middle_value = 0;
    for (int i = 0; i < 61; i++) {
        if (max_middle_value < tmp_middle_values[i])
            max_middle_value = tmp_middle_values[i];
    }

    for (int i = 0; i < 61; i++) {
        DrawPoint2(line_chart_params.line_chart_31_series_8, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_middle_value, count, tmp_middle_values[i]);
        count = count + 5;
    }
}

void MainWindow::on_pushButton_47_clicked()
{
    ui->label_311->setText("Stop-Middle");
}

void MainWindow::on_pushButton_48_clicked()
{
    ui->label_311->setText("Start-Right");
    line_chart_params.line_chart_31_series_9->clear();

    QList<double> tmp_right_values = { 6000, 5500, 5200, 5000, 4000, 3700, 3000, 3000, 3700, 4000, 5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000,
                                       50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000, 6000, 5500, 5200, 5000, 4000, 3700, 3000, 0, 1000, 1200, 3000, 3700, 4000,
                                       5000, 5200, 5500, 6000, 7000, 8000, 10000, 15000, 20000, 30000, 40000, 50000, 40000, 30000, 20000, 15000, 10000, 8000, 7000};
    double count = 400;
    double max_right_value = 0;
    for (int i = 0; i < 61; i++) {
        if (max_right_value < tmp_right_values[i])
            max_right_value = tmp_right_values[i];
    }

    for (int i = 0; i < 61; i++) {
        DrawPoint2(line_chart_params.line_chart_31_series_9, line_chart_params.line_chart_31_value_axis_1, line_chart_params.line_chart_31_value_axis_2,
                   400, max_right_value, count, tmp_right_values[i]);
        count = count + 5;
    }
}

void MainWindow::on_pushButton_49_clicked()
{
    ui->label_311->setText("Stop-Right");
    ui->lineEdit_31->setEnabled(true);
    ui->lineEdit_32->setEnabled(true);
    ui->comboBox_8->setEnabled(true);
}

void MainWindow::on_pushButton_50_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_3->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/systemCloseImage.png); background-repeat: no-repeat; }"
                                    "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/systemOpenImage.png);"
                                    "background-repeat: no-repeat; }");
}

void MainWindow::on_pushButton_51_clicked()
{
    ui->label_313->setText("Off");
}

void MainWindow::on_pushButton_52_clicked()
{
    ui->label_313->setText("On");
}

void MainWindow::on_pushButton_53_clicked()
{
    ui->label_313->setText("On");
}

void MainWindow::on_pushButton_54_clicked()
{
    ui->label_313->setText("Off");
}

void MainWindow::on_pushButton_55_clicked()
{
    ui->label_313->setText("On");
}

void MainWindow::on_pushButton_56_clicked()
{
    ui->label_313->setText("Off");
}

void MainWindow::on_pushButton_57_clicked()
{
    ui->label_313->setText("On");
}

void MainWindow::on_pushButton_58_clicked()
{
    ui->label_313->setText("Off");
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_3->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/systemCloseImage.png); background-repeat: no-repeat; }"
                                    "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/systemOpenImage.png);"
                                    "background-repeat: no-repeat; }");
}

void MainWindow::on_pushButton_60_clicked()
{
    string_list_model = new QStringListModel(this);

    QStringList list_model_data;
    list_model_data << "Try - 1" << "Try - 2" << "Try - 3" << "Try - 4" << "Try - 5";
    string_list_model->setStringList(list_model_data);
    ui->listView_2->setModel(string_list_model);
}

void MainWindow::on_pushButton_61_clicked()
{
    ui->lineEdit_33->clear();
    ui->lineEdit_34->clear();
    ui->comboBox_9->setCurrentIndex(-1);

    ui->label_315->setText("X");
    ui->label_317->setText("X");
    ui->label_319->setText("X");
    ui->label_323->setText("Default");
    ui->label_324->setText("Default");
    ui->label_325->setText("Default");

    line_chart_params.line_chart_32_series->clear();
    line_chart_params.line_chart_33_series->clear();
    line_chart_params.line_chart_34_series->clear();
}

void MainWindow::on_pushButton_62_clicked()
{
    ui->label_324->setText("Pass");
}

void MainWindow::on_pushButton_63_clicked()
{
    ui->label_323->setText("Pass");
    ui->lineEdit_33->setEnabled(false);
    ui->lineEdit_34->setEnabled(false);
    ui->comboBox_9->setEnabled(false);
}

void MainWindow::on_pushButton_64_clicked()
{
    line_chart_params.line_chart_32 = new QChart();
    line_chart_params.line_chart_32_series = new QLineSeries();
    line_chart_params.line_chart_32_value_axis_1 = new QValueAxis();
    line_chart_params.line_chart_32_value_axis_2 = new QValueAxis();
    LineChartInit3(ui->chartView_32, line_chart_params.line_chart_32, line_chart_params.line_chart_32_series, line_chart_params.line_chart_32_value_axis_1,
                   line_chart_params.line_chart_32_value_axis_2, QColor(0, 255, 0));

    x_line_chart_axis_value = 0;
    y_line_chart_axis_value = 0;
    line_chart_thread_value = 0;

    line_chart_thread = new LineChartThread();
    connect(line_chart_thread, SIGNAL(atLineChartValueChanged()),
            this, SLOT(onLineChartValueChanged()));
    line_chart_thread->start();
    ui->label_325->setText("Start-Left");
}

void MainWindow::on_pushButton_65_clicked()
{
    line_chart_thread->stop = true;
    ui->label_325->setText("Stop-Left");
}

void MainWindow::on_pushButton_66_clicked()
{
    line_chart_params.line_chart_33 = new QChart();
    line_chart_params.line_chart_33_series = new QLineSeries();
    line_chart_params.line_chart_33_value_axis_1 = new QValueAxis();
    line_chart_params.line_chart_33_value_axis_2 = new QValueAxis();
    LineChartInit3(ui->chartView_33, line_chart_params.line_chart_33, line_chart_params.line_chart_33_series, line_chart_params.line_chart_33_value_axis_1,
                   line_chart_params.line_chart_33_value_axis_2, QColor(0, 0, 255));

    x_line_chart_axis_value = 0;
    y_line_chart_axis_value = 0;
    line_chart_thread_value = 1;

    line_chart_thread = new LineChartThread();
    connect(line_chart_thread, SIGNAL(atLineChartValueChanged()),
            this, SLOT(onLineChartValueChanged()));
    line_chart_thread->start();
    ui->label_325->setText("Start-Middle");
}

void MainWindow::on_pushButton_67_clicked()
{
    line_chart_thread->stop = true;
    ui->label_325->setText("Stop-Middle");
}

void MainWindow::on_pushButton_68_clicked()
{
    line_chart_params.line_chart_34 = new QChart();
    line_chart_params.line_chart_34_series = new QLineSeries();
    line_chart_params.line_chart_34_value_axis_1 = new QValueAxis();
    line_chart_params.line_chart_34_value_axis_2 = new QValueAxis();
    LineChartInit3(ui->chartView_34, line_chart_params.line_chart_34, line_chart_params.line_chart_34_series, line_chart_params.line_chart_34_value_axis_1,
                   line_chart_params.line_chart_34_value_axis_2, QColor(0, 130, 130));

    x_line_chart_axis_value = 0;
    y_line_chart_axis_value = 0;
    line_chart_thread_value = 2;

    line_chart_thread = new LineChartThread();
    connect(line_chart_thread, SIGNAL(atLineChartValueChanged()),
            this, SLOT(onLineChartValueChanged()));
    line_chart_thread->start();
    ui->label_325->setText("Start-Right");
}

void MainWindow::on_pushButton_69_clicked()
{
    line_chart_thread->stop = true;
    ui->label_325->setText("Stop-Right");
    ui->lineEdit_33->setEnabled(true);
    ui->lineEdit_34->setEnabled(true);
    ui->comboBox_9->setEnabled(true);
}

void MainWindow::on_pushButton_70_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_3->setStyleSheet("QPushButton { border: 1px solid black; color: rgb(194, 194, 194); text-align: left; font: 22px 'Roboto'; "
                                    "padding-left: 65px; background-image: url(:/images/images/systemCloseImage.png); background-repeat: no-repeat; }"
                                    "QPushButton::hover { color: rgb(94, 94, 94); background-image: url(:/images/images/systemOpenImage.png);"
                                    "background-repeat: no-repeat; }");
}

void MainWindow::on_pushButton_71_clicked()
{
    if (ui->checkBox_3->isChecked() == true)
        ui->label_326->setText("Pass1");
    else if (ui->checkBox_5->isChecked() == true)
        ui->label_326->setText("Pass2");
    else if (ui->checkBox_4->isChecked() == true)
        ui->label_326->setText("Pass3");
    else if (ui->checkBox_2->isChecked() == true)
        ui->label_326->setText("Pass4");
    else if (ui->checkBox->isChecked() == true)
        ui->label_326->setText("Pass5");
}

void MainWindow::on_pushButton_72_clicked()
{
    if (ui->comboBox_10->currentIndex() == 0)
        ui->label_328->setText("Param - 1");
    else if (ui->comboBox_10->currentIndex() == 1)
        ui->label_328->setText("Param - 2");
    else if (ui->comboBox_10->currentIndex() == 2)
        ui->label_328->setText("Param - 3");
    ui->label_330->setText(ui->lineEdit_35->text());
    ui->label_332->setText(ui->lineEdit_36->text());

    if (ui->comboBox_11->currentIndex() == 0)
        ui->label_334->setText("1 Direction");
    else if (ui->comboBox_11->currentIndex() == 1)
        ui->label_334->setText("2 Direction");
    ui->label_335->setText("Pass");

    ui->comboBox_10->setCurrentIndex(-1);
    ui->lineEdit_35->clear();
    ui->lineEdit_36->clear();
    ui->comboBox_11->setCurrentIndex(-1);
}

void MainWindow::on_pushButton_73_clicked()
{
    ui->label_341->setText(ui->lineEdit_37->text());
    ui->label_343->setText(ui->lineEdit_38->text());
    ui->label_345->setText(ui->lineEdit_39->text());
    ui->label_347->setText(ui->lineEdit_40->text());
    ui->label_348->setText("Pass");

    ui->lineEdit_37->clear();
    ui->lineEdit_38->clear();
    ui->lineEdit_39->clear();
    ui->lineEdit_40->clear();
}

void MainWindow::on_pushButton_74_clicked()
{
    ui->label_354->setText(ui->lineEdit_41->text());
    ui->label_356->setText(ui->lineEdit_42->text());
    ui->label_358->setText(ui->lineEdit_43->text());
    ui->label_359->setText("Pass");

    ui->lineEdit_41->clear();
    ui->lineEdit_42->clear();
    ui->lineEdit_43->clear();
}

void MainWindow::on_pushButton_75_clicked()
{
    if (ui->comboBox_12->currentIndex() == 0)
        ui->label_364->setText("Low");
    else if (ui->comboBox_12->currentIndex() == 1)
        ui->label_364->setText("High");
    ui->label_366->setText(ui->label_374->text());

    if (ui->comboBox_13->currentIndex() == 0)
        ui->label_368->setText("Param - 1");
    else if (ui->comboBox_13->currentIndex() == 1)
        ui->label_368->setText("Param - 2");
    else if (ui->comboBox_13->currentIndex() == 2)
        ui->label_368->setText("Param - 3");
    ui->label_370->setText(ui->lineEdit_44->text());

    ui->comboBox_12->setCurrentIndex(-1);
    ui->slider->setValue(0);
    ui->slider->setMinimum(0);
    ui->slider->setMaximum(5);
    ui->label_374->setText("0");
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0)
        ui->stackedWidget_2->setCurrentIndex(0);
    else if (index == 1)
        ui->stackedWidget_2->setCurrentIndex(1);
    else if (index == 2)
        ui->stackedWidget_2->setCurrentIndex(2);
    else if (index == 3)
        ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index == 0)
        ui->stackedWidget_4->setCurrentIndex(0);
    else if (index == 1)
        ui->stackedWidget_4->setCurrentIndex(1);
    else if (index == 2)
        ui->stackedWidget_4->setCurrentIndex(2);
    else if (index == 3)
        ui->stackedWidget_4->setCurrentIndex(3);
}

void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->lineEdit_12->setText("0.00");
        ui->lineEdit_12->setEnabled(true);
        ui->lineEdit_15->setText("0.00");
        ui->lineEdit_15->setEnabled(true);
        ui->lineEdit_18->setText("0.00");
        ui->lineEdit_18->setEnabled(true);
        ui->lineEdit_13->setText("0.00");
        ui->lineEdit_13->setEnabled(true);
        ui->lineEdit_16->setText("0.00");
        ui->lineEdit_16->setEnabled(true);
        ui->lineEdit_19->setText("0.00");
        ui->lineEdit_19->setEnabled(true);
        ui->lineEdit_14->setText("0.00");
        ui->lineEdit_14->setEnabled(true);
        ui->lineEdit_17->setText("0.00");
        ui->lineEdit_17->setEnabled(true);
        ui->lineEdit_20->setText("0.00");

        ui->lineEdit_20->setEnabled(true);
        ui->lineEdit_23->setEnabled(true);
        ui->lineEdit_24->setEnabled(true);
        ui->lineEdit_25->setEnabled(true);
        ui->lineEdit_26->setEnabled(true);
        ui->lineEdit_27->setEnabled(true);
        ui->lineEdit_28->setEnabled(true);
        ui->lineEdit_21->setEnabled(true);
        ui->lineEdit_22->setEnabled(true);

    } else if (index == 1) {
        ui->lineEdit_12->setText("0.00");
        ui->lineEdit_12->setEnabled(false);
        ui->lineEdit_15->setText("0.00");
        ui->lineEdit_15->setEnabled(false);
        ui->lineEdit_18->setText("0.00");
        ui->lineEdit_18->setEnabled(false);
        ui->lineEdit_13->setText("0.00");
        ui->lineEdit_13->setEnabled(false);
        ui->lineEdit_16->setText("0.00");
        ui->lineEdit_16->setEnabled(false);
        ui->lineEdit_19->setText("0.00");
        ui->lineEdit_19->setEnabled(false);
        ui->lineEdit_14->setText("0.00");
        ui->lineEdit_14->setEnabled(false);
        ui->lineEdit_17->setText("0.00");
        ui->lineEdit_17->setEnabled(false);
        ui->lineEdit_20->setText("0.00");
        ui->lineEdit_20->setEnabled(false);

        ui->lineEdit_23->setEnabled(true);
        ui->lineEdit_24->setEnabled(true);
        ui->lineEdit_25->setEnabled(true);
        ui->lineEdit_26->setEnabled(true);
        ui->lineEdit_27->setEnabled(true);
        ui->lineEdit_28->setEnabled(true);
        ui->lineEdit_21->setEnabled(true);
        ui->lineEdit_22->setEnabled(true);

    } else if (index == 2) {
        ui->lineEdit_12->setText("0.00");
        ui->lineEdit_12->setEnabled(false);
        ui->lineEdit_15->setText("0.00");
        ui->lineEdit_15->setEnabled(false);
        ui->lineEdit_18->setText("0.00");
        ui->lineEdit_18->setEnabled(false);
        ui->lineEdit_13->setText("0.00");
        ui->lineEdit_13->setEnabled(false);
        ui->lineEdit_16->setText("0.00");
        ui->lineEdit_16->setEnabled(false);
        ui->lineEdit_19->setText("0.00");
        ui->lineEdit_19->setEnabled(false);
        ui->lineEdit_14->setText("0.00");
        ui->lineEdit_14->setEnabled(false);
        ui->lineEdit_17->setText("0.00");
        ui->lineEdit_17->setEnabled(false);
        ui->lineEdit_20->setText("0.00");
        ui->lineEdit_20->setEnabled(false);

        ui->lineEdit_23->setEnabled(true);
        ui->lineEdit_24->setEnabled(true);
        ui->lineEdit_25->setEnabled(true);
        ui->lineEdit_26->setEnabled(true);
        ui->lineEdit_27->setEnabled(true);
        ui->lineEdit_28->setEnabled(true);
        ui->lineEdit_21->setEnabled(true);
        ui->lineEdit_22->setEnabled(true);
    }
}

void MainWindow::on_comboBox_7_currentIndexChanged(int index)
{
    if (index == 0) {
        if (ui->comboBox_6->currentIndex() == 0) {
            static_parameters.record_value_1 = "27712";
            static_parameters.record_value_2 = "60";
            static_parameters.record_value_3 = "Text - 1";
            static_parameters.record_value_4 = "MR102";
            static_parameters.record_value_5 = "19";
            static_parameters.record_value_6 = "12";
            static_parameters.record_value_7 = "3.2";
            static_parameters.record_value_8 = "0.01";

            ui->label_271->setText(QString::number(1.2));
            ui->label_274->setText(QString::number(-1.18));
            ui->label_277->setText(QString::number(2.0));
            ui->label_280->setText(QString::number(-0.18));
            ui->label_283->setText(QString::number(2.1));
            ui->label_286->setText(QString::number(-2.42));
            ui->label_256->setText(QString::number(1.4));
            ui->label_259->setText(QString::number(1.97));

            ui->label_266->setText("Manual");
            ui->label_237->setText("6.59");
            ui->label_243->setText("1.52");
            ui->label_249->setText("4.55");
            ui->label_239->setText("6.4");
            ui->label_245->setText("1.61");
            ui->label_251->setText("4.47");
            ui->label_241->setText("6.71");
            ui->label_247->setText("1.48");
            ui->label_253->setText("4.63");

        } else if (ui->comboBox_6->currentIndex() == 1) {
            static_parameters.record_value_1 = "16672";
            static_parameters.record_value_2 = "81";
            static_parameters.record_value_3 = "Text - 2";
            static_parameters.record_value_4 = "MR203";
            static_parameters.record_value_5 = "21";
            static_parameters.record_value_6 = "9";
            static_parameters.record_value_7 = "1.7";
            static_parameters.record_value_8 = "0.12";

            ui->label_271->setText(QString::number(2.9));
            ui->label_274->setText(QString::number(-1.8));
            ui->label_277->setText(QString::number(2.27));
            ui->label_280->setText(QString::number(-1.31));
            ui->label_283->setText(QString::number(1.85));
            ui->label_286->setText(QString::number(-1.19));
            ui->label_256->setText(QString::number(1.51));
            ui->label_259->setText(QString::number(3.97));

            ui->label_266->setText("a, b, c Values");
            ui->label_237->setText("7.13");
            ui->label_243->setText("3.43");
            ui->label_249->setText("2.94");
            ui->label_239->setText("7.02");
            ui->label_245->setText("3.37");
            ui->label_251->setText("2.89");
            ui->label_241->setText("7.21");
            ui->label_247->setText("3.41");
            ui->label_253->setText("2.98");

        } else if (ui->comboBox_6->currentIndex() == 2) {
            static_parameters.record_value_1 = "36732";
            static_parameters.record_value_2 = "15";
            static_parameters.record_value_3 = "Text - 3";
            static_parameters.record_value_4 = "MR304";
            static_parameters.record_value_5 = "28";
            static_parameters.record_value_6 = "23";
            static_parameters.record_value_7 = "2.56";
            static_parameters.record_value_8 = "0.62";

            ui->label_271->setText(QString::number(3.65));
            ui->label_274->setText(QString::number(-0.14));
            ui->label_277->setText(QString::number(1.95));
            ui->label_280->setText(QString::number(-1.95));
            ui->label_283->setText(QString::number(2.68));
            ui->label_286->setText(QString::number(-2.51));
            ui->label_256->setText(QString::number(1.43));
            ui->label_259->setText(QString::number(2.18));

            ui->label_266->setText("a, b, c Values");
            ui->label_237->setText("1.88");
            ui->label_243->setText("9.11");
            ui->label_249->setText("4.05");
            ui->label_239->setText("1.89");
            ui->label_245->setText("9.09");
            ui->label_251->setText("3.98");
            ui->label_241->setText("1.67");
            ui->label_247->setText("9.24");
            ui->label_253->setText("3.87");

        }
    } else if (index == 1) {
        if (ui->comboBox_6->currentIndex() == 0) {
            static_parameters.record_value_1 = "055194";
            static_parameters.record_value_2 = "98";
            static_parameters.record_value_3 = "Text - 4";
            static_parameters.record_value_4 = "MA103";
            static_parameters.record_value_5 = "95";
            static_parameters.record_value_6 = "57";
            static_parameters.record_value_7 = "4.3";
            static_parameters.record_value_8 = "0.54";

            ui->label_271->setText(QString::number(3.41));
            ui->label_274->setText(QString::number(-3.29));
            ui->label_277->setText(QString::number(1.34));
            ui->label_280->setText(QString::number(-2.87));
            ui->label_283->setText(QString::number(2.43));
            ui->label_286->setText(QString::number(-0.56));
            ui->label_256->setText(QString::number(3.41));
            ui->label_259->setText(QString::number(5.07));

            ui->label_266->setText("Manual");
            ui->label_237->setText("8.19");
            ui->label_243->setText("3.07");
            ui->label_249->setText("0.05");
            ui->label_239->setText("8.38");
            ui->label_245->setText("3.17");
            ui->label_251->setText("0.16");
            ui->label_241->setText("8.01");
            ui->label_247->setText("3.25");
            ui->label_253->setText("0.01");

        } else if (ui->comboBox_6->currentIndex() == 1) {
            static_parameters.record_value_1 = "98312";
            static_parameters.record_value_2 = "43";
            static_parameters.record_value_3 = "Text - 5";
            static_parameters.record_value_4 = "MR213";
            static_parameters.record_value_5 = "52";
            static_parameters.record_value_6 = "76";
            static_parameters.record_value_7 = "9.1";
            static_parameters.record_value_8 = "0.18";

            ui->label_271->setText(QString::number(2.78));
            ui->label_274->setText(QString::number(-0.95));
            ui->label_277->setText(QString::number(0.65));
            ui->label_280->setText(QString::number(-2.47));
            ui->label_283->setText(QString::number(1.82));
            ui->label_286->setText(QString::number(-1.28));
            ui->label_256->setText(QString::number(1.78));
            ui->label_259->setText(QString::number(2.38));

            ui->label_266->setText("a, b, c Values");
            ui->label_237->setText("2.41");
            ui->label_243->setText("0.23");
            ui->label_249->setText("5.09");
            ui->label_239->setText("2.33");
            ui->label_245->setText("0.19");
            ui->label_251->setText("5.01");
            ui->label_241->setText("2.49");
            ui->label_247->setText("0.28");
            ui->label_253->setText("4.89");

        } else if (ui->comboBox_6->currentIndex() == 2) {
            static_parameters.record_value_1 = "16123";
            static_parameters.record_value_2 = "15";
            static_parameters.record_value_3 = "Text - 6";
            static_parameters.record_value_4 = "RM111";
            static_parameters.record_value_5 = "66";
            static_parameters.record_value_6 = "9";
            static_parameters.record_value_7 = "0.99";
            static_parameters.record_value_8 = "1.21";

            ui->label_271->setText(QString::number(2.31));
            ui->label_274->setText(QString::number(-3.67));
            ui->label_277->setText(QString::number(2.54));
            ui->label_280->setText(QString::number(-2.32));
            ui->label_283->setText(QString::number(3.21));
            ui->label_286->setText(QString::number(-0.29));
            ui->label_256->setText(QString::number(1.95));
            ui->label_259->setText(QString::number(4.23));

            ui->label_266->setText("a, b, c Values");
            ui->label_237->setText("11.23");
            ui->label_243->setText("4.69");
            ui->label_249->setText("4.16");
            ui->label_239->setText("10.98");
            ui->label_245->setText("4.56");
            ui->label_251->setText("4.01");
            ui->label_241->setText("11.29");
            ui->label_247->setText("4.44");
            ui->label_253->setText("4.27");

        }
    } else if (index == 2) {
        if (ui->comboBox_6->currentIndex() == 0) {
            static_parameters.record_value_1 = "53123";
            static_parameters.record_value_2 = "81";
            static_parameters.record_value_3 = "Text - 7";
            static_parameters.record_value_4 = "AS712";
            static_parameters.record_value_5 = "92";
            static_parameters.record_value_6 = "23";
            static_parameters.record_value_7 = "1.3";
            static_parameters.record_value_8 = "0.23";

            ui->label_271->setText(QString::number(2.89));
            ui->label_274->setText(QString::number(-0.14));
            ui->label_277->setText(QString::number(1.54));
            ui->label_280->setText(QString::number(-0.92));
            ui->label_283->setText(QString::number(2.73));
            ui->label_286->setText(QString::number(-1.56));
            ui->label_256->setText(QString::number(1.57));
            ui->label_259->setText(QString::number(3.34));

            ui->label_266->setText("a, b, c Values");
            ui->label_237->setText("0.87");
            ui->label_243->setText("3.12");
            ui->label_249->setText("9.08");
            ui->label_239->setText("0.59");
            ui->label_245->setText("3.29");
            ui->label_251->setText("9.48");
            ui->label_241->setText("0.55");
            ui->label_247->setText("3.17");
            ui->label_253->setText("9.31");

        } else if (ui->comboBox_6->currentIndex() == 1) {
            static_parameters.record_value_1 = "61655";
            static_parameters.record_value_2 = "32";
            static_parameters.record_value_3 = "Text - 8";
            static_parameters.record_value_4 = "AS982";
            static_parameters.record_value_5 = "11";
            static_parameters.record_value_6 = "88";
            static_parameters.record_value_7 = "3.98";
            static_parameters.record_value_8 = "1.83";

            ui->label_271->setText(QString::number(3.2));
            ui->label_274->setText(QString::number(-0.47));
            ui->label_277->setText(QString::number(1.0));
            ui->label_280->setText(QString::number(-2.42));
            ui->label_283->setText(QString::number(1.01));
            ui->label_286->setText(QString::number(-0.94));
            ui->label_256->setText(QString::number(2.10));
            ui->label_259->setText(QString::number(5.43));

            ui->label_266->setText("Manual");
            ui->label_237->setText("3.18");
            ui->label_243->setText("1.17");
            ui->label_249->setText("5.16");
            ui->label_239->setText("3.13");
            ui->label_245->setText("1.38");
            ui->label_251->setText("5.61");
            ui->label_241->setText("3.01");
            ui->label_247->setText("1.53");
            ui->label_253->setText("5.59");

        } else if (ui->comboBox_6->currentIndex() == 2) {
            static_parameters.record_value_1 = "06327";
            static_parameters.record_value_2 = "31";
            static_parameters.record_value_3 = "Text - 9";
            static_parameters.record_value_4 = "KA321";
            static_parameters.record_value_5 = "29";
            static_parameters.record_value_6 = "24";
            static_parameters.record_value_7 = "1.56";
            static_parameters.record_value_8 = "5.43";

            ui->label_271->setText(QString::number(3.12));
            ui->label_274->setText(QString::number(-3.19));
            ui->label_277->setText(QString::number(2.09));
            ui->label_280->setText(QString::number(-1.79));
            ui->label_283->setText(QString::number(2.79));
            ui->label_286->setText(QString::number(-1.13));
            ui->label_256->setText(QString::number(1.76));
            ui->label_259->setText(QString::number(3.97));

            ui->label_266->setText("a, b, c Values");
            ui->label_237->setText("5.16");
            ui->label_243->setText("9.98");
            ui->label_249->setText("12.69");
            ui->label_239->setText("5.21");
            ui->label_245->setText("10.01");
            ui->label_251->setText("12.83");
            ui->label_241->setText("5.09");
            ui->label_247->setText("9.82");
            ui->label_253->setText("12.72");
        }
    }
}

void MainWindow::on_listView_2_clicked(const QModelIndex &index)
{
    int row_list_view = index.row();
    QStringList list;
    QStringList list0 = {"Left", "12.5", "5.4", "6.2", "Middle", "9.0", "2.1", "11.7", "Right", "7.43", "6.13", "2.32", "Right", "1.5", "2.1", "11.7"};
    QStringList list1 = {"Left", "14.4", "5.2", "0.98", "Middle", "0.1", "43.21", "10", "Right", "16.54", "5.55", "12", "Right", "0.76", "1.23", "41.09"};
    QStringList list2 = {"Left", "16.7", "8.4", "1.4", "Middle", "4.67", "27.81", "6.78", "Right", "11.11", "11.27", "19.08", "Right", "6.81", "14.54", "3.2"};
    QStringList list3 = {"Left", "14.2", "9.43", "7.32", "Middle", "21.34", "17.0", "1.23", "Right", "54.21", "0.71", "7.65", "Right", "2.28", "20.98", "16.54"};
    QStringList list4 = {"Left", "41.5", "11.45", "5.7", "Middle", "33.33", "8.19", "7.15", "Right", "32.23", "3.69", "1.98", "Right", "8.07", "9.03", "12.12"};

    for (int i = 0; i < list0.size(); i++) {
        if (row_list_view == 0)
            list.append(list0[i]);
        else if (row_list_view == 1)
            list.append(list1[i]);
        else if (row_list_view == 2)
            list.append(list2[i]);
        else if (row_list_view == 3)
            list.append(list3[i]);
        else if (row_list_view == 4)
            list.append(list4[i]);
    }

    standard_item_model = new QStandardItemModel(4, 4, this);
    standard_item_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Sensor"));
    standard_item_model->setHeaderData(1, Qt::Horizontal, QObject::tr("a Value"));
    standard_item_model->setHeaderData(2, Qt::Horizontal, QObject::tr("b Value"));
    standard_item_model->setHeaderData(3, Qt::Horizontal, QObject::tr("c Value"));

    int count = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            QModelIndex index = standard_item_model->index(row,col,QModelIndex());
            standard_item_model->setData(index, list[count]);
            count++;
        }
    }

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 70);
    ui->tableView->setColumnWidth(2, 70);
    ui->tableView->setColumnWidth(3, 70);
    ui->tableView->setModel(standard_item_model);
}

void MainWindow::onLoginDialog(QString password)
{
    if (password == "pass1") {
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_5->setCurrentIndex(1);
        ui->comboBox_3->setEnabled(false);
        ui->comboBox_4->setEnabled(false);

    } else if (password == "pass2") {
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget_6->setCurrentIndex(0);
        ui->pushButton_3->setStyleSheet("border: 1px solid black; color: rgb(94, 94, 94); text-align: left; font: 22px 'Roboto'; "
                                        "padding-left: 65px; background-image: url(:/images/images/parametersOpenImage.png); "
                                        "background-repeat: no-repeat;");

        ui->label_354->setText("X");
        ui->label_356->setText("X");
        ui->label_358->setText("X");
        ui->lineEdit_41->clear();
        ui->lineEdit_42->clear();
        ui->lineEdit_43->clear();
        ui->label_359->setText("Default");

        ui->label_364->setText("X");
        ui->label_366->setText("X");
        ui->label_368->setText("X");
        ui->label_370->setText("X");
        ui->comboBox_12->setCurrentIndex(-1);
        ui->slider->setValue(0);
        ui->slider->setMinimum(0);
        ui->slider->setMaximum(5);
        ui->label_374->setText("0");
        ui->comboBox_13->setCurrentIndex(-1);
        ui->lineEdit_44->clear();
        ui->label_371->setText("Default");

        ui->label_328->setText("X");
        ui->label_330->setText("X");
        ui->label_332->setText("X");
        ui->label_334->setText("X");
        ui->comboBox_10->setCurrentIndex(-1);
        ui->lineEdit_35->clear();
        ui->lineEdit_36->clear();
        ui->comboBox_11->setCurrentIndex(-1);
        ui->label_335->setText("Default");

        ui->checkBox_3->setChecked(false);
        ui->checkBox_5->setChecked(false);
        ui->checkBox_4->setChecked(false);
        ui->checkBox_2->setChecked(false);
        ui->checkBox->setChecked(false);
        ui->label_326->setText("Default");

        ui->label_341->setText("X");
        ui->label_343->setText("X");
        ui->label_345->setText("X");
        ui->label_347->setText("X");
        ui->lineEdit_37->clear();
        ui->lineEdit_38->clear();
        ui->lineEdit_39->clear();
        ui->lineEdit_40->clear();
        ui->label_348->setText("Default");

        connect(ui->slider, SIGNAL(valueChanged(int)),
                this, SLOT(onSliderValue()));

    } else if (password == "pass3") {
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget_6->setCurrentIndex(1);
        ui->pushButton_3->setStyleSheet("border: 1px solid black; color: rgb(94, 94, 94); text-align: left; font: 22px 'Roboto'; "
                                        "padding-left: 65px; background-image: url(:/images/images/parametersOpenImage.png); "
                                        "background-repeat: no-repeat;");
        ui->label_313->setText("Default");

    } else if (password == "pass4") {
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget_6->setCurrentIndex(2);
        ui->pushButton_3->setStyleSheet("border: 1px solid black; color: rgb(94, 94, 94); text-align: left; font: 22px 'Roboto'; "
                                        "padding-left: 65px; background-image: url(:/images/images/parametersOpenImage.png); "
                                        "background-repeat: no-repeat;");

    } else if (password == "pass5") {
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget_6->setCurrentIndex(3);
        ui->pushButton_3->setStyleSheet("border: 1px solid black; color: rgb(94, 94, 94); text-align: left; font: 22px 'Roboto'; "
                                        "padding-left: 65px; background-image: url(:/images/images/parametersOpenImage.png); "
                                        "background-repeat: no-repeat;");
    }
}

void MainWindow::onSliderValue()
{
    ui->label_374->setText(QString::number(ui->slider->value()));
}

void MainWindow::onMousePressedFunction1()
{
    MousePressedFunction(ui->label_119, ui->mouseMoveFunction->x_press_value, ui->mouseMoveFunction->y_press_value);
    double value_1 = RandomFunction(-4, 4);
    double value_2 = RandomFunction(-3, 3);
    double value_3 = RandomFunction(-3, 3);
    SchematicsMousePressedFunction(ui->mouseMoveFunction->x_press_value, ui->mouseMoveFunction->y_press_value, value_1, value_2, value_3);
}

void MainWindow::onMouseMovedFunction1()
{
    MouseMovedFunction(ui->label_119, ui->mouseMoveFunction->x_first_move_value, ui->mouseMoveFunction->y_first_move_value, ui->mouseMoveFunction->y_move_value);
}

void MainWindow::onMouseReleasedFunction1()
{
    MouseReleasedFunction(ui->mouseMoveFunction, ui->label_119, static_parameters.value_list_1, static_parameters.value_list_2, static_parameters.value_list_3,
                          static_parameters.meter_array, ui->mouseMoveFunction->y_first_move_value, ui->mouseMoveFunction->y_last_move_value);
}

void MainWindow::onMousePressedFunction2()
{
    MousePressedFunction(ui->label_138, ui->mouseMoveFunction_2->x_press_value, ui->mouseMoveFunction_2->y_press_value);
    double value_1 = RandomFunction(-4, 4);
    double value_2 = RandomFunction(-3, 3);
    double value_3 = RandomFunction(-3, 3);
    SchematicsMousePressedFunction(ui->mouseMoveFunction_2->x_press_value, ui->mouseMoveFunction_2->y_press_value, value_1, value_2, value_3);
}

void MainWindow::onMouseMovedFunction2()
{
    MouseMovedFunction(ui->label_138, ui->mouseMoveFunction_2->x_first_move_value, ui->mouseMoveFunction_2->y_first_move_value, ui->mouseMoveFunction_2->y_move_value);
}

void MainWindow::onMouseReleasedFunction2()
{
    MouseReleasedFunction(ui->mouseMoveFunction_2, ui->label_138, static_parameters.value_list_4, static_parameters.value_list_5, static_parameters.value_list_6,
                          static_parameters.meter_array, ui->mouseMoveFunction_2->y_first_move_value, ui->mouseMoveFunction_2->y_last_move_value);
}

void MainWindow::onMousePressedFunction3()
{
    MousePressedFunction(ui->label_139, ui->mouseMoveFunction_3->x_press_value, ui->mouseMoveFunction_3->y_press_value);
    double value_1 = RandomFunction(-4, 4);
    double value_2 = RandomFunction(-3, 3);
    double value_3 = RandomFunction(-3, 3);
    SchematicsMousePressedFunction(ui->mouseMoveFunction_3->x_press_value, ui->mouseMoveFunction_3->y_press_value, value_1, value_2, value_3);
}

void MainWindow::onMouseMovedFunction3()
{
   MouseMovedFunction(ui->label_139, ui->mouseMoveFunction_3->x_first_move_value, ui->mouseMoveFunction_3->y_first_move_value, ui->mouseMoveFunction_3->y_move_value);
}

void MainWindow::onMouseReleasedFunction3()
{
    MouseReleasedFunction(ui->mouseMoveFunction_3, ui->label_139, static_parameters.value_list_7, static_parameters.value_list_8, static_parameters.value_list_9,
                          static_parameters.meter_array, ui->mouseMoveFunction_3->y_first_move_value, ui->mouseMoveFunction_3->y_last_move_value);
}

void MainWindow::LineChartConfig1()
{
    line_chart_params.limits_series_color_1.setRgb(255, 0, 0);
    line_chart_params.data_series_pen_width_1 = 2;
    line_chart_params.limit_series_pen_width_1 = 1;
    line_chart_params.chart_background_color_1.setRgb(94, 94, 94);
    line_chart_params.chart_font_size_1 = 7;
    line_chart_params.chart_line_color_1.setRgb(146, 146, 146);
    line_chart_params.chart_line_pen_width_1 = 1;
    line_chart_params.chart_values_label_color_1.setRgb(255, 255, 255);

    line_chart_params.line_chart_1 = new QChart();
    line_chart_params.line_chart_1_series_1 = new QLineSeries();
    line_chart_params.line_chart_1_series_2 = new QLineSeries();
    line_chart_params.line_chart_1_series_3 = new QLineSeries();
    line_chart_params.line_chart_1_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_1_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_1_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_2 = new QChart();
    line_chart_params.line_chart_2_series_1 = new QLineSeries();;
    line_chart_params.line_chart_2_series_2 = new QLineSeries();
    line_chart_params.line_chart_2_series_3 = new QLineSeries();
    line_chart_params.line_chart_2_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_2_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_2_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_3 = new QChart();
    line_chart_params.line_chart_3_series_1 = new QLineSeries();
    line_chart_params.line_chart_3_series_2 = new QLineSeries();
    line_chart_params.line_chart_3_series_3 = new QLineSeries();
    line_chart_params.line_chart_3_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_3_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_3_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_4 = new QChart();
    line_chart_params.line_chart_4_series_1 = new QLineSeries();
    line_chart_params.line_chart_4_series_2 = new QLineSeries();
    line_chart_params.line_chart_4_series_3 = new QLineSeries();
    line_chart_params.line_chart_4_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_4_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_4_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_5 = new QChart();
    line_chart_params.line_chart_5_series_1 = new QLineSeries();
    line_chart_params.line_chart_5_series_2 = new QLineSeries();
    line_chart_params.line_chart_5_series_3 = new QLineSeries();
    line_chart_params.line_chart_5_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_5_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_5_color.setRgb(37, 209, 218);

    line_chart_params.line_chart_6 = new QChart();
    line_chart_params.line_chart_6_series_1 = new QLineSeries();
    line_chart_params.line_chart_6_series_2 = new QLineSeries();
    line_chart_params.line_chart_6_series_3 = new QLineSeries();
    line_chart_params.line_chart_6_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_6_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_6_color.setRgb(224, 166, 31);

    line_chart_params.line_chart_7 = new QChart();
    line_chart_params.line_chart_7_series_1 = new QLineSeries();
    line_chart_params.line_chart_7_series_2 = new QLineSeries();
    line_chart_params.line_chart_7_series_3 = new QLineSeries();
    line_chart_params.line_chart_7_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_7_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_7_color.setRgb(255, 128, 128);

    line_chart_params.line_chart_8 = new QChart();
    line_chart_params.line_chart_8_series_1 = new QLineSeries();
    line_chart_params.line_chart_8_series_2 = new QLineSeries();
    line_chart_params.line_chart_8_series_3 = new QLineSeries();
    line_chart_params.line_chart_8_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_8_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_8_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_9 = new QChart();
    line_chart_params.line_chart_9_series_1 = new QLineSeries();
    line_chart_params.line_chart_9_series_2 = new QLineSeries();
    line_chart_params.line_chart_9_series_3 = new QLineSeries();
    line_chart_params.line_chart_9_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_9_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_9_color.setRgb(37, 209, 218);

    line_chart_params.line_chart_10 = new QChart();
    line_chart_params.line_chart_10_series_1 = new QLineSeries();
    line_chart_params.line_chart_10_series_2 = new QLineSeries();
    line_chart_params.line_chart_10_series_3 = new QLineSeries();
    line_chart_params.line_chart_10_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_10_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_10_color.setRgb(224, 166, 31);

    line_chart_params.line_chart_11 = new QChart();
    line_chart_params.line_chart_11_series_1 = new QLineSeries();
    line_chart_params.line_chart_11_series_2 = new QLineSeries();
    line_chart_params.line_chart_11_series_3 = new QLineSeries();
    line_chart_params.line_chart_11_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_11_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_11_color.setRgb(255, 128, 128);

    line_chart_params.line_chart_12 = new QChart();
    line_chart_params.line_chart_12_series_1 = new QLineSeries();
    line_chart_params.line_chart_12_series_2 = new QLineSeries();
    line_chart_params.line_chart_12_series_3 = new QLineSeries();
    line_chart_params.line_chart_12_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_12_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_12_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_13 = new QChart();
    line_chart_params.line_chart_13_series_1 = new QLineSeries();
    line_chart_params.line_chart_13_series_2 = new QLineSeries();
    line_chart_params.line_chart_13_series_3 = new QLineSeries();
    line_chart_params.line_chart_13_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_13_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_13_color.setRgb(37, 209, 218);

    line_chart_params.line_chart_14 = new QChart();
    line_chart_params.line_chart_14_series_1 = new QLineSeries();
    line_chart_params.line_chart_14_series_2 = new QLineSeries();
    line_chart_params.line_chart_14_series_3 = new QLineSeries();
    line_chart_params.line_chart_14_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_14_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_14_color.setRgb(224, 166, 31);

    line_chart_params.line_chart_15 = new QChart();
    line_chart_params.line_chart_15_series_1 = new QLineSeries();
    line_chart_params.line_chart_15_series_2 = new QLineSeries();
    line_chart_params.line_chart_15_series_3 = new QLineSeries();
    line_chart_params.line_chart_15_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_15_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_15_color.setRgb(255, 128, 128);

    LineChartInit1(ui->chartView_13, line_chart_params.line_chart_1, line_chart_params.line_chart_1_series_1, line_chart_params.line_chart_1_series_2,
                   line_chart_params.line_chart_1_series_3, line_chart_params.line_chart_1_value_axis_2, line_chart_params.line_chart_1_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_1_color, line_chart_params.limits_series_color_1, line_chart_params.data_series_pen_width_1,
                   line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1, line_chart_params.chart_font_size_1,
                   line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1, line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_15, line_chart_params.line_chart_2, line_chart_params.line_chart_2_series_1, line_chart_params.line_chart_2_series_2,
                   line_chart_params.line_chart_2_series_3, line_chart_params.line_chart_2_value_axis_2, line_chart_params.line_chart_2_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_2_color, line_chart_params.limits_series_color_1, line_chart_params.data_series_pen_width_1,
                   line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1, line_chart_params.chart_font_size_1,
                   line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1, line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_14, line_chart_params.line_chart_3, line_chart_params.line_chart_3_series_1, line_chart_params.line_chart_3_series_2,
                   line_chart_params.line_chart_3_series_3, line_chart_params.line_chart_3_value_axis_2, line_chart_params.line_chart_3_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_3_color, line_chart_params.limits_series_color_1, line_chart_params.data_series_pen_width_1,
                   line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1, line_chart_params.chart_font_size_1,
                   line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1, line_chart_params.chart_values_label_color_1);

    LineChartInit1(ui->chartView_4, line_chart_params.line_chart_4, line_chart_params.line_chart_4_series_1, line_chart_params.line_chart_4_series_2,
                   line_chart_params.line_chart_4_series_3, line_chart_params.line_chart_4_value_axis_2, line_chart_params.line_chart_4_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_4_color, line_chart_params.limits_series_color_1, line_chart_params.data_series_pen_width_1,
                   line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1, line_chart_params.chart_font_size_1,
                   line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1, line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView, line_chart_params.line_chart_5, line_chart_params.line_chart_5_series_1, line_chart_params.line_chart_5_series_2,
                   line_chart_params.line_chart_5_series_3, line_chart_params.line_chart_5_value_axis_2, line_chart_params.line_chart_5_value_axis_1,
                   static_parameters.value_3, static_parameters.value_4, 0, 1, 0, 1, line_chart_params.line_chart_5_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_2, line_chart_params.line_chart_6, line_chart_params.line_chart_6_series_1, line_chart_params.line_chart_6_series_2,
                   line_chart_params.line_chart_6_series_3, line_chart_params.line_chart_6_value_axis_2, line_chart_params.line_chart_6_value_axis_1,
                   static_parameters.value_5, static_parameters.value_6, 0, 1, 0, 1, line_chart_params.line_chart_6_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_3, line_chart_params.line_chart_7, line_chart_params.line_chart_7_series_1, line_chart_params.line_chart_7_series_2,
                   line_chart_params.line_chart_7_series_3, line_chart_params.line_chart_7_value_axis_2, line_chart_params.line_chart_7_value_axis_1,
                   static_parameters.value_7, static_parameters.value_8, 0, 1, 0, 1, line_chart_params.line_chart_7_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);

    LineChartInit1(ui->chartView_8, line_chart_params.line_chart_8, line_chart_params.line_chart_8_series_1, line_chart_params.line_chart_8_series_2,
                   line_chart_params.line_chart_8_series_3, line_chart_params.line_chart_8_value_axis_2, line_chart_params.line_chart_8_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_8_color, line_chart_params.limits_series_color_1, line_chart_params.data_series_pen_width_1,
                   line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1, line_chart_params.chart_font_size_1,
                   line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1, line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_5, line_chart_params.line_chart_9, line_chart_params.line_chart_9_series_1, line_chart_params.line_chart_9_series_2,
                   line_chart_params.line_chart_9_series_3, line_chart_params.line_chart_9_value_axis_2, line_chart_params.line_chart_9_value_axis_1,
                   static_parameters.value_3, static_parameters.value_4, 0, 1, 0, 1, line_chart_params.line_chart_9_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_6, line_chart_params.line_chart_10, line_chart_params.line_chart_10_series_1, line_chart_params.line_chart_10_series_2,
                   line_chart_params.line_chart_10_series_3, line_chart_params.line_chart_10_value_axis_2, line_chart_params.line_chart_10_value_axis_1,
                   static_parameters.value_5, static_parameters.value_6, 0, 1, 0, 1, line_chart_params.line_chart_10_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_7, line_chart_params.line_chart_11, line_chart_params.line_chart_11_series_1, line_chart_params.line_chart_11_series_2,
                   line_chart_params.line_chart_11_series_3, line_chart_params.line_chart_11_value_axis_2, line_chart_params.line_chart_11_value_axis_1,
                   static_parameters.value_7, static_parameters.value_8, 0, 1, 0, 1, line_chart_params.line_chart_11_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);

    LineChartInit1(ui->chartView_12, line_chart_params.line_chart_12, line_chart_params.line_chart_12_series_1, line_chart_params.line_chart_12_series_2,
                   line_chart_params.line_chart_12_series_3, line_chart_params.line_chart_12_value_axis_2, line_chart_params.line_chart_12_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_12_color, line_chart_params.limits_series_color_1, line_chart_params.data_series_pen_width_1,
                   line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1, line_chart_params.chart_font_size_1,
                   line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1, line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_9, line_chart_params.line_chart_13, line_chart_params.line_chart_13_series_1, line_chart_params.line_chart_13_series_2,
                   line_chart_params.line_chart_13_series_3, line_chart_params.line_chart_13_value_axis_2, line_chart_params.line_chart_13_value_axis_1,
                   static_parameters.value_3, static_parameters.value_4, 0, 1, 0, 1, line_chart_params.line_chart_13_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_10, line_chart_params.line_chart_14, line_chart_params.line_chart_14_series_1, line_chart_params.line_chart_14_series_2,
                   line_chart_params.line_chart_14_series_3, line_chart_params.line_chart_14_value_axis_2, line_chart_params.line_chart_14_value_axis_1,
                   static_parameters.value_5, static_parameters.value_6, 0, 1, 0, 1, line_chart_params.line_chart_14_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
    LineChartInit1(ui->chartView_11, line_chart_params.line_chart_15, line_chart_params.line_chart_15_series_1, line_chart_params.line_chart_15_series_2,
                   line_chart_params.line_chart_15_series_3, line_chart_params.line_chart_15_value_axis_2, line_chart_params.line_chart_15_value_axis_1,
                   static_parameters.value_7, static_parameters.value_8, 0, 1, 0, 1, line_chart_params.line_chart_15_color, line_chart_params.limits_series_color_1,
                   line_chart_params.data_series_pen_width_1, line_chart_params.limit_series_pen_width_1, line_chart_params.chart_background_color_1,
                   line_chart_params.chart_font_size_1, line_chart_params.chart_line_color_1, line_chart_params.chart_line_pen_width_1,
                   line_chart_params.chart_values_label_color_1);
}

void MainWindow::LineChartConfig2()
{
    line_chart_params.limits_series_color_2.setRgb(255, 0, 0);
    line_chart_params.data_series_pen_width_2 = 2;
    line_chart_params.limit_series_pen_width_2 = 1;
    line_chart_params.chart_background_color_2.setRgb(94, 94, 94);
    line_chart_params.chart_font_size_2 = 7;
    line_chart_params.chart_line_color_2.setRgb(146, 146, 146);
    line_chart_params.chart_line_pen_width_2 = 1;
    line_chart_params.chart_values_label_color_2.setRgb(255, 255, 255);

    line_chart_params.line_chart_16 = new QChart();
    line_chart_params.line_chart_16_series_1 = new QLineSeries();
    line_chart_params.line_chart_16_series_2 = new QLineSeries();
    line_chart_params.line_chart_16_series_3 = new QLineSeries();
    line_chart_params.line_chart_16_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_16_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_16_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_17 = new QChart();
    line_chart_params.line_chart_17_series_1 = new QLineSeries();;
    line_chart_params.line_chart_17_series_2 = new QLineSeries();
    line_chart_params.line_chart_17_series_3 = new QLineSeries();
    line_chart_params.line_chart_17_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_17_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_17_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_18 = new QChart();
    line_chart_params.line_chart_18_series_1 = new QLineSeries();
    line_chart_params.line_chart_18_series_2 = new QLineSeries();
    line_chart_params.line_chart_18_series_3 = new QLineSeries();
    line_chart_params.line_chart_18_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_18_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_18_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_19 = new QChart();
    line_chart_params.line_chart_19_series_1 = new QLineSeries();
    line_chart_params.line_chart_19_series_2 = new QLineSeries();
    line_chart_params.line_chart_19_series_3 = new QLineSeries();
    line_chart_params.line_chart_19_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_19_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_19_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_20 = new QChart();
    line_chart_params.line_chart_20_series_1 = new QLineSeries();
    line_chart_params.line_chart_20_series_2 = new QLineSeries();
    line_chart_params.line_chart_20_series_3 = new QLineSeries();
    line_chart_params.line_chart_20_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_20_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_20_color.setRgb(37, 209, 218);

    line_chart_params.line_chart_21 = new QChart();
    line_chart_params.line_chart_21_series_1 = new QLineSeries();
    line_chart_params.line_chart_21_series_2 = new QLineSeries();
    line_chart_params.line_chart_21_series_3 = new QLineSeries();
    line_chart_params.line_chart_21_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_21_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_21_color.setRgb(224, 166, 31);

    line_chart_params.line_chart_22 = new QChart();
    line_chart_params.line_chart_22_series_1 = new QLineSeries();
    line_chart_params.line_chart_22_series_2 = new QLineSeries();
    line_chart_params.line_chart_22_series_3 = new QLineSeries();
    line_chart_params.line_chart_22_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_22_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_22_color.setRgb(255, 128, 128);

    line_chart_params.line_chart_23 = new QChart();
    line_chart_params.line_chart_23_series_1 = new QLineSeries();
    line_chart_params.line_chart_23_series_2 = new QLineSeries();
    line_chart_params.line_chart_23_series_3 = new QLineSeries();
    line_chart_params.line_chart_23_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_23_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_23_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_24 = new QChart();
    line_chart_params.line_chart_24_series_1 = new QLineSeries();
    line_chart_params.line_chart_24_series_2 = new QLineSeries();
    line_chart_params.line_chart_24_series_3 = new QLineSeries();
    line_chart_params.line_chart_24_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_24_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_24_color.setRgb(37, 209, 218);

    line_chart_params.line_chart_25 = new QChart();
    line_chart_params.line_chart_25_series_1 = new QLineSeries();
    line_chart_params.line_chart_25_series_2 = new QLineSeries();
    line_chart_params.line_chart_25_series_3 = new QLineSeries();
    line_chart_params.line_chart_25_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_25_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_25_color.setRgb(224, 166, 31);

    line_chart_params.line_chart_26 = new QChart();
    line_chart_params.line_chart_26_series_1 = new QLineSeries();
    line_chart_params.line_chart_26_series_2 = new QLineSeries();
    line_chart_params.line_chart_26_series_3 = new QLineSeries();
    line_chart_params.line_chart_26_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_26_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_26_color.setRgb(255, 128, 128);

    line_chart_params.line_chart_27 = new QChart();
    line_chart_params.line_chart_27_series_1 = new QLineSeries();
    line_chart_params.line_chart_27_series_2 = new QLineSeries();
    line_chart_params.line_chart_27_series_3 = new QLineSeries();
    line_chart_params.line_chart_27_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_27_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_27_color.setRgb(11, 244, 17);

    line_chart_params.line_chart_28 = new QChart();
    line_chart_params.line_chart_28_series_1 = new QLineSeries();
    line_chart_params.line_chart_28_series_2 = new QLineSeries();
    line_chart_params.line_chart_28_series_3 = new QLineSeries();
    line_chart_params.line_chart_28_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_28_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_28_color.setRgb(37, 209, 218);

    line_chart_params.line_chart_29 = new QChart();
    line_chart_params.line_chart_29_series_1 = new QLineSeries();
    line_chart_params.line_chart_29_series_2 = new QLineSeries();
    line_chart_params.line_chart_29_series_3 = new QLineSeries();
    line_chart_params.line_chart_29_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_29_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_29_color.setRgb(224, 166, 31);

    line_chart_params.line_chart_30 = new QChart();
    line_chart_params.line_chart_30_series_1 = new QLineSeries();
    line_chart_params.line_chart_30_series_2 = new QLineSeries();
    line_chart_params.line_chart_30_series_3 = new QLineSeries();
    line_chart_params.line_chart_30_value_axis_1 = new QValueAxis;
    line_chart_params.line_chart_30_value_axis_2 = new QValueAxis;
    line_chart_params.line_chart_30_color.setRgb(255, 128, 128);

    LineChartInit1(ui->chartView_28, line_chart_params.line_chart_16, line_chart_params.line_chart_16_series_1, line_chart_params.line_chart_16_series_2,
                   line_chart_params.line_chart_16_series_3, line_chart_params.line_chart_16_value_axis_2, line_chart_params.line_chart_16_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_16_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_30, line_chart_params.line_chart_17, line_chart_params.line_chart_17_series_1, line_chart_params.line_chart_17_series_2,
                   line_chart_params.line_chart_17_series_3, line_chart_params.line_chart_17_value_axis_2, line_chart_params.line_chart_17_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_17_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_29, line_chart_params.line_chart_18, line_chart_params.line_chart_18_series_1, line_chart_params.line_chart_18_series_2,
                   line_chart_params.line_chart_18_series_3, line_chart_params.line_chart_18_value_axis_2, line_chart_params.line_chart_18_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_18_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);

    LineChartInit1(ui->chartView_19, line_chart_params.line_chart_19, line_chart_params.line_chart_19_series_1, line_chart_params.line_chart_19_series_2,
                   line_chart_params.line_chart_19_series_3, line_chart_params.line_chart_19_value_axis_2, line_chart_params.line_chart_19_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_19_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_16, line_chart_params.line_chart_20, line_chart_params.line_chart_20_series_1, line_chart_params.line_chart_20_series_2,
                   line_chart_params.line_chart_20_series_3, line_chart_params.line_chart_20_value_axis_2, line_chart_params.line_chart_20_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_20_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_17, line_chart_params.line_chart_21, line_chart_params.line_chart_21_series_1, line_chart_params.line_chart_21_series_2,
                   line_chart_params.line_chart_21_series_3, line_chart_params.line_chart_21_value_axis_2, line_chart_params.line_chart_21_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_21_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_18, line_chart_params.line_chart_22, line_chart_params.line_chart_22_series_1, line_chart_params.line_chart_22_series_2,
                   line_chart_params.line_chart_22_series_3, line_chart_params.line_chart_22_value_axis_2, line_chart_params.line_chart_22_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_22_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);

    LineChartInit1(ui->chartView_23, line_chart_params.line_chart_23, line_chart_params.line_chart_23_series_1, line_chart_params.line_chart_23_series_2,
                   line_chart_params.line_chart_23_series_3, line_chart_params.line_chart_23_value_axis_2, line_chart_params.line_chart_23_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_23_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_20, line_chart_params.line_chart_24, line_chart_params.line_chart_24_series_1, line_chart_params.line_chart_24_series_2,
                   line_chart_params.line_chart_24_series_3, line_chart_params.line_chart_24_value_axis_2, line_chart_params.line_chart_24_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_24_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_21, line_chart_params.line_chart_25, line_chart_params.line_chart_25_series_1, line_chart_params.line_chart_25_series_2,
                   line_chart_params.line_chart_25_series_3, line_chart_params.line_chart_25_value_axis_2, line_chart_params.line_chart_25_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_25_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_22, line_chart_params.line_chart_26, line_chart_params.line_chart_26_series_1, line_chart_params.line_chart_26_series_2,
                   line_chart_params.line_chart_26_series_3, line_chart_params.line_chart_26_value_axis_2, line_chart_params.line_chart_26_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_26_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);

    LineChartInit1(ui->chartView_27, line_chart_params.line_chart_27, line_chart_params.line_chart_27_series_1, line_chart_params.line_chart_27_series_2,
                   line_chart_params.line_chart_27_series_3, line_chart_params.line_chart_27_value_axis_2, line_chart_params.line_chart_27_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_27_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_24, line_chart_params.line_chart_28, line_chart_params.line_chart_28_series_1, line_chart_params.line_chart_28_series_2,
                   line_chart_params.line_chart_28_series_3, line_chart_params.line_chart_28_value_axis_2, line_chart_params.line_chart_28_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_28_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_25, line_chart_params.line_chart_29, line_chart_params.line_chart_29_series_1, line_chart_params.line_chart_29_series_2,
                   line_chart_params.line_chart_29_series_3, line_chart_params.line_chart_29_value_axis_2, line_chart_params.line_chart_29_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_29_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
    LineChartInit1(ui->chartView_26, line_chart_params.line_chart_30, line_chart_params.line_chart_30_series_1, line_chart_params.line_chart_30_series_2,
                   line_chart_params.line_chart_30_series_3, line_chart_params.line_chart_30_value_axis_2, line_chart_params.line_chart_30_value_axis_1,
                   1, 0, 0, 1, 0, 1, line_chart_params.line_chart_30_color, line_chart_params.limits_series_color_2, line_chart_params.data_series_pen_width_2,
                   line_chart_params.limit_series_pen_width_2, line_chart_params.chart_background_color_2, line_chart_params.chart_font_size_2,
                   line_chart_params.chart_line_color_2, line_chart_params.chart_line_pen_width_2, line_chart_params.chart_values_label_color_2);
}

void MainWindow::LineChartInit1(QChartView *tmp_chart_view, QChart *tmp_chart, QLineSeries *tmp_line_series_1, QLineSeries *tmp_line_series_2, QLineSeries *tmp_line_series_3,
                                QValueAxis *tmp_value_axis_1, QValueAxis *tmp_value_axis_2, double value_1, double value_2, double value_3, double value_4, double value_5,
                                double value_6, QColor color_1, QColor color_2, int value_7, int value_8, QColor color_3, int value_9, QColor color_4, int value_10, QColor color_5)
{
    QPen tmp_pen_1(color_1);
    tmp_pen_1.setWidth(value_7);
    tmp_line_series_1->setPen(tmp_pen_1);
    QPen tmp_pen_2(color_2);
    tmp_pen_2.setWidth(value_8);
    tmp_line_series_2->setPen(tmp_pen_2);
    QPen tmp_pen_3(color_2);
    tmp_pen_3.setWidth(value_8);
    tmp_line_series_3->setPen(tmp_pen_3);

    QLinearGradient tmp_linear_gradient_1;
    tmp_linear_gradient_1.setStart(QPointF(0, 0));
    tmp_linear_gradient_1.setFinalStop(QPointF(0, 1));
    tmp_linear_gradient_1.setColorAt(0.0, color_3);
    tmp_linear_gradient_1.setColorAt(1.0, color_3);
    tmp_linear_gradient_1.setCoordinateMode(QGradient::ObjectBoundingMode);
    tmp_chart->setBackgroundBrush(tmp_linear_gradient_1);

    QLinearGradient tmp_linear_gradient_2;
    tmp_linear_gradient_2.setStart(QPointF(0, 1));
    tmp_linear_gradient_2.setFinalStop(QPointF(1, 0));
    tmp_linear_gradient_2.setColorAt(0.0, color_3);
    tmp_linear_gradient_2.setColorAt(1.0, color_3);
    tmp_linear_gradient_2.setCoordinateMode(QGradient::ObjectBoundingMode);
    tmp_chart->setPlotAreaBackgroundBrush(tmp_linear_gradient_2);
    tmp_chart->setPlotAreaBackgroundVisible(true);

    QFont tmp_font;
    tmp_font.setPixelSize(value_9);
    tmp_value_axis_1->setLabelsFont(tmp_font);
    tmp_value_axis_2->setLabelsFont(tmp_font);

    QPen tmp_pen_4(color_4);
    tmp_pen_4.setWidth(value_10);
    tmp_value_axis_1->setLinePen(tmp_pen_4);
    tmp_value_axis_2->setLinePen(tmp_pen_4);

    QBrush tmp_brush(color_5);
    tmp_value_axis_1->setLabelsBrush(tmp_brush);
    tmp_value_axis_2->setLabelsBrush(tmp_brush);

    tmp_value_axis_1->setGridLineVisible(false);
    tmp_value_axis_2->setGridLineVisible(false);

    tmp_line_series_1->append(0, 0);
    tmp_line_series_2->append(0, value_1);
    tmp_line_series_3->append(0, value_2);

    tmp_chart->legend()->hide();
    tmp_chart->addSeries(tmp_line_series_1);
    tmp_chart->addSeries(tmp_line_series_2);
    tmp_chart->addSeries(tmp_line_series_3);
    tmp_chart->createDefaultAxes();
    tmp_chart->setMargins(QMargins(0,0,0,0));

    tmp_value_axis_1->setMin(value_3);
    tmp_value_axis_1->setMax(value_4);
    tmp_value_axis_2->setMin(value_5);
    tmp_value_axis_2->setMax(value_6);

    tmp_chart->setAxisX(tmp_value_axis_1, tmp_line_series_1);
    tmp_chart->setAxisY(tmp_value_axis_2, tmp_line_series_1);
    tmp_chart->setAxisX(tmp_value_axis_1, tmp_line_series_2);
    tmp_chart->setAxisY(tmp_value_axis_2, tmp_line_series_2);
    tmp_chart->setAxisX(tmp_value_axis_1, tmp_line_series_3);
    tmp_chart->setAxisY(tmp_value_axis_2, tmp_line_series_3);

    tmp_chart_view->setChart(tmp_chart);
}

void MainWindow::LineChartInit2(QChartView *tmp_chart_view, QChart *tmp_chart, QLineSeries *line_series_1, QLineSeries *line_series_2, QLineSeries *line_series_3, QLineSeries *line_series_4,
                                QLineSeries *line_series_5, QLineSeries *line_series_6, QLineSeries *line_series_7, QLineSeries *line_series_8, QLineSeries *line_series_9, QValueAxis *x_axis,
                                QValueAxis *y_axis, QColor color_1, QColor color_2, QColor color_3, QColor color_4, QColor color_5, QColor color_6, QColor color_7, QColor color_8, QColor color_9)
{
    QPen pen_1(color_1);
    pen_1.setWidth(2);
    line_series_1->setPen(pen_1);

    QPen pen_2(color_2);
    pen_2.setWidth(2);
    line_series_2->setPen(pen_2);

    QPen pen_3(color_3);
    pen_3.setWidth(2);
    line_series_3->setPen(pen_3);

    QPen pen_4(color_4);
    pen_4.setWidth(2);
    line_series_4->setPen(pen_4);

    QPen pen_5(color_5);
    pen_5.setWidth(2);
    line_series_5->setPen(pen_5);

    QPen pen_6(color_6);
    pen_6.setWidth(2);
    line_series_6->setPen(pen_6);

    QPen pen_7(color_7);
    pen_7.setWidth(2);
    line_series_7->setPen(pen_7);

    QPen pen_8(color_8);
    pen_8.setWidth(2);
    line_series_8->setPen(pen_8);

    QPen pen_9(color_9);
    pen_9.setWidth(2);
    line_series_9->setPen(pen_9);

    tmp_chart->legend()->hide();
    tmp_chart->addSeries(line_series_1);
    tmp_chart->addSeries(line_series_2);
    tmp_chart->addSeries(line_series_3);
    tmp_chart->addSeries(line_series_4);
    tmp_chart->addSeries(line_series_5);
    tmp_chart->addSeries(line_series_6);
    tmp_chart->addSeries(line_series_7);
    tmp_chart->addSeries(line_series_8);
    tmp_chart->addSeries(line_series_9);
    tmp_chart->createDefaultAxes();

    tmp_chart->setAxisX(x_axis, line_series_1);
    tmp_chart->setAxisX(x_axis, line_series_2);
    tmp_chart->setAxisX(x_axis, line_series_3);
    tmp_chart->setAxisX(x_axis, line_series_4);
    tmp_chart->setAxisX(x_axis, line_series_5);
    tmp_chart->setAxisX(x_axis, line_series_6);
    tmp_chart->setAxisX(x_axis, line_series_7);
    tmp_chart->setAxisX(x_axis, line_series_8);
    tmp_chart->setAxisX(x_axis, line_series_9);

    tmp_chart->setAxisY(y_axis, line_series_1);
    tmp_chart->setAxisY(y_axis, line_series_2);
    tmp_chart->setAxisY(y_axis, line_series_3);
    tmp_chart->setAxisY(y_axis, line_series_4);
    tmp_chart->setAxisY(y_axis, line_series_5);
    tmp_chart->setAxisY(y_axis, line_series_6);
    tmp_chart->setAxisY(y_axis, line_series_7);
    tmp_chart->setAxisY(y_axis, line_series_8);
    tmp_chart->setAxisY(y_axis, line_series_9);

    tmp_chart_view->setChart(tmp_chart);
}

void MainWindow::LineChartInit3(QChartView *tmp_chart_view, QChart *tmp_chart, QLineSeries *line_series, QValueAxis *x_value_axis, QValueAxis *y_value_axis, QColor color)
{
    QPen tmp_pen(color);
    tmp_pen.setWidth(2);
    line_series->setPen(tmp_pen);
    tmp_chart->legend()->hide();
    tmp_chart->addSeries(line_series);
    tmp_chart->createDefaultAxes();

    QFont labelsFont;
    labelsFont.setPixelSize(8);
    x_value_axis->setLabelsFont(labelsFont);
    y_value_axis->setLabelsFont(labelsFont);
    tmp_chart->setAxisX(x_value_axis, line_series);
    tmp_chart->setAxisY(y_value_axis, line_series);

    tmp_chart_view->setChart(tmp_chart);
}

void MainWindow::ClearLineCharts1()
{
    line_chart_params.x_axis_value_1 = 0;

    line_chart_params.line_chart_1_series_1->clear();
    line_chart_params.line_chart_1_series_2->clear();
    line_chart_params.line_chart_1_series_3->clear();
    line_chart_params.line_chart_1_series_1->append(0, 0);
    line_chart_params.line_chart_1_series_2->append(0, 1);
    line_chart_params.line_chart_1_series_3->append(0, 0);

    line_chart_params.line_chart_2_series_1->clear();
    line_chart_params.line_chart_2_series_2->clear();
    line_chart_params.line_chart_2_series_3->clear();
    line_chart_params.line_chart_2_series_1->append(0, 0);
    line_chart_params.line_chart_2_series_2->append(0, 1);
    line_chart_params.line_chart_2_series_3->append(0, 0);

    line_chart_params.line_chart_3_series_1->clear();
    line_chart_params.line_chart_3_series_2->clear();
    line_chart_params.line_chart_3_series_3->clear();
    line_chart_params.line_chart_3_series_1->append(0, 0);
    line_chart_params.line_chart_3_series_2->append(0, 1);
    line_chart_params.line_chart_3_series_3->append(0, 0);

    line_chart_params.line_chart_4_series_1->clear();
    line_chart_params.line_chart_4_series_2->clear();
    line_chart_params.line_chart_4_series_3->clear();
    line_chart_params.line_chart_4_series_1->append(0, 0);
    line_chart_params.line_chart_4_series_2->append(0, 1);
    line_chart_params.line_chart_4_series_3->append(0, 0);

    line_chart_params.line_chart_5_series_1->clear();
    line_chart_params.line_chart_5_series_2->clear();
    line_chart_params.line_chart_5_series_3->clear();
    line_chart_params.line_chart_5_series_1->append(0, 0);
    line_chart_params.line_chart_5_series_2->append(0, static_parameters.value_3);
    line_chart_params.line_chart_5_series_3->append(0, static_parameters.value_4);

    line_chart_params.line_chart_6_series_1->clear();
    line_chart_params.line_chart_6_series_2->clear();
    line_chart_params.line_chart_6_series_3->clear();
    line_chart_params.line_chart_6_series_1->append(0, 0);
    line_chart_params.line_chart_6_series_2->append(0, static_parameters.value_5);
    line_chart_params.line_chart_6_series_3->append(0, static_parameters.value_6);

    line_chart_params.line_chart_7_series_1->clear();
    line_chart_params.line_chart_7_series_2->clear();
    line_chart_params.line_chart_7_series_3->clear();
    line_chart_params.line_chart_7_series_1->append(0, 0);
    line_chart_params.line_chart_7_series_2->append(0, static_parameters.value_7);
    line_chart_params.line_chart_7_series_3->append(0, static_parameters.value_8);

    line_chart_params.line_chart_8_series_1->clear();
    line_chart_params.line_chart_8_series_2->clear();
    line_chart_params.line_chart_8_series_3->clear();
    line_chart_params.line_chart_8_series_1->append(0, 0);
    line_chart_params.line_chart_8_series_2->append(0, 1);
    line_chart_params.line_chart_8_series_3->append(0, 0);

    line_chart_params.line_chart_9_series_1->clear();
    line_chart_params.line_chart_9_series_2->clear();
    line_chart_params.line_chart_9_series_3->clear();
    line_chart_params.line_chart_9_series_1->append(0, 0);
    line_chart_params.line_chart_9_series_2->append(0, static_parameters.value_3);
    line_chart_params.line_chart_9_series_3->append(0, static_parameters.value_4);

    line_chart_params.line_chart_10_series_1->clear();
    line_chart_params.line_chart_10_series_2->clear();
    line_chart_params.line_chart_10_series_3->clear();
    line_chart_params.line_chart_10_series_1->append(0, 0);
    line_chart_params.line_chart_10_series_2->append(0, static_parameters.value_5);
    line_chart_params.line_chart_10_series_3->append(0, static_parameters.value_6);

    line_chart_params.line_chart_11_series_1->clear();
    line_chart_params.line_chart_11_series_2->clear();
    line_chart_params.line_chart_11_series_3->clear();
    line_chart_params.line_chart_11_series_1->append(0, 0);
    line_chart_params.line_chart_11_series_2->append(0, static_parameters.value_7);
    line_chart_params.line_chart_11_series_3->append(0, static_parameters.value_8);

    line_chart_params.line_chart_12_series_1->clear();
    line_chart_params.line_chart_12_series_2->clear();
    line_chart_params.line_chart_12_series_3->clear();
    line_chart_params.line_chart_12_series_1->append(0, 0);
    line_chart_params.line_chart_12_series_2->append(0, 1);
    line_chart_params.line_chart_12_series_3->append(0, 0);

    line_chart_params.line_chart_13_series_1->clear();
    line_chart_params.line_chart_13_series_2->clear();
    line_chart_params.line_chart_13_series_3->clear();
    line_chart_params.line_chart_13_series_1->append(0, 0);
    line_chart_params.line_chart_13_series_2->append(0, static_parameters.value_3);
    line_chart_params.line_chart_13_series_3->append(0, static_parameters.value_4);

    line_chart_params.line_chart_14_series_1->clear();
    line_chart_params.line_chart_14_series_2->clear();
    line_chart_params.line_chart_14_series_3->clear();
    line_chart_params.line_chart_14_series_1->append(0, 0);
    line_chart_params.line_chart_14_series_2->append(0, static_parameters.value_5);
    line_chart_params.line_chart_14_series_3->append(0, static_parameters.value_6);

    line_chart_params.line_chart_15_series_1->clear();
    line_chart_params.line_chart_15_series_2->clear();
    line_chart_params.line_chart_15_series_3->clear();
    line_chart_params.line_chart_15_series_1->append(0, 0);
    line_chart_params.line_chart_15_series_2->append(0, static_parameters.value_7);
    line_chart_params.line_chart_15_series_3->append(0, static_parameters.value_8);
}

void MainWindow::ClearLineCharts2()
{
    line_chart_params.x_axis_value_2 = 0;

    line_chart_params.line_chart_16_series_1->clear();
    line_chart_params.line_chart_16_series_2->clear();
    line_chart_params.line_chart_16_series_3->clear();
    line_chart_params.line_chart_16_series_1->append(0, 0);
    line_chart_params.line_chart_16_series_2->append(0, 1);
    line_chart_params.line_chart_16_series_3->append(0, 0);

    line_chart_params.line_chart_17_series_1->clear();
    line_chart_params.line_chart_17_series_2->clear();
    line_chart_params.line_chart_17_series_3->clear();
    line_chart_params.line_chart_17_series_1->append(0, 0);
    line_chart_params.line_chart_17_series_2->append(0, 1);
    line_chart_params.line_chart_17_series_3->append(0, 0);

    line_chart_params.line_chart_18_series_1->clear();
    line_chart_params.line_chart_18_series_2->clear();
    line_chart_params.line_chart_18_series_3->clear();
    line_chart_params.line_chart_18_series_1->append(0, 0);
    line_chart_params.line_chart_18_series_2->append(0, 1);
    line_chart_params.line_chart_18_series_3->append(0, 0);

    line_chart_params.line_chart_19_series_1->clear();
    line_chart_params.line_chart_19_series_2->clear();
    line_chart_params.line_chart_19_series_3->clear();
    line_chart_params.line_chart_19_series_1->append(0, 0);
    line_chart_params.line_chart_19_series_2->append(0, 1);
    line_chart_params.line_chart_19_series_3->append(0, 0);

    line_chart_params.line_chart_20_series_1->clear();
    line_chart_params.line_chart_20_series_2->clear();
    line_chart_params.line_chart_20_series_3->clear();
    line_chart_params.line_chart_20_series_1->append(0, 0);
    line_chart_params.line_chart_20_series_2->append(0, 1);
    line_chart_params.line_chart_20_series_3->append(0, 0);

    line_chart_params.line_chart_21_series_1->clear();
    line_chart_params.line_chart_21_series_2->clear();
    line_chart_params.line_chart_21_series_3->clear();
    line_chart_params.line_chart_21_series_1->append(0, 0);
    line_chart_params.line_chart_21_series_2->append(0, 1);
    line_chart_params.line_chart_21_series_3->append(0, 0);

    line_chart_params.line_chart_22_series_1->clear();
    line_chart_params.line_chart_22_series_2->clear();
    line_chart_params.line_chart_22_series_3->clear();
    line_chart_params.line_chart_22_series_1->append(0, 0);
    line_chart_params.line_chart_22_series_2->append(0, 1);
    line_chart_params.line_chart_22_series_3->append(0, 0);

    line_chart_params.line_chart_23_series_1->clear();
    line_chart_params.line_chart_23_series_2->clear();
    line_chart_params.line_chart_23_series_3->clear();
    line_chart_params.line_chart_23_series_1->append(0, 0);
    line_chart_params.line_chart_23_series_2->append(0, 1);
    line_chart_params.line_chart_23_series_3->append(0, 0);

    line_chart_params.line_chart_24_series_1->clear();
    line_chart_params.line_chart_24_series_2->clear();
    line_chart_params.line_chart_24_series_3->clear();
    line_chart_params.line_chart_24_series_1->append(0, 0);
    line_chart_params.line_chart_24_series_2->append(0, 1);
    line_chart_params.line_chart_24_series_3->append(0, 0);

    line_chart_params.line_chart_25_series_1->clear();
    line_chart_params.line_chart_25_series_2->clear();
    line_chart_params.line_chart_25_series_3->clear();
    line_chart_params.line_chart_25_series_1->append(0, 0);
    line_chart_params.line_chart_25_series_2->append(0, 1);
    line_chart_params.line_chart_25_series_3->append(0, 0);

    line_chart_params.line_chart_26_series_1->clear();
    line_chart_params.line_chart_26_series_2->clear();
    line_chart_params.line_chart_26_series_3->clear();
    line_chart_params.line_chart_26_series_1->append(0, 0);
    line_chart_params.line_chart_26_series_2->append(0, 1);
    line_chart_params.line_chart_26_series_3->append(0, 0);

    line_chart_params.line_chart_27_series_1->clear();
    line_chart_params.line_chart_27_series_2->clear();
    line_chart_params.line_chart_27_series_3->clear();
    line_chart_params.line_chart_27_series_1->append(0, 0);
    line_chart_params.line_chart_27_series_2->append(0, 1);
    line_chart_params.line_chart_27_series_3->append(0, 0);

    line_chart_params.line_chart_28_series_1->clear();
    line_chart_params.line_chart_28_series_2->clear();
    line_chart_params.line_chart_28_series_3->clear();
    line_chart_params.line_chart_28_series_1->append(0, 0);
    line_chart_params.line_chart_28_series_2->append(0, 1);
    line_chart_params.line_chart_28_series_3->append(0, 0);

    line_chart_params.line_chart_29_series_1->clear();
    line_chart_params.line_chart_29_series_2->clear();
    line_chart_params.line_chart_29_series_3->clear();
    line_chart_params.line_chart_29_series_1->append(0, 0);
    line_chart_params.line_chart_29_series_2->append(0, 1);
    line_chart_params.line_chart_29_series_3->append(0, 0);

    line_chart_params.line_chart_30_series_1->clear();
    line_chart_params.line_chart_30_series_2->clear();
    line_chart_params.line_chart_30_series_3->clear();
    line_chart_params.line_chart_30_series_1->append(0, 0);
    line_chart_params.line_chart_30_series_2->append(0, 1);
    line_chart_params.line_chart_30_series_3->append(0, 0);
}

void MainWindow::DrawShape1(QList<int> array, int x, int width, int height, int array_length)
{
    for (int i = 0; i < array_length; i++) {
        if (array[i] == 0) {
            pen.setColor(QColor(94, 94, 94));
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(118, 118, 118)));
            painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 1) {
            pen.setColor(QColor(118, 118, 118));
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(118, 118, 118)));
            painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 2) {
            pen.setColor(QColor(194, 194, 194));
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(194, 194, 194)));
            painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 3) {
            pen.setColor(QColor(52, 154, 211));
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(52, 152, 211)));
            painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 4) {
            pen.setColor(QColor(150, 117, 0));
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(150, 117, 0)));
            painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 5) {
            pen.setColor(QColor(181, 0, 0));
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(181, 0, 0)));
            painter->drawRect(QRect(x, i * height, width, height));
        }
    }

    graphics_scene->addPixmap(*pixmap);
    ui->graphicsView->setScene(graphics_scene);
}

void MainWindow::DrawShape2(QGraphicsView *tmp_graph_view, QGraphicsScene *tmp_graph_scene, QPixmap *tmp_pixmap, QPainter *tmp_painter,
                            QPen tmp_pen, QList<int> array, int x, int width, int height, int array_length)
{
    for (int i = 0; i < array_length; i++) {
        if (array[i] == 0) {
            tmp_pen.setColor(QColor(94, 94, 94));
            tmp_pen.setWidth(1);
            tmp_painter->setPen(tmp_pen);
            tmp_painter->setBrush(QBrush(QColor(118, 118, 118)));
            tmp_painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 1) {
            tmp_pen.setColor(QColor(118, 118, 118));
            tmp_pen.setWidth(1);
            tmp_painter->setPen(tmp_pen);
            tmp_painter->setBrush(QBrush(QColor(118, 118, 118)));
            tmp_painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 2) {
            tmp_pen.setColor(QColor(194, 194, 194));
            tmp_pen.setWidth(1);
            tmp_painter->setPen(tmp_pen);
            tmp_painter->setBrush(QBrush(QColor(194, 194, 194)));
            tmp_painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 3) {
            tmp_pen.setColor(QColor(52, 154, 211));
            tmp_pen.setWidth(1);
            tmp_painter->setPen(tmp_pen);
            tmp_painter->setBrush(QBrush(QColor(52, 152, 211)));
            tmp_painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 4) {
            tmp_pen.setColor(QColor(150, 117, 0));
            tmp_pen.setWidth(1);
            tmp_painter->setPen(tmp_pen);
            tmp_painter->setBrush(QBrush(QColor(150, 117, 0)));
            tmp_painter->drawRect(QRect(x, i * height, width, height));
        } else if(array[i] == 5) {
            tmp_pen.setColor(QColor(181, 0, 0));
            tmp_pen.setWidth(1);
            tmp_painter->setPen(tmp_pen);
            tmp_painter->setBrush(QBrush(QColor(181, 0, 0)));
            tmp_painter->drawRect(QRect(x, i * height, width, height));
        }
    }

    tmp_graph_scene->addPixmap(*tmp_pixmap);
    tmp_graph_view->setScene(tmp_graph_scene);
}

void MainWindow::DrawGraphicsFunction(double zoom_count)
{
    static_parameters.value_list_1.clear();
    static_parameters.value_list_2.clear();
    static_parameters.value_list_3.clear();
    static_parameters.value_list_4.clear();
    static_parameters.value_list_5.clear();
    static_parameters.value_list_6.clear();
    static_parameters.value_list_7.clear();
    static_parameters.value_list_8.clear();
    static_parameters.value_list_9.clear();

    int pixmap_x_axis = 0;
    int add_margin_x_value = 0;
    int sum_x = 0;
    if (zoom_count == 1) {
        pixmap_x_axis = 160;
        add_margin_x_value = 12;
    } else {
        pixmap_x_axis = 138;
        add_margin_x_value = 0;
    }

    if (static_parameters.zoom_state == 0)
        sum_x = 0;
    else if (static_parameters.zoom_state == 1)
        sum_x = 9;

    int pixmap_width = (int)(588 * zoom_count);
    QGraphicsScene *tmp_graph_scene = new QGraphicsScene(this);
    QPixmap *tmp_pixmap = new QPixmap(pixmap_x_axis, pixmap_width);
    tmp_pixmap->fill(QColor(94, 94, 94));
    QPainter *tmp_painter = new QPainter(tmp_pixmap);
    QPen tmp_pen;

    int random_1 = 0;
    int random_2 = 0;
    int random_3 = 0;
    if (static_parameters.button_counter_list.length() == 1) {
        for (int i = 0; i < 30; i++) {
            random_1 = rand() % 5 + 1;
            static_parameters.value_list_1.append(random_1);
            static_parameters.value_list_1.append(random_1);
            random_2 = rand() % 5 + 1;
            static_parameters.value_list_2.append(random_2);
            static_parameters.value_list_2.append(random_2);
            random_3 = rand() % 5 + 1;
            static_parameters.value_list_3.append(random_3);
            static_parameters.value_list_3.append(random_3);
        }

        ui->label_120->setText(static_parameters.record_value_list_1[static_parameters.button_counter_list[0]]);
        DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.value_list_1, 2 + add_margin_x_value,
                   30, (590 / 59) * zoom_count, 59);
        DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.value_list_2, 36 + add_margin_x_value,
                   30, (590 / 59) * zoom_count, 59);
        DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.value_list_3, 70 + add_margin_x_value,
                   30, (590 / 59) * zoom_count, 59);
        DrawText2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.meter_array,
                  102 + add_margin_x_value, 30 * zoom_count, 10, static_parameters.meter_array.length());

        ui->stackedWidget_3->setCurrentIndex(0);
        QGraphicsScene *empty_graph_scene = new QGraphicsScene(this);

        ui->groupBox_26->setStyleSheet("border: 0px;");
        ui->mouseMoveFunction_2->setScene(empty_graph_scene);
        ui->label_136->setText("");
        ui->groupBox_27->setStyleSheet("border: 0px;");
        ui->mouseMoveFunction_3->setScene(empty_graph_scene);
        ui->label_137->setText("");

        static_parameters.chart_or_graphic_state = false;

        ui->label_119->setStyleSheet("background-color: rgb(0, 0, 0); border: 0px;");
        ui->label_119->setGeometry(92 + sum_x, 300, 31, 10);
        ui->label_138->setStyleSheet("background-color: rgb(94, 94, 94); border: 0px;");
        ui->label_138->setGeometry(92 + sum_x, 300, 31, 10);
        ui->label_139->setStyleSheet("background-color: rgb(94, 94, 94); border: 0px;");
        ui->label_139->setGeometry(92 + sum_x, 300, 31, 10);
    } else {
        for (int i = 0; i < 30; i++) {
            static_parameters.value_list_1.append(0);
            static_parameters.value_list_2.append(0);
            static_parameters.value_list_3.append(0);
        }

        ui->label_120->setText(static_parameters.record_value_list_1[static_parameters.button_counter_list[0]]);
        DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.value_list_1, 2 + add_margin_x_value,
                   30, (590 / 20) * zoom_count, 29);
        DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.value_list_2, 36 + add_margin_x_value,
                   30, (590 / 20) * zoom_count, 29);
        DrawShape2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.value_list_3, 70 + add_margin_x_value,
                   30, (590 / 20) * zoom_count, 29);
        DrawText2(ui->mouseMoveFunction, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, static_parameters.meter_array, 102 + add_margin_x_value,
                  30 * zoom_count, 10, static_parameters.meter_array.length());

        ui->stackedWidget_3->setCurrentIndex(0);
        QGraphicsScene *empty_graph_scene = new QGraphicsScene(this);

        ui->groupBox_26->setStyleSheet("border: 0px;");
        ui->mouseMoveFunction_2->setScene(empty_graph_scene);
        ui->label_136->setText("");
        ui->groupBox_27->setStyleSheet("border: 0px;");
        ui->mouseMoveFunction_3->setScene(empty_graph_scene);
        ui->label_137->setText("");

        static_parameters.chart_or_graphic_state = true;

        ui->label_167->setGeometry(10, 98, 34, 4);
        ui->label_168->setGeometry(10, 142, 34, 4);
        ui->label_170->setGeometry(129, 90, 80, 60);
        ui->label_166->setGeometry(10, 118, 34, 8);
        ui->label_169->setGeometry(165, 115, 10, 10);
        ui->label_154->setText("0.00");
        ui->label_155->setText("0.00");
        ui->label_156->setText("0.00");

        ui->label_119->setStyleSheet("background-color: rgb(118, 118, 118); border: 0px;");
        ui->label_119->setGeometry(93 + sum_x, 300, 29, 10);
        ui->label_138->setStyleSheet("background-color: rgb(94, 94, 94); border: 0px;");
        ui->label_138->setGeometry(92 + sum_x, 300, 31, 10);
        ui->label_139->setStyleSheet("background-color: rgb(94, 94, 94); border: 0px;");
        ui->label_139->setGeometry(92 + sum_x, 300, 31, 10);
    }
}

void MainWindow::DrawPoint1(QLineSeries *line_series_1, QLineSeries *line_series_2, QLineSeries *line_series_3, QValueAxis *x_value_axis, QValueAxis *y_value_axis,
                            double value_1, double value_2, double value_3, double value_4, double value_5, double value_6, double value_7, double value_8)
{
    x_value_axis->setMin(value_5);
    x_value_axis->setMax(value_6);
    y_value_axis->setMin(value_7);
    y_value_axis->setMax(value_8);
    line_series_1->append(value_1, value_2);
    line_series_2->append(value_1, value_3);
    line_series_3->append(value_1, value_4);
}

void MainWindow::DrawPoint2(QLineSeries *line_series, QValueAxis *x_value_axis, QValueAxis *y_value_axis, double min_x_value, double max_y_value, double x_value, double y_value)
{
    x_value_axis->setMin(min_x_value);
    x_value_axis->setMax(x_value);
    y_value_axis->setMin(0);
    y_value_axis->setMax(max_y_value);
    line_series->append(x_value, y_value);
}

void MainWindow::DrawPoint3(QLineSeries *line_series, QValueAxis *x_value_axis, QValueAxis *y_value_axis, double max_y_value, double x_value, double y_value)
{
    x_value_axis->setMin(0);
    x_value_axis->setMax(x_value);
    y_value_axis->setMin(0);
    y_value_axis->setMax(max_y_value);
    line_series->append(x_value, y_value);
}

void MainWindow::DrawText1(QList<int> array, int x, int y_limit, int sum, int array_length)
{
    pen.setColor(QColor(194, 194, 194));
    pen.setWidth(1);
    painter->setFont(QFont("Arial", 9));
    painter->setPen(pen);
    for (int i = 0; i < array_length; i++)
        painter->drawText(x, (i * y_limit) + sum, QString::number(array[i]) + "m");

    graphics_scene->addPixmap(*pixmap);
    ui->graphicsView->setScene(graphics_scene);
}

void MainWindow::DrawText2(QGraphicsView *tmp_graph_view, QGraphicsScene *tmp_graph_scene, QPixmap *tmp_pixmap, QPainter *tmp_painter, QPen tmp_pen,
                           QList<int> array, int x, int y_limit, int sum, int array_length)
{
    tmp_pen.setColor(QColor(194, 194, 194));
    tmp_pen.setWidth(1);
    tmp_painter->setFont(QFont("Arial", 8));
    tmp_painter->setPen(tmp_pen);
    for (int i = 0; i < array_length; i++)
        tmp_painter->drawText(x, (i * y_limit) + sum, QString::number(array[i]));

    tmp_graph_scene->addPixmap(*tmp_pixmap);
    tmp_graph_view->setScene(tmp_graph_scene);
}

void MainWindow::MouseReleasedFunction(QGraphicsView *tmp_graph_view, QLabel *label, QList<int> first_array, QList<int> second_array, QList<int> third_array,
                                       QList<int> meter_array, int y_first_value, int y_last_value)
{
    if (static_parameters.released_state == true && static_parameters.moving_state == true) {
        static_parameters.moving_state = false;

        double diff_low = ((y_first_value) - 20) / 10;
        int diff_low_value = (int)(round(diff_low));
        double diff_high = ((y_last_value) - 20) / 10;
        int diff_high_value = (int)(round(diff_high));
        QList<int> tmp_array_1;
        QList<int> tmp_array_2;
        QList<int> tmp_array_3;
        QList<int> tmp_array_4;
        int low_value = 0;
        int high_value = 0;

        if (diff_low_value < diff_high_value) {
            low_value = diff_low_value;
            high_value = diff_high_value;
        } else if (diff_low_value > diff_high_value) {
            low_value = diff_high_value;
            high_value = diff_low_value;
        }

        for (int i = low_value; i < high_value; i++) {
            tmp_array_1.append(first_array[i]);
            tmp_array_2.append(second_array[i]);
            tmp_array_3.append(third_array[i]);
        }

        for (int i = (low_value / 3); i < (high_value / 3); i++)
            tmp_array_4.append(meter_array[i]);

        label->setGeometry(10, 20, 0, 0);
        QGraphicsScene *tmp_graph_scene = new QGraphicsScene(this);
        QPixmap *tmp_pixmap = new QPixmap(160, 588);
        tmp_pixmap->fill(QColor(94, 94, 94));
        QPainter *tmp_painter = new QPainter(tmp_pixmap);
        QPen tmp_pen;
        DrawShape2(tmp_graph_view, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, tmp_array_1, 23, 30, 590 / tmp_array_1.size(), tmp_array_1.size());
        DrawShape2(tmp_graph_view, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, tmp_array_2, 57, 30, 590 / tmp_array_2.size(), tmp_array_2.size());
        DrawShape2(tmp_graph_view, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, tmp_array_3, 91, 30, 590 / tmp_array_3.size(), tmp_array_3.size());
        DrawText2(tmp_graph_view, tmp_graph_scene, tmp_pixmap, tmp_painter, tmp_pen, tmp_array_4, 123, 590 / tmp_array_4.size(), 10, tmp_array_4.size());

        ui->pushButton_22->setEnabled(true);
        ui->pushButton_22->setStyleSheet("border: 1px solid black; border-radius: 5px; background-image: url(:/images/images/reductStockImage.png); background-repeat: no-repeat;");
        ui->label_116->setText("Reduce");

    } else if (static_parameters.released_state == false) {
        static_parameters.moving_state = true;
    }
}

void MainWindow::MousePressedFunction(QLabel *label, int x_press, int y_press)
{
    static_parameters.released_state = false;
    static_parameters.moving_state = true;

    int y_coord = y_press;
    if (y_coord <= 25)
        y_coord = 20;
    else if (y_coord >= 600)
        y_coord = 600;
    else
        y_coord = y_coord + 15;

    int x_sum_1 = 0;
    int x_sum_2 = 0;
    if (static_parameters.zoom_state == 0) {
        x_sum_1 = 0;
        x_sum_2 = 0;
    } else if (static_parameters.zoom_state == 1) {
        x_sum_1 = 9;
        x_sum_2 = 21;
    }

    if (x_press > (23 - x_sum_2) && x_press < (54 - x_sum_2))
        label->setGeometry(24 + x_sum_1, y_coord, 31, 10);
    else if (x_press > (57 - x_sum_2) && x_press < (88 - x_sum_2))
        label->setGeometry(58 + x_sum_1, y_coord, 31, 10);
    else if (x_press > (91 - x_sum_2) && x_press < (121 - x_sum_2))
        label->setGeometry(92 + x_sum_1, y_coord, 31, 10);
}

void MainWindow::MouseMovedFunction(QLabel *label, int x_first, int y_first, int y_move)
{
    if (static_parameters.moving_state == true) {
        static_parameters.released_state = true;

        int x_sum_1 = 0;
        int x_sum_2 = 0;
        if (static_parameters.zoom_state == 0) {
            x_sum_1 = 0;
            x_sum_2 = 0;
        } else if (static_parameters.zoom_state == 1) {
            x_sum_1 = 9;
            x_sum_2 = 21;
        }

        int y_coord = y_first;
        int y_move_coord = y_move;
        if (y_coord >= 20 && y_coord <= 610 && y_move_coord >= 20 && y_move_coord <= 610) {
            int diff = y_move_coord - y_coord;
            if (diff < 0)
                y_coord = y_coord + diff;

            int height_geo = abs(diff);
            if (x_first > (23 - x_sum_2) && x_first < (54 - x_sum_2))
                label->setGeometry(24 + x_sum_1, y_coord, 31, height_geo);
            else if (x_first > (57 - x_sum_2) && x_first < (88 - x_sum_2))
                label->setGeometry(58 + x_sum_1, y_coord, 31, height_geo);
            else if (x_first > (91 - x_sum_2) && x_first < (121 - x_sum_2))
                label->setGeometry(92 + x_sum_1, y_coord, 31, height_geo);
        }
    }
}

void MainWindow::SchematicsMousePressedFunction(int x_value, int y_value, double value_1, double value_2, double value_3)
{
    if (x_value > 23 && x_value < 121 && y_value > 20 && y_value < 610) {
        double value_double_1 = 120 - ((value_1 / 4) * 80);
        int value_int_1 = (int)value_double_1;
        if (value_int_1 < 30)
            value_int_1 = 30;
        else if (value_int_1 > 202)
            value_int_1 = 202;
        ui->label_166->setGeometry(10, value_int_1, 34, 8);

        double value_double_2 = 170 + ((value_2 / 3) * 90);
        int value_int_2 = (int)value_double_2;
        if (value_int_2 < 80)
            value_int_2 = 80;
        else if (value_int_2 > 250)
            value_int_2 = 250;
        double value_double_3 = 120 - ((value_3 / 3) * 90);
        int value_int_3 = (int)value_double_3;
        if (value_int_3 < 30)
            value_int_3 = 30;
        else if (value_int_3 > 200)
            value_int_3 = 200;
        ui->label_169->setGeometry(value_int_2, value_int_3, 10, 10);

        ui->label_154->setText(QString::number(RoundFunction(value_1, 2)));
        ui->label_155->setText(QString::number(RoundFunction(value_2, 2)));
        ui->label_156->setText(QString::number(RoundFunction(value_3, 2)));
    }
}

double MainWindow::RandomFunction(double min, double max)
{
    return min + (max - min) * ((double)rand() / (double)RAND_MAX);
}

double MainWindow::RoundFunction(double number, int pow_factor)
{
    double ret = number * pow(10, pow_factor);
    ret = round(ret);
    ret = ret / pow(10, pow_factor);

    return ret;
}
