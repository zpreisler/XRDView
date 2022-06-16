#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

class GraphicsView : public QGraphicsView
{

	Q_OBJECT

	public:
		 explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
		 explicit GraphicsView(QWidget *parent = nullptr);
};

#endif // GRAPHICSVIEW_H
