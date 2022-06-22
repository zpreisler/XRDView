#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPoint>


#include <iostream>

#include "chart.h"
#include "chartview.h"
#include "graphicsscene.h"

class GraphicsView : public QGraphicsView
{

	Q_OBJECT

	public:
		 explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
		 explicit GraphicsView(QWidget *parent = nullptr);

          void resize();
    private:
          void wheelEvent(QWheelEvent *e);
          void scaleView(qreal scaleFactor);



};

#endif // GRAPHICSVIEW_H
