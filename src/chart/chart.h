//
// Created by dzgeorgy on 12.08.2019.
//
#pragma once

#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
class QGestureEvent;

QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart {

public:
    explicit Chart(QGraphicsItem *parent = 0, Qt::WindowFlags windowFlags = nullptr);

    ~Chart();

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);

};