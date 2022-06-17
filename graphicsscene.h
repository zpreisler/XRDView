#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include "h5data.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

	private:

		 Datacube *datacube;

	public:

		 QGraphicsPixmapItem *pix;

		 explicit GraphicsScene(QObject *parent = nullptr);
		 explicit GraphicsScene(Datacube *datacube, QObject *parent = nullptr);

	protected:
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

	signals:
		void clicked(int x, int y);

	public slots:
		void newChannel(int channel);

};

#endif // GRAPHICSSCENE_H
