#pragma once

#define dotSize 10

class Point : public QGraphicsPixmapItem{
	public:
	Point(int x, int y){
		QPixmap pixmap(dotSize,dotSize);
		pixmap.fill(Qt::white);
		setPixmap(pixmap);
		setPos(x-dotSize/2,y-dotSize/2);
	}
};
