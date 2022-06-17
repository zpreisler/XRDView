#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent) : QChartView(chart, parent)
{

}

ChartView::ChartView(QWidget *parent) : QChartView(parent)
{

}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
	std::cout << "X: " << event->pos().x() << " Y: " << event->pos().y() << "\n";

	QChartView::mouseMoveEvent(event);

}

void ChartView::mousePressEvent(QMouseEvent *event)
{

	QPointF value = this->chart()->mapToValue(event->pos());


	int channel = static_cast<int>(value.x());

	std::cout << "Pressed X: " << value.x() << " Y: " << value.y() << " channel: " << channel << "\n";

	emit clicked(channel);

	QChartView::mousePressEvent(event);

}
