#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent) : QChartView(chart, parent)
{

}

ChartView::ChartView(QWidget *parent) : QChartView(parent)
{

}
