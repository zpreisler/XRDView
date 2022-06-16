#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QtCharts>
#include <iostream>

class ChartView : public QChartView
{
    Q_OBJECT

	public:
		explicit ChartView(QChart* chart, QWidget *parent = nullptr);
		explicit ChartView(QWidget *parent = nullptr);

	public slots:
		void clicked(int x,int y);
};

#endif // CHARTVIEW_H
