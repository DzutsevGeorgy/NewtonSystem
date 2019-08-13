//
// Created by dzgeorgy on 12.08.2019.
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    int i{0};
    double x{-0.1}, y{0.5}, matrix[2][2], dx, dy, result[2], norm;
    std::string text;
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
        text += "iteration = ";
        text += std::to_string(i);
        text += "\t x = ";
        text += std::to_string(x);
        text += "\t y = ";
        text += std::to_string(y);
        text += "\t dx = ";
        text += std::to_string(dx);
        text += "\t dy = ";
        text += std::to_string(dy);
        text += "\t norm = ";
        text += std::to_string(norm);
        text += "\n";
        //std::cout << std::setprecision(8);
        //std::cout << "i = " << i << " x = " << x << " y = " << y << " dx = " << dx << " dy = " << dy << " norm = " << norm << std::endl;
    } while (norm >= 0.0001);
    text += "Итоговый результат: \tx = ";
    text += std::to_string(x);
    text += "\t y = ";
    text += std::to_string(y);
    ui->label_4->setText(QString::fromStdString(text));
}

MainWindow::~MainWindow() {
    delete ui;
}