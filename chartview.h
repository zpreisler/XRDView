#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QtCharts>
#include <iostream>

#include <h5data.h>

class ChartView : public QChartView
{
    Q_OBJECT

	public:
		explicit ChartView(QChart* chart, QWidget *parent);
		explicit ChartView(QWidget *parent);
		explicit ChartView(Datacube *datacube, QWidget *parent);

};

#endif // CHARTVIEW_H
