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

    static double fun1(double x, double y) {
        return sin(y + 0.5) - x - 1;
    }

    static double fun2(double x, double y) {
        return y + cos(x - 2);
    }

    static double der1_x(double x, double y) {
        return -1;
    }

    static double der1_y(double x, double y) {
        return cos(y + 0.5);
    }

    static double der2_x(double x, double y) {
        return -sin(x - 2);
    }

    static double der2_y(double x, double y) {
        return 1;
    }

    static void inverse_matrix(double matrix[2][2]) {
        double det, element;
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        element = matrix[1][1];
        matrix[1][1] = matrix[0][0] / det;
        matrix[0][0] = element / det;
        matrix[0][1] = -matrix[0][1] / det;
        matrix[1][0] = -matrix[1][0] / det;
    }
};