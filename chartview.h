#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QtCharts>

class ChartView : public QChartView
{
    Q_OBJECT

	public:
		ChartView(QChart* chart, QWidget *parent = nullptr);
		ChartView(QWidget *parent = nullptr);
};

#endif // CHARTVIEW_H
