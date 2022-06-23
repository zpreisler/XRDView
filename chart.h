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

		void drawLine(QLineSeries*,int,int);

		explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
		explicit Chart(Datacube *datacube, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
   private:
      QLineSeries *verticalLine;
      void updateVerticalLine();
	public slots:
		void newLine(int x,int y);
       void addLine(QPoint point, QColor color);
       void removeLine(QColor color);
       void addVerticalLine(qint32 channel);
       void updateAxes();




};

#endif // CHART_H
