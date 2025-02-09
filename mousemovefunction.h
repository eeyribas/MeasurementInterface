#ifndef MOUSEMOVEFUNCTION_H
#define MOUSEMOVEFUNCTION_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QEvent>

class MouseMoveFunction : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MouseMoveFunction(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

    bool left_right_button_state;
    int x_press_value, y_press_value;
    int x_first_move_value, y_first_move_value;
    int x_move_value, y_move_value;
    int x_last_move_value, y_last_move_value;

signals:
    void mousePressedSignal();
    void mouseMovedSignal();
    void mouseReleasedSignal();
    void mouseDoubleClickSignal();
};

#endif // MOUSEMOVEFUNCTION_H
