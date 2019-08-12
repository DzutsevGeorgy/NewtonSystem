//
// Created by dzgeorgy on 12.08.2019.
//
#pragma once

#include <QMainWindow>
#include <cmath>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    static long double fun1(long double x, long double y) {
        return sin(y + 0.5) - x - 1;
    }

    static long double fun2(long double x, long double y) {
        return y + cos(x - 2);
    }

    static long double der1_x(long double x, long double y) {
        return -1;
    }

    static long double der1_y(long double x, long double y) {
        return cos(y + 0.5);
    }

    static long double der2_x(long double x, long double y) {
        return -sin(x - 2);
    }

    static long double der2_y(long double x, long double y) {
        return 1;
    }

    static void inverse_matrix(long double matrix[2][2]) {
        long double det, element;
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        element = matrix[1][1];
        matrix[1][1] = matrix[0][0] / det;
        matrix[0][0] = element / det;
        matrix[0][1] = -matrix[0][1] / det;
        matrix[1][0] = -matrix[1][0] / det;
    }
};