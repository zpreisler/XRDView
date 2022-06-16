#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "h5data.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Data datacube("xrd.h5","data");

	GraphicsScene *scene = new GraphicsScene(this);

	ui->XRDGraphicsView->setScene(scene);

	SliceAndDice *slice = new SliceAndDice(&datacube);

	slice->slicedice(590);
	QGraphicsPixmapItem *pix = scene->addPixmap(slice->pix);

	slice->slicedice(190);
	pix->setPixmap(slice->pix);

	ChartView *chartView = ui->SpectraChartView;

	QtCharts::QChart *chart = new QtCharts::QChart();
	QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

	float *spectra = slice->get_pixel(20,20);
	for(int i=0; i < static_cast<int>(slice->datacube->dims[2]); i++){
		series->append(i,*(spectra + i));
	}

	chart->addSeries(series);
	chart->legend()->hide();
	chart->createDefaultAxes();
	chart->setTitle("XRD spectra");

	chartView->setChart(chart);

	QObject::connect(scene,&GraphicsScene::clicked,
			chartView,&ChartView::clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

