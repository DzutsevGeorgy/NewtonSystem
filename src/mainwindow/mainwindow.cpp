//
// Created by dzgeorgy on 12.08.2019.
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    int i{0};
    long double x{-0.1}, y{0.5};
    long double matrix[2][2], dx, dy, result[2], norm;
    do {
        matrix[0][0] = der1_x(x, y);
        matrix[0][1] = der1_y(x, y);
        matrix[1][0] = der2_x(x, y);
        matrix[1][1] = der2_y(x, y);
        inverse_matrix(matrix);
        dx = -matrix[0][0] * fun1(x, y) + -matrix[0][1] * fun2(x, y);
        dy = -matrix[1][0] * fun1(x, y) + -matrix[1][1] * fun2(x, y);
        x += dx;
        y += dy;
        result[0] = fun1(x, y);
        result[1] = fun2(x, y);
        norm = sqrt(result[0] * result[0] + result[1] * result[1]);
        i++;
        std::cout << "i = " << i << " x = " << x << " y = " << y << " dx = " << dx << " dy = " << dy << std::endl;
    } while (norm >= 0.0000000000001);
}

MainWindow::~MainWindow() {
    delete ui;
}