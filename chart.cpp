#include "chart.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent,wFlags)
{

}

Chart::Chart(SliceAndDice *s, QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent,wFlags)
{

	Chart::slice = s;

	QLineSeries *line = new QtCharts::QLineSeries();

	drawLine(line,20,20);

	this->addSeries(line);
	this->legend()->hide();
	this->setTitle("XRD spectra");

}

void Chart::drawLine(QLineSeries *line, int x, int y)
{

	float *spectra = slice->get_pixel(x,y);
	for(int i=0; i < static_cast<int>(slice->datacube->dims[2]); i++){
		line->append(i,*(spectra + i));
	}

}

void Chart::clicked(int x,int y)
{

	std::cout << "Chart Clicked x: " << x << " y: " << y << "\n";	

	this->removeAllSeries();

	QLineSeries *line = new QtCharts::QLineSeries();

	drawLine(line,x,y);

	this->addSeries(line);


}
