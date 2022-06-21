#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
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

	protected:
		void mouseMoveEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);

	signals:
		void clicked(int channel);

};

#endif // CHARTVIEW_H
