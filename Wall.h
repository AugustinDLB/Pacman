#pragma once

class Wall : public QGraphicsRectItem {
  public:
	Wall(int x, int y, int width, int height)
		: QGraphicsRectItem(x*base, y*base, width*base, height*base)
	{
		setPen(QPen(Qt::blue, 2));
	}
};


