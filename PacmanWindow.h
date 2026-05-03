#pragma once

extern int base;
extern const int stepSize; 
enum Direction { Up, Down, Right, Left };
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>
#include "Point.h"
#include "Wall.h"
class Enemy;

class PacmanWindow : public QGraphicsView {
  private:
	QGraphicsPixmapItem* PacmanImg;
	QGraphicsScene* scene;
	QGraphicsTextItem *scoreText;
	QTimer *timer;
	int score;
	int PacX,PacY;
	Enemy* RedEnemy;
	
	void addWall(int x, int y, int width, int height);
	void addPoint(int x, int y);
	void keyPressEvent(QKeyEvent* event);
	void setupScene();
	void checkCollisionwithPoints(const QGraphicsPixmapItem* pacmanItem);
	void setUpWalls();
	int DirRedEnemy(Direction dir);
	void ChoseDirRed();
	
  public:
  	bool checkCollisionwithWalls(const QGraphicsPixmapItem* pacmanItem) const;
	void updateWindow();

	PacmanWindow(QWidget* parent = nullptr);
	~PacmanWindow();
};



class Enemy : public QObject{
  public:
	Enemy(QPixmap EnemyPNG,int x, int y, QGraphicsScene* scene);
	int x;
	int y;
	QGraphicsPixmapItem* EnemyImg;	
};
