//
// Created by dzgeorgy on 12.08.2019.
//
#pragma once

#include <QMainWindow>
#include <cmath>
#include "../chart/chart.h"
#include "../chartview/chartview.h"
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QTextEdit>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <fstream>
#include <ctime>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void solve();

    void load();

    void save();

    static void app() {
        make_msg_box("Программа для решения системы уравнений методом Ньютона.\nАвтор: Дзуцев Георгий\nГруппа: ИСп-12");
    }

    static void help() {
        make_msg_box("");
    }

    void file() {
        if (is_file_opened) {
            auto created = QString::fromStdString(formatted_time(file_info.st_ctime));
            auto modified = QString::fromStdString(formatted_time(file_info.st_mtime));
            make_msg_box(QString("Файл создан: %1\nФайл изменен: %2\nРазмер файла: %3 байт")
                                 .arg(created, modified,
                                      QString::number(file_info.st_size)));
        } else {
            make_msg_box("Нет информации о файле!");
        }
    }

private:
    Ui::MainWindow *ui;
    bool is_file_opened = false;
    struct stat file_info = {};

    void calculate_result(double x, double y, double eps);

    void make_chart();

    static void make_msg_box(const QString &message) {
        QMessageBox msg_box;
        msg_box.setText(message);
        msg_box.exec();
    }

    static QString build_line(int i, double x, double y, double dx, double dy, double norm) {
        char buf[80];
        int res = snprintf(buf, sizeof(buf), "\t%d\t||\t%f\t||\t%f\t||\t%f\t||\t%f\t||\t%f\t\n", i, x, y, dx, dy, norm);
        return QString(buf);
    }

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

    template<typename It, typename F>
    QString add_table_row(It begin, It end, int columns, F &&format) {
        if (begin == end) return QString();
        QString output = "";
        int n = 0;
        do {
            if (!n) output += "<tr>";
            output += "<td align=\"center\">" + format(*begin) + "</td>";
            if (++n == columns) {
                n = 0;
                output += "</tr>";
            }
            ++begin;
        } while (begin != end);
        return output;
    }

    static void set_html(QTextEdit *edit, const QString &html) {
        QtConcurrent::run([=] {
            auto doc = new QTextDocument;
            doc->setHtml(html);
            doc->moveToThread(edit->thread());
            QObject src;
            QObject::connect(&src, &QObject::destroyed, qApp, [=] {
                doc->setParent(edit);
                edit->setDocument(doc);
            });
        });
    }

    static std::string formatted_time(time_t timestamp) {
        char buf[80];
        tm *tm = std::localtime(&timestamp);
        std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", tm);
        return buf;
    }

};