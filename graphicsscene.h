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
    private:
     //Scale factor to identify the correspondence between the image point and the real pixel
      qreal scaleFactor=1;
      void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
       void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

	signals:
        void clicked(int x, int y);
        void moving(QPointF point);

	public slots:
		void newChannel(int channel);

};

#endif // GRAPHICSSCENE_H
