#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <iostream>
#include "h5data.h"

class Chart : public QChart
{

	Q_OBJECT

	public:

		Datacube *datacube;
		SliceAndDice *slice;

		void drawLine(QLineSeries*,int,int);

		explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
		explicit Chart(SliceAndDice *slice, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

	public slots:
		void clicked(int x,int y);
};

#endif // CHART_H
