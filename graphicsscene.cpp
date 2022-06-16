#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{

}
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "X: " << event->pos().x() << " Y: " << event->pos().y() << "\n";
	std::cout << "X: " << event->screenPos().x() << " Y: " << event->screenPos().y() << "\n";
	std::cout << "X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";

}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "Pressed X: " << event->pos().x() << " Y: " << event->pos().y() << "\n";
	std::cout << "Pressed X: " << event->screenPos().x() << " Y: " << event->screenPos().y() << "\n";
	std::cout << "Pressed X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";

	emit clicked(event->scenePos().x(),event->scenePos().y());

}
