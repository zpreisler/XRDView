#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent) : QChartView(chart, parent)
{

}

ChartView::ChartView(QWidget *parent) : QChartView(parent)
{

}

void ChartView::clicked(int x,int y)
{

	std::cout << "Clicked x: " << x << " y: " << y << "\n";	

}
