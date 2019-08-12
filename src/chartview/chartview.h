//
// Created by dzgeorgy on 12.08.2019.
//
#pragma once

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView {

public:
    explicit ChartView(QChart *chart, QWidget *parent = nullptr);

protected:
    bool viewportEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    bool m_isTouching;

};