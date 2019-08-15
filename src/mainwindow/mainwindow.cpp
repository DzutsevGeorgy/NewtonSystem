//
// Created by dzgeorgy on 12.08.2019.
//
#include "mainwindow.h"
#include "ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->solveButton, SIGNAL(clicked()), this, SLOT(solve()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(load()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->app, SIGNAL(triggered()), this, SLOT(app()));
    connect(ui->help, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->file, SIGNAL(triggered()), this, SLOT(file()));
    make_chart();
}

void MainWindow::load() {
    std::ifstream file("result.html");
    if (file.is_open()) {
        is_file_opened = true;
        stat("result.html", &file_info);
        std::string html, line;
        while (std::getline(file, line)) { html.append(line); }
        set_html(ui->textEdit, QString::fromStdString(html));
    } else {
        make_msg_box("Не найден файл \"result.html\"");
    }
}

void MainWindow::save() {
    auto doc = ui->textEdit->document();
    std::ofstream file("result.html");
    if (file.is_open() && !doc->isEmpty()) {
        file << doc->toHtml().toStdString();
        file.close();
        make_msg_box("Решение сохранено в файл \"result.html\"");
    } else {
        make_msg_box("Решение отсутствует!");
    }
}

void MainWindow::solve() {
    bool correct_x, correct_y, correct_eps;
    auto x_in = ui->xInput->text();
    auto y_in = ui->yInput->text();
    auto eps_in = ui->epsInput->text();
    x_in.replace(',', '.');
    y_in.replace(',', '.');
    eps_in.replace(',', '.');
    double x = x_in.toDouble(&correct_x);
    double y = y_in.toDouble(&correct_y);
    double eps = eps_in.toDouble(&correct_eps);
    if (correct_x && correct_y && correct_eps) {
        calculate_result(x, y, eps);
    } else {
        make_msg_box("Данные введены неверно!");
    }
}

void MainWindow::make_chart() {
    auto *line1 = new QSplineSeries();
    auto *line2 = new QSplineSeries();
    line1->setName("sin(y + 0.5) - x = 1");
    line2->setName("y + cos(x - 2) = 0");
    for (int x = -10; x < 10; x += 1) {
        line1->append(x, -cos(x - 2));
        line2->append(sin(x + 0.5) - 1, x);
    }
    auto *chart = new Chart();
    chart->addSeries(line1);
    chart->addSeries(line2);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-1, 1);
    chart->axes(Qt::Horizontal).first()->setRange(-1, 1);
    auto *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(400, 400);
    ui->verticalLayout->addWidget(chartView);
}

void MainWindow::calculate_result(double x, double y, double eps) {
    int i{0};
    double matrix[2][2], dx, dy, result[2], norm;
    QString text;
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
        ++i;
        double table[]{
                static_cast<double>(i), x, y, dx, dy, norm
        };
        int precision = abs(static_cast<int>(log10(eps)));
        text += add_table_row(std::begin(table), std::end(table), 6,
                              [&precision](double arg) { return QString::number(arg, 'f', precision); });
    } while (norm >= eps);
    std::string header_row[]{
            "Итерация", "Значение X", "Значение Y", "Изменение X", "Изменение Y", "Норма"
    };
    text.prepend(add_table_row(std::begin(header_row), std::end(header_row), 6,
                               [](const std::string &arg) { return QString::fromStdString(arg); }))
            .prepend(R"(<table width="100%" border="1">)")
            .append("</table>");
    ui->textEdit->setReadOnly(true);
    set_html(ui->textEdit, text);
}

MainWindow::~MainWindow() {
    delete ui;
}