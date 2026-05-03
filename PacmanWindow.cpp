#include "PacmanWindow.h"

int Player_height = 10;
int Player_Width = 10;
int screenWidth = 270;
int screenHeight = 500;
int base = 20;
int xBase = 27;
int yBase = 36;
const int stepSize = 10;
int PosXRedEnemy = base * xBase / 2;
int PosYRedEnemy = base * yBase / 2;

PacmanWindow::PacmanWindow(QWidget* parent) : QGraphicsView(parent)
{
	score = 0;
	scene = new QGraphicsScene(this);
	setScene(scene);
	setupScene();
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &PacmanWindow::updateWindow);
	timer->start(100);
}

void PacmanWindow::updateWindow()
{
	scoreText->setPlainText("Score: " + QString::number(score));
	PacmanImg->setPos(PacX, PacY);
	checkCollisionwithPoints(PacmanImg);
	ChoseDirRed();
	RedEnemy->EnemyImg->setPos(RedEnemy->x, RedEnemy->y);
	if(PacmanImg->collidesWithItem(RedEnemy->EnemyImg)){
		abort();
		}
}

PacmanWindow::~PacmanWindow()
{
	delete scene;
	delete timer;
}

void PacmanWindow::setupScene()
{
	// Add Pacman image
	QPixmap PacmanPNG("Pacman.png");
	QPixmap RedEnemyPNG("RedEnemy.png");
	PacmanPNG = PacmanPNG.scaled(base, base);
	PacmanImg = scene->addPixmap(PacmanPNG);
	RedEnemy = new Enemy(RedEnemyPNG, PosXRedEnemy, PosYRedEnemy, scene);
	PacX = base * (xBase / 2);
	PacY = base * 28;
	scene->setBackgroundBrush(Qt::black);

	setUpWalls();

	// Fill with squares
	Point tempPoint(0, 0);
	for (int i = 0; i <= base * xBase; i += base) {
		for (int j = 0; j <= base * yBase; j += base) {
			tempPoint.setPos(i, j);
			if (j != 16 * base and j != 17 * base and j != 18 * base and
				!checkCollisionwithWalls(&tempPoint))
				if ((i < 10 * base or i > 18 * base or j < 10 * base or
					 j > 24 * base))
					addPoint(i, j);
		}

		scoreText = new QGraphicsTextItem("Score ");
		scoreText->setPos(11 * base, 21 * base);
		scoreText->setFont(QFont("Arcade Classic", 20));
		scoreText->setDefaultTextColor(Qt::yellow);
		scene->addItem(scoreText);
	}
}

void PacmanWindow::setUpWalls()
{
	// Border walls
	addWall(0, 0, xBase, 1);
	addWall(0, yBase, xBase, 1);
	addWall(xBase, 0, 1, (yBase + 1));
	addWall(0, 0, 1, yBase);

	// Others walls
	addWall(13, 0, 2, 5);
	// First layer
	addWall(3, 3, 3, 2);
	addWall(8, 3, 3, 2);
	addWall(17, 3, 3, 2);
	addWall(22, 3, 3, 2);
	// Second layer
	addWall(3, 7, 3, 1);
	addWall(22, 7, 3, 1);
	addWall(11, 7, 6, 1);
	addWall(13, 7, 2, 4);
	addWall(8, 7, 1, 9);
	addWall(19, 7, 1, 9);
	addWall(17, 10, 3, 1);
	addWall(8, 10, 3, 1);

	// Side borders
	addWall(0, 10, 6, 1);
	addWall(xBase - 5, 10, 5, 1);
	addWall(5, 10, 1, 5);
	addWall(xBase - 5, 10, 1, 5);
	addWall(0, 15, 6, 1);
	addWall(xBase - 5, 15, 6, 1);
	addWall(0, 19, 6, 1);
	addWall(xBase - 5, 19, 6, 1);
	addWall(5, 19, 1, 6);
	addWall(xBase - 5, 19, 1, 6);
	addWall(0, 24, 6, 1);
	addWall(xBase - 5, 24, 6, 1);

	// Bottom part
	addWall(8, 19, 1, 6);
	addWall(xBase - 8, 19, 1, 6);
	addWall(11, 24, 6, 1);
	addWall(13, 24, 2, 4);

	addWall(3, 27, 2, 1);
	addWall(7, 27, 4, 1);
	addWall(17, 27, 4, 1);
	addWall(23, 27, 2, 1);
	addWall(4, 27, 1, 4);
	addWall(23, 27, 1, 4);
	addWall(1, 30, 1, 1);
	addWall(xBase - 1, 30, 1, 1);

	// Second bottom part

	addWall(10, 30, 8, 1);
	addWall(13, 30, 2, 4);
	addWall(3, 33, 8, 1);
	addWall(xBase - 10, 33, 8, 1);
	addWall(7, 30, 1, 3);
	addWall(xBase - 7, 30, 1, 3);

}


void PacmanWindow::checkCollisionwithPoints(
	const QGraphicsPixmapItem* pacmanItem)
{
	for (QGraphicsItem* item : scene->items()) {
		if (dynamic_cast<Point*>(item)) {
			if (pacmanItem->collidesWithItem(item)) {
				scene->removeItem(item);
				delete item;
				score += 1;
				return;
			}
		}
	}
	return;
}

void PacmanWindow::keyPressEvent(QKeyEvent* event)
{
	int nextX = PacmanImg->x();
	int nextY = PacmanImg->y();

	PacmanImg->setTransformOriginPoint(PacmanImg->boundingRect().center());
	switch (event->key()) {
	case Qt::Key_Left:
		nextX = PacmanImg->x() - stepSize;
		PacmanImg->setRotation(180);
		break;
	case Qt::Key_Right:
		nextX = PacmanImg->x() + stepSize;
		PacmanImg->setRotation(0);
		break;
	case Qt::Key_Up:
		nextY = PacmanImg->y() - stepSize;
		PacmanImg->setRotation(-90);
		break;
	case Qt::Key_Down:
		nextY = PacmanImg->y() + stepSize;
		PacmanImg->setRotation(90);
		break;
	default:
		break;
	}

	QGraphicsPixmapItem tempPacman;
	tempPacman.setPixmap(PacmanImg->pixmap());
	tempPacman.setPos(nextX, nextY);

	if (!checkCollisionwithWalls(&tempPacman)) {
		PacX = nextX;
		PacY = nextY;
	}
}

void PacmanWindow::addWall(int x, int y, int width, int height)
{
	Wall* wall = new Wall(x, y, width, height);
	scene->addItem(wall);
}

void PacmanWindow::addPoint(int x, int y)
{
	Point* point = new Point(x, y);
	scene->addItem(point);
}

bool PacmanWindow::checkCollisionwithWalls(
	const QGraphicsPixmapItem* pacmanItem) const
{
	for (QGraphicsItem* item : scene->items()) {
		if (dynamic_cast<Wall*>(item)) {
			if (pacmanItem->collidesWithItem(item)) {
				return true;
			}
		}
	}
	return false;
}

Enemy::Enemy(QPixmap EnemyPNG, int posx, int posy, QGraphicsScene* scene)
{
	EnemyPNG = EnemyPNG.scaled(base, base);
	EnemyImg = scene->addPixmap(EnemyPNG);
	EnemyImg->setPos(posx, posy);
	x = posx;
	y = posy;
}

void PacmanWindow::ChoseDirRed()
{
	int distX = RedEnemy->x - PacX;
	int distY = RedEnemy->y - PacY;
	Direction dir;
	if (abs(distX) > abs(distY)) {
		dir = distX > 0 ? Left : Right;
	}
	else {
		dir = distY > 0 ? Up : Down;
	}
	if(!DirRedEnemy(dir)){
		if (abs(distX) < abs(distY)) 
			dir = distX > 0 ? Left : Right;
		else 
			dir = distY > 0 ? Up : Down;
	}
	

}

int PacmanWindow::DirRedEnemy(Direction dir)
{
	int nextX = RedEnemy->EnemyImg->x();
	int nextY = RedEnemy->EnemyImg->y();
	RedEnemy->EnemyImg->setTransformOriginPoint(
		RedEnemy->EnemyImg->boundingRect().center());
	switch (dir) {
	case Left:
		nextX = RedEnemy->EnemyImg->x() - stepSize;
		break;
	case Right:
		nextX = RedEnemy->EnemyImg->x() + stepSize;
		break;
	case Up:
		nextY = RedEnemy->EnemyImg->y() - stepSize;
		break;
	case Down:
		nextY = RedEnemy->EnemyImg->y() + stepSize;
		break;
	default:
		break;
	}

	QGraphicsPixmapItem tempPacman;
	tempPacman.setPixmap(RedEnemy->EnemyImg->pixmap());
	tempPacman.setPos(nextX, nextY);

	if (checkCollisionwithWalls(&tempPacman)) {
		return false;
	}
	RedEnemy->x = nextX;
	RedEnemy->y = nextY;
	return true;
}
