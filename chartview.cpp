#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent) : QChartView(chart, parent)
{

}

ChartView::ChartView(QWidget *parent) : QChartView(parent)
{

    setRenderHint(QPainter::Antialiasing);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setStyleSheet("background-color:white");
    setStyleSheet("border: 1px solid black");
    setContentsMargins(0, 0, 0, 0);

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


