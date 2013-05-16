/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QBoxPlotSeries>
#include <QBoxSet>
#include <QLegend>
#include <QBarCategoryAxis>

#include "boxdatareader.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//![1]

//![2]
    QBoxPlotSeries *series = new QBoxPlotSeries();
    series->setName("Box & Whiskers");
//![2]

    QFile stockData(":stock");
    if (!stockData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    BoxDataReader dataReader(&stockData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            series->append(set);
    }

//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple boxplotchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
//![4]

//![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![6]

//![7]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(600, 400);
    window.show();
//![7]

    return a.exec();
}
