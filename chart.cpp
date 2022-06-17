#include "chart.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent,wFlags)
{

}

Chart::Chart(Datacube *datacube, QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent,wFlags)
{

	Chart::datacube = datacube;
	QLineSeries *line = new QtCharts::QLineSeries();

	drawLine(line,0,0);

	this->addSeries(line);
	this->legend()->hide();
	this->setTitle("XRD spectra");

}

void Chart::drawLine(QLineSeries *line, int x, int y)
{

	float *spectra = datacube->get_pixel(x,y);

	for(int i=0; i < static_cast<int>(datacube->dims[2]); i++){
		line->append(i,*(spectra + i));
	}

}

void Chart::newLine(int x,int y)
{

	this->removeAllSeries();

	QLineSeries *line = new QtCharts::QLineSeries();
	drawLine(line,x,y);

	this->addSeries(line);

}
