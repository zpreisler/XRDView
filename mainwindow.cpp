#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "h5data.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Datacube *datacube = new Datacube("xrd.h5","data");

	GraphicsScene *scene = new GraphicsScene(datacube,this);
	ui->XRDGraphicsView->setScene(scene);

	ChartView *chartView = ui->SpectraChartView;

	Chart *chart = new Chart(datacube);
	chartView->setChart(chart);

	QObject::connect(scene,&GraphicsScene::clicked,
			chart,&Chart::newLine);

	QObject::connect(chartView,&ChartView::clicked,
			scene,&GraphicsScene::newChannel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

