#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene{parent}
{

}

GraphicsScene::GraphicsScene(Datacube *datacube, QObject *parent) : QGraphicsScene{parent}
{
	GraphicsScene::datacube = datacube;

	datacube->slicedice(0);
	
	pix = addPixmap(datacube->pix);

}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";

}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "Pressed X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";

	emit clicked(event->scenePos().x(),event->scenePos().y());

}
 
void GraphicsScene::newChannel(int channel)
{

	std::cout << "channel:" << channel << "\n";

	datacube->slicedice(channel);
	pix->setPixmap(datacube->pix);

}
