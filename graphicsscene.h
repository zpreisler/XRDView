#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
	public:
		 explicit GraphicsScene(QObject *parent = nullptr);

	protected:
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSSCENE_H
